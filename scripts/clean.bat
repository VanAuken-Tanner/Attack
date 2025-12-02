@echo off

IF EXIST ".\build\Attack!.exe" (
    echo Cleaning...
    del .\build\*.exe /Q
    IF NOT EXIST ".\build\Attack!.exe" (
        echo Clean Success!
    )
) ELSE (
    echo Nothing to Clean.
)