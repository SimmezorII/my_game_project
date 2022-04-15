@echo off

mkdir ..\build
pushd ..\build

cl -Zi D:\myHandmadeProject\game_project\code\source_files\my_game.cpp  ..\code\lib_files\raylib.lib

popd
