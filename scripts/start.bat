@echo off

if exist ".\build\Attack!.exe" (
    echo Starting Attack!
    .\build\Attack!.exe
) else (
    echo Failed to start - no Attack!.exe found.
)
