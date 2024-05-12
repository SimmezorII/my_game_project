/* ========================================================================

======================================================================== */

#pragma once

#ifndef game_engine_cpp
#define game_engine_cpp

#include <iostream>
#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"

// #include "code/header_files/raygui.h"
#include "../header_files/globals.h"
#include "../header_files/game_entities.h"
#include "../header_files/game_engine_func.h"

// #include "code/header_files/screens.h"

using namespace std;

//========================================================================

#define internal static
#define local_persist static
#define global_variable static

// Used by ColorFieldTileEntityList, reset with MovePressed
static bool enemy_colored = false;
static int entity_checked = 0;

inline bool Init(int width, int height, char title[])
{

	InitWindow(width, height, title);

	return 0;
}

inline texture myLoadTexture(std::string path)
{
	Texture2D temp = { 0 };

	texture myTemp = { 0, 0, 0, 0 };

	temp = LoadTexture(path.c_str());
	if (temp.id != 0)
	{
		myTemp.tex = temp;
		myTemp.w = temp.width;
		myTemp.h = temp.height;
		myTemp.path = path;
	}
	else
	{
		printf("Unable to create texture from %s\n", path.c_str());
	}

	return myTemp;
}

inline texture myLoadTextureFromImage(std::string path)
{
	texture myTemp = { 0, 0, 0, 0 };

	Image imOrigin = LoadImage(path.c_str());   // Loaded in CPU memory (RAM)

    ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);         // Format image to RGBA 32bit (required for texture update) <-- ISSUE

    Texture2D temp = LoadTextureFromImage(imOrigin);    // Image converted to texture, GPU memory (VRAM)

    Image imCopy = ImageCopy(imOrigin);

	game_image_list.push_back(imOrigin);
	game_imagecopy_list.push_back(imCopy);

	temp = LoadTextureFromImage(imOrigin);
	if (temp.id != 0)
	{
		myTemp.tex = temp;
		myTemp.w = temp.width;
		myTemp.h = temp.height;
		myTemp.path = path;
		myTemp.img_array_index = game_image_list.size()-1;
	}
	else
	{
		printf("Unable to create texture from %s\n", path.c_str());
	}

	return myTemp;
}



inline void CreateTextTexture_No_GlobalFont(Font font, std::string TextureText, Color TextColor)
{
	// texture temp;
	// return temp;
}

inline void CreateTextTexture(std::string TextureText)
{
	// texture temp;

	//

	////Return success
	// return temp;
}

inline void AddText(std::string msg, int x, int y)
{

	// text txt;

	// txt.fontsize = FONT_SIZE;
	// txt.x = x;
	// txt.y = y;

	// txt.tex = CreateTextTexture(msg);

	// text_list.push_back(txt);
}

inline int GetIndexForTexture(string pngname)
{

	// return -1 if no texture found;
	int index = -1;

	for (size_t i = 0; i < png_list.size(); i++)
	{
		if (!png_list[i].find(pngname))
		{

			index = i;
			break;
		}
	}

	return index;
}

inline bool LoadFont(Font font)
{
	bool success = true;

	return success;
}

inline bool GUI_CreateTextures()
{
	// Loading success flag
	bool success = true;

	for (size_t i = 0; i < png_list.size(); i++)
	{
		texture temp = myLoadTexture(GUI_ASSET_PATH + png_list[i]);

		gui_texture_list.push_back(temp);
	}

	cout << "entity texture list: " << gui_texture_list.size() << endl;

	return success;
}

inline bool GAME_CreateTextures()
{
	// Loading success flag
	bool success = true;

	for (size_t i = 0; i < png_list.size(); i++)
	{

		texture temp = myLoadTexture(GAME_ASSET_PATH + png_list[i]);

		gui_texture_list.push_back(temp);
	}
	cout << "entity texture list: " << gui_texture_list.size() << endl;

	return success;
}

inline bool GAME_CreateTexturesFromImage()
{
	// Loading success flag
	bool success = true;

	for (size_t i = 0; i < png_list.size(); i++)
	{
		texture temp = myLoadTextureFromImage(GAME_ASSET_PATH + png_list[i]);

		gui_texture_list.push_back(temp);
	}
	cout << "entity texture list: " << gui_texture_list.size() << endl;

	return success;
}




inline void SetSpriteTextures()
{
	for (size_t n = 0; n < sprite_list.size(); n++)
	{
		for (size_t i = 0; i < gui_texture_list.size(); i++)
		{
			if (gui_texture_list[i].path.find(sprite_list[n].img) != std::string::npos)
			{

				sprite_list[n].index = i;
				break;
			}
			else
			{
				// sprite_list[n].index = 0;
			}
		}
	}
}

inline void setSprite(entity& e, string sprite_name)
{

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_name.compare(sprite_list[i].name) == 0)
		{
			// cout << "Sprite found " << sprite_list[i].img << endl;

			e.sprite = &sprite_list[i];
		}
	}
}
inline void setSprite(entity& e, int sprite_ID)
{

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].ID == sprite_ID)
		{
			// cout << "Sprite found " << sprite_list[i].img << endl;

			e.sprite = &sprite_list[i];
			break;
		}
	}
}

inline sprite& getSprite(string sprite_name)
{

	for (size_t i = 0; i < sprite_list.size(); i++)
	{

		if (sprite_name.compare(sprite_list[i].name) == 0)
		{
			cout << "getEnityByID entity found " << entity_list[i].ID << endl;

			return sprite_list[i];
			break;
		}
	}

	printf("Sprite with name %s could not be found, returned first sprite in list", sprite_name.c_str());
	return sprite_list[0];
}

inline sprite& getSprite(int sprite_ID)
{

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].ID == sprite_ID)
		{
			// cout << "Sprite found " << sprite_list[i].img << endl;

			return sprite_list[i];
			break;
		}
	}

	return sprite_list[0];
}

// TODO: Checking against entity x/y, perhaps should use entity_tile instead
inline entity* getEntityByPosition(int pos_x, int pos_y, vector<entity*> entities)
{

	cout << "This happens getEntityByPosition star" << endl;

	cout << "pos x" << pos_x;
	cout << "pos y" << pos_y;

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (entities[i]->entity_tile.x == pos_x && entities[i]->entity_tile.y == pos_y)
		{
			cout << "---------------------------------------------------------" << endl;
			cout << "getEnityByPosition X entity found " << entities[i]->x << endl;
			cout << "getEnityByPosition Y entity found " << entities[i]->y << endl;
			cout << "getEnityByPosition tile X entity found " << entities[i]->entity_tile.x << endl;
			cout << "getEnityByPosition tile Y entity found " << entities[i]->entity_tile.y << endl;

			return entities[i];
		}
	}

	return entities[0];
}

