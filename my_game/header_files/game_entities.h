#pragma once

#if !defined(GAME_ENTITIES_H)
/* ========================================================================

======================================================================== */
#include <string>
#include <vector>
#include "raylib.h"


using namespace std;


enum CollisionEffect {
  COLLISION = 0,
  NO_COLLISION = 1,
  UP_LAYER = 10,
  DOWN_LAYER = 11,
  UP_TWO_LAYER = 12,
  DOWN_TWO_LAYER = 13,

};



struct win32_window_dimension {
  int Width;
  int Height;
};

struct color {
  int r;
  int g;
  int b;
};

struct texture {
  int w;
  int h;

  Texture2D tex;

  std::string path;
  int img_array_index;

  // SDL_Texture* sdl_texture;
};

struct text {
  int x;
  int y;
  int fontsize;

  color txt_color;
  //	texture tex;
  //	std::string txt;
};

struct sprite {
  int ID;
  int tex_ID;

  std::string name;

  int x;
  int y;
  int w;
  int h;

  int offset_x;
  int offset_y;

  int index;

  std::string img;
};

struct point {
  float x;
  float y;
};

struct ellipse {

  point center;

  float w;
  float h;

  bool is_on_ellipse(point p) {
    return std::pow(p.x - center.x, 2) / std::pow(h, 2) +
               std::pow(p.y - center.y, 2) / std::pow(w, 2) ==
           1.0;
  }

  bool is_inside_ellipse(point p) {
    return std::pow(p.x - center.x, 2) / std::pow(h, 2) +
               std::pow(p.y - center.y, 2) / std::pow(w, 2) <
           1.0;
  }
};

struct entity {
  int ID;
  float x;
  float y;
  float w;
  float h;

  sprite *sprite;

  float alpha = 1;

  Rectangle entity_tile = {x, y, w, h};

  Rectangle offset_rect;

  bool render_this = true;
  bool use_shader = false;

  float offset_x;
  float offset_y;

  int layer = 0;

  ellipse el;
  int coll_check_type = 0;
  int collision_effect = 0;
};

struct pos {
  float x;  // index
  float y;  // index
  float screen_x;
  float screen_y;
  int index;
};

struct tile {
  int x;
  int y;
  int w;
  int h;

  sprite *sprite;

  bool render = false;
};

struct tile_rect {
  float line_1_p1_x;
  float line_1_p1_y;

  float line_1_p2_x;
  float line_1_p2_y;

  float line_2_p1_x;
  float line_2_p1_y;

  float line_2_p2_x;
  float line_2_p2_y;

  float line_3_p1_x;
  float line_3_p1_y;

  float line_3_p2_x;
  float line_3_p2_y;

  float line_4_p1_x;
  float line_4_p1_y;

  float line_4_p2_x;
  float line_4_p2_y;
};

struct tile_triangles {
  float tri_1_line_1_x;
  float tri_1_line_1_y;

  float tri_1_line_2_x;
  float tri_1_line_2_y;

  float tri_1_line_3_x;
  float tri_1_line_3_y;

  float tri_2_line_1_x;
  float tri_2_line_1_y;

  float tri_2_line_2_x;
  float tri_2_line_2_y;

  float tri_2_line_3_x;
  float tri_2_line_3_y;

  float tri_3_line_1_x;
  float tri_3_line_1_y;

  float tri_3_line_2_x;
  float tri_3_line_2_y;

  float tri_3_line_3_x;
  float tri_3_line_3_y;

  float tri_4_line_1_x;
  float tri_4_line_1_y;

  float tri_4_line_2_x;
  float tri_4_line_2_y;

  float tri_4_line_3_x;
  float tri_4_line_3_y;
};

struct target {
  entity *pEntity;

  bool is_on_move_field = false;
  bool is_attacking = false;

  int right_vel = 0;
  int left_vel = 0;
  int up_vel = 0;
  int down_vel = 0;
};

struct field {
  int range;
  int type;
  int x;
  int y;

