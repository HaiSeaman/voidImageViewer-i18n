# End-to-end regression test for the borderless caption overlay while panning.
#
# Bug covered
# -----------
# With the default "scroll_window=1" the image pan uses ScrollWindowEx() on the
# whole client area. In borderless mode the caption (file name at the top left,
# min/max/close buttons at the top right) is painted *into that same client
# area*, so every scroll step drags the overlay pixels along with the image and
# leaves a trail of stale copies behind (and offsets the buttons).
#
# How the test detects it
# -----------------------
# The viewer is opened on a solid black image, so the caption strip is the only
# source of bright pixels in the client area. The client bitmap is captured
# before and after a pan drag and the bright pixels below the caption band
# (y >= Y_CAP) are counted:
#   * before the drag : 0 expected (nothing painted below the band)
#   * after  the drag : 0 expected when the overlay is excluded from the scroll
# Any bright pixel below the band after the drag is a stale overlay copy.
# The number of bright pixels *inside* the band is reported too, so a run that
# never drew the overlay at all cannot pass silently.
#
# Usage:
#   powershell -File tests\e2e_overlay_scroll_test.ps1 -ExePath <exe> -ImagePath <bmp>
#   powershell -File tests\e2e_overlay_scroll_test.ps1 -ExePath <exe> -ImagePath <bmp> -Attach
#
# -Attach tests a viewer that is already running (single-instance builds hand the
# file over to an existing window, so the test must not always start its own).
#
# Exit code 0 = PASS, 1 = FAIL.

param(
	[Parameter(Mandatory = $true)][string]$ExePath,
	[Parameter(Mandatory = $true)][string]$ImagePath,
	[string]$OutDir = "",
	[switch]$Attach,
	[int]$WheelNotches = 4,
	[int]$DragSteps = 12,
	[int]$TotalDragX = 240,
	[int]$TotalDragY = 180
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class OverlayNative {
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern void mouse_event(uint flags, uint dx, uint dy, int data, UIntPtr extra);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hwnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hwnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr hwnd, ref POINT pt);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hwnd);
    [DllImport("user32.dll")] public static extern IntPtr GetDC(IntPtr hwnd);
    [DllImport("user32.dll")] public static extern int ReleaseDC(IntPtr hwnd, IntPtr hdc);
    [DllImport("gdi32.dll")] public static extern bool BitBlt(IntPtr dst, int x, int y, int w, int h, IntPtr src, int sx, int sy, uint rop);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

# height of the borderless caption strip (_VIV_CAP_BTN_H in src/viv.c)
$Y_CAP = 28
# how far below the strip stale copies are looked for
$SEARCH_H = 420
# left column / right button column widths that are scanned
$LEFT_W = 700
$RIGHT_W = 140

$MOUSEEVENTF_LEFTDOWN = 0x02
$MOUSEEVENTF_LEFTUP = 0x04
$MOUSEEVENTF_WHEEL = 0x0800
$SRCCOPY = 0x00CC0020

if ([string]::IsNullOrEmpty($OutDir)) {
	$OutDir = Join-Path (Split-Path $PSScriptRoot -Parent) ".workbuddy\build\overlay_test"
}
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$report = New-Object System.Collections.Generic.List[string]
function Say([string]$s) {
	$report.Add($s)
	Write-Output $s
}

function Get-Rect([IntPtr]$hwnd) {
	$r = New-Object OverlayNative+RECT
	[void][OverlayNative]::GetWindowRect($hwnd, [ref]$r)
	return $r
}

function Get-Client([IntPtr]$hwnd) {
	$r = New-Object OverlayNative+RECT
	[void][OverlayNative]::GetClientRect($hwnd, [ref]$r)
	return $r
}