// TODO: Checking against entity x/y, perhaps should use entity_tile instead
inline entity& getEntityByPosition(int pos_x, int pos_y, vector<entity>& entities)
{

	cout << "This happens getEntityByPosition ref" << endl;

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (entities[i].x == pos_x && entities[i].y == pos_y)
		{
			cout << "getEnityByPosition entity found " << endl;

			cout << "getEnityByPosition X entity found " << entities[i].x << endl;
			cout << "getEnityByPosition Y entity found " << entities[i].y << endl;
			cout << "getEnityByPosition tile X entity found " << entities[i].entity_tile.x << endl;
			cout << "getEnityByPosition tile Y entity found " << entities[i].entity_tile.y << endl;

			cout << "sprite name: " << entities[i].sprite->name << endl;

			return entities[i];
		}
	}

	return entities[0];
}

inline entity& getEntityByID(int entity_ID, vector<entity>& entities)
{

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (entities[i].ID == entity_ID)
		{
			cout << "getEnityByID entity found " << entity_list[i].ID << endl;

			return entities[i];
		}
	}

	return entities[0];
}

inline entity& getEntityByID(string sprite_name, vector<entity>& entities)
{

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (sprite_name.compare(entities[i].sprite->name) == 0)
		{
			cout << "getEnityByID entity found " << entity_list[i].ID << endl;

			return entities[i];
		}
	}

	cout << "getEnityByID entity not found " << entity_list[0].ID << endl;

	return entities[0];
}

inline entity* getEntityByID(int entity_ID, vector<entity*> entities)
{
	cout << "Trying to find ID: " << entity_ID << endl;

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (entities[i]->ID == entity_ID)
		{

			cout << "getEnityByID entity found " << entities[i]->ID << endl;

			return entities[i];
		}else
		{
			cout << "getEnityByID else entity found " << entities[i]->ID << endl;
		}
	}

	// Log(entities[0]->sprite->name);

	cout << "getEnityByID entity not found, instead set to first with ID: " << entities[0]->ID << endl;

	return entities[0];
}

Rectangle tempcheckrect = { 0, 0, 0, 0 };

Rectangle& getEntityRect(entity& e)
{

	tempcheckrect = { (float)(e.x + e.sprite->offset_x), (float)(e.y + e.sprite->offset_y), (float)e.w, (float)e.h };

	return tempcheckrect;
}

inline entity& getEntityByID(int entity_ID)
{

	for (size_t i = 0; i < entity_list.size(); i++)
	{

		if (entity_list[i].ID == entity_ID)
		{
			// cout << "entity found " << entity_list[i].ID << endl;

			return entity_list[i];
		}
	}

	return entity_list[0];
}

Rectangle recSprite2;
Rectangle recEntity2;

global_variable vector<pos> Layer1;
global_variable vector<pos> Layer2;

inline int getCurrentToRender()
{
	cout << "This is called" << endl;

	for (size_t i = 0; i < 1024; i++)
	{
		if (AllRenderObjects[i][0].layer != -1)
		{
			objects_to_render[1]++;
		}
	}
	return 0;
}

pos temp = { 0, 0 };

static int index_counter = 0;

inline void calcDrawLayer(int layer, vector<pos>& poslayer)
{
	int counter = 0;

	// temp.y = 32 * (layer - 1);

	temp.x = 32 * (layer - 1);

	for (size_t i = 0; i < layer - 1; i++)
	{
		counter++;
	}

	for (size_t i = 0; i < layer + counter; i++)
	{
		temp.index = index_counter;

		poslayer.push_back(temp);

		index_counter++;

		temp.y = temp.y + down_vel / 2;
		temp.x = temp.x + left_vel / 2;
	}

	// cout << poslayer.size() << endl;
	temp = { 0, 0 };
}

static int added_once = 0;