  int w;
  int h;

  tile tiles[1024];

  int sum_of_field_tiles;

  bool render_field = false;

  float field_alpha = 1;

  vector<tile> track_tiles;

  vector<tile> collision_tiles;

  int last_tile_x = -10000;
  int last_tile_y = -10000;
};

struct stats {
  float MaxHP = 0;
  float CurrentHP = 0;
  float Attack = 0;
  float Defence = 0;
};

struct combatant {
  int move_range;

  int attack_range;

  int current_movecount = 0;
  int current_steps = 0;

  entity *pEntity;

  sprite unique_sprite;

  std::vector<int> movelist;

  field move_field;
  field attack_field;
  field position_field;

  stats Stats = {200, 200, 20, 20};

  bool EllipsePointsCollisions[12] = {false, false, false, false, false, false,
                                      false, false, false, false, false, false};

  int EllipsePointsCollisionsType[12];

  vector<point> EllipsePoints;

  int x_vel;
  int y_vel;

  ellipse roaming_ellipse;

  vector<entity*> EntitiesVicinity;

};

struct enemy {
  int max_hp;
  int current_hp;
};

struct RenderObject {
  Texture2D texture;
  Rectangle source;
  Rectangle dest;
  Vector2 origin;
  float rotation;

  Color tint;

  int layer = -1;
  bool render_this = false;
  bool use_shader = false;
  //	float offset_x;
  //	float offset_y;
};

struct Render_List {
  std::vector<RenderObject *> List;

  bool render_this = false;
};



struct gui {
  float x;
  float y;
  bool visable;

  vector<entity> EntityList;
};

struct menu {
  int X_COUNT = 0;
  int Z_COUNT = 0;

  int MOVE_COUNT = 1;

  vector<Rectangle> MenuRects;

  bool is_menu_up = false;

  bool is_pre_state = false;

  int MaxButtons;
  int TopButtonIndex = 1;
  int CurrentButtonIndex = 1;

  Rectangle MenuTarget;
};

struct map {
  vector<entity> EntityList;

  // vector<tile> ColoredMovedTiles;

  vector<combatant> CombatantList;
  vector<combatant> EnemyList;

  int CurrentRow = 0;
  int CurrentLayer = 0;

  int Cords[40][20][10];
  string StringCords[40][20];
  pos PosCords[40][20];
};

struct resource {
  vector<string> SpriteLines;
  vector<string> EntityLines;

  // Unused
  vector<string> MapLines;

  vector<string> MapLinesTiledFormat;

  vector<string> DebugInfoLines;
};

struct editor {
  int NumOfAdded = 1;
  entity *GameEntity;
};

struct game_state {
  int GAME_TURN = 0;
  bool PLAYER_TURN = true;

  int RENDER_INDEX = 0;

  bool InitCombat = false;

  bool AnimatingMovement = false;
  bool AnimatingEnemyMovement = false;

  int CurrentLayerList[1000];

  int ObjectsToRender[10];

  resource Resources;
  vector<int> MoveList;

  // List of .png files loaded for the game
  vector<string> PNGList;

  // List of .png files loaded for the game as long string
  string AllPNGList;

  vector<texture> GameTextureList;
  vector<Image> GameImageList;
  vector<sprite> SpriteList;
  vector<entity> EntityList;

  vector<Render_List> RenderList;

  RenderObject AllRenderObjects[4096][2];

  vector<RenderObject *> SortedRenderObjectList;

  combatant WorldPlayer;
  combatant &CombatantSelected = WorldPlayer;

  vector<field *> FieldList;

  vector<entity*> EntitiesCollision;

  vector<int> CollisionEffects = {COLLISION,  NO_COLLISION, UP_LAYER,
                                  DOWN_LAYER, UP_TWO_LAYER, DOWN_TWO_LAYER};

  target Target;

  gui Gui;
  map Map;
  menu ActionMenu;

  // Editor related functions
  editor Editor;
};





#define GAME_H
#endif
