

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

global_variable int GAMESCREEN_OFFSET_X = 0;
global_variable int GAMESCREEN_OFFSET_Y = 0;

global_variable enum { TITLE = 0, OPTIONS, GAMEPLAY, ENDING, GUI } GameScreen;

struct game_log {
  int LogScrollCounter = 99;
  int CurrentLineLog = 0;
  int DebugLogScrollCounter = 99;
  int CurrentLineDebuglog = 0;
  int LogReset = 0;

  vector<string> DebugInfoLines;
  vector<string> LogLines;
  vector<string> DebugLogLines;
};

struct vel {
  int right;
  int left;
  int up;
  int down;
};

global_variable enum Direction {
  UP = 1,
  DOWN = -1,
  LEFT = 2,
  RIGHT = -2,
  DOWNUP = 3,
  UPDOWN = -3,
  RIGHTLEFT = 4,
  LEFTRIGHT = -4
} Dir;

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
  INDEX_UP2 = 1,
  INDEX_UP_RIGHT = 2,
  INDEX_RIGHT = 3,
  INDEX_RIGHT2 = 4,
  INDEX_DOWN_RIGHT = 5,
  INDEX_DOWN = 6,
  INDEX_DOWN2 = 7,
  INDEX_DOWN_LEFT = 8,
  INDEX_LEFT = 9,
  INDEX_LEFT2 = 10,
  INDEX_UP_LEFT = 11

} CollisionPoint;

global_variable enum {
  TILE = 0,
  ELLIPSE = 1,
  POINT = 2,
  LINE_UP = 3,
  LINE_LEFT = 4,
  LINE_DOWN = 5,
  LINE_RIGHT = 6,
  LINE_DIAG = 7,
  TRIPLE_LINE_RIGHT = 8,

} CollisionCheck;

global_variable bool DEBUG_PRINT = false;

global_variable int TARGET_FPS = 120;

global_variable float PLAYER_INPUT_DELAY = 0.01;

global_variable float TARGET_INPUT_DELAY = 0.1;

global_variable float ENEMY_INPUT_DELAY = 0.1;
global_variable float ANIMATION_SPEED = 0.05;

global_variable int GAMEWINDOW_WIDTH = 1280 + 300;
global_variable int GAMEWINDOW_HEIGHT = 720;

global_variable int GRID_WIDTH = 1280;
global_variable int GRID_HEIGHT = 640;

global_variable Camera2D CAMERA;
global_variable float CAMERA_ZOOM = 1.0f;
global_variable bool TOGGLE_CAMERA_MODE = true;

global_variable float RENDER_SCALE = 1.0f;

// This path is relative to the .exe file
global_variable char cstrGAME_ASSET_PATH[100] = "..\\..\\resources\\assets\\game\\";

global_variable char cstrGUI_ASSET_PATH[100] = "..\\..\\resources\\assets\\gui\\";

global_variable char cstrMAPS_PATH[100] = "..\\..\\resources\\assets\\textfiles\\";

global_variable string GAME_ASSET_PATH = "..\\..\\resources\\assets\\game\\";

global_variable string GUI_ASSET_PATH = "..\\..\\resources\\assets\\gui\\";

global_variable string MAPS_PATH = "..\\..\\resources\\assets\\textfiles\\";

global_variable string TILED_MAPS_PATH = "..\\..\\resources\\assets\\game\\tsx\\";

global_variable char TEST_SHADER[100] = "../../resources/assets/shaders/outline.fs";

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

global_variable int SLIME_ID = 211;
global_variable int SLIME_ID2 = 212;
global_variable int SLIME_SPRITE_ID = 200;

global_variable int PLAYER_SPRITE_ID = 67;
global_variable int PLAYER_ID = 9;

global_variable Shader GAME_SHADER;

global_variable float GLOBAL_ALPHA = 0.5;
/////////////////////////////////////////////////////

global_variable int DEBUG_ENEMEY_INDEX = 0;

global_variable vel PLAYER_VEL = {(GAME_TILE_WIDTH / 8), -(GAME_TILE_WIDTH / 8),
                                  (GAME_TILE_HEIGHT / 8),
                                  -(GAME_TILE_HEIGHT / 8)};

global_variable vel COMBAT_VEL = {(GAME_TILE_WIDTH / 2), -(GAME_TILE_WIDTH / 2),
                                  -(GAME_TILE_HEIGHT / 2),
                                  (GAME_TILE_HEIGHT / 2)};

global_variable vel ROAMING_VEL = {
    (GAME_TILE_WIDTH / 1), -(GAME_TILE_WIDTH / 1), -(GAME_TILE_HEIGHT / 1),
    (GAME_TILE_HEIGHT / 1)};

global_variable point MOUSE_POINT;

//#############################  unhandled 

static Rectangle recSprite2;
static Rectangle recEntity2;

global_variable vector<pos> Layer1;
global_variable vector<pos> Layer2;

static pos temp = {0, 0};

static int index_counter = 0;

static int added_once = 0;


//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

static int framesCounter;
static int finishScreen;

//----------------------------------------------------------------------------------
//  Variables Definition
//----------------------------------------------------------------------------------

static Rectangle panelRec2 = {20, 40, 200, 150};
static Rectangle panelContentRec2 = {0, 0, 340, 340};
static Vector2 panelScroll2 = {99, -20};

static Rectangle ctrlvalue = {0, 0, 0, 0};

static float fix_offset_x = 0;
static float fix_offset_y = 0;

static Rectangle recSprite = {64, 0, 64, 32};

static Rectangle recEntity = {0, 0, 0, 0};

static bool global_render = false;

static Vector2 global_vec = {0, 0};

static Rectangle global_temp1 = {-100, -100, 0, 0};

static Rectangle global_temp2 = {-100, -100, 0, 0};

static Rectangle gui_temp = {0, 0, 100, 18};

static bool on_field = false;

static bool MoveLogic_collision = false;

#define GLOBALS_H
#endif
#pragma once
