@echo off

rem IF NOT EXIST ..\build mkdir ..\build

rem IF NOT EXIST ..\build\raylib.dll copy code\lib_files\raylib.dll ..\build

build-windows.bat -d | findstr error

rem pushd ..\build

rem cl -Zi ..\code\source_files\my_game.cpp  ..\code\lib_files\raylib.lib

rem popd