function Capture-Client([IntPtr]$hwnd) {
	$cr = Get-Client $hwnd
	$w = $cr.Right - $cr.Left
	$h = $cr.Bottom - $cr.Top
	$bmp = New-Object System.Drawing.Bitmap($w, $h, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
	$g = [System.Drawing.Graphics]::FromImage($bmp)
	$hdc = $g.GetHdc()
	$src = [OverlayNative]::GetDC($hwnd)
	[void][OverlayNative]::BitBlt($hdc, 0, 0, $w, $h, $src, 0, 0, $SRCCOPY)
	[void][OverlayNative]::ReleaseDC($hwnd, $src)
	$g.ReleaseHdc($hdc)
	$g.Dispose()
	return $bmp
}

# count near-white pixels in the client-area rectangle [x0,x1) x [y0,y1)
function Count-Bright([System.Drawing.Bitmap]$bmp, [int]$x0, [int]$y0, [int]$x1, [int]$y1) {	$x0 = [Math]::Max(0, $x0)
	$y0 = [Math]::Max(0, $y0)
	$x1 = [Math]::Min($bmp.Width, $x1)
	$y1 = [Math]::Min($bmp.Height, $y1)
	if ($x1 -le $x0 -or $y1 -le $y0) { return 0 }

	$rect = New-Object System.Drawing.Rectangle(0, 0, $bmp.Width, $bmp.Height)
	$data = $bmp.LockBits($rect, [System.Drawing.Imaging.ImageLockMode]::ReadOnly, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
	$stride = $data.Stride
	$bytes = New-Object byte[] ($stride * $bmp.Height)
	[System.Runtime.InteropServices.Marshal]::Copy($data.Scan0, $bytes, 0, $bytes.Length)
	$bmp.UnlockBits($data)

	$count = 0
	for ($y = $y0; $y -lt $y1; $y++) {
		$row = $y * $stride
		for ($x = $x0; $x -lt $x1; $x++) {
			$i = $row + $x * 4
			if (($bytes[$i] -ge 180) -and ($bytes[$i + 1] -ge 180) -and ($bytes[$i + 2] -ge 180)) {
				$count++
			}
		}
	}
	return $count
}

# count the red hover/press background of the close button (small region only)
function Count-Red([System.Drawing.Bitmap]$bmp, [int]$x0, [int]$y0, [int]$x1, [int]$y1) {
	$count = 0
	for ($y = $y0; $y -lt $y1; $y++) {
		for ($x = $x0; $x -lt $x1; $x++) {
			if ($x -ge $bmp.Width -or $y -ge $bmp.Height) { continue }
			$c = $bmp.GetPixel($x, $y)
			if (($c.R -ge 170) -and ($c.G -le 90) -and ($c.B -le 90)) { $count++ }
		}
	}
	return $count
}

function Drag([int]$x, [int]$y, [int]$dx, [int]$dy, [int]$steps) {
	[void][OverlayNative]::SetCursorPos($x, $y)
	Start-Sleep -Milliseconds 150
	[OverlayNative]::mouse_event($MOUSEEVENTF_LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 80
	for ($i = 1; $i -le $steps; $i++) {
		[void][OverlayNative]::SetCursorPos(($x + [int]($dx * $i / $steps)), ($y + [int]($dy * $i / $steps)))
		Start-Sleep -Milliseconds 25
	}
	[OverlayNative]::mouse_event($MOUSEEVENTF_LEFTUP, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 500
}

function Wheel-Zoom([int]$x, [int]$y, [int]$notches) {
	[void][OverlayNative]::SetCursorPos($x, $y)
	Start-Sleep -Milliseconds 150
	for ($i = 0; $i -lt $notches; $i++) {
		[OverlayNative]::mouse_event($MOUSEEVENTF_WHEEL, 0, 0, 120, [UIntPtr]::Zero)
		Start-Sleep -Milliseconds 120
	}
	Start-Sleep -Milliseconds 400
}

$exeName = [System.IO.Path]::GetFileNameWithoutExtension($ExePath)
$proc = $null
$hwnd = [IntPtr]::Zero

try {
	Say "== e2e_overlay_scroll_test against: $ExePath"
	Say "   image: $ImagePath"

	if (-not $Attach) {
		# start from factory defaults: the app saves its settings next to the exe
		# on exit, and a leftover left_click_action=5 would turn the pan drag into
		# a 1:1 scroll and invalidate this test. Write the defaults instead of
		# deleting the file - a dying instance can hold the ini open for a moment.
		$defaults = @(
			"[voidImageViewer]",
			"left_click_action=0",
			"mouse_wheel_action=0",
			"scroll_window=1",
			"show_caption=0",
			"show_status=0",
			"show_controls=0",
			"hover_show_ui=0",
			"fit_window_to_image=1",
			"auto_zoom=1",
			"fill_window=1"
		)
		[System.IO.File]::WriteAllLines((Join-Path (Split-Path $ExePath) "voidImageViewer.ini"), $defaults)
	}

	if ($Attach) {
		$deadline = (Get-Date).AddSeconds(10)
		while ((Get-Date) -lt $deadline) {
			$cand = @(Get-Process -Name $exeName -ErrorAction SilentlyContinue | Where-Object { $_.MainWindowHandle -ne 0 })
			if ($cand.Count -gt 0) { $hwnd = $cand[0].MainWindowHandle; break }
			Start-Sleep -Milliseconds 200
		}
		if ($hwnd -eq [IntPtr]::Zero) { throw "no running $exeName window found to attach to" }
	}
	else {
		$proc = Start-Process -FilePath $ExePath -ArgumentList ('"{0}"' -f $ImagePath) -PassThru
		$deadline = (Get-Date).AddSeconds(15)
		while ((Get-Date) -lt $deadline) {
			Start-Sleep -Milliseconds 200
			if ($proc.HasExited) { throw "process exited during startup" }
			$proc.Refresh()
			if ($proc.MainWindowHandle -ne 0) { $hwnd = $proc.MainWindowHandle; break }
		}
		if ($hwnd -eq [IntPtr]::Zero) { throw "no main window appeared" }
	}

	Start-Sleep -Milliseconds 1200
	[void][OverlayNative]::SetForegroundWindow($hwnd)
	Start-Sleep -Milliseconds 400

	$cr = Get-Client $hwnd
	$cw = $cr.Right - $cr.Left
	$ch = $cr.Bottom - $cr.Top
	Say "   client area: ${cw}x${ch}"

	# client-area centre in SCREEN coordinates (mouse_event / SetCursorPos work
	# in screen space, the window is not necessarily at 0,0)
	function Client-ToScreen([IntPtr]$hwnd, [int]$x, [int]$y) {
		$pt = New-Object OverlayNative+POINT
		$pt.X = $x
		$pt.Y = $y
		[void][OverlayNative]::ClientToScreen($hwnd, [ref]$pt)
		return $pt
	}
	$c = Client-ToScreen $hwnd ([int]($cw / 2)) ([int]($ch / 2))
	$cx = $c.X
	$cy = $c.Y

	# zoom in so the image is larger than the viewport (that is what makes the
	# left-drag pan instead of moving the window)
	Wheel-Zoom $cx $cy $WheelNotches

	# baseline: only the caption strip may contain bright pixels
	$bmp0 = Capture-Client $hwnd
	$band0 = Count-Bright $bmp0 0 0 $cw $Y_CAP
	$below0 = Count-Bright $bmp0 0 $Y_CAP $LEFT_W ($Y_CAP + $SEARCH_H)
	$right0 = Count-Bright $bmp0 ([Math]::Max(0, $cw - $RIGHT_W)) $Y_CAP $cw ($Y_CAP + $SEARCH_H)
	$bmp0.Save((Join-Path $OutDir "overlay_1_before_drag.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	Say ("   before drag: band(0..$Y_CAP)=$band0 below-left=$below0 below-right=$right0")

	# pan: the window must not move (that would mean the drag moved the window
	# instead of the image and the test would not exercise the scroll path)
	$wrBefore = Get-Rect $hwnd
	Drag $cx $cy $TotalDragX $TotalDragY $DragSteps
	$wrAfter = Get-Rect $hwnd
	$windowMoved = (($wrBefore.Left -ne $wrAfter.Left) -or ($wrBefore.Top -ne $wrAfter.Top))
	Say ("   window rect: $($wrBefore.Left),$($wrBefore.Top) -> $($wrAfter.Left),$($wrAfter.Top)")

	$bmp1 = Capture-Client $hwnd
	$band1 = Count-Bright $bmp1 0 0 $cw $Y_CAP
	$below1 = Count-Bright $bmp1 0 $Y_CAP $LEFT_W ($Y_CAP + $SEARCH_H)
	$right1 = Count-Bright $bmp1 ([Math]::Max(0, $cw - $RIGHT_W)) $Y_CAP $cw ($Y_CAP + $SEARCH_H)
	$bmp1.Save((Join-Path $OutDir "overlay_2_after_drag.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	Say ("   after drag:  band(0..$Y_CAP)=$band1 below-left=$below1 below-right=$right1")

	# crop of the interesting area, for visual inspection
	$cropW = [Math]::Min($cw, 900)
	$cropH = [Math]::Min($ch, 600)
	$crop = New-Object System.Drawing.Bitmap($cropW, $cropH)
	$gc = [System.Drawing.Graphics]::FromImage($crop)
	$gc.DrawImage($bmp1, (New-Object System.Drawing.Rectangle(0, 0, $cropW, $cropH)), (New-Object System.Drawing.Rectangle(0, 0, $cropW, $cropH)), [System.Drawing.GraphicsUnit]::Pixel)
	$gc.Dispose()
	$crop.Save((Join-Path $OutDir "overlay_3_after_drag_crop.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	$crop.Dispose()
	$bmp0.Dispose()
	$bmp1.Dispose()

	# --- phase 3: the close button hover feedback must still repaint.
	# (_viv_cap_draw_all intersects the button strip with the paint clip; this
	# catches a regression where the buttons would no longer be repainted.)
	$closeW = 46
	[void][OverlayNative]::SetCursorPos($cx, $cy)
	Start-Sleep -Milliseconds 500
	$bmpH0 = Capture-Client $hwnd
	$redRest = Count-Red $bmpH0 ($cw - $closeW) 0 $cw $Y_CAP
	$bmpH0.Save((Join-Path $OutDir "overlay_4_close_rest.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	$b = Client-ToScreen $hwnd ($cw - [int]($closeW / 2)) ([int]($Y_CAP / 2))
	[void][OverlayNative]::SetCursorPos($b.X, $b.Y)
	Start-Sleep -Milliseconds 600
	$bmpH1 = Capture-Client $hwnd
	$redHover = Count-Red $bmpH1 ($cw - $closeW) 0 $cw $Y_CAP
	$bmpH1.Save((Join-Path $OutDir "overlay_5_close_hover.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	[void][OverlayNative]::SetCursorPos($cx, $cy)
	$bmpH0.Dispose()
	$bmpH1.Dispose()
	Say ("   close button: red@rest=$redRest red@hover=$redHover")

	$failures = 0
	if ($windowMoved) {
		Say "FAIL premise - the window moved during the drag (expected a pan); the scroll path was not exercised"
		$failures++
	}
	if ($band1 -eq 0) {
		Say "FAIL control - no caption/buttons were drawn in the top band; the overlay is missing"
		$failures++
	}
	if ($below1 -gt 0) {
		Say "FAIL stale-overlay - $below1 bright pixel(s) below the caption band at the left"
		$failures++
	}
	if ($right1 -gt 0) {
		Say "FAIL stale-overlay - $right1 bright pixel(s) below the caption band on the right"
		$failures++
	}
	if ($redHover -eq 0) {
		Say "FAIL hover-repaint - the close button shows no hover feedback (clip region too tight?)"
		$failures++
	}
	if ($redRest -gt 0) {
		Say "FAIL hover-clear - the close button still shows hover feedback after the cursor left"
		$failures++
	}
	if ($failures -eq 0) {
		Say "PASS - the caption overlay stayed in place while panning"
	}
	else {
		Say ("== RESULT: " + $failures + " check(s) FAILED")
	}
	Say ("   screenshots: " + $OutDir)
	return $failures
}
finally {
	$report | Out-File -FilePath (Join-Path $OutDir "overlay_test_report.txt") -Encoding utf8
	if ($proc -ne $null -and (-not $Attach)) {
		if (-not $proc.HasExited) {
			$proc.CloseMainWindow() | Out-Null
			if (-not $proc.WaitForExit(2000)) { Stop-Process -Id $proc.Id -Force }
		}
	}
}
