@echo off
echo This program will DELETE all files with syntax Mapeador_WAYPOINTS_*.???

echo Would you like to continue [Y/N]?

set /p cont=
if "%cont%"=="y" goto proceed
if "%cont%"=="Y" goto proceed
if "%cont%"=="n" goto ini
if "%cont%"=="N" goto ini
goto close

:proceed
@echo on
del Mapeador_WAYPOINTS_*.???
echo Finished
pause
goto close

:close
@cls&exit

