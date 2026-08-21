# E2E behavior test for the left-drag pan feature.
#
# Usage:  powershell -File tests\e2e_drag_test.ps1 <exe-path>
#
# Scenarios (default config: borderless, left_click_action=0 scroll,
# fill_window=1, wheel=zoom):
#   TEST 1  maximized, image fills window, drag        -> window must NOT move
#   TEST 2  maximized, wheel-zoomed in, drag           -> window must NOT move (pan)
#   TEST 3  restored normal window, image fills, drag  -> window MUST move
#
# Output: one PASS/FAIL line per scenario, exit code 1 if any failed.

param(
    [Parameter(Mandatory = $true)]
    [string]$ExePath
)

$ErrorActionPreference = 'Stop'

Add-Type -AssemblyName System.Windows.Forms

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class Native {
    [DllImport("user32.dll")] public static extern bool SetCursorPos(int x, int y);
    [DllImport("user32.dll")] public static extern void mouse_event(uint flags, uint dx, uint dy, int data, UIntPtr extra);
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hwnd, out RECT rect);
    [DllImport("user32.dll")] public static extern bool IsZoomed(IntPtr hwnd);
    [DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
}
"@

$MOUSEEVENTF_LEFTDOWN = 0x02
$MOUSEEVENTF_LEFTUP   = 0x04
$MOUSEEVENTF_WHEEL    = 0x0800
$WM_SYSCOMMAND        = 0x0112
$SC_RESTORE           = 0xF120
$SC_MAXIMIZE          = 0xF030

$failures = 0
function Report([string]$name, [bool]$ok, [string]$detail) {
    if ($ok) { Write-Output ("PASS {0} - {1}" -f $name, $detail) }
    else { $script:failures++; Write-Output ("FAIL {0} - {1}" -f $name, $detail) }
}

function Get-RectStr([IntPtr]$hwnd) {
    $r = New-Object Native+RECT
    [void][Native]::GetWindowRect($hwnd, [ref]$r)
    return @{ Str = "{0},{1},{2},{3}" -f $r.Left, $r.Top, $r.Right, $r.Bottom; L = $r.Left; T = $r.Top; R = $r.Right; B = $r.Bottom }
}

function Center-Of($rect) {
    return @{ X = [int](($rect.L + $rect.R) / 2); Y = [int](($rect.T + $rect.B) / 2) }
}

