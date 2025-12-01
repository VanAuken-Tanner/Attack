@echo off

ECHO Compiling Attack!...

SET debug=%1
SET build_cmd=%2

IF NOT DEFINED build_cmd (SET build_cmd="core")
IF NOT DEFINED debug (SET debug="false")

IF "%debug%"=="d" (

    ECHO DEBUGGING ENABLED
    g++ -std=c++20^
    -Wall -D DEBUG_LEVEL=3^
    -D GLEW_STATIC -L deps\external\GLFW\lib -L deps\external\GLEW\lib^
    -o build\Attack!.exe^
    deps\external\vendor\imgui\*.cpp^
    src\engine\*.cpp^
    src\scenes\*.cpp^
    src\*.cpp^
    -lglew32s -lglfw3 -lgdi32 -lopengl32

) ELSE IF %debug%=="false" (

    g++ -std=c++20^
    -D GLEW_STATIC -L deps\external\GLFW\lib -L deps\external\GLEW\lib^
    -o build\Attack!.exe^
    deps\external\vendor\imgui\*.cpp^
    src\engine\*.cpp^
    src\scenes\*.cpp^
    src\*.cpp^
    -lglew32s -lglfw3 -lgdi32 -lopengl32
    
)  

if exist ".\build\Attack!.exe" (
    echo Compiling Success!
) else (
    echo Failed to compile.
)