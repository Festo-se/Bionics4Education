@ECHO OFF
SETLOCAL EnableDelayedExpansion

REM Bionics Kit Flash-Tool


echo Bionics Kit Flash-Tool Bionics-Kit_Software_v.2.0.0
echo PLEASE DISCONNECT ALL OTHER USB-TO-SERIAL DEVICES
echo.

pause
echo.

SET device_name=USB Serial Port

:loop
echo searching for COM port. . .
echo.
SET res=-1 

SET exclude_1=''
SET exclude_2=''
SET exclude_3=''

FOR /F "tokens=*" %%A IN ('WMIC path win32_pnpentity get ClassGuid^,Caption^| find "{4d36e978-e325-11ce-bfc1-08002be10318}" ^| findstr "(COM[0-9])*" ^| find "!device_name!"') DO (

   SET var=%%A

    FOR /F "TOKENS=2 DELIMS=(" %%a IN ("!var!") DO (
        SET var2=%%a
    )

    FOR /F "TOKENS=1 DELIMS=)" %%a IN ("!var2!") DO (
        SET var3=%%a
    )

    REM echo !var3!

    REM flash parallel
    CMD /c "tools\esptool.exe --chip esp32 --port !VAR3! erase_flash
    CMD /c "tools\esptool.exe --chip esp32 --port !VAR3! --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0x0000 bin\Bionics-Kit_Software_v.2.0.0.bin" 
    set res=1

)

if %res% == -1 (
    echo No Bionics Kit found
    echo.
)

echo.
echo Press ENTER for continue or CLOSE the window to leave the application
echo.
pause
goto loop
