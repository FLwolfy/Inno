@echo off
cd /d "%~dp0"

echo Enter the IDE to generate (e.g. xcode4, vs2022, gmake2):
set /p IDE_NAME=

.premake\Windows\premake5.exe %IDE_NAME%

exit /b 0
