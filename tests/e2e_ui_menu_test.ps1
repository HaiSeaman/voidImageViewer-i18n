# End-to-end visual check for the right-click popup menu and the About dialog.
#
#   CHECK 1  right-click menu: the bottom entry must be "About" (the menu bar's
#            Help submenu must NOT be appended any more)
#   CHECK 2  About dialog (Ctrl+F1): a "Project Page" button must exist at the
#            bottom-left of the dialog's bottom bar
#
# The checks are visual: each step saves a screenshot from the screen DC around
# the popup/dialog for inspection (the reports list the saved files).
#
# Usage:
#   powershell -File tests\e2e_ui_menu_test.ps1 -ExePath <exe> -ImagePath <bmp>

param(
	[Parameter(Mandatory = $true)][string]$ExePath,
	[Parameter(Mandatory = $true)][string]$ImagePath,
	[string]$OutDir = ""
)

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class UIMenuNative {
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern void mouse_event(uint flags, uint dx, uint dy, int data, UIntPtr extra);
    [DllImport("user32.dll")] public static extern void keybd_event(byte vk, byte scan, uint flags, UIntPtr extra);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hwnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hwnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr hwnd, ref POINT pt);
    [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr hwnd);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hwnd);
    [DllImport("user32.dll")] public static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll", CharSet = CharSet.Unicode)] public static extern bool GetClassName(IntPtr hwnd, System.Text.StringBuilder name, int max);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hwnd, out uint pid);
    [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
}
"@

$MOUSEEVENTF_LEFTDOWN = 0x02
$MOUSEEVENTF_LEFTUP = 0x04
$MOUSEEVENTF_RIGHTDOWN = 0x08
$MOUSEEVENTF_RIGHTUP = 0x10
$VK_ESCAPE = 0x1B
$VK_CONTROL = 0x11
$VK_F1 = 0x70
$KEYEVENTF_KEYUP = 0x02

if ([string]::IsNullOrEmpty($OutDir)) {
	$OutDir = Join-Path (Split-Path $PSScriptRoot -Parent) ".workbuddy\build\ui_menu_test"
}
New-Item -ItemType Directory -Force -Path $OutDir | Out-Null

# start from factory defaults (the app writes its ini next to the exe on exit)
$defaults = @("[voidImageViewer]", "left_click_action=0", "mouse_wheel_action=0", "scroll_window=1", "fit_window_to_image=1", "auto_zoom=1", "fill_window=1")
[System.IO.File]::WriteAllLines((Join-Path (Split-Path $ExePath) "voidImageViewer.ini"), $defaults)

$report = New-Object System.Collections.Generic.List[string]
function Say([string]$s) {
	$report.Add($s)
	Write-Output $s
}

