# Pack and Publish Colors.Dev Native NuGet Package
# This script builds the project, creates the NuGet package, and optionally publishes it

param(
    [string]$ApiKey = "",
    [switch]$PublishToNuGet = $false,
    [switch]$BuildFirst = $true
)

$ErrorActionPreference = "Stop"

# Get the project directory
$projectDir = $PSScriptRoot

Write-Host "Colors.Dev NuGet Package Builder" -ForegroundColor Cyan
Write-Host "=================================" -ForegroundColor Cyan
Write-Host ""

# Build the project if requested
if ($BuildFirst) {
    Write-Host "Building Colors.Dev in Release mode..." -ForegroundColor Yellow

    # Build Win32 Release
    Write-Host "Building Win32 Release..." -ForegroundColor Gray
    msbuild "$projectDir\Colors.Dev.vcxproj" /p:Configuration=Release /p:Platform=Win32 /m
    if ($LASTEXITCODE -ne 0) {
        Write-Error "Win32 Release build failed!"
        exit 1
    }

    # Build x64 Release
    Write-Host "Building x64 Release..." -ForegroundColor Gray
    msbuild "$projectDir\Colors.Dev.vcxproj" /p:Configuration=Release /p:Platform=x64 /m
    if ($LASTEXITCODE -ne 0) {
        Write-Error "x64 Release build failed!"
        exit 1
    }

    Write-Host "Build completed successfully!" -ForegroundColor Green
    Write-Host ""
}

# Check if NuGet.exe exists
$nugetExe = "nuget.exe"
if (-not (Get-Command $nugetExe -ErrorAction SilentlyContinue)) {
    Write-Host "NuGet.exe not found in PATH. Downloading..." -ForegroundColor Yellow
    $nugetExe = "$projectDir\nuget.exe"
    if (-not (Test-Path $nugetExe)) {
        Invoke-WebRequest -Uri "https://dist.nuget.org/win-x86-commandline/latest/nuget.exe" -OutFile $nugetExe
    }
}

# Pack the NuGet package
Write-Host "Creating NuGet package..." -ForegroundColor Yellow
& $nugetExe pack "$projectDir\Colors.Dev.nuspec" -OutputDirectory "$projectDir"

if ($LASTEXITCODE -ne 0) {
    Write-Error "NuGet pack failed!"
    exit 1
}

# Find the generated .nupkg file
$nupkgFiles = Get-ChildItem "$projectDir\Colors.Dev.*.nupkg" | Sort-Object LastWriteTime -Descending
if ($nupkgFiles.Count -eq 0) {
    Write-Error "No .nupkg file found!"
    exit 1
}

$nupkgFile = $nupkgFiles[0]
Write-Host "Package created: $($nupkgFile.Name)" -ForegroundColor Green
Write-Host ""

# Publish if requested
if ($PublishToNuGet) {
    if ([string]::IsNullOrWhiteSpace($ApiKey)) {
        Write-Error "API Key is required to publish. Use -ApiKey parameter."
        exit 1
    }

    Write-Host "Publishing to NuGet.org..." -ForegroundColor Yellow
    & $nugetExe push $nupkgFile.FullName -Source https://api.nuget.org/v3/index.json -ApiKey $ApiKey

    if ($LASTEXITCODE -ne 0) {
        Write-Error "NuGet publish failed!"
        exit 1
    }

    Write-Host "Package published successfully!" -ForegroundColor Green
} else {
    Write-Host "Package created but not published." -ForegroundColor Yellow
    Write-Host "To publish, run:" -ForegroundColor Yellow
    Write-Host "  nuget push $($nupkgFile.Name) -Source https://api.nuget.org/v3/index.json -ApiKey YOUR_API_KEY" -ForegroundColor White
    Write-Host ""
    Write-Host "Or run this script with -PublishToNuGet -ApiKey YOUR_API_KEY" -ForegroundColor White
}

Write-Host ""
Write-Host "Done!" -ForegroundColor Green