function Drag([int]$x, [int]$y, [int]$dx, [int]$dy) {
    [void][Native]::SetCursorPos($x, $y)
    Start-Sleep -Milliseconds 150
    [Native]::mouse_event($MOUSEEVENTF_LEFTDOWN, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 100
    $steps = 10
    for ($i = 1; $i -le $steps; $i++) {
        [void][Native]::SetCursorPos(($x + [int]($dx * $i / $steps)), ($y + [int]($dy * $i / $steps)))
        Start-Sleep -Milliseconds 30
    }
    [Native]::mouse_event($MOUSEEVENTF_LEFTUP, 0, 0, 0, [UIntPtr]::Zero)
    Start-Sleep -Milliseconds 400
}

function Wheel-Zoom([int]$x, [int]$y, [int]$notches) {
    [void][Native]::SetCursorPos($x, $y)
    Start-Sleep -Milliseconds 150
    $delta = 120 * [Math]::Sign($notches)
    for ($i = 0; $i -lt [Math]::Abs($notches); $i++) {
        [Native]::mouse_event($MOUSEEVENTF_WHEEL, 0, 0, $delta, [UIntPtr]::Zero)
        Start-Sleep -Milliseconds 120
    }
    Start-Sleep -Milliseconds 400
}

$image = Join-Path $PSScriptRoot "test_image.bmp"
if (-not (Test-Path $image)) { throw "missing $image - run make_test_image.ps1 first" }

# the app writes its ini next to the exe on exit; start from factory defaults
Remove-Item (Join-Path (Split-Path $ExePath) "voidImageViewer.ini") -ErrorAction SilentlyContinue

Write-Output ("== e2e_drag_test against: " + $ExePath)

$proc = Start-Process -FilePath $ExePath -ArgumentList ('"{0}"' -f $image) -PassThru
try {
    # wait for the main window, the image load and the auto-fit resize to settle
    $hwnd = [IntPtr]::Zero
    $deadline = (Get-Date).AddSeconds(10)
    while ((Get-Date) -lt $deadline) {
        Start-Sleep -Milliseconds 200
        if ($proc.HasExited) { throw "process exited during startup" }
        $proc.Refresh()
        if ($proc.MainWindowHandle -ne 0) { $hwnd = $proc.MainWindowHandle; break }
    }
    if ($hwnd -eq [IntPtr]::Zero) { throw "no main window appeared" }
    Start-Sleep -Milliseconds 1000

    # maximize explicitly (the auto-fit resize cancels the /maximized flag)
    [void][Native]::SendMessage($hwnd, $WM_SYSCOMMAND, [IntPtr]$SC_MAXIMIZE, [IntPtr]::Zero)
    $deadline = (Get-Date).AddSeconds(5)
    while (-not [Native]::IsZoomed($hwnd) -and ((Get-Date) -lt $deadline)) {
        Start-Sleep -Milliseconds 100
    }
    if (-not [Native]::IsZoomed($hwnd)) { throw "window refused to maximize" }
    Start-Sleep -Milliseconds 500

    # --- TEST 1: maximized + image fills window -> drag must do nothing ---
    $r1 = Get-RectStr $hwnd
    $c = Center-Of $r1
    Drag $c.X $c.Y 200 120
    $r1b = Get-RectStr $hwnd
    $ok = ([Native]::IsZoomed($hwnd)) -and ($r1b.Str -eq $r1.Str)
    Report "TEST1 maximized+fit drag=noop" $ok ("rect '$($r1.Str)' -> '$($r1b.Str)' zoomed=" + [Native]::IsZoomed($hwnd))

    # --- TEST 2: maximized + zoomed in -> drag pans, window must not move ---
    $c = Center-Of (Get-RectStr $hwnd)
    Wheel-Zoom $c.X $c.Y 4
    $r2 = Get-RectStr $hwnd
    $c = Center-Of $r2
    Drag $c.X $c.Y (-250) (-150)
    $r2b = Get-RectStr $hwnd
    $ok = ([Native]::IsZoomed($hwnd)) -and ($r2b.Str -eq $r2.Str)
    Report "TEST2 maximized+zoomed drag=pan" $ok ("rect '$($r2.Str)' -> '$($r2b.Str)' zoomed=" + [Native]::IsZoomed($hwnd))

    # --- TEST 3: restored normal window + image fits -> drag must move window ---
    [void][Native]::SendMessage($hwnd, $WM_SYSCOMMAND, [IntPtr]$SC_RESTORE, [IntPtr]::Zero)
    Start-Sleep -Milliseconds 600
    # zoom back out to fit: TEST 2 left the image zoomed in, and a zoomed
    # image must pan instead of moving the window
    $r3 = Get-RectStr $hwnd
    if ([Native]::IsZoomed($hwnd)) { throw "window did not restore" }
    $c = Center-Of $r3
    Wheel-Zoom $c.X $c.Y (-12)
    Start-Sleep -Milliseconds 300

    # drag toward the middle of the work area so we never push into a screen edge
    $wa = [System.Windows.Forms.Screen]::PrimaryScreen.WorkingArea
    $r3 = Get-RectStr $hwnd
    $c = Center-Of $r3
    $dx = ($wa.Left + $wa.Width / 2) - $c.X
    $dy = ($wa.Top + $wa.Height / 2) - $c.Y
    if ([Math]::Abs($dx) -lt 100) { $dx = 160 }
    if ([Math]::Abs($dy) -lt 100) { $dy = 110 }
    if ($dx -gt 220) { $dx = 220 }
    if ($dx -lt -220) { $dx = -220 }
    if ($dy -gt 160) { $dy = 160 }
    if ($dy -lt -160) { $dy = -160 }
    Drag $c.X $c.Y $dx $dy
    $r3b = Get-RectStr $hwnd
    $ok = ($r3b.Str -ne $r3.Str)
    Report "TEST3 normal-window drag=move" $ok ("rect '$($r3.Str)' -> '$($r3b.Str)'")

    [void][Native]::SetCursorPos(($wa.Left + $wa.Width / 2), ($wa.Top + $wa.Height / 2))
}
finally {
    if (-not $proc.HasExited) {
        $proc.CloseMainWindow() | Out-Null
        if (-not $proc.WaitForExit(2000)) { Stop-Process -Id $proc.Id -Force }
    }
}

if ($failures -gt 0) { Write-Output ("== RESULT: " + $failures + " test(s) FAILED"); exit 1 }
Write-Output "== RESULT: all tests PASSED"; exit 0
