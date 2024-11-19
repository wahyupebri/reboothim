@echo off
setlocal EnableDelayedExpansion

set "inputFile=machines.txt"
set "commandProgram=RebootHIM.exe"

for /f "tokens=1,2 delims=;" %%a in (%inputFile%) do (
    set "parameter1=%%a"
    set "parameter2=%%b"

    echo --Rebooting !parameter1! with IP !parameter2!
    %commandProgram% !parameter2! !parameter1!
)

endlocal