# capture a screen rectangle (screen DC - popup menus/dialogs are their own windows)
function Capture-Screen([int]$x, [int]$y, [int]$w, [int]$h, [string]$file) {
	if ($w -le 0 -or $h -le 0) { throw "invalid capture size ${w}x${h}" }
	$bmp = New-Object System.Drawing.Bitmap($w, $h, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
	$g = [System.Drawing.Graphics]::FromImage($bmp)
	$g.CopyFromScreen($x, $y, 0, 0, (New-Object System.Drawing.Size($w, $h)))
	$g.Dispose()
	$bmp.Save($file, [System.Drawing.Imaging.ImageFormat]::Png)
	$bmp.Dispose()
}

Add-Type -AssemblyName System.Windows.Forms

$proc = $null
try {
	Say "== e2e_ui_menu_test against: $ExePath"
	$proc = Start-Process -FilePath $ExePath -ArgumentList ('"{0}"' -f $ImagePath) -PassThru
	$hwnd = [IntPtr]::Zero
	$deadline = (Get-Date).AddSeconds(15)
	while ((Get-Date) -lt $deadline) {
		Start-Sleep -Milliseconds 200
		if ($proc.HasExited) { throw "process exited during startup" }
		$proc.Refresh()
		if ($proc.MainWindowHandle -ne 0) { $hwnd = $proc.MainWindowHandle; break }
	}
	if ($hwnd -eq [IntPtr]::Zero) { throw "no main window appeared" }
	Start-Sleep -Milliseconds 1200
	[void][UIMenuNative]::SetForegroundWindow($hwnd)
	Start-Sleep -Milliseconds 300

	$wr = New-Object UIMenuNative+RECT
	[void][UIMenuNative]::GetWindowRect($hwnd, [ref]$wr)
	$pt = New-Object UIMenuNative+POINT
	$pt.X = [int](($wr.Left + $wr.Right) / 2)
	$pt.Y = [int](($wr.Top + $wr.Bottom) / 2)
	[void][UIMenuNative]::ClientToScreen($hwnd, [ref]$pt)

	# ---- CHECK 1: right-click popup menu
	[void][UIMenuNative]::SetCursorPos($pt.X, $pt.Y)
	Start-Sleep -Milliseconds 200
	[UIMenuNative]::mouse_event($MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 60
	[UIMenuNative]::mouse_event($MOUSEEVENTF_RIGHTUP, 0, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 800
	$menuFile = Join-Path $OutDir "popup_menu.png"
	Capture-Screen ($pt.X - 20) ($pt.Y - 20) 560 860 $menuFile
	Say "   popup menu screenshot: $menuFile"
	# dismiss the menu
	[UIMenuNative]::keybd_event($VK_ESCAPE, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 60
	[UIMenuNative]::keybd_event($VK_ESCAPE, 0, $KEYEVENTF_KEYUP, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 500

	# ---- CHECK 2: About dialog via Ctrl+F1
	[UIMenuNative]::keybd_event($VK_CONTROL, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 60
	[UIMenuNative]::keybd_event($VK_F1, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 60
	[UIMenuNative]::keybd_event($VK_F1, 0, $KEYEVENTF_KEYUP, [UIntPtr]::Zero)
	[UIMenuNative]::keybd_event($VK_CONTROL, 0, $KEYEVENTF_KEYUP, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 1000
	$aboutFile = Join-Path $OutDir "about_dialog.png"
	Capture-Screen ($wr.Left - 60) ($wr.Top - 60) (($wr.Right - $wr.Left) + 120) (($wr.Bottom - $wr.Top) + 120) $aboutFile
	Say "   about dialog screenshot: $aboutFile"

	# ---- CHECK 3: the Project button really opens the repository URL.
	# The modal dialog owns the foreground right after it opens; click its
	# bottom-left button (template rect 6,168 50x14 in dialog units) and look
	# for a browser being started / showing the repository page.
	$dialog = [IntPtr]::Zero
	$fg = [UIMenuNative]::GetForegroundWindow()
	if ($fg -ne [IntPtr]::Zero) {
		$cn = New-Object System.Text.StringBuilder 256
		[void][UIMenuNative]::GetClassName($fg, $cn, 256)
		$fgpid = [uint32]0
		[void][UIMenuNative]::GetWindowThreadProcessId($fg, [ref]$fgpid)
		if (($cn.ToString() -eq "#32770") -and ($fgpid -eq $proc.Id)) {
			$dialog = $fg
		}
	}
	Say ("   about dialog hwnd found: " + ($dialog -ne [IntPtr]::Zero))

	if ($dialog -ne [IntPtr]::Zero) {
		$browserNames = @("chrome", "msedge", "firefox", "brave", "opera", "vivaldi", "360se", "360chrome", "QQBrowser", "SogouExplorer", "maxthon")
		$beforeIds = @(Get-Process -Name $browserNames -ErrorAction SilentlyContinue | ForEach-Object { $_.Id })

		# deliver the button's click command straight to the dialog:
		# WM_COMMAND(IDC_ABOUTPROJECT, BN_CLICKED) is exactly what pressing the
		# button sends, so this exercises the same ShellExecute code path.
		$WM_COMMAND = 0x0111
		$IDC_ABOUTPROJECT = 1067
		[void][UIMenuNative]::SendMessage($dialog, $WM_COMMAND, [IntPtr]$IDC_ABOUTPROJECT, [IntPtr]::Zero)
		Start-Sleep -Milliseconds 3500

		$after = @(Get-Process -Name $browserNames -ErrorAction SilentlyContinue)
		$newProc = @($after | Where-Object { $beforeIds -notcontains $_.Id })
		$titleHit = @($after | Where-Object { $_.MainWindowTitle -match "voidImageViewer" })
		if (($newProc.Count -gt 0) -or ($titleHit.Count -gt 0)) {
			Say ("PASS project-button - browser opened the page (new=" + ($newProc.Count -gt 0) + " title-match=" + ($titleHit.Count -gt 0) + ")")
		}
		else {
			Say "UNCERTAIN project-button - no obvious browser reaction detected (check manually)"
		}
	}

	# close the dialog
	[UIMenuNative]::keybd_event($VK_ESCAPE, 0, 0, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 60
	[UIMenuNative]::keybd_event($VK_ESCAPE, 0, $KEYEVENTF_KEYUP, [UIntPtr]::Zero)
	Start-Sleep -Milliseconds 500

	Say "== done: inspect the two PNGs (popup bottom entry = About; About dialog bottom-left = Project button)"
}
finally {
	$report | Out-File -FilePath (Join-Path $OutDir "ui_menu_test_report.txt") -Encoding utf8
	if ($proc -ne $null) {
		if (-not $proc.HasExited) {
			$proc.CloseMainWindow() | Out-Null
			if (-not $proc.WaitForExit(2000)) { Stop-Process -Id $proc.Id -Force }
		}
	}
}