inline void RenderEntities(vector<entity>& entities, int render_list_index)
{
	int templayer = 0;

	int lowerlayer = 0;

	int entity_count = 0;

	DebugLog("RenderEntities entities.size(): ", (int)entities.size());

	for (size_t i = 0; i < entities.size(); i++)
	{
		recSprite2 = { (float)entities[i].sprite->x, (float)entities[i].sprite->y, (float)entities[i].sprite->w, (float)entities[i].sprite->h };

		recEntity2 = { (float)entities[i].x + entities[i].sprite->offset_x, /*((-GAME_TILE_HEIGHT / 2)*/  (float)entities[i].y + entities[i].sprite->offset_y, (float)entities[i].w, (float)entities[i].h };

		entities[i].entity_tile.x = entities[i].x;

		entities[i].entity_tile.y = entities[i].y;

		if (entities[i].ID == target->ID)
		{
			lowerlayer = 1;
		}
		else
		{
			lowerlayer = 0;
		}


		templayer = entities[i].y - lowerlayer + (800 * entities[i].layer);

		if (entities[i].ID == 999)
		{
			//	cout << "99 "<< endl;
			templayer = templayer - 30;
		}

		if (entities[i].ID == GRID_SPRITE_ID)
		{
			templayer = templayer -1000;
		}

		AllRenderObjects[i + objects_to_render[render_list_index]][render_list_index] = { getTexture(entities[i].sprite->ID).tex, recSprite2, recEntity2, {0, 0}, 0, WHITE, templayer, entities[i].render_this, entities[i].use_shader };

		if (render_list[render_list_index].List.size() < entities.size() + objects_to_render[render_list_index])
		{
			render_list[render_list_index].List.push_back(&AllRenderObjects[i + objects_to_render[render_list_index]][render_list_index]);
		}
		else
		{
			render_list[render_list_index].List[i + objects_to_render[render_list_index]] = &AllRenderObjects[i + objects_to_render[render_list_index]][render_list_index];
		}

		if (render_entity_boxes == true)
		{
			DrawRectangleLines(entities[i].entity_tile.x, entities[i].entity_tile.y, tile_width, tile_height, BLUE);

			DrawRectangleLines(entities[i].x, entities[i].y, entities[i].w, entities[i].h, RED);

			DrawRectangleLines((float)entities[i].x + entities[i].sprite->offset_x, (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w, entities[i].h, GREEN);
		}
	}

	if (objects_to_render[render_list_index] < objects_to_render[render_list_index] + entities.size())
	{
		objects_to_render[render_list_index] = objects_to_render[render_list_index] + entities.size();
	}
}


inline void RenderEntityBoxes(vector<entity>& entities)
{

	int templayer = 0;

	int lowerlayer = 0;

	int offset_x = 0;
	int offset_y = 0;

	for (size_t i = 0; i < entities.size(); i++)
	{

		recSprite2 = { (float)entities[i].sprite->x, (float)entities[i].sprite->y, (float)entities[i].sprite->w, (float)entities[i].sprite->h };

		recEntity2 = { (float)entities[i].x + entities[i].sprite->offset_x, (float)entities[i].y + entities[i].sprite->offset_y, (float)entities[i].w, (float)entities[i].h };

		entities[i].entity_tile.x = entities[i].x;

		entities[i].entity_tile.y = entities[i].y;

		if (entities[i].w < 500)
		{
			offset_x = (entities[i].w - tile_width) / 2;
		}

		if (entities[i].h < 500)
		{
			offset_y = entities[i].h - (tile_height);
		}

		entities[i].offset_rect = { gamescreen_offset_x + entities[i].x - offset_x, gamescreen_offset_y + entities[i].y - offset_y, entities[i].w, entities[i].h };

		if (ToggleEntityBoxes == true)
		{
			DrawRectangleLines(gamescreen_offset_x + entities[i].x - offset_x, gamescreen_offset_y + entities[i].y - offset_y, entities[i].w, entities[i].h, RED);
			DrawRectangleLines(gamescreen_offset_x + (float)entities[i].x + entities[i].sprite->offset_x, gamescreen_offset_y + (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w, entities[i].h, GREEN);
			DrawRectangleLines(gamescreen_offset_x + entities[i].entity_tile.x, gamescreen_offset_y + entities[i].entity_tile.y, tile_width, tile_height, BLUE);
		}
	}
}

inline void RenderWholeEntity(texture* Texture)
{
}

inline void RenderTextTexture(texture* Texture, int x, int y)
{
}

static int current_frame = 0;

inline void AnimateMovement(entity* en, Direction d)
{

	switch (d)
	{
	case UP:

		en->sprite->x = (current_frame * en->sprite->w);

		en->sprite->y = en->sprite->h * 2;

		current_frame++;

		if (current_frame >= 4)
		{
			current_frame = 0;
		}

		break;

	case DOWN:

		en->sprite->x = (current_frame * en->sprite->w);

		en->sprite->y = 0;

		current_frame++;

		if (current_frame >= 4)
		{
			current_frame = 0;
		}

		break;

	case LEFT:

		en->sprite->x = (current_frame * en->sprite->w);

		en->sprite->y = en->sprite->h * 3;

		current_frame++;

		if (current_frame >= 4)
		{
			current_frame = 1;
		}

		break;

	case RIGHT:

		en->sprite->x = (current_frame * en->sprite->w);

		en->sprite->y = en->sprite->h;

		current_frame++;

		if (current_frame >= 4)
		{
			current_frame = 1;
		}

		break;
	}
}

static int current_frame2 = 0;

static float timer = 0.0f;

static int loop = 0;

inline void PrintMoveList()
{
	for (size_t i = 0; i < move_list.size(); i++)
	{
		switch (move_list[i])
		{
		case UP:

			printf("[UP]");

			break;

		case DOWN:

			printf("[DOWN]");

			break;

		case LEFT:

			printf("[LEFT]");

			break;

		case RIGHT:

			printf("[RIGHT]");

			break;
		}
	}

	printf("\n");
}

inline void Animate(entity* en)
{
	timer += GetFrameTime();

	if (timer >= 0.12)
	{
		timer = 0.0;

		en->sprite->x = (current_frame2 * en->sprite->w);

		// en->sprite->y = en->sprite->h * 2;

		en->sprite->y = 0;

		current_frame2++;

		en->x = en->x + left_vel / 4;
		en->y = en->y + down_vel / 4;

		if (current_frame2 > 5)
		{
			current_frame2 = 0;
		}

		loop++;
	}

	if (loop >= 20)
	{
		en->x = 480;
		en->y = 208;

		loop = 0;
	}
}

inline void MovementAnimated(entity* en)
{
	static int movecount = 0;

	static int steps = 0;

	printf("MovementAnimated: %d\n", movecount);

	if (moving == true)
	{
		if (movecount < move_list.size())
		{

			printf("steps lower than size\n");

			if (move_list[movecount] == LEFT)
			{

				printf("steps LEFT\n");

				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en->sprite->x = (current_frame2 * en->sprite->w);

					en->sprite->y = 0;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en->x = en->x + (left_vel / 2);
					en->y = en->y + (down_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[LEFT]");
					}
				}
			}

			else if (move_list[movecount] == RIGHT)
			{

				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en->sprite->x = (current_frame2 * en->sprite->w);

					en->sprite->y = 2 * en->sprite->h;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en->x = en->x + (right_vel / 2);
					en->y = en->y + (up_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[RIGHT]");
					}
				}
			}
			else if (move_list[movecount] == UP)
			{

				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en->sprite->x = (current_frame2 * en->sprite->w);

					en->sprite->y = 3 * en->sprite->h;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en->x = en->x + (left_vel / 2);
					en->y = en->y + (up_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[UP]");
					}
				}
			}
			else if (move_list[movecount] == DOWN)
			{

				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en->sprite->x = (current_frame2 * en->sprite->w);

					en->sprite->y = 1 * en->sprite->h;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en->x = en->x + (right_vel / 2);
					en->y = en->y + (down_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[DOWN]");
					}
				}
			}
		}
		else
		{
			printf("steps reset\n");
			player_animation = false;
			moving = false;

			if (move_list.back() == LEFT)
			{

				printf("(move_list.back() == LEFT)\n");

				// en->sprite->x = 0;

				// en->sprite->y = 0;
			}
			else if (move_list.back() == RIGHT)
			{
				en->sprite->x = 0;

				en->sprite->y = 2 * en->sprite->h;
			}
			else if (move_list.back() == UP)
			{

				en->sprite->x = 0;

				en->sprite->y = 3 * en->sprite->h;
			}
			else if (move_list.back() == DOWN)
			{
				en->sprite->x = 0;

				en->sprite->y = 1 * en->sprite->h;
			}

			steps = 0;
			movecount = 0;

			move_list.clear();
		}
	}
}

