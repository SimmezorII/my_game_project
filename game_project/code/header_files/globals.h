

#pragma once
#if !defined(GLOBALS_H)
/* ========================================================================

======================================================================== */

#include <string>
#include <vector>

#include "game_entities.h"


using namespace std;

//========================================================================
#define internal static
#define local_persist static
#define global_variable static

//========================================================================

global_variable bool ActionButton[10];

global_variable bool SaveButton001;
global_variable bool SaveButton002;
global_variable bool ReloadButton;

global_variable bool NewEntityButton = false;

global_variable bool PLACING_ENTITY = false;

global_variable bool ToggleSpriteOffsetX = false;
global_variable bool ToggleSpriteX = false;
global_variable bool ToggleSpriteOffsetY = false;
global_variable bool ToggleSpriteY = false;

global_variable bool dropDown001EditMode = false;
global_variable bool ToggleEntityBoxes = false;

global_variable int GAME_TILE_WIDTH = 64;
global_variable int GAME_TILE_HEIGHT = 32;

global_variable int X_TILES = 20;
global_variable int Y_TILES = 40;

global_variable int GAMESCREEN_OFFSET_X = GAME_TILE_WIDTH;
global_variable int GAMESCREEN_OFFSET_Y = GAME_TILE_HEIGHT;

global_variable enum { TITLE = 0, OPTIONS, GAMEPLAY, ENDING, GUI } GameScreen;

global_variable enum Direction { UP = 1, DOWN = -1, LEFT = 2, RIGHT = -2 } Dir;

global_variable enum {
  SQUARE = 0,
  NON_ISO_SQUARE = 1,
  LINE = 2,
  CROSS = 3,
  CHECKERED_SQURE = 4,
  TRIANGLE = 10,
  CONE = 20
} TilePattern;

global_variable enum {
  BLUE_TILE = 1,
  GREEN_TILE = 2,
  RED_TILE = 3,
  YELLOW_TILE = 4
} TileColor;

global_variable enum {
  INDEX_UP = 0,
  INDEX_UP_RIGHT = 1,
  INDEX_RIGHT = 2,
  INDEX_DOWN_RIGHT = 3,
  INDEX_DOWN = 4,
  INDEX_DOWN_LEFT = 5,
  INDEX_LEFT = 6,
  INDEX_UP_LEFT = 7

} CollisionPoint;

global_variable enum {
  TILE = 0,
  ELLIPSE = 1,
  POINT = 3

} CollisionCheck;

global_variable bool DEBUG_PRINT = false;

global_variable int TARGET_FPS = 120;

global_variable float INPUT_DELAY = 0.01;

global_variable int GAMEWINDOW_WIDTH = 1600;
global_variable int GAMEWINDOW_HEIGHT = 940;

global_variable int GRID_WIDTH = 1280;
global_variable int GRID_HEIGHT = 640;

// This path is relative to the .exe file
global_variable char cstrGAME_ASSET_PATH[100] = "resources\\assets\\game\\";

global_variable char cstrGUI_ASSET_PATH[100] = "resources\\assets\\gui\\";

global_variable char cstrMAPS_PATH[100] = "resources\\assets\\textfiles\\";

global_variable string GAME_ASSET_PATH = "resources\\assets\\game\\";

global_variable string GUI_ASSET_PATH = "resources\\assets\\gui\\";

global_variable string MAPS_PATH = "resources\\assets\\textfiles\\";

global_variable string TILED_MAPS_PATH = "resources\\assets\\game\\tsx\\";

global_variable int FONT_SIZE = 10;

global_variable game_log GAME_LOG;

global_variable float GUI_ACTION_BUTTON_HEIGHT = 20;

global_variable float GUI_ACTION_BUTTON_WIDTH = 48;

global_variable int ACTION_MENU_BUTTONS_MAX = 12;

global_variable bool DEBUG_RENDER_BOXES = false;

global_variable bool DEBUG_TOGGLE_COMBAT = false;

global_variable bool DEBUG_TOGGLE_UNUSED = false;

global_variable bool DEBUG_TOGGLE_ENEMY_MOVE_FIELDS = false;

global_variable int GRID_SPRITE_ID = 29;

global_variable int GRID_ID = 200;
global_variable int TARGET_ID = 207;

global_variable Shader GAME_SHADER;

global_variable float GLOBAL_ALPAH = 0.5;
/////////////////////////////////////////////////////



#define GLOBALS_H
#endif
#pragma once
