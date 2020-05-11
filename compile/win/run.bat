::===============================================================
:: Author: Rudy Faile @rfaile313
:: Description: Custom Run, Build, Clean, Debug Script
:: License: MIT
:: args in bat are %1, %2, etc - so run build means %1 is build
::===============================================================
@echo off

:: Determines output and launcher
SET EXECUTABLE=draw_game.exe
SET DEXECUTABLE=draw_game_debug.exe
SET ICONRES=..\..\..\Resources\icon\icon.res
:: Source to build from (can use abs or rel path)
SET SOURCE=..\..\..\main.c

SET RAYLIB=C:\RAYLIB\RAYLIB\SRC

SET COMPILER=gcc
SET CFLAGS=-O1 -Wall -std=c99 -Wno-missing-braces
SET LIBFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32
:: FOR INCLUDE AND LIB: This is running with MinGW which already has Raylib in the -I and -L :-) 
:: Flags below for hiding windows console on executable
SET WINFLAGS=-Wl,-subsystem,windows

IF [%1] == [] GOTO RUN
IF [%1] == [clean] GOTO CLEAN
IF [%1] == [build] GOTO BUILD
IF [%1] == [debug] GOTO DEBUG
ECHO Invalid Command. Try run or run clean or run build or run debug
GOTO:EOF 

:RUN
IF EXIST Build RMDIR /Q/S Build && echo **Cleaned Build folder + files** 
IF NOT EXIST Build MKDIR Build
PUSHD Build
xcopy /i /e /q ..\..\..\Resources Resources
%COMPILER% %SOURCE% -o %EXECUTABLE% %CFLAGS% %LIBFLAGS% %WINFLAGS% %ICONRES% && echo **Build Successful. Running.** && echo. && %EXECUTABLE%
POPD
GOTO:EOF

:BUILD
IF EXIST Build RMDIR /Q/S Build && echo **Cleaned Build folder + files** 
IF NOT EXIST Build MKDIR Build
PUSHD Build
xcopy /i /e /q ..\..\..\Resources Resources
%COMPILER% %SOURCE% -o %EXECUTABLE% %CFLAGS% %LIBFLAGS% %WINFLAGS% %ICONRES% && echo **Build Successful.** && echo.
POPD
GOTO:EOF 

:DEBUG
IF EXIST Debug RMDIR /Q/S Debug && echo **Cleaned Debug folder + files** 
IF NOT EXIST Debug MKDIR Debug
PUSHD Debug
tcc %SOURCE% -o %DEXECUTABLE% -std=c99 -Wall -DPLATFORM_DESKTOP -I. -L. -lmsvcrt -lraylib -lopengl32 -lgdi32 -lkernel32 -lshell32 -luser32 && echo. && echo **Debug Build Successful** && echo. && %DEXECUTABLE%
POPD
GOTO:EOF 

:CLEAN
IF NOT EXIST Build echo. && echo **No build directory at the moment**
IF NOT EXIST Debug echo. && echo **No debug directory at the moment**
IF EXIST Build RMDIR /Q/S Build && echo **Cleaned Build folder + files** 
IF EXIST Debug RMDIR /Q/S Debug && echo **Cleaned Debug folder + files** 
GOTO:EOF 