inline void EnemyMovementAnimated()
{

	static int movecount = 0;

	static int steps = 0;

	static int enemy_checked = 0;

	combatant& en = enemy_list[enemy_checked];

	if (!en.movelist.empty())
	{
		if (movecount < en.movelist.size())
		{
			if (en.movelist[movecount] == LEFT)
			{
				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);

					en.pEntity->sprite->y = 0;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en.pEntity->x = en.pEntity->x + (left_vel / 2);
					en.pEntity->y = en.pEntity->y + (down_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[LEFT]");
					}
				}
			}

			else if (en.movelist[movecount] == RIGHT)
			{

				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);

					en.pEntity->sprite->y = 2 * en.pEntity->sprite->h;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en.pEntity->x = en.pEntity->x + (right_vel / 2);
					en.pEntity->y = en.pEntity->y + (up_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[RIGHT]");
					}
				}
			}
			else if (en.movelist[movecount] == UP)
			{

				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);

					en.pEntity->sprite->y = 3 * en.pEntity->sprite->h;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en.pEntity->x = en.pEntity->x + (left_vel / 2);
					en.pEntity->y = en.pEntity->y + (up_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[UP]");
					}
				}
			}
			else if (en.movelist[movecount] == DOWN)
			{
				timer += GetFrameTime();

				if (timer >= 0.12)
				{
					timer = 0.0;

					/// Animation

					en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);

					en.pEntity->sprite->y = 1 * en.pEntity->sprite->h;

					current_frame2++;

					if (current_frame2 > 5)
					{
						current_frame2 = 0;
					}

					//// Movement

					steps++;

					en.pEntity->x = en.pEntity->x + (right_vel / 2);
					en.pEntity->y = en.pEntity->y + (down_vel / 2);

					if (steps == 2)
					{
						movecount++;
						steps = 0;
						printf("[DOWN]");
					}
				}
			}
		}
		else
		{
			printf(" enemy steps reset");

			if (!en.movelist.empty())
			{
				if (en.movelist.back() == LEFT)
				{
					en.pEntity->sprite->x = 0;

					en.pEntity->sprite->y = 0;
				}
				else if (en.movelist.back() == RIGHT)
				{
					en.pEntity->sprite->x = 0;

					en.pEntity->sprite->y = 2 * en.pEntity->sprite->h;
				}
				else if (en.movelist.back() == UP)
				{

					en.pEntity->sprite->x = 0;

					en.pEntity->sprite->y = 3 * en.pEntity->sprite->h;
				}
				else if (en.movelist.back() == DOWN)
				{
					en.pEntity->sprite->x = 0;

					en.pEntity->sprite->y = 1 * en.pEntity->sprite->h;
				}
			}

			steps = 0;
			movecount = 0;
			en.movelist.clear();

			enemy_checked++;
		}
	}
	else
	{
		enemy_checked++;
	}

	if (enemy_checked >= enemy_list.size())
	{
		enemy_checked = 0;
		enemy_moving = false;
	}
}

inline void RenderTextList()
{

	for (size_t i = 0; i < text_list.size(); i++)
	{
	}
}

Rectangle infoRect = { (GameGui.x - 200), GameGui.y, 100, 16 };

// inline void RendedDebugInfo()
//{
//	//strdup(game_entity->sprite->name.c_str()
//
//
//	infoRect.x = (GameGui.x);
//
//	infoRect.y = 20 ;
//
//	for (size_t i = 0; i < debug_info_lines.size(); i++)
//	{
//		GuiLabel({ infoRect.x, infoRect.y +( i * infoRect.height), infoRect.width, infoRect.height }, debug_info_lines[i].c_str());
//		//GuiTextBox({ infoRect.x, infoRect.y + (i * infoRect.height) +12, infoRect.width, infoRect.height }, strdup(debug_info_lines[i].c_str()), 12, false);
//	}
//
//	debug_info_lines[6] = "tempint : ";
//	debug_info_lines[6].append(to_string(LogScrollCounter));
// }

inline void DisplayEntityInfo(entity game_entity, int x, int y)
{

	// AddText("Entity ID: " + to_string(game_entity.ID), x, y + (1 * FONT_SIZE));
	// AddText("Entity x:" + to_string(game_entity.x), x, y + (2 * FONT_SIZE));
	// AddText("Entity y:" + to_string(game_entity.y), x, y + (3 * FONT_SIZE));
	// AddText("Entity w:" + to_string(game_entity.w), x, y + (4 * FONT_SIZE));
	// AddText("Entity h:" + to_string(game_entity.h), x, y + (5 * FONT_SIZE));

	// AddText("sprite ID:" + to_string(game_entity.sprite.img_ID), x, y + (6 * FONT_SIZE));
	// AddText("sprite name:", x, y + (7 * FONT_SIZE));
	// AddText("" + (game_entity.sprite.img), x, y + (8 * FONT_SIZE));
	// AddText("sprite x:" + to_string(game_entity.sprite.x), x, y + (9 * FONT_SIZE));
	// AddText("sprite y:" + to_string(game_entity.sprite.y), x, y + (10 * FONT_SIZE));
	// AddText("sprite w:" + to_string(game_entity.sprite.w), x, y + (11 * FONT_SIZE));
	// AddText("sprite h:" + to_string(game_entity.sprite.h), x, y + (12 * FONT_SIZE));
}

inline bool CheckCollisionRects(Rectangle a, Rectangle b)
{
	// The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	// Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.width;
	topA = a.y;
	bottomA = a.y + a.height;

	// Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.width;
	topB = b.y;
	bottomB = b.y + b.height;

	// If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	// If none of the sides from A are outside B
	return true;
}

inline bool CheckCollisionMouseEntity()
{
	bool ret = false;

	float mouseX = GetMouseX(); // Returns mouse position X
	float mouseY = GetMouseY();

	Rectangle mouseRect = { mouseX, mouseY, 1, 1 };
	//	Rectangle tempEntityRect;

	for (size_t i = 0; i < entity_list.size(); i++)
	{
		Rectangle tempEntityRect = { entity_list[i].x, entity_list[i].y, entity_list[i].w, entity_list[i].h };

		if (CheckCollisionRects(mouseRect, tempEntityRect))
		{
			// printf("Collision with Entity: %d", entity_list[i].ID);

			ret = true;
		}
	}

	return ret;
}

float offset = 4;

