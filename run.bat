::===============================================================
:: Author: Rudy Faile @rfaile313
:: Description: Custom Run Script
:: args in bat are %1, %2, etc - so run build means %1 is build
::===============================================================
@echo off

IF [%1] == [build] GOTO BUILD
IF [%1] == [debug] GOTO DEBUG
IF [%1] == [run]   GOTO RUN
IF [%1] == [clean] GOTO CLEAN

IF [%1] == [] echo. && echo Value Missing! Try run build or run debug or run clean or run run
GOTO:EOF 

:BUILD
call "build.bat" -d && echo. && echo **build.bat ran with -d**
GOTO:EOF 

:DEBUG
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 && devenv builds-debug\windows-msvc\draw_game.exe
GOTO:EOF 

:CLEAN
RMDIR /Q/S TEMP && echo **Removed TEMP folder + files** && RMDIR /Q/S BUILDS-DEBUG && echo **Removed BUILDS-DEBUG folder + files** && RMDIR /Q/S BUILDS && echo **Removed BUILDS folder + files** 
GOTO:EOF 

:RUN
builds-debug\windows-msvc\draw_game.exe
GOTO:EOF 




