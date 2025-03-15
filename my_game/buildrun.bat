@REM @echo off

@REM IF NOT EXIST ..\build mkdir ..\build

@REM IF NOT EXIST ..\build\raylib.dll copy code\lib_files\raylib.dll ..\build


@REM pushd ..\build

@REM cl -Zi ..\code\source_files\my_game.cpp  ..\code\lib_files\raylib.lib

build-windows.bat -dr

@REM popd

@REM ..\build\my_game.exe

