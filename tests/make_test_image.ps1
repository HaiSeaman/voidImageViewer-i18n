# Generates tests\test_image.bmp used by e2e_drag_test.ps1.
Add-Type -AssemblyName System.Drawing

$bmp = New-Object System.Drawing.Bitmap(2000, 1400)
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.Clear([System.Drawing.Color]::SteelBlue)
$pen = New-Object System.Drawing.Pen([System.Drawing.Color]::Yellow, 12)
for ($i = 0; $i -lt 2000; $i += 100) {
    $g.DrawLine($pen, $i, 0, $i, 1400)
    $g.DrawLine($pen, 0, $i, 2000, $i)
}
$font = New-Object System.Drawing.Font("Arial", 60)
$brush = [System.Drawing.Brushes]::White
$g.DrawString("VIV DRAG TEST 2000x1400", $font, $brush, 100, 100)
$g.Dispose()

$out = Join-Path $PSScriptRoot "test_image.bmp"
$bmp.Save($out, [System.Drawing.Imaging.ImageFormat]::Bmp)
$bmp.Dispose()
Write-Output "created $out"
