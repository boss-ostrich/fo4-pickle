@echo off
REM FalloutPickle build script for x64 Native Tools Command Prompt (VS 2022)

REM Step 1: Delete the existing build directory
rmdir /S /Q build

REM Step 2: Recreate the build directory
mkdir build

REM Step 3: Change into the build directory
cd build

REM Step 4: Run CMake to configure the project
cmake .. -G "Visual Studio 17 2022" -A x64 -DF4SE_PATH="C:/SDKs/F4SE"

IF %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed.
    exit /b %ERRORLEVEL%
)

REM Step 5: Build the project
cmake --build . --config Debug

IF %ERRORLEVEL% NEQ 0 (
    echo Build failed.
    exit /b %ERRORLEVEL%
)

echo Build succeeded.