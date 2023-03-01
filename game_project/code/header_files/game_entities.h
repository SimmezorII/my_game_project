#pragma once

#if !defined(GAME_ENTITIES_H)
/* ========================================================================

======================================================================== */
#include <string>
#include "globals.h"

struct win32_window_dimension
{
	int Width;
	int Height;
};

struct color
{
	int r;
	int g;
	int b;
};

struct texture
{
	int w;
	int h;

	Texture2D tex;

	std::string path;

	// SDL_Texture* sdl_texture;
};

struct text
{

	int x;
	int y;
	int fontsize;

	color txt_color;
	//	texture tex;
	//	std::string txt;
};

struct gui
{

	float x;
	float y;
	bool visable;
};

struct sprite
{

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

struct stats
{

	float max_hp;
	float current_hp;
	float defence;
	float attack;
};

struct entity
{

	int ID;
	float x;
	float y;
	float w;
	float h;

	sprite *sprite;

	Rectangle entity_tile = {x, y, 64, 32};

	Rectangle offset_rect;

	bool render_this = true;

	float offset_x;
	float offset_y;

	stats entity_stats = {200, 200, 20, 20};
};

struct pos
{

	float x; // index
	float y; // index
	float screen_x;
	float screen_y;
	int index;
};

struct tile
{

	int x;
	int y;
	int w;
	int h;

	sprite *sprite;
};

struct tile_rect
{
	int line_1_p1_x;
	int line_1_p1_y;

	int line_1_p2_x;
	int line_1_p2_y;

	int line_2_p1_x;
	int line_2_p1_y;

	int line_2_p2_x;
	int line_2_p2_y;

	int line_3_p1_x;
	int line_3_p1_y;

	int line_3_p2_x;
	int line_3_p2_y;

	int line_4_p1_x;
	int line_4_p1_y;

	int line_4_p2_x;
	int line_4_p2_y;
};

struct tile_triangles
{
	int tri_1_line_1_x;
	int tri_1_line_1_y;

	int tri_1_line_2_x;
	int tri_1_line_2_y;

	int tri_1_line_3_x;
	int tri_1_line_3_y;

	int tri_2_line_1_x;
	int tri_2_line_1_y;

	int tri_2_line_2_x;
	int tri_2_line_2_y;

	int tri_2_line_3_x;
	int tri_2_line_3_y;

	int tri_3_line_1_x;
	int tri_3_line_1_y;

	int tri_3_line_2_x;
	int tri_3_line_2_y;

	int tri_3_line_3_x;
	int tri_3_line_3_y;

	int tri_4_line_1_x;
	int tri_4_line_1_y;

	int tri_4_line_2_x;
	int tri_4_line_2_y;

	int tri_4_line_3_x;
	int tri_4_line_3_y;
};

struct field
{

	int range;
	int type;
	int x;
	int y;

	int w;
	int h;

	tile tiles[124];

	int sum_of_field_tiles;

	bool render_field = false;
};

struct combatant
{

	int move_range;

	int attack_range;

	int current_movecount = 1;

	entity *pEntity;

	std::vector<int> movelist;
};

struct enemy
{

	int max_hp;
	int current_hp;
};

struct RenderObject
{

	Texture2D texture;
	Rectangle source;
	Rectangle dest;
	Vector2 origin;
	float rotation;
	Color tint;
	int layer = -1;
	bool render_this = false;
	//	float offset_x;
	//	float offset_y;
};

struct Render_List
{

	std::vector<RenderObject *> List;

	bool render_this = false;
};

#define GAME_H
#endif
