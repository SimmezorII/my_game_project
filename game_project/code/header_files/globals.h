

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

global_variable int gamescreen_offset_x = GAME_TILE_WIDTH;
global_variable int gamescreen_offset_y = GAME_TILE_HEIGHT;

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
} Pat;

global_variable enum {
  BLUE_TILE = 1,
  GREEN_TILE = 2,
  RED_TILE = 3,
  YELLOW_TILE = 4
} Col;

global_variable bool DEBUG_PRINT = false;

global_variable int TARGET_FPS = 120;

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

// old global_variable vector<string> png_list;

// old global_variable vector<string> gui_png_list;

// old global_variable string all_png_list;

// old global_variable string sprite_png_list;


//old global_variable vector<texture> gui_texture_list;

// old global_variable vector<Image> game_image_list;

// old global_variable vector<Image> game_imagecopy_list;

// old global_variable vector<texture> text_texture_list;

// old global_variable vector<sprite> sprite_list;

// old global_variable vector<entity> entity_list;
 
global_variable vector<entity> gui_entity_list;

//global_variable vector<entity> GameState.Map.EntityList;

global_variable vector<entity> new_entity_list;

global_variable vector<entity *> game_entity_list;

global_variable vector<tile> colored_moved_tiles;

global_variable vector<tile> colored_enemy_tiles;

global_variable vector<tile> spawn_tiles;

global_variable vector<combatant> combatant_list;

global_variable vector<combatant> enemy_list;

global_variable vector<text> text_list;

global_variable vector<Direction> move_list;

global_variable bool moving = false;

global_variable bool enemy_moving = false;

global_variable int index_count = 0;

global_variable int temp_movecount[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

global_variable int X_pressed_count = 0;

global_variable int Z_pressed_count = 0;

// global_variable int sum_of_field_tiles;

global_variable int tile_width = GAME_TILE_WIDTH;

global_variable int tile_height = GAME_TILE_HEIGHT;

global_variable int player_entity_ID = -1;

global_variable combatant player;

global_variable combatant world_player;

global_variable Rectangle last_tile = {-100, -100, 0, 0};

global_variable vector<string> sprite_lines;

global_variable vector<string> entity_lines;

global_variable vector<string> map_lines;

global_variable vector<string> map_tiled_lines;

global_variable vector<string> debug_info_lines;

global_variable vector<string> log_lines;

global_variable vector<string> debuglog_lines;

global_variable vector<Render_List> render_list;

global_variable vector<RenderObject *> SortedRenderObject_list;

global_variable vector<RenderObject *> SortedRenderObject_list_2;

global_variable vector<field *> fields;

global_variable int last_sorted_list[4000];

// global_variable unsigned int objects_to_render = 0;

global_variable vector<int> objects_to_render;

global_variable unsigned int entity_count = 0;

global_variable int combatant_selected = -1;

global_variable gui GameGui = {0, 0, false};

global_variable vector<Rectangle> ActionMenuRects;

global_variable bool action_menu_up = false;

global_variable int NumOfActionMenuButtons = 12;

global_variable bool move_field_up = false;

global_variable bool target_field_up = false;

global_variable bool render_entity_boxes = false;

global_variable bool combat = false;

global_variable bool precombat = false;

global_variable bool draw_fields = false;

global_variable bool attacking = false;

global_variable bool toggle_enemy_movefields = false;

global_variable float input_delay = 0.1;

global_variable entity *game_entity;

global_variable entity *new_game_entity;

global_variable entity *target;

global_variable Rectangle *action_target;

global_variable field target_field;

global_variable field attack_target_field;
global_variable field attack_field;

global_variable Rectangle action_target_rect;

global_variable int top_button_index = 1;

global_variable int currentbutton_index = 1;

global_variable RenderObject AllRenderObjects[2048][4];

global_variable Font font;
global_variable Music music;
global_variable Sound fxCoin;

global_variable float GUI_ACTION_BUTTON_HEIGHT = 20;

global_variable float GUI_ACTION_BUTTON_WIDTH = 48;

global_variable int right_vel = (GAME_TILE_WIDTH / 2);
global_variable int left_vel = -(GAME_TILE_WIDTH / 2);
global_variable int up_vel = -(GAME_TILE_HEIGHT / 2);
global_variable int down_vel = (GAME_TILE_HEIGHT / 2);

global_variable int LogScrollCounter = 99;

global_variable int currentline_log = 0;

global_variable int DebugLogScrollCounter = 99;

global_variable int currentline_debuglog = 0;

global_variable int logreset = 0;

global_variable int game_turn = 0;

global_variable bool PLAYER_TURN = true;

global_variable int num_of_added = 1;

global_variable string string_cords[40][20];

global_variable int cords[40][20][10];

global_variable pos pos_cords[40][20];

global_variable int row = 0;

global_variable float entity_offset_y = 0;
global_variable float entity_offset_x = 0;

global_variable int GRID_SPRITE_ID = 29;

global_variable int RENDER_INDEX = 0;

global_variable int CURRENT_LAYER = 0;

/// PLAYER STATS

global_variable int player_max_hp = 200;

global_variable int player_current_hp = player_max_hp;

global_variable float player_attack = 20;

global_variable float player_defense = 20;

/// ENEMY STATS

global_variable int enemy_max_hp = 400;

global_variable int enemy_current_hp = enemy_max_hp;

global_variable float enemy_attack = 20;

global_variable float enemy_defense = 20;

/////////////////////////////////////////////////////

global_variable bool player_animation = true;

global_variable vector<Direction> enemy_movelist;

global_variable Shader shader;

global_variable bool collision_map = false;

global_variable vector<point> ellipses_point;

global_variable tile_triangles temp4;

global_variable field position_field;

global_variable field spawn_field;

global_variable field enemy_move_field;

global_variable field enemy_move_field_two;

global_variable vector<bool> collision_arry;

#define GLOBALS_H
#endif
#pragma once
