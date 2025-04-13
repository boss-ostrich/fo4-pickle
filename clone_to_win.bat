@echo off
setlocal

:: Source path inside WSL (accessed via UNC)
set "WSL_PATH=\\wsl$\Ubuntu\home\zzs\FalloutPickle"

:: Destination path on your native C: drive
set "WIN_DEST=C:\Dev\FalloutPickle_LocalBuild"

echo Copying FalloutPickle from WSL to %WIN_DEST%...

robocopy "%WSL_PATH%" "%WIN_DEST%" /E /MIR /XD build .git .vs /XF *.o *.obj *.pch *.dll *.exe

if %ERRORLEVEL% LEQ 1 (
    echo ✅ Copy complete.
) else (
    echo ⚠️ Copy finished with warnings or errors. (robocopy exit code: %ERRORLEVEL%)
)

endlocal
pause
