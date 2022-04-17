@echo off

IF NOT EXIST ..\build mkdir ..\build

IF NOT EXIST ..\build\raylib.dll copy code\lib_files\raylib.dll ..\build


pushd ..\build

cl -Zi ..\code\source_files\my_game.cpp  ..\code\lib_files\raylib.lib

copy ..\code\lib_files\raylib.dll 


popd

..\build\my_game.exe

