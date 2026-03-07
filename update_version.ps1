# update_version.ps1
# Updates version information in import_exports.h with current UTC timestamp during pre-build events.

$readMe = "$PSScriptRoot\README.md"
$importExports = "$PSScriptRoot\import_exports.h"
$utcNow = [DateTime]::UtcNow

# Calculate components
$fullYear = $utcNow.Year
$yearOffset = $fullYear - 2020
$month = $utcNow.Month
$day = $utcNow.Day
$time = $utcNow.ToString("HHmm")

# Read the file
$content = Get-Content $importExports -Raw

# Update each component using regex
$content = $content -replace '(#define COLORS_DEV_FULL_YEAR\s+)\d+', "`${1}$fullYear"
$content = $content -replace '(#define COLORS_DEV_YEAR_OFFSET\s+)\d+', "`${1}$yearOffset"
$content = $content -replace '(#define COLORS_DEV_MONTH\s+)\d+', "`${1}$month"
$content = $content -replace '(#define COLORS_DEV_DAY\s+)\d+', "`${1}$day"
$content = $content -replace '(#define COLORS_DEV_UTC_TIME\s+)\d+', "`${1}$time"

# Write back to file
Set-Content $importExports -Value $content -NoNewline

Write-Host "Version updated: $yearOffset.$month.$day.$time"
