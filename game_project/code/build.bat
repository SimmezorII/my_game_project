@echo off

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl -Zi ..\code\source_files\my_game.cpp  ..\code\lib_files\raylib.lib

popd
