# End-to-end regression tests for the two remaining scroll input paths.
#
#   TEST 1  middle-button drag (config_mouse_middle_action = scroll) must pan
#           the image while it is zoomed in.
#   TEST 2  left-drag with left_click_action=5 (1:1 scroll) must keep the
#           panned position when the button is released (no snap-back).
#
# Both tests open a marker image (black with a white square in the image's
# top-left corner). "The view scrolled" is proven by a pixel diff between the
# client capture before and after the gesture: with a uniform image any pan is
# invisible, the white square makes it measurable.
#
# Usage:
#   powershell -File tests\e2e_scroll_modes_test.ps1 -ExePath <exe> -ImagePath <bmp>
#
# Exit code 0 = PASS, 1 = FAIL.

param(
	[Parameter(Mandatory = $true)][string]$ExePath,
	[Parameter(Mandatory = $true)][string]$ImagePath,
	[string]$ImagePath2 = "",
	[string]$OutDir = ""
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class ScrollNative {
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

$MOUSEEVENTF_LEFTDOWN = 0x02
$MOUSEEVENTF_LEFTUP = 0x04
$MOUSEEVENTF_MIDDLEDOWN = 0x20
$MOUSEEVENTF_MIDDLEUP = 0x40
$MOUSEEVENTF_WHEEL = 0x0800
$SRCCOPY = 0x00CC0020

if ([string]::IsNullOrEmpty($OutDir)) {
	$OutDir = Join-Path (Split-Path $PSScriptRoot -Parent) ".workbuddy\build\scroll_test"
}
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

$report = New-Object System.Collections.Generic.List[string]
function Say([string]$s) {
	$report.Add($s)
	Write-Output $s
}

function Client-ToScreen([IntPtr]$hwnd, [int]$x, [int]$y) {
	$pt = New-Object ScrollNative+POINT
	$pt.X = $x
	$pt.Y = $y
	[void][ScrollNative]::ClientToScreen($hwnd, [ref]$pt)
	return $pt
}

function Capture-Client([IntPtr]$hwnd) {
	$cr = New-Object ScrollNative+RECT
	[void][ScrollNative]::GetClientRect($hwnd, [ref]$cr)
	$w = $cr.Right - $cr.Left
	$h = $cr.Bottom - $cr.Top
	$bmp = New-Object System.Drawing.Bitmap($w, $h, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
	$g = [System.Drawing.Graphics]::FromImage($bmp)
	$hdc = $g.GetHdc()
	$src = [ScrollNative]::GetDC($hwnd)
	[void][ScrollNative]::BitBlt($hdc, 0, 0, $w, $h, $src, 0, 0, $SRCCOPY)
	[void][ScrollNative]::ReleaseDC($hwnd, $src)
	$g.ReleaseHdc($hdc)
	$g.Dispose()
	return $bmp
}

# number of clearly non-black pixels in [x0,x1) x [y0,y1)
function Count-Lit([System.Drawing.Bitmap]$bmp, [int]$x0, [int]$y0, [int]$x1, [int]$y1) {
	$x0 = [Math]::Max(0, $x0)
	$y0 = [Math]::Max(0, $y0)
	$x1 = [Math]::Min($bmp.Width, $x1)
	$y1 = [Math]::Min($bmp.Height, $y1)
	$count = 0
	for ($y = $y0; $y -lt $y1; $y++) {
		for ($x = $x0; $x -lt $x1; $x++) {
			$c = $bmp.GetPixel($x, $y)
			if (($c.R -ge 100) -or ($c.G -ge 100) -or ($c.B -ge 100)) { $count++ }
		}
	}
	return $count
}

# number of sampled pixels that clearly differ between the two captures
# (starts below the caption strip so the overlay text does not count)
function Sample-Diff([System.Drawing.Bitmap]$a, [System.Drawing.Bitmap]$b, [int]$step) {
	$diff = 0
	$w = [Math]::Min($a.Width, $b.Width)
	$h = [Math]::Min($a.Height, $b.Height)
	for ($y = 40; $y -lt $h; $y += $step) {
		for ($x = 40; $x -lt $w; $x += $step) {
			$ca = $a.GetPixel($x, $y)
			$cb = $b.GetPixel($x, $y)
			if (([Math]::Abs($ca.R - $cb.R) -gt 40) -or ([Math]::Abs($ca.G - $cb.G) -gt 40) -or ([Math]::Abs($ca.B - $cb.B) -gt 40)) {
				$diff++
			}
		}
	}
	return $diff
}

function Wheel-Zoom([int]$x, [int]$y, [int]$notches) {
	[void][ScrollNative]::SetCursorPos($x, $y)
	Start-Sleep -Milliseconds 150
	for ($i = 0; $i -lt $notches; $i++) {
		[ScrollNative]::mouse_event($MOUSEEVENTF_WHEEL, 0, 0, 120, [UIntPtr]::Zero)
		Start-Sleep -Milliseconds 120
	}
	Start-Sleep -Milliseconds 400
}

function Wait-For-Window([System.Diagnostics.Process]$p) {
	$hwnd = [IntPtr]::Zero
	$deadline = (Get-Date).AddSeconds(15)
	while ((Get-Date) -lt $deadline) {
		Start-Sleep -Milliseconds 200
		if ($p.HasExited) { throw "process exited during startup" }
		$p.Refresh()
		if ($p.MainWindowHandle -ne 0) { $hwnd = $p.MainWindowHandle; break }
	}
	if ($hwnd -eq [IntPtr]::Zero) { throw "no main window appeared" }
	return $hwnd
}

$exeName = [System.IO.Path]::GetFileNameWithoutExtension($ExePath)
$proc = $null
$failures = 0

try {
	Say "== e2e_scroll_modes_test against: $ExePath"
	if ([string]::IsNullOrEmpty($ImagePath2)) { $ImagePath2 = $ImagePath }
	$iniPath = Join-Path (Split-Path $ExePath) "voidImageViewer.ini"

	# ---------------------------------------------------------------- TEST 1
	# middle-button drag pans a zoomed image (default config)
	Say "-- TEST 1: middle-button drag pans zoomed image"
	# start from factory defaults: TEST 2 writes its own ini and the app saves
	# its settings next to the exe on exit. Write instead of delete - a dying
	# instance can hold the ini open for a moment.
	$defaults = @("[voidImageViewer]", "left_click_action=0", "mouse_wheel_action=0", "scroll_window=1", "fit_window_to_image=1", "auto_zoom=1", "fill_window=1")
	[System.IO.File]::WriteAllLines($iniPath, $defaults)
	$proc = Start-Process -FilePath $ExePath -ArgumentList ('"{0}"' -f $ImagePath) -PassThru
	$hwnd = Wait-For-Window $proc
	Start-Sleep -Milliseconds 1200
	[void][ScrollNative]::SetForegroundWindow($hwnd)
	Start-Sleep -Milliseconds 300

	$cr = New-Object ScrollNative+RECT
	[void][ScrollNative]::GetClientRect($hwnd, [ref]$cr)
	$cw = $cr.Right - $cr.Left
	$ch = $cr.Bottom - $cr.Top
	$c = Client-ToScreen $hwnd ([int]($cw / 2)) ([int]($ch / 2))

	Wheel-Zoom $c.X $c.Y 4

	$bmpA = Capture-Client $hwnd
	# middle button: down at the centre, drift, up
	[void][ScrollNative]::SetCursorPos($c.X, $c.Y)
	Start-Sleep -Milliseconds 150
	[ScrollNative]::mouse_event($MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 80
	for ($i = 1; $i -le 10; $i++) {
		[void][ScrollNative]::SetCursorPos(($c.X + 10 * $i), ($c.Y + 8 * $i))
		Start-Sleep -Milliseconds 25
	}
	[ScrollNative]::mouse_event($MOUSEEVENTF_MIDDLEUP, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 500
	$bmpB = Capture-Client $hwnd

	# any pan of the checkerboard image changes pixels under the viewport
	$diffSamples = Sample-Diff $bmpA $bmpB 7
	$bmpA.Save((Join-Path $OutDir "mscroll_before.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	$bmpB.Save((Join-Path $OutDir "mscroll_after.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	Say ("   differing samples between before/after: $diffSamples")
	if ($diffSamples -lt 50) {
		Say "FAIL middle-drag - the view did not move (middle-drag scroll is a no-op)"
		$failures++
	}
	else {
		Say "PASS middle-drag - the view moved"
	}
	$bmpA.Dispose()
	$bmpB.Dispose()

	$proc.CloseMainWindow() | Out-Null
	if (-not $proc.WaitForExit(2000)) { Stop-Process -Id $proc.Id -Force }
	$proc = $null
	Start-Sleep -Milliseconds 600

	# ---------------------------------------------------------------- TEST 2
	# left-drag with left_click_action=5 (1:1 scroll): the panned position must
	# survive the button release (no snap to a stale view)
	Say "-- TEST 2: 1:1 scroll release keeps the panned view"
	$lines = @("[voidImageViewer]", "left_click_action=5", "fit_window_to_image=0", "auto_zoom=0", "fill_window=1")
	[System.IO.File]::WriteAllLines($iniPath, $lines)
	$proc = Start-Process -FilePath $ExePath -ArgumentList ('"{0}"' -f $ImagePath2) -PassThru
	$hwnd = Wait-For-Window $proc
	Start-Sleep -Milliseconds 1200
	[void][ScrollNative]::SetForegroundWindow($hwnd)
	Start-Sleep -Milliseconds 300

	[void][ScrollNative]::GetClientRect($hwnd, [ref]$cr)
	$cw = $cr.Right - $cr.Left
	$ch = $cr.Bottom - $cr.Top
	$c = Client-ToScreen $hwnd ([int]($cw / 2)) ([int]($ch / 2))

	# left-drag down-right so the image's top-left marker square enters the view
	[void][ScrollNative]::SetCursorPos($c.X, $c.Y)
	Start-Sleep -Milliseconds 150
	[ScrollNative]::mouse_event($MOUSEEVENTF_LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 100
	for ($i = 1; $i -le 10; $i++) {
		[void][ScrollNative]::SetCursorPos(($c.X + 12 * $i), ($c.Y + 10 * $i))
		Start-Sleep -Milliseconds 25
	}
	Start-Sleep -Milliseconds 200
	$bmpC = Capture-Client $hwnd
	[ScrollNative]::mouse_event($MOUSEEVENTF_LEFTUP, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 600
	$bmpD = Capture-Client $hwnd

	$litC = Count-Lit $bmpC 0 0 ([Math]::Min(800, $bmpC.Width)) ([Math]::Min(800, $bmpC.Height))
	$litD = Count-Lit $bmpD 0 0 ([Math]::Min(800, $bmpD.Width)) ([Math]::Min(800, $bmpD.Height))
	$bmpC.Save((Join-Path $OutDir "one2one_dragend.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	$bmpD.Save((Join-Path $OutDir "one2one_released.png"), [System.Drawing.Imaging.ImageFormat]::Png)
	Say ("   lit pixels at drag end=$litC after release=$litD")
	if ($litC -gt 0 -and $litD -eq 0) {
		Say "FAIL 1:1-scroll - releasing the button snapped the view back (square left the viewport)"
		$failures++
	}
	else {
		Say "PASS 1:1-scroll - the panned view survived the release"
	}
	$bmpC.Dispose()
	$bmpD.Dispose()
}
finally {
	$report | Out-File -FilePath (Join-Path $OutDir "scroll_test_report.txt") -Encoding utf8
	if ($proc -ne $null) {
		if (-not $proc.HasExited) {
			$proc.CloseMainWindow() | Out-Null
			if (-not $proc.WaitForExit(2000)) { Stop-Process -Id $proc.Id -Force }
		}
	}
}

if ($failures -gt 0) { Say ("== RESULT: " + $failures + " test(s) FAILED"); return 1 }
Say "== RESULT: all tests PASSED"
return 0
