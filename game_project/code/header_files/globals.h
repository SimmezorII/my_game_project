

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

global_variable int gamescreen_offset_x = 64;
global_variable int gamescreen_offset_y = 32;

global_variable enum { TITLE = 0, OPTIONS, GAMEPLAY, ENDING, GUI } GameScreen;

global_variable enum Direction { UP = 0, DOWN, LEFT, RIGHT } Dir;

global_variable enum  { SQUARE = 0, NON_ISO_SQUARE = 1, LINE = 2, CROSS = 3 , CHECKERED_SQURE = 4, TRIANGLE = 10, CONE = 20 } Pat;

global_variable enum { BLUE_TILE = 1, GREEN_TILE = 2, RED_TILE = 3,  YELLOW_TILE = 4 } Col;


global_variable  int currentScreen = 0;

//global_variable SDL_Window* game_window = NULL;
//
//global_variable SDL_Renderer* GAME_RENDERER = NULL;

global_variable  int GAMEWINDOW_WIDTH = 1600;
global_variable  int GAMEWINDOW_HEIGHT = 940;

global_variable  int GRID_WIDTH = 1280;
global_variable  int GRID_HEIGHT = 640;

// This path is relative to the .exe file
global_variable char cstrGAME_ASSET_PATH[100] = "resources\\assets\\game\\";

global_variable char cstrGUI_ASSET_PATH[100] = "resources\\assets\\gui\\";

global_variable char cstrMAPS_PATH[100] = "resources\\assets\\textfiles\\";


global_variable string GAME_ASSET_PATH = "resources\\assets\\game\\";

global_variable string GUI_ASSET_PATH = "resources\\assets\\gui\\";

global_variable string MAPS_PATH = "resources\\assets\\textfiles\\";

//global_variable TTF_Font *GAME_FONT = NULL;

global_variable int FONT_SIZE = 10;

//global_variable SDL_Color TEXT_COLOR;

global_variable vector <string> png_list;

global_variable vector <string> gui_png_list;

global_variable string all_png_list;

global_variable string sprite_png_list;

global_variable win32_window_dimension window;

global_variable vector<texture> entity_texture_list;

global_variable vector<texture> gui_texture_list;

global_variable vector<texture> text_texture_list;

global_variable vector<sprite>	sprite_list;

global_variable vector<entity>	entity_list;

global_variable vector<entity>	gui_entity_list;

global_variable vector<entity>	map_entity_list;

global_variable vector<entity>	new_entity_list;

global_variable vector<entity *>	game_entity_list;

global_variable vector<tile>	colored_moved_tiles;

global_variable vector<tile>	colored_enemy_tiles;

global_variable vector<tile>	spawn_tiles;

global_variable vector<combatant>	combatant_list;

global_variable vector<combatant>	enemy_list;

global_variable vector<text>	text_list;

global_variable vector<Direction>	move_list;

global_variable bool moving = false;

global_variable int index_count = 0;

global_variable int temp_movecount[10] = { 1,1,1,1,1,1,1,1,1,1};

global_variable int X_pressed_count = 0;

global_variable int Z_pressed_count = 0;

//global_variable int sum_of_field_tiles;

global_variable int tile_width = 64;

global_variable int tile_height = 32;

global_variable int player_entity_ID = -1;

global_variable combatant player;

global_variable combatant world_player;

global_variable Rectangle last_tile = { -100,-100,0,0 };

global_variable vector<string> sprite_lines;

global_variable vector<string> entity_lines;

global_variable vector<string> map_lines;

global_variable vector<string> debug_info_lines;

global_variable vector<string> log_lines;

global_variable vector<string> debuglog_lines;

global_variable vector< Render_List > render_list;

global_variable vector< RenderObject *> SortedRenderObject_list;


global_variable int last_sorted_list[2000];

//global_variable unsigned int objects_to_render = 0;

global_variable vector<int> objects_to_render;

global_variable unsigned int entity_count = 0;

global_variable int combatant_selected = -1;

global_variable gui GameGui = { 0,0, false };

global_variable vector<Rectangle> ActionMenuRects;

global_variable bool ActionMenuUp = false;

global_variable int NumOfActionMenuButtons = 12;

global_variable bool move_field_up = false;

global_variable bool target_field_up = false;

global_variable bool render_entity_boxes = false;

global_variable bool combat = false;

global_variable bool precombat = false;

global_variable bool draw_fields = false;

global_variable bool attacking = false;

global_variable float input_delay = 0.1;

global_variable entity * game_entity;

global_variable entity * new_game_entity;

global_variable entity * target;

global_variable Rectangle * action_target;

global_variable field target_field;

global_variable Rectangle action_target_rect;

global_variable int top_button_index = 1;

global_variable int currentbutton_index = 1;

global_variable RenderObject AllRenderObjects[1024];

global_variable Font font;
global_variable Music music;
global_variable Sound fxCoin;

global_variable float GUI_ACTION_BUTTON_HEIGHT = 20;

global_variable float GUI_ACTION_BUTTON_WIDTH = 48;

global_variable int right_vel = 32;
global_variable int left_vel = -32;
global_variable int up_vel = -16;
global_variable int down_vel = 16;

global_variable vector<pos> Layers[80];

global_variable int LogScrollCounter = 99;

global_variable int currentline_log = 0;

global_variable int DebugLogScrollCounter = 99;

global_variable int currentline_debuglog = 0;

global_variable int logreset = 0;

global_variable int game_turn = 0;

global_variable bool PLAYER_TURN = false;

global_variable int num_of_added = 1;

global_variable string string_cords[40][20];

global_variable int cords[40][20];

global_variable pos pos_cords[40][20];

global_variable int row = 0;

global_variable float entity_offset_y = 0;
global_variable float entity_offset_x = 0;

global_variable int GRID_SPRITE_ID = 29;


/// PLAYER STATS 

global_variable int player_max_hp = 200;

global_variable int player_current_hp  = player_max_hp;

global_variable float player_attack = 20;

global_variable float player_defense = 20;


/// ENEMY STATS

global_variable int enemy_max_hp = 400;

global_variable int enemy_current_hp = enemy_max_hp;

global_variable float enemy_attack = 20;

global_variable float enemy_defense = 20;


#define GLOBALS_H
#endif
#pragma once
