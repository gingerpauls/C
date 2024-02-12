REM %windir%\system32\cmd.exe /k D:\Programming\handmade\misc\shell.bat
@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl library.c
pause