inline void InitActionMenu()
{

	Rectangle temp;

	temp = { 0, 0, (float)((GUI_ACTION_BUTTON_WIDTH) * 1.5), ((GUI_ACTION_BUTTON_HEIGHT)+offset / 2) * NumOfActionMenuButtons };

	ActionMenuRects.push_back(temp);

	temp = { 0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	action_target = &action_target_rect;
}

inline void setActionMenu()
{
	float EntityX = 0;
	float EntityY = 0;
	float EntityW = 0;
	float EntityH = 0;

	if (combatant_selected > -1)
	{

		EntityX = combatant_list[combatant_selected].pEntity->x;
		EntityY = combatant_list[combatant_selected].pEntity->y;
		EntityW = combatant_list[combatant_selected].pEntity->w;
		EntityH = combatant_list[combatant_selected].pEntity->h;
	}
	else
	{
	}

	// This is the Action menu box/panel
	ActionMenuRects[0].x = (float)(EntityX + (EntityW * 2.5)) + 20;
	ActionMenuRects[0].y = (float)(EntityY - (EntityH * 0.5)) + 16;

	for (size_t i = 1; i < ActionMenuRects.size(); i++)
	{
		ActionMenuRects[i].x = (float)(EntityX + (EntityW * 2.5)) + 4 + 20;
		ActionMenuRects[i].y = (float)(EntityY - (EntityH * 0.5)) + (i * GUI_ACTION_BUTTON_HEIGHT);
	}

	action_target->x = ActionMenuRects[currentbutton_index].x;
	action_target->y = ActionMenuRects[currentbutton_index].y;
}

inline bool setMouseEntity()
{

	bool ret = false;

	float mouseX = GetMouseX();
	float mouseY = GetMouseY();

	Rectangle mouseRect = { mouseX, mouseY, 1, 1 };
	//	Rectangle tempEntityRect;

	for (size_t i = 0; i < entity_list.size(); i++)
	{

		if (CheckCollisionRects(mouseRect, getEntityRect(entity_list[i])) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			// printf("Collision with Entity: %d", entity_list[i].ID);

			game_entity = &entity_list[i];

			ret = true;
		}
	}

	return ret;
}

inline bool setMouseEntity(vector<entity>& entities)
{

	bool ret = false;

	float mouseX = GetMouseX() - gamescreen_offset_x;
	float mouseY = GetMouseY() - gamescreen_offset_y;

	Rectangle mouseRect = { mouseX, mouseY, 1, 1 };
	//	Rectangle tempEntityRect;

	for (size_t i = 0; i < entities.size(); i++)
	{
		Rectangle tempEntityRect = { (float)entities[i].x + entities[i].sprite->offset_x, (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w, entities[i].h };

		if (CheckCollisionRects(mouseRect, tempEntityRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			// printf("Collision with Entity: %d", entity_list[i].ID);

			game_entity = &entities[i];

			ret = true;
		}
	}

	return ret;
}

/////-------------------------------------------------  RenderField -------------------------------------------

Rectangle recSprite = { 64, 0, 64, 32 };

Rectangle recEntity = { 0, 0, 0, 0 };

Vector2 vec = { 0, 0 };

bool render = false;

inline void SetRenderField(field* fieldRef, bool render)
{
	int tiles = *(&fieldRef->tiles + 1) - fieldRef->tiles;
	for (size_t i = 0; i < tiles; i++)
	{
		fieldRef->tiles[i].render = render;
	}
}


inline void RenderAllFields()
{
	int render_list_index = 0;
	int diff = 0;

	for (size_t n = 0; n < fields.size(); n++)
	{
		for (size_t i = 0; i < fields[n]->sum_of_field_tiles; i++)
		{
			recEntity = { (float)(fields[n]->tiles[i].x), (float)(fields[n]->tiles[i].y), (float)tile_width, (float)tile_height };

			recSprite = { (float)(fields[n]->tiles[i].sprite->x), (float)(fields[n]->tiles[i].sprite->y), (float)fields[n]->tiles[i].sprite->w, (float)fields[n]->tiles[i].sprite->h };

			if ((fields[n]->tiles[i].render == true) && (fields[n]->render_field == true))
			{
				render = true;
			}
			else
			{
				render = false;
			}

			AllRenderObjects[i + objects_to_render[render_list_index]][render_list_index] = { getTexture(fields[n]->tiles[i].sprite->ID).tex, recSprite, recEntity, vec, 0, Fade(WHITE, fields[n]->field_alpha), -60,render };

			if (render_list[render_list_index].List.size() < fields[n]->sum_of_field_tiles + objects_to_render[render_list_index])
			{
				render_list[render_list_index].List.push_back(&AllRenderObjects[i + objects_to_render[render_list_index]][render_list_index]);
			}
			else
			{
				render_list[render_list_index].List[i + objects_to_render[render_list_index]] = &AllRenderObjects[i + objects_to_render[render_list_index]][render_list_index];
				diff = (int)render_list[render_list_index].List.size() - (fields[n]->sum_of_field_tiles + objects_to_render[render_list_index]);
			}
		}

		if (objects_to_render[render_list_index] < objects_to_render[render_list_index] + fields[n]->sum_of_field_tiles)
		{
			objects_to_render[render_list_index] = objects_to_render[render_list_index] + fields[n]->sum_of_field_tiles;
		}
	}

	for (size_t j = 0; j < diff; j++)
	{
		render_list[render_list_index].List[((render_list[render_list_index].List.size()) - diff) + j]->render_this = false;
	}
}



inline void swap(RenderObject xp, RenderObject yp)
{
	RenderObject temp = xp;
	xp = yp;
	yp = temp;
}

static bool sorted = false;

static int firstround = 0;

static int secondround = 0;
inline void SortLayerRenderObjectList()
{
	RenderObject temp;

	int i = 0;
	int j = 0;
	int n = SortedRenderObject_list.size();

	int num_of_lists = 0;
	int list_index = 0;
	int count = 0;

	int newlist_size = 0;

	for (num_of_lists = 0; num_of_lists < render_list.size(); num_of_lists++)
	{
		for (list_index = 0; list_index < render_list[num_of_lists].List.size(); list_index++)
		{
			newlist_size++;
		}
	}

	DebugLog(" SortedRenderObject_list.size():", (int)SortedRenderObject_list.size());
	DebugLog("newlist_size:", newlist_size);

	// cout << newlist_size << endl;

	for (num_of_lists = 0; num_of_lists < render_list.size(); num_of_lists++)
	{
		//cout << render_list[num_of_lists].List.size() << " ";

		for (list_index = 0; list_index < render_list[num_of_lists].List.size(); list_index++)
		{
			if (SortedRenderObject_list.size() < newlist_size)
			{
				SortedRenderObject_list.push_back(render_list[num_of_lists].List[list_index]);

				last_sorted_list[i] = SortedRenderObject_list[i]->layer;
				i++;
			}
			else
			{
				SortedRenderObject_list[count] = render_list[num_of_lists].List[list_index];
				count++;
			}
		}
	}
	// cout << SortedRenderObject_list.size() << endl;

	if (sorted == false)
	{

		// cout << "start sorting" << endl;

		for (i = 0; i < n - 1; i++)
		{
			for (j = 0; j < n - i - 1; j++)
			{

				if (SortedRenderObject_list[j]->layer > SortedRenderObject_list[j + 1]->layer)
				{
					swap(SortedRenderObject_list[j], SortedRenderObject_list[j + 1]);
				}
				else
				{
				}
			}
		}

		for (i = 0; i < SortedRenderObject_list.size(); i++)
		{
			last_sorted_list[i] = SortedRenderObject_list[i]->layer;

			// cout << last_sorted_list[i] << " ";
		}

		// cout << endl;
	}
	else
	{
		for (i = 0; i < SortedRenderObject_list.size(); i++)
		{
			if (SortedRenderObject_list.empty() != true)
			{

				if (last_sorted_list[i] != SortedRenderObject_list[i]->layer)
				{
					// cout << last_sorted_list[i] << " " << SortedRenderObject_list[i]->layer;
					sorted = false;

					break;
				}
			}
		}
	}

	for (i = 0; i < SortedRenderObject_list.size(); i++)
	{
		if (SortedRenderObject_list.empty() != true)
		{

			last_sorted_list[i] = SortedRenderObject_list[i]->layer;
		}
	}

	if (firstround == 0)
	{
		firstround++;
	}
	else if (firstround == 1)
	{
		firstround++;
		sorted = true;
	}
	else
	{
	}
	if (sorted == false)
	{
	}
}

inline void SortLayerRenderObjectList(Render_List& render_list, vector<RenderObject*>& Sortedlist)
{
	RenderObject temp;

	int i = 0;
	int j = 0;
	int n = Sortedlist.size();

	int num_of_lists = 0;
	int list_index = 0;
	int count = 0;

	for (list_index = 0; list_index < render_list.List.size(); list_index++)
	{
		if (Sortedlist.size() < render_list.List.size())
		{
			Sortedlist.push_back(render_list.List[list_index]);

			last_sorted_list[i] = Sortedlist[i]->layer;
			i++;
		}
		else
		{
			Sortedlist[count] = render_list.List[list_index];
			count++;
		}
	}

	if (sorted == false)
	{
		for (i = 0; i < n - 1; i++)
		{
			for (j = 0; j < n - i - 1; j++)
			{

				if (Sortedlist[j]->layer > Sortedlist[j + 1]->layer)
				{
					swap(Sortedlist[j], Sortedlist[j + 1]);
				}
				else
				{
				}
			}
		}
		for (i = 0; i < Sortedlist.size(); i++)
		{
			last_sorted_list[i] = Sortedlist[i]->layer;
		}
	}
	else
	{
		for (i = 0; i < Sortedlist.size(); i++)
		{
			if (Sortedlist.empty() != true)
			{
				if (last_sorted_list[i] != Sortedlist[i]->layer)
				{
					sorted = false;
					break;
				}
			}
		}
	}

	for (i = 0; i < Sortedlist.size(); i++)
	{
		if (Sortedlist.empty() != true)
		{
			last_sorted_list[i] = Sortedlist[i]->layer;
		}
	}

	if (firstround == 0)
	{
		firstround++;
	}
	else if (firstround == 1)
	{
		firstround++;
		sorted = true;
	}
	else
	{
	}
	if (sorted == false)
	{

	}
}



inline void RenderAllLayers()
{
	float offset_x = 0;
	float offset_y = 0;

	float dest_x = 0;

	float dest_y = 0;

	int render_count = 0;

	DebugLog("SortedRenderObject_list: ", (int)SortedRenderObject_list.size());

	for (size_t i = 0; i < SortedRenderObject_list.size(); i++)
	{
		if (SortedRenderObject_list[i] != NULL)
		{
			if (SortedRenderObject_list[i]->render_this == true)
			{
				render_count++;
				if (SortedRenderObject_list[i]->dest.width < 500)
				{
					offset_x = (SortedRenderObject_list[i]->dest.width - tile_width) / 2;
				}

				if (SortedRenderObject_list[i]->dest.height < 500)
				{
					offset_y = SortedRenderObject_list[i]->dest.height - (tile_height);
				}

				if (SortedRenderObject_list[i]->texture.id == getSprite(GRID_SPRITE_ID).tex_ID)
				{
					offset_x = 0;

					offset_y = 0;
				}

				dest_x = SortedRenderObject_list[i]->dest.x + gamescreen_offset_x - offset_x;

				dest_y = SortedRenderObject_list[i]->dest.y + gamescreen_offset_y - offset_y;

				DrawTexturePro(SortedRenderObject_list[i]->texture, SortedRenderObject_list[i]->source,
					{ dest_x, dest_y, SortedRenderObject_list[i]->dest.width, SortedRenderObject_list[i]->dest.height },
					SortedRenderObject_list[i]->origin, SortedRenderObject_list[i]->rotation, SortedRenderObject_list[i]->tint);
			}
		}
	}

	DebugLog("render_count: ", render_count);
}


inline void RenderAllLayers(vector<RenderObject*>& RenderObjectList)
{
	float offset_x = 0;
	float offset_y = 0;

	float dest_x = 0;

	float dest_y = 0;

	int render_count = 0;

	DebugLog("RenderObjectList: ", (int)RenderObjectList.size());

	for (size_t i = 0; i < RenderObjectList.size(); i++)
	{
		if (RenderObjectList[i] != NULL)
		{
			if (RenderObjectList[i]->render_this == true)
			{
				render_count++;
				if (RenderObjectList[i]->dest.width < 500)
				{
					offset_x = (RenderObjectList[i]->dest.width - tile_width) / 2;
				}

				if (RenderObjectList[i]->dest.height < 500)
				{
					offset_y = RenderObjectList[i]->dest.height - (tile_height);
				}

				if (RenderObjectList[i]->texture.id == getSprite(GRID_SPRITE_ID).tex_ID)
				{
					offset_x = 0;

					offset_y = 0;
				}

				dest_x = RenderObjectList[i]->dest.x + gamescreen_offset_x - offset_x;

				dest_y = RenderObjectList[i]->dest.y + gamescreen_offset_y - offset_y;


				if ( RenderObjectList[i]->use_shader == true)
				{
					BeginShaderMode(shader);
				}else
				{
					EndShaderMode();
				}
				
				DrawTexturePro(RenderObjectList[i]->texture, RenderObjectList[i]->source,
					{ dest_x, dest_y, RenderObjectList[i]->dest.width, RenderObjectList[i]->dest.height },
					RenderObjectList[i]->origin, RenderObjectList[i]->rotation, RenderObjectList[i]->tint);
			}
		}
	}

	DebugLog("render_count: ", render_count);
}



/////----------------------------------------------------------------------------------------------------

Rectangle temp1 = { -100, -100, 0, 0 };

Rectangle temp2 = { -100, -100, 0, 0 };

void CycleColoredTiles(entity* target, vector<tile>& colored_tiles)
{
	static int index = 0;

	if (IsKeyPressed(KEY_RIGHT))
	{
		if (index < colored_tiles.size() - 1) {
			index++;
		}
		else
		{
			index = 0;
		}
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		if (index > 0) {
			index--;
		}
		else
		{
			index = colored_tiles.size() - 1;
		}
	}

	if (IsKeyPressed(KEY_UP))
	{
		if (index < colored_tiles.size() - 1) {
			index++;
		}
		else
		{
			index = 0;
		}
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		if (index > 0) {
			index--;
		}
		else
		{
			index = colored_tiles.size() - 1;
		}
	}

	//cout << "index:" << index << endl;
	//cout << " colored_tiles[index].x:" << colored_tiles[index].x << endl;

	target->x = colored_tiles[index].x;
	target->y = colored_tiles[index].y;
}



/////-------------------------------------------------  ColorFieldTile -------------------------------------------



inline void SetFieldTileColors(field& fieldRef, int Sprite_ID)
{
	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		target_field.tiles[i].sprite = &getSprite(Sprite_ID);
	}
}

inline bool ColorFieldTileEntityList(vector<tile>& colored_tiles, field* fieldRef, vector<combatant>& list, int iTileColor)
{
	bool colored_tile = false;

	Rectangle temp1 = { -100, -100, 0, 0 };
	Rectangle temp2 = { -100, -100, 0, 0 };

	tile temptile;

	if (colored_tiles.empty())
	{
		for (size_t i = 0; i < list.size(); i++)
		{
			temp2 = { list[i].pEntity->x, list[i].pEntity->y, list[i].pEntity->w, list[i].pEntity->h };
			if (list[i].pEntity->x == combatant_list[combatant_selected].pEntity->x && list[i].pEntity->y == combatant_list[combatant_selected].pEntity->y)
			{
				// cout << "Player X Y" << endl;
			}
			else
			{
				if (enemy_colored == false)
				{
					for (size_t j = 0; j < fieldRef->sum_of_field_tiles; j++)
					{
						temp1 = { (float)(fieldRef->tiles[j].x), (float)(fieldRef->tiles[j].y), (float)tile_width, (float)tile_height };

						if (
							CheckCollisionRecs(
								{ (float)(temp2.x - 1 + (tile_width / 2)), (float)(temp2.y - 1 + (tile_height / 2)), 2, 2 },
								{ (float)(temp1.x - 1 + (tile_width / 2)), (float)(temp1.y - 1 + (tile_height / 2)), 2, 2 }))
						{
							fieldRef->tiles[j].sprite = &getSprite(iTileColor);

							colored_tiles.push_back(fieldRef->tiles[j]);

							colored_tile = true;

							cout << "coloured tile 1 " << i << endl;
						}
						else
						{
						}
					}

					if (entity_checked >= list.size())
					{
						enemy_colored = true;
					}
					else
					{
						entity_checked++;
					}
				}
			}
		}

	}
	else
	{
		for (size_t i = 0; i < list.size(); i++)
		{
			temp2 = { list[i].pEntity->x, list[i].pEntity->y, list[i].pEntity->w, list[i].pEntity->h };
			if (list[i].pEntity->x == combatant_list[combatant_selected].pEntity->x && list[i].pEntity->y == combatant_list[combatant_selected].pEntity->y)
			{
				// cout << "Player X Y" << endl;
			}
			else
			{
				if (enemy_colored == false)
				{
					for (size_t j = 0; j < fieldRef->sum_of_field_tiles; j++)
					{
						temp1 = { (float)(fieldRef->tiles[j].x), (float)(fieldRef->tiles[j].y), (float)tile_width, (float)tile_height };

						if (
							CheckCollisionRecs(
								{ (float)(temp2.x - 1 + (tile_width / 2)), (float)(temp2.y - 1 + (tile_height / 2)), 2, 2 },
								{ (float)(temp1.x - 1 + (tile_width / 2)), (float)(temp1.y - 1 + (tile_height / 2)), 2, 2 }))
						{
							fieldRef->tiles[j].sprite = &getSprite(iTileColor);

							if (fieldRef->tiles[j].x == colored_tiles[i].x && fieldRef->tiles[j].y == colored_tiles[i].y)
							{
								colored_tiles[i].sprite = &getSprite(iTileColor);
							}
							else
							{
								colored_tiles.push_back(fieldRef->tiles[j]);
							}

							colored_tile = true;

							cout << "coloured tile 2 " << i << endl;
						}
						else
						{
						}
					}

					if (entity_checked >= list.size())
					{
						enemy_colored = true;
					}
					else
					{
						entity_checked++;
					}
				}
			}
		}
	}

	return colored_tile;

}

inline bool ColorFieldTileEntityList(vector<tile>& colored_tiles, field* fieldRef, vector<entity>& entity_list, int iTileColor)
{
	bool colored_tile = false;

	Rectangle temp2;
	tile temptile;

	for (size_t i = 0; i < entity_list.size(); i++)
	{
		temp2 = { (float)entity_list[i].x, (float)entity_list[i].y, (float)entity_list[i].w, (float)entity_list[i].h };

		if (entity_list[i].x == combatant_list[combatant_selected].pEntity->x && entity_list[i].y == combatant_list[combatant_selected].pEntity->y)
		{
			// cout << "Player X Y" << endl;
		}
		else
		{
			// Check layer
			if (combatant_list[combatant_selected].pEntity->layer != entity_list[i].layer)
			{

			}
			else
			{
				if (enemy_colored == false)
				{
					for (size_t j = 0; j < fieldRef->sum_of_field_tiles; j++)
					{
						temp1 = { (float)(fieldRef->tiles[j].x), (float)(fieldRef->tiles[j].y), (float)tile_width, (float)tile_height };

						if (
							CheckCollisionRecs(
								{ (float)(temp2.x - 1 + (tile_width / 2)), (float)(temp2.y - 1 + (tile_height / 2)), 2, 2 },
								{ (float)(temp1.x - 1 + (tile_width / 2)), (float)(temp1.y - 1 + (tile_height / 2)), 2, 2 }))
						{

							if (last_tile.x != temp2.x || last_tile.y != temp2.y)
							{
								fieldRef->tiles[j].sprite = &getSprite(iTileColor); // red tile

								colored_enemy_tiles.push_back(fieldRef->tiles[j]);

								last_tile = { temp2.x, temp2.y, 0, 0 };

								colored_tile = true;
							}
							else
							{
							}
						}
						else
						{
						}
					}

					if (entity_checked >= entity_list.size())
					{
						enemy_colored = true;
					}
					else
					{
						entity_checked++;
					}
				}
			}



		}
	}

	return colored_tile;
}

inline bool ColorFieldTile(field& fieldRef, entity* target)
{
	bool colored_tile = false;

	temp2 = { (float)target->x, (float)target->y, (float)target->w, (float)target->h };

	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		temp1 = { (float)(fieldRef.tiles[i].x), (float)(fieldRef.tiles[i].y), (float)tile_width, (float)tile_height };

		if (
			CheckCollisionRecs(
				{ (float)(temp2.x - 1 + (tile_width / 2)), (float)(temp2.y - 1 + (tile_height / 2)), 2, 2 },
				{ (float)(temp1.x - 1 + (tile_width / 2)), (float)(temp1.y - 1 + (tile_height / 2)), 2, 2 }))
		{
			if (last_tile.x != temp2.x || last_tile.y != temp2.y)
			{
				fieldRef.tiles[i].sprite = &getSprite(YELLOW_TILE); // red tile
				fieldRef.tiles[i].render = true;
				colored_moved_tiles.push_back(fieldRef.tiles[i]);

				last_tile = { temp2.x, temp2.y, 0, 0 };

				colored_tile = true;

				// cout << "colored_moved_tiles.push_back(temptile);" << endl;

				break;
			}
			else
			{
			}
		}
		else
		{
		}
	}

	return colored_tile;
}

inline void ResetMovedTilesColor(field& fieldRef, int Sprite_ID)
{
	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{

		for (size_t j = 0; j < colored_moved_tiles.size(); j++)
		{
			// cout << "same2" << endl;

			if (fieldRef.tiles[i].x == colored_moved_tiles[j].x && fieldRef.tiles[i].y == colored_moved_tiles[j].y)
			{
				// cout << "same3" << endl;
				fieldRef.tiles[i].sprite = &getSprite(Sprite_ID);
				fieldRef.tiles[i].render = true;
			}
		}
	}
}

inline bool IsInArray(int* Array, int Size, int number)
{
	bool result = false;
	// int arraySize = sizeof(Array) / sizeof(Array[0]);

	for (size_t i = 0; i < Size; i++)
	{
		if (Array[i] == number)
		{
			result = true;
			break;
		}
	}

	return result;
}

inline void randomSpawnTile(field& fieldRef, field& spawn_field)
{
	int numOfTiles = 10;
	int randomTilesIndex[124];

	int temp = -99;

	int temp2 = -99;

	float tempvar;

	if (fieldRef.sum_of_field_tiles != 0)
	{
		for (size_t i = 0; i < numOfTiles; i++)
		{

			temp = GetRandomValue(0, (fieldRef.sum_of_field_tiles - 1));

			while (IsInArray(randomTilesIndex, i, temp))
			{
				temp2 = GetRandomValue(0, (fieldRef.sum_of_field_tiles - 1));

				temp = temp2;
			}

			randomTilesIndex[i] = temp;
		}

		cout << "fieldRef.sum_of_field_tiles " << fieldRef.sum_of_field_tiles;

		cout << endl;

		for (size_t k = 0; k < numOfTiles; k++)
		{
			cout << randomTilesIndex[k] << " ";
		}

		cout << endl;

		spawn_field.sum_of_field_tiles = numOfTiles;

		spawn_field.h = 0;
		spawn_field.w = 0;

		spawn_field.x = 0;
		spawn_field.y = 0;

		for (int i = 0; i < numOfTiles; i++)
		{
			tempvar = fieldRef.tiles[randomTilesIndex[i]].h;

			spawn_field.tiles[i].h = tempvar;
			tempvar = fieldRef.tiles[randomTilesIndex[i]].w;

			spawn_field.tiles[i].w = tempvar;

			tempvar = fieldRef.tiles[randomTilesIndex[i]].x;
			spawn_field.tiles[i].x = tempvar;

			tempvar = fieldRef.tiles[randomTilesIndex[i]].y;
			spawn_field.tiles[i].y = tempvar;

			spawn_field.tiles[i].sprite = &getSprite(BLUE_TILE);
		}

		cout << endl;
		cout << "Fields set " << fieldRef.sum_of_field_tiles << " " << spawn_field.sum_of_field_tiles << endl;
	}
	else
	{
		cout << "Fields not set " << fieldRef.sum_of_field_tiles << " " << spawn_field.sum_of_field_tiles << endl;
	}
}

inline void drawIsoTriangles(entity* e)
{

	// temp3 = getTileRect(e->entity_tile);

	// DrawLine(temp3.line_1_p1_x, temp3.line_1_p1_y, temp3.line_1_p2_x, temp3.line_1_p2_y, BLUE);
	// DrawLine(temp3.line_2_p1_x, temp3.line_2_p1_y, temp3.line_2_p2_x, temp3.line_2_p2_y, RED);
	// DrawLine(temp3.line_3_p1_x, temp3.line_3_p1_y, temp3.line_3_p2_x, temp3.line_3_p2_y, GREEN);
	// DrawLine(temp3.line_4_p1_x, temp3.line_4_p1_y, temp3.line_4_p2_x, temp3.line_4_p2_y, ORANGE);

	temp4 = getTileTriangles(e->entity_tile);

	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	p1.x = temp4.tri_1_line_1_x;
	p1.y = temp4.tri_1_line_1_y;

	p2.x = temp4.tri_1_line_2_x;
	p2.y = temp4.tri_1_line_2_y;

	p3.x = temp4.tri_1_line_3_x;
	p3.y = temp4.tri_1_line_3_y;

	DrawTriangle(p1, p2, p3, BLUE);

	p1.x = temp4.tri_2_line_1_x;
	p1.y = temp4.tri_2_line_1_y;

	p2.x = temp4.tri_2_line_2_x;
	p2.y = temp4.tri_2_line_2_y;

	p3.x = temp4.tri_2_line_3_x;
	p3.y = temp4.tri_2_line_3_y;

	DrawTriangle(p1, p2, p3, RED);

	p1.x = temp4.tri_3_line_1_x;
	p1.y = temp4.tri_3_line_1_y;

	p2.x = temp4.tri_3_line_2_x;
	p2.y = temp4.tri_3_line_2_y;

	p3.x = temp4.tri_3_line_3_x;
	p3.y = temp4.tri_3_line_3_y;

	DrawTriangle(p1, p2, p3, GREEN);

	p1.x = temp4.tri_4_line_1_x;
	p1.y = temp4.tri_4_line_1_y;

	p2.x = temp4.tri_4_line_2_x;
	p2.y = temp4.tri_4_line_2_y;

	p3.x = temp4.tri_4_line_3_x;
	p3.y = temp4.tri_4_line_3_y;

	DrawTriangle(p1, p2, p3, ORANGE);
}

inline void drawInnerIsoRect(entity* e)
{

	// temp3 = getTileInnerRect(e->entity_tile);

	// DrawLine(temp3.line_1_p1_x, temp3.line_1_p1_y, temp3.line_1_p2_x, temp3.line_1_p2_y, YELLOW);
	// DrawLine(temp3.line_2_p1_x, temp3.line_2_p1_y, temp3.line_2_p2_x, temp3.line_2_p2_y, YELLOW);
	// DrawLine(temp3.line_3_p1_x, temp3.line_3_p1_y, temp3.line_3_p2_x, temp3.line_3_p2_y, YELLOW);
	// DrawLine(temp3.line_4_p1_x, temp3.line_4_p1_y, temp3.line_4_p2_x, temp3.line_4_p2_y, YELLOW);
}

inline void InitDebugLog()
{

	string temp;

	for (size_t i = 0; i < 100; i++)
	{

		temp = "Log line " + to_string(i);

		debuglog_lines.push_back(temp);
	}
}

inline void InitLog()
{

	string temp;

	for (size_t i = 0; i < 100; i++)
	{

		temp = "Log line " + to_string(i);

		log_lines.push_back(temp);
	}
}

#endif