::===============================================================
:: Author: Rudy Faile @rfaile313
:: Description: Custom Run, Build, Clean, Debug Script
:: License: MIT
:: args in bat are %1, %2, etc - so run build means %1 is build
::===============================================================
@echo off

:: Project Source (Unity Build)
SET SOURCE=..\..\..\main.c
:: Project Executable
SET EXECUTABLE=draw_game
:: MSVC
SET COMPILER=cl
:: Compiler Flags https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-alphabetically?view=vs-2019\
SET CFLAGS=/nologo /Zi /O2 /Fe%EXECUTABLE% /I..\raylib %SOURCE% /link..\raylib\raylib.lib

SET VCVARSALL="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"
SET COPYDLL="..\raylib\raylib.dll ." 
SET SUCCESS=********************Build Successful. Running.************************

IF [%1] == [] GOTO RUN
IF [%1] == [clean] GOTO CLEAN
IF [%1] == [build] GOTO BUILD
IF [%1] == [debug] GOTO DEBUG
ECHO Invalid Command. Commands: run, run clean, run build, or run debug
GOTO:EOF 

:RUN
IF NOT EXIST Build MKDIR Build
PUSHD Build
call %VCVARSALL% x64
copy %COPYDLL%
%COMPILER% %CFLAGS% && echo. && echo %SUCCESS% && echo. && %EXECUTABLE%.exe
POPD
GOTO:EOF

:BUILD
IF NOT EXIST Build MKDIR Build
PUSHD Build
call %VCVARSALL% x64
copy %COPYDLL%
%COMPILER% %CFLAGS% && echo. && echo %SUCCESS% && echo.
POPD
GOTO:EOF 

:DEBUG
IF NOT EXIST Build MKDIR Build
PUSHD Build
remedybg.exe %EXECUTABLE%.exe
POPD
GOTO:EOF 

:CLEAN
IF NOT EXIST Build echo. && echo **No build directory at the moment**
IF EXIST Build RMDIR /Q/S Build && echo **Cleaned Build folder + files**  
GOTO:EOF 

