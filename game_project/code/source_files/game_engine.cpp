/* ========================================================================

======================================================================== */

#pragma once

#ifndef game_engine_cpp
#define game_engine_cpp


#include <iostream>
#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"

//#include "code/header_files/raygui.h"
#include "../header_files/globals.h"
#include "../header_files/game_entities.h"


//#include "code/header_files/screens.h"

using namespace std;

//========================================================================

#define internal static 
#define local_persist static 
#define global_variable static

static tile_triangles temp4;

//Used by ColorFieldTileEntityList, reset with MovePressed
 static bool enemy_colored = false;
 static int entity_checked = 0;


inline void Log(string text, float value)
{
	if (currentline_log != 0)
	{
		if (log_lines[currentline_log - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}
	else
	{
		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}


	if (currentline_log >= 100)
	{
		logreset++;
		currentline_log = 0;
	}

	//tempint = currentline_log;
}


inline void Log(string text, int value)
{
	if (currentline_log != 0)
	{
		if (log_lines[currentline_log - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}
	else
	{
		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}


	if (currentline_log >= 100)
	{
		logreset++;
		currentline_log = 0;
	}

	//tempint = currentline_log;
}

inline void Log(string text)
{
	if (currentline_log != 0)
	{
		if (log_lines[currentline_log - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		log_lines[currentline_log] = text;


		currentline_log++;
	}
	else
	{
		log_lines[currentline_log] = text;


		currentline_log++;
	}


	if (currentline_log >= 100)
	{
		logreset++;
		currentline_log = 0;
	}

	//tempint = currentline_log;
}



inline void DebugLog(string text)
{
	bool stringfound = false;
	int tempindex = -1;

	if (currentline_debuglog != 0)
	{
		for (size_t i = 0; i < currentline_debuglog; i++)
		{
			if (debuglog_lines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			debuglog_lines[tempindex] = text;
		}
		else
		{
			debuglog_lines[currentline_debuglog] = text;
			currentline_debuglog++;
		}

	}
	else
	{
		debuglog_lines[currentline_debuglog] = text;
		currentline_debuglog++;
	}


}

inline void DebugLog(string text, float value)
{
	bool stringfound = false;
	int tempindex = -1;

	if (currentline_debuglog != 0)
	{
		for (size_t i = 0; i < currentline_debuglog; i++)
		{
			if (debuglog_lines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			debuglog_lines[tempindex] = text;
			debuglog_lines[tempindex].append(to_string(value));
		}
		else
		{
			debuglog_lines[currentline_debuglog] = text;
			debuglog_lines[currentline_debuglog].append(to_string(value));
			currentline_debuglog++;
		}

	}
	else
	{
		debuglog_lines[currentline_debuglog] = text;
		debuglog_lines[currentline_debuglog].append(to_string(value));
		currentline_debuglog++;
	}


}


inline void DebugLog(string text, int value)
{
	bool stringfound = false;
	int tempindex = -1;

	if (currentline_debuglog != 0)
	{
		for (size_t i = 0; i < currentline_debuglog; i++)
		{
			if (debuglog_lines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			debuglog_lines[tempindex] = text;
			debuglog_lines[tempindex].append(to_string(value));
		}
		else
		{
			debuglog_lines[currentline_debuglog] = text;
			debuglog_lines[currentline_debuglog].append(to_string(value));
			currentline_debuglog++;
		}

	}
	else
	{
		debuglog_lines[currentline_debuglog] = text;
		debuglog_lines[currentline_debuglog].append(to_string(value));
		currentline_debuglog++;
	}


}




inline bool Init(int width, int height, char title[]) {

	InitWindow(width, height, title);


	return 0;
}


inline texture& getTexture(string sprite_name)
{

	string temp_img = "";

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].name == sprite_name)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			temp_img = sprite_list[i].img;
			break;
		}
	}



	for (size_t n = 0; n < gui_texture_list.size(); n++)
	{
		//	cout << "Path found " << gui_texture_list[n].path << endl;

		std::size_t found = gui_texture_list[n].path.find(temp_img);
		if (found != std::string::npos)
		{
			//cout << "Texture found " << gui_texture_list[n].path << endl;

			return gui_texture_list[n];
			break;
		}
	}

	return gui_texture_list[0];
}


inline texture& getTexture(int sprite_ID)
{

	string temp_img = "";

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].ID == sprite_ID)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			temp_img = sprite_list[i].img;
			break;
		}
	}



	for (size_t n = 0; n < gui_texture_list.size(); n++)
	{
		//	cout << "Path found " << gui_texture_list[n].path << endl;

		std::size_t found = gui_texture_list[n].path.find(temp_img);
		if (found != std::string::npos)
		{
			//cout << "Texture found " << gui_texture_list[n].path << endl;

			return gui_texture_list[n];
			break;
		}
	}

	return gui_texture_list[0];
}


inline texture myLoadTexture(std::string path)
{
	Texture2D temp = { 0 };

	texture myTemp = { 0,0,0,0};

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


inline void CreateTextTexture_No_GlobalFont(Font font, std::string TextureText, Color TextColor)
{
	//texture temp;
	//return temp;
}

inline void CreateTextTexture(std::string TextureText)
{
	//texture temp;

	//

	////Return success
	//return temp;
}

inline void AddText(std::string msg, int x, int y) {

	//text txt;

	//txt.fontsize = FONT_SIZE;
	//txt.x = x;
	//txt.y = y;

	//txt.tex = CreateTextTexture(msg);

	//text_list.push_back(txt);

}



inline int GetIndexForTexture(string pngname) {

	// return -1 if no texture found;
	int index = -1;

	for (size_t i = 0; i < png_list.size(); i++)
	{
		if (!png_list[i].find(pngname)) {

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
	//Loading success flag
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
	//Loading success flag
	bool success = true;

	for (size_t i = 0; i < png_list.size(); i++)
	{

		texture temp = myLoadTexture(GAME_ASSET_PATH + png_list[i]);

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
			if (gui_texture_list[i].path.find(sprite_list[n].img) != std::string::npos) {

				sprite_list[n].index = i;
				break;
			}
			else 
			{
				//sprite_list[n].index = 0;
			}
		}
	}
}


inline void setSprite(entity &e, string sprite_name)
{

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].name == sprite_name)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			e.sprite = &sprite_list[i];

		}
	}
}
inline void setSprite(entity &e, int sprite_ID)
{

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].ID == sprite_ID)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			e.sprite = &sprite_list[i];
			break;
		}
	}
}

inline sprite& getSprite(string sprite_name) {

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].name == sprite_name)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			return sprite_list[i];
			break;
		}
	}

	return sprite_list[0];
}

inline sprite& getSprite(int sprite_ID) {

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].ID == sprite_ID)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			return sprite_list[i];
			break;
		}
	}

	return sprite_list[0];
}



inline entity& getEnityByID(int entity_ID, vector<entity> &entities) {

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


inline entity& getEnityByID(string sprite_name, vector<entity>& entities) {

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (sprite_name.compare(entities[i].sprite->name) == 0)
		{
			cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx getEnityByID entity found " << entity_list[i].ID << endl;

			return entities[i];
		}

	}

	cout << "getEnityByID entity not found " << entity_list[0].ID << endl;


	return entities[0];
}




inline entity* getEnityByID(int entity_ID, vector<entity *> entities) {

	for (size_t i = 0; i < entities.size(); i++)
	{

		if (entities[i]->ID == entity_ID)
		{

			//Log(entities[i]->sprite->name);

			return entities[i];
		}

	}

	//Log(entities[0]->sprite->name);

	return entities[0];
}



 Rectangle tempcheckrect = { 0,0,0,0 };

 Rectangle & getEntityRect(entity & e){

	tempcheckrect = { (float)(e.x + e.sprite->offset_x), (float)(e.y +e.sprite->offset_y),(float)e.w, (float)e.h };

	return tempcheckrect;
}


inline entity& getEnityByID(int entity_ID) {

	for (size_t i = 0; i < entity_list.size(); i++)
	{

		if (entity_list[i].ID == entity_ID)
		{
			//cout << "entity found " << entity_list[i].ID << endl;

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
		if (AllRenderObjects[i].layer != -1) {
			objects_to_render[1]++;
		}
	
	}
	return 0;
}


 pos temp = { 0,0 };

static int index_counter = 0;

inline void calcDrawLayer(int layer, vector<pos> &poslayer)
{
	int counter = 0;
	

	//temp.y = 32 * (layer - 1);

	temp.x = 32 * (layer - 1);

	for (size_t i = 0; i < layer-1; i++)
	{
		counter++;
	}


	for (size_t i = 0; i < layer+ counter; i++)
	{
		temp.index = index_counter;

		poslayer.push_back(temp);

		index_counter++;

		temp.y = temp.y + down_vel/2;
		temp.x = temp.x + left_vel/2;

	}

	//cout << poslayer.size() << endl;
	temp = { 0,0 };
}

inline void RenderGuiEntities() {


	//// Rectangle type
	//typedef struct Rectangle {
	//	float x;
	//	float y;
	//	float width;
	//	float height;
	//} Rectangle;

	//// N-Patch layout info
	//typedef struct NPatchInfo {
	//	Rectangle source;       // Texture source rectangle
	//	int left;               // Left border offset
	//	int top;                // Top border offset
	//	int right;              // Right border offset
	//	int bottom;             // Bottom border offset
	//	int layout;             // Layout of the n-patch: 3x3, 1x3 or 3x1
	//} NPatchInfo;

	int  templayer = 0;

	int lowerlayer = 0;
	
	for (size_t i = 0; i < gui_entity_list.size(); i++)
	{

		Vector2 vec = { 0 , 0 };

		recSprite2 = { (float)gui_entity_list[i].sprite->x, (float)gui_entity_list[i].sprite->y,(float)gui_entity_list[i].sprite->w,(float)gui_entity_list[i].sprite->h };

		recEntity2 = { (float)gui_entity_list[i].x + gui_entity_list[i].sprite->offset_x , (float)gui_entity_list[i].y + gui_entity_list[i].sprite->offset_y, (float)gui_entity_list[i].w, (float)gui_entity_list[i].h };
		
		gui_entity_list[i].entity_tile.x = gui_entity_list[i].x;

		gui_entity_list[i].entity_tile.y = gui_entity_list[i].y;

		DrawRectangleLines(gui_entity_list[i].entity_tile.x, gui_entity_list[i].entity_tile.y, tile_width ,tile_height, BLUE);

		DrawRectangleLines(gui_entity_list[i].x, gui_entity_list[i].y, gui_entity_list[i].w, gui_entity_list[i].h, RED);

		DrawRectangleLines((float)gui_entity_list[i].x + gui_entity_list[i].sprite->offset_x, (float)gui_entity_list[i].y + gui_entity_list[i].sprite->offset_y, gui_entity_list[i].w, gui_entity_list[i].h, GREEN);
		

		if (gui_entity_list[i].ID == target->ID)
		{
			lowerlayer = 1;
		}
		else
		{
			lowerlayer = 0;
		}

		templayer = gui_entity_list[i].y - lowerlayer;

		AllRenderObjects[i] = { getTexture(gui_entity_list[i].sprite->ID).tex, recSprite2, recEntity2, vec, 0, WHITE, templayer, true };
	
		if (render_list[0].List.size() < gui_entity_list.size()) {

			render_list[0].List.push_back(&AllRenderObjects[i]);

			//objects_to_render++;
		}
		else
		{
			render_list[0].List[i] = &AllRenderObjects[i];
		}

		//DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint)
		//cout << RenderObject_list[i]->layer;
	
	}


}

inline void RenderMapEntities() {


	//// Rectangle type
	//typedef struct Rectangle {
	//	float x;
	//	float y;
	//	float width;
	//	float height;
	//} Rectangle;

	//// N-Patch layout info
	//typedef struct NPatchInfo {
	//	Rectangle source;       // Texture source rectangle
	//	int left;               // Left border offset
	//	int top;                // Top border offset
	//	int right;              // Right border offset
	//	int bottom;             // Bottom border offset
	//	int layout;             // Layout of the n-patch: 3x3, 1x3 or 3x1
	//} NPatchInfo;

	int  templayer = 0;

	int lowerlayer = 0;

	int entity_count = 0;

	for (size_t i = 0; i < map_entity_list.size(); i++)
	{

		Vector2 vec = { 0 , 0 };

		recSprite2 = { (float)map_entity_list[i].sprite->x, (float)map_entity_list[i].sprite->y,(float)map_entity_list[i].sprite->w,(float)map_entity_list[i].sprite->h };

		recEntity2 = { (float)map_entity_list[i].x + map_entity_list[i].sprite->offset_x , (float)map_entity_list[i].y + map_entity_list[i].sprite->offset_y, (float)map_entity_list[i].w, (float)map_entity_list[i].h };

		map_entity_list[i].entity_tile.x = map_entity_list[i].x;

		map_entity_list[i].entity_tile.y = map_entity_list[i].y;

		DrawRectangleLines(map_entity_list[i].entity_tile.x, map_entity_list[i].entity_tile.y, tile_width, tile_height, BLUE);

		DrawRectangleLines(map_entity_list[i].x, map_entity_list[i].y, map_entity_list[i].w, map_entity_list[i].h, RED);

		DrawRectangleLines((float)map_entity_list[i].x + map_entity_list[i].sprite->offset_x, (float)map_entity_list[i].y + map_entity_list[i].sprite->offset_y, map_entity_list[i].w, map_entity_list[i].h, GREEN);


		if (map_entity_list[i].ID == target->ID)
		{
			lowerlayer = 1;
		}
		else
		{
			lowerlayer = 0;
		}

		templayer = map_entity_list[i].y - lowerlayer;

		AllRenderObjects[i + objects_to_render[0]] = { getTexture(map_entity_list[i].sprite->ID).tex, recSprite2, recEntity2, vec, 0, WHITE, templayer, true };

		if (render_list[0].List.size() < map_entity_list.size() + objects_to_render[0]) {

			render_list[0].List.push_back(&AllRenderObjects[i + objects_to_render[0]]);

			entity_count++;
		}
		else
		{
			render_list[0].List[i] = &AllRenderObjects[i + objects_to_render[0]];
		}

		//DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin, float rotation, Color tint)
		//cout << RenderObject_list[i]->layer;

	}


}


static int added_once = 0;

inline void RenderEntities(vector<entity> &entities) {

	int  templayer = 0;

	int lowerlayer = 0;

	int entity_count = 0;

	for (size_t i = 0; i < entities.size(); i++)
	{

		recSprite2 = { (float)entities[i].sprite->x, (float)entities[i].sprite->y,(float)entities[i].sprite->w,(float)entities[i].sprite->h };

		recEntity2 = { (float)entities[i].x + entities[i].sprite->offset_x , (float)entities[i].y + entities[i].sprite->offset_y, (float)entities[i].w, (float)entities[i].h };

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

		templayer = entities[i].y - lowerlayer;


		if (entities[i].ID == 99)
		{
		//	cout << "99 "<< endl;
			templayer = -99;
		}
	
		if (entities[i].ID == 1)
		{
			templayer = -50;
		}


		AllRenderObjects[i + objects_to_render[0] + objects_to_render[1]] = { getTexture(entities[i].sprite->ID).tex, recSprite2, recEntity2, {0,0}, 0, WHITE, templayer, entities[i].render_this };

		if (render_list[0].List.size() < entities.size() + objects_to_render[0]) {

			render_list[0].List.push_back(&AllRenderObjects[i + objects_to_render[0]]);
		}
		else
		{
			render_list[0].List[i + objects_to_render[0]] = &AllRenderObjects[i + objects_to_render[0]];
		}

		if (render_entity_boxes == true)
		{
			DrawRectangleLines(entities[i].entity_tile.x, entities[i].entity_tile.y, tile_width, tile_height, BLUE);

			DrawRectangleLines(entities[i].x, entities[i].y, entities[i].w, entities[i].h, RED);

			DrawRectangleLines((float)entities[i].x + entities[i].sprite->offset_x, (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w, entities[i].h, GREEN);
		}



	}

	if (objects_to_render[0] < objects_to_render[0] + entities.size())
	{

		objects_to_render[0] = objects_to_render[0] + entities.size();
	
	}





}

inline void RenderEntityBoxes(vector<entity> &entities) {

	int  templayer = 0;

	int lowerlayer = 0;


	for (size_t i = 0; i < entities.size(); i++)
	{

		recSprite2 = { (float)entities[i].sprite->x, (float)entities[i].sprite->y,(float)entities[i].sprite->w,(float)entities[i].sprite->h };

		recEntity2 = { (float)entities[i].x + entities[i].sprite->offset_x , (float)entities[i].y + entities[i].sprite->offset_y, (float)entities[i].w, (float)entities[i].h };

		entities[i].entity_tile.x = entities[i].x;

		entities[i].entity_tile.y = entities[i].y;


		if (render_entity_boxes == true)
		{
			DrawRectangleLines(entities[i].entity_tile.x, entities[i].entity_tile.y, tile_width, tile_height, BLUE);

			DrawRectangleLines(entities[i].x, entities[i].y, entities[i].w, entities[i].h, RED);

			DrawRectangleLines((float)entities[i].x + entities[i].sprite->offset_x, (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w, entities[i].h, GREEN);
		}

	}

}





inline void RenderWholeEntity(texture* Texture) {




}


inline void RenderTextTexture(texture* Texture, int x, int y) {


}


static int current_frame = 0;


inline void AnimateMovement( entity  *en, Direction d )
{


	switch (d) {
	case UP: 

		en->sprite->x = (current_frame * en->sprite->w);

		en->sprite->y = en->sprite->h * 2;

		current_frame++;


		if (current_frame >= 4)
		{
			current_frame = 0
;
		}

		break;

	case DOWN: 

		en->sprite->x = (current_frame *  en->sprite->w);

		en->sprite->y = 0;

		current_frame++;


		if (current_frame >= 4)
		{
			current_frame = 0;
		}
		
		break;

	case LEFT: 

		en->sprite->x = (current_frame *  en->sprite->w);

		en->sprite->y = en->sprite->h * 3;

		current_frame++;


		if (current_frame >= 4)
		{
			current_frame = 1;
		}


		break;

	case RIGHT:

		en->sprite->x = (current_frame *  en->sprite->w);

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
		switch (move_list[i]) {
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


inline void Animate(entity  *en) 
{
	timer += GetFrameTime();

	if (timer >= 0.12)
	{
		timer = 0.0;


		en->sprite->x = (current_frame2 * en->sprite->w);

		//en->sprite->y = en->sprite->h * 2;

		en->sprite->y = 0;

		current_frame2++;

		en->x = en->x + left_vel/4;
		en->y = en->y + down_vel/4;


		if (current_frame2 > 5)
		{
			current_frame2 = 0;

		}

		loop++;
	
	}

	if(loop >= 20)
	{
		en->x = 480;
		en->y = 208;

		loop = 0;
	
	}




}

static int movecount = 0;

static int steps = 0;

inline void MovementAnimated(entity  *en)
{
	if (moving == true)
	{
		if (movecount < move_list.size())
		{

			//printf("steps lower than size\n");


			if (move_list[movecount] == LEFT)
			{

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

			moving = false;

			if (move_list.back() == LEFT)
			{

				en->sprite->x = 0;

				en->sprite->y = 0;

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

inline void RenderTextList() {


	for (size_t i = 0; i < text_list.size(); i++)
	{

	}

}



 Rectangle infoRect = { (GameGui.x - 200) , GameGui.y , 100, 16 };


//inline void RendedDebugInfo()
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
//}



 Rectangle DebugLogInfoRect = { 0 , 0 , 100, 16 };

 Rectangle DebugScrollBar = { 8 + 400, GAMEWINDOW_HEIGHT - 200 - 16, 10, 16 * 11 };


inline void RenderDebugLog()
{
	DebugLogInfoRect.x = 20 + 400;

	DebugLogInfoRect.y = GAMEWINDOW_HEIGHT - 200;

	int rendernum = 0;

	for (size_t i = debuglog_lines.size(); i-- > 0; )
	{
		if (rendernum < currentline_debuglog)
		{
			// Render only 11 lines at the time, as it scrolls
			if (rendernum < 89) {

				if (rendernum > 89 - DebugLogScrollCounter - 1)
				{
					//GuiLabel({ DebugLogInfoRect.x, DebugLogInfoRect.y + ((i - DebugLogScrollCounter) * DebugLogInfoRect.height) - (DebugLogInfoRect.height * 1), DebugLogInfoRect.width, DebugLogInfoRect.height }, debuglog_lines[(currentline_debuglog - 1 - rendernum)].c_str());
					rendernum++;
				}
				else
				{
					rendernum++;

				}

			}
			else
			{
				//GuiLabel({ DebugLogInfoRect.x, DebugLogInfoRect.y + ((i - DebugLogScrollCounter) * DebugLogInfoRect.height) - (DebugLogInfoRect.height * 1), DebugLogInfoRect.width, DebugLogInfoRect.height }, debuglog_lines[(currentline_debuglog - 1 - rendernum)].c_str());

				rendernum++;

			}

		}

	}

	//DebugLogScrollCounter = GuiScrollBar(DebugScrollBar, DebugLogScrollCounter, 100 - currentline_debuglog, 89);
}




inline void DisplayEntityInfo(entity game_entity, int x, int y) {

	//AddText("Entity ID: " + to_string(game_entity.ID), x, y + (1 * FONT_SIZE));
	//AddText("Entity x:" + to_string(game_entity.x), x, y + (2 * FONT_SIZE));
	//AddText("Entity y:" + to_string(game_entity.y), x, y + (3 * FONT_SIZE));
	//AddText("Entity w:" + to_string(game_entity.w), x, y + (4 * FONT_SIZE));
	//AddText("Entity h:" + to_string(game_entity.h), x, y + (5 * FONT_SIZE));

	//AddText("sprite ID:" + to_string(game_entity.sprite.img_ID), x, y + (6 * FONT_SIZE));
	//AddText("sprite name:", x, y + (7 * FONT_SIZE));
	//AddText("" + (game_entity.sprite.img), x, y + (8 * FONT_SIZE));
	//AddText("sprite x:" + to_string(game_entity.sprite.x), x, y + (9 * FONT_SIZE));
	//AddText("sprite y:" + to_string(game_entity.sprite.y), x, y + (10 * FONT_SIZE));
	//AddText("sprite w:" + to_string(game_entity.sprite.w), x, y + (11 * FONT_SIZE));
	//AddText("sprite h:" + to_string(game_entity.sprite.h), x, y + (12 * FONT_SIZE));


}

inline bool CheckCollisionRects(Rectangle a, Rectangle b)
{
	//The sides of the rectangles
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.width;
	topA = a.y;
	bottomA = a.y + a.height;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.width;
	topB = b.y;
	bottomB = b.y + b.height;

	//If any of the sides from A are outside of B
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

	//If none of the sides from A are outside B
	return true;
}


inline bool CheckCollisionMouseEntity() {
	bool ret = false;

	int mouseX = GetMouseX();                                                    // Returns mouse position X
	int mouseY = GetMouseY();

	Rectangle mouseRect = { mouseX,mouseY,1,1 };
	//	Rectangle tempEntityRect;


	for (size_t i = 0; i < entity_list.size(); i++)
	{
		Rectangle tempEntityRect = { entity_list[i].x,entity_list[i].y,entity_list[i].w,entity_list[i].h };


		if (CheckCollisionRects(mouseRect, tempEntityRect))
		{
			//printf("Collision with Entity: %d", entity_list[i].ID);


			ret = true;
		}


	}

	return ret;


}



 float offset = 4;


inline void initActionMenu()
{


	Rectangle temp;

	temp = { 0,0 , (float)((GUI_ACTION_BUTTON_WIDTH) * 1.5), ((GUI_ACTION_BUTTON_HEIGHT)+offset / 2) * NumOfActionMenuButtons };

	ActionMenuRects.push_back(temp);

	temp = { 0,0 , GUI_ACTION_BUTTON_WIDTH , GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0,0, GUI_ACTION_BUTTON_WIDTH , GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0,0, GUI_ACTION_BUTTON_WIDTH , GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0,0, GUI_ACTION_BUTTON_WIDTH , GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);

	temp = { 0,0, GUI_ACTION_BUTTON_WIDTH , GUI_ACTION_BUTTON_HEIGHT };

	ActionMenuRects.push_back(temp);
}



inline void setActionMenu()
{
	float EntityX;
	float EntityY;
	float EntityW;
	float EntityH;


	if (combatant_selected > -1) {

		EntityX = combatant_list[combatant_selected].pEntity->x;
		EntityY = combatant_list[combatant_selected].pEntity->y;
		EntityW = combatant_list[combatant_selected].pEntity->w;
		EntityH = combatant_list[combatant_selected].pEntity->h;

	}
	else 
	{

	}

	// This is the Action menu box/panel
	ActionMenuRects[0].x = (float)(EntityX + EntityW) + 20;
	ActionMenuRects[0].y = (float)(EntityY - EntityH) + 16;


	for (size_t i = 1; i < ActionMenuRects.size(); i++)
	{
		ActionMenuRects[i].x = (float)(EntityX + EntityW) + 4 + 20;
		ActionMenuRects[i].y = (float)(EntityY - EntityH) + (i * GUI_ACTION_BUTTON_HEIGHT);
	}
	
	action_target->x = ActionMenuRects[currentbutton_index].x;
	action_target->y = ActionMenuRects[currentbutton_index].y;
}



inline bool setMouseEntity() {

	bool ret = false;

	int mouseX = GetMouseX();                                     
	int mouseY = GetMouseY();


	Rectangle mouseRect = { mouseX,mouseY,1,1 };
	//	Rectangle tempEntityRect;


	for (size_t i = 0; i < entity_list.size(); i++)
	{
		
		if (CheckCollisionRects(mouseRect, getEntityRect(entity_list[i])) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			//printf("Collision with Entity: %d", entity_list[i].ID);


			game_entity = &entity_list[i];

			ret = true;
		}


	}

	return ret;

}

inline bool setMouseEntity(vector<entity> &entities) {

	bool ret = false;

	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	Rectangle mouseRect = { mouseX,mouseY,1,1 };
	//	Rectangle tempEntityRect;


	for (size_t i = 0; i < entities.size(); i++)
	{
		Rectangle tempEntityRect = { (float)entities[i].x + entities[i].sprite->offset_x, (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w, entities[i].h };
	

		if (CheckCollisionRects(mouseRect, tempEntityRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			//printf("Collision with Entity: %d", entity_list[i].ID);


			game_entity = &entities[i];

			ret = true;
		}


	}

	return ret;

}



/////-------------------------------------------------  RenderField -------------------------------------------

 Rectangle recSprite = { 64, 0, 64, 32 };

 Rectangle recEntity = { 0, 0, 0,0 };

 Vector2 vec = { 0 , 0 };

inline void RenderField(field &fieldRef) {


	int list_next = 0;

	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		recEntity = { (float)(fieldRef.tiles[i].x), (float)(fieldRef.tiles[i].y) , (float)tile_width , (float)tile_height };

		recSprite = { (float)(fieldRef.tiles[i].sprite->x), (float)(fieldRef.tiles[i].sprite->y) , (float)fieldRef.tiles[i].sprite->w ,(float)fieldRef.tiles[i].sprite->h };

		//DrawTexturePro( getTexture("BlueTile").tex , recSprite, recEntity, vec, 0, WHITE);

		//DrawTexturePro(getTexture(target_field.tiles[i].sprite->ID).tex, recSprite, recEntity, vec, 0, WHITE);

		//cout << objects_to_render[list_next] << endl;

		AllRenderObjects[i + objects_to_render[list_next] ] = { getTexture(fieldRef.tiles[i].sprite->ID).tex, recSprite, recEntity, vec, 0, WHITE, -60, fieldRef.render_field };


		if (render_list[list_next].List.size() < fieldRef.sum_of_field_tiles + objects_to_render[list_next]) {

			//cout << "index to render: " << (i  + objects_to_render[1]) << endl;
			render_list[list_next].List.push_back(&AllRenderObjects[i + objects_to_render[list_next]]);

	
		}
		else
		{
			render_list[list_next].List[i + objects_to_render[list_next]] = &AllRenderObjects[i + objects_to_render[list_next]];
		}
		if (move_field_up == true) 
		{
			DrawRectangleLines(recEntity.x - 1 + (tile_width / 2), recEntity.y - 1 + (tile_height / 2), 2, 2, BLACK);
		}
	
	}

	if (move_field_up == true)
	{
		DrawRectangleLines(target_field.x, target_field.y, target_field.w, target_field.h, RED);
	}


	if (objects_to_render[list_next] < objects_to_render[list_next] + fieldRef.sum_of_field_tiles )
	{

		objects_to_render[list_next] = objects_to_render[list_next] + fieldRef.sum_of_field_tiles;

	}



}


inline void swap(RenderObject xp, RenderObject yp)
{
	RenderObject temp = xp;
	xp = yp;
	yp = temp;
}

inline void SortLayerRenderObjectList()
{
	bool sorted = false;

	RenderObject temp;

	int i = 0; 
	int	j = 0;
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

	// cout << newlist_size << endl;


	for (num_of_lists = 0; num_of_lists < render_list.size(); num_of_lists++)
	{
		for (list_index = 0; list_index < render_list[num_of_lists].List.size(); list_index++)
		{
			if (SortedRenderObject_list.size() < newlist_size)
			{
				SortedRenderObject_list.push_back(render_list[num_of_lists].List[list_index]);
			}
			else
			{
				SortedRenderObject_list[count] = render_list[num_of_lists].List[list_index];
				count++;
			}
		}
	}
	// cout << SortedRenderObject_list.size() << endl;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (SortedRenderObject_list[j]->layer > SortedRenderObject_list[j + 1]->layer)
			{
				swap(SortedRenderObject_list[j], SortedRenderObject_list[j + 1]);
			}
		}
	}

}



inline void RenderAllLayers() 
{


	for (size_t i = 0; i < SortedRenderObject_list.size(); i++)
	{
		if (SortedRenderObject_list[i] != NULL)
		{
			if (SortedRenderObject_list[i]->render_this == true)
			{
				DrawTexturePro(SortedRenderObject_list[i]->texture, SortedRenderObject_list[i]->source, SortedRenderObject_list[i]->dest, SortedRenderObject_list[i]->origin, SortedRenderObject_list[i]->rotation, SortedRenderObject_list[i]->tint);
			}		
		}
	}
}

//inline void Render_listsTwo()
//{
//	int draw = 1;
//
//	for (size_t i = 0; i < Render_lists[draw].size(); i++)
//	{
//	
//			DrawTexturePro(Render_lists[draw][i]->texture, Render_lists[draw][i]->source, Render_lists[draw][i]->dest, Render_lists[draw][i]->origin, Render_lists[draw][i]->rotation, Render_lists[draw][i]->tint);
//
//	}
//
//}
//
//inline void Render_listsOne()
//{
//	int draw = 0;
//
//	for (size_t i = 0; i < Render_lists[draw].size(); i++)
//	{
//
//		DrawTexturePro(Render_lists[draw][i]->texture, Render_lists[draw][i]->source, Render_lists[draw][i]->dest, Render_lists[draw][i]->origin, Render_lists[draw][i]->rotation, Render_lists[draw][i]->tint);
//
//	}
//
//}

/////----------------------------------------------------------------------------------------------------

/////-------------------------------------------------  ColorFieldTile -------------------------------------------

 Rectangle temp1 = { -100,-100,0,0 };

 Rectangle temp2 = { -100,-100,0,0 };

inline void SetFieldTileColors(field &fieldRef, int Sprite_ID)
{
	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		target_field.tiles[i].sprite = &getSprite(Sprite_ID); 
	}
}



inline bool ColorFieldTileEntityList(vector<tile> &colored_tiles , field *fieldRef, vector<entity> &entity_list)
{
	bool colored_tile = false;

	Rectangle temp2;
	tile temptile;

	for (size_t i = 0; i < entity_list.size(); i++)
	{
		temp2 = { (float)entity_list[i].x,(float)entity_list[i].y,(float)entity_list[i].w,(float)entity_list[i].h };
		if ( entity_list[i].x == combatant_list[combatant_selected].pEntity->x && entity_list[i].y == combatant_list[combatant_selected].pEntity->y )
		{
			//cout << "Player X Y" << endl;
		}
		else 
		{
			if (enemy_colored == false)
			{
				for (size_t j = 0; j < fieldRef->sum_of_field_tiles; j++)
				{
					temp1 = { (float)(fieldRef->tiles[j].x), (float)(fieldRef->tiles[j].y) , (float)tile_width , (float)tile_height };

					if (
						CheckCollisionRecs(
							{ (float)(temp2.x - 1 + (tile_width / 2)), (float)(temp2.y - 1 + (tile_height / 2)), 2 ,2 },
							{ (float)(temp1.x - 1 + (tile_width / 2)), (float)(temp1.y - 1 + (tile_height / 2)), 2, 2 }))
					{


						if (last_tile.x != temp2.x || last_tile.y != temp2.y)
						{
							fieldRef->tiles[j].sprite = &getSprite(4); // red tile

							colored_enemy_tiles.push_back(fieldRef->tiles[j]);

							last_tile = { temp2.x, temp2.y,0,0 };

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

	return colored_tile;
}

inline bool ColorFieldTile( field &fieldRef, entity  *target)
{
	bool colored_tile = false;

	temp2 = { (float)target->x,(float)target->y,(float)target->w,(float)target->h };

	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		temp1 = { (float)(fieldRef.tiles[i].x), (float)(fieldRef.tiles[i].y) , (float)tile_width , (float)tile_height };

		if (
			CheckCollisionRecs(
				{ (float)(temp2.x - 1 + (tile_width / 2)), (float)(temp2.y - 1 + (tile_height / 2)), 2 ,2 },
				{ (float)(temp1.x - 1 + (tile_width / 2)), (float)(temp1.y - 1 + (tile_height / 2)), 2, 2 }))
		{
			if (last_tile.x != temp2.x || last_tile.y != temp2.y)
			{
				fieldRef.tiles[i].sprite = &getSprite(4); // red tile

				colored_moved_tiles.push_back(fieldRef.tiles[i]);

				last_tile = { temp2.x, temp2.y,0,0 };

				colored_tile = true;

				cout << "colored_moved_tiles.push_back(temptile);" << endl;

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


inline void ResetMovedTilesColor(field &fieldRef, int Sprite_ID)
{
	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{

		for (size_t j = 0; j < colored_moved_tiles.size(); j++)
		{
			//cout << "same2" << endl;

			if (fieldRef.tiles[i].x == colored_moved_tiles[j].x && fieldRef.tiles[i].y == colored_moved_tiles[j].y)
			{
				//cout << "same3" << endl;
				fieldRef.tiles[i].sprite = &getSprite(Sprite_ID);
			}
		}
	}
}


inline bool IsInArray(int * Array, int Size, int number)
{
	bool result = false;
	//int arraySize = sizeof(Array) / sizeof(Array[0]);

	for (size_t i = 0; i < Size; i++)
	{
		if (Array[i] == number) {
			result = true;
			break;
		}
	}

	return result;
}


inline void randomSpawnTile(field &fieldRef, field &spawn_field)
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

			spawn_field.tiles[i].sprite = &getSprite(4);

		}

		cout << endl;
		cout << "Fields set " << fieldRef.sum_of_field_tiles << " " << spawn_field.sum_of_field_tiles << endl;
	}
	else 
	{
		cout << "Fields not set " << fieldRef.sum_of_field_tiles << " " <<  spawn_field.sum_of_field_tiles << endl;
	}

	
}

inline tile_rect getTileRect(Rectangle &t)
{
	tile_rect temp;

	temp.line_1_p1_x = t.x + t.width / 2;
	temp.line_1_p1_y = t.y;

	temp.line_1_p2_x = t.x;
	temp.line_1_p2_y = t.y + t.height / 2;

	temp.line_2_p1_x = t.x;
	temp.line_2_p1_y = t.y + t.height / 2;

	temp.line_2_p2_x = t.x + t.width / 2;
	temp.line_2_p2_y = t.y + t.height;

	temp.line_3_p1_x = t.x + t.width / 2;
	temp.line_3_p1_y = t.y + t.height;

	temp.line_3_p2_x = t.x + t.width;
	temp.line_3_p2_y = t.y + t.height / 2;

	temp.line_4_p1_x = t.x + t.width;
	temp.line_4_p1_y = t.y + t.height / 2;

	temp.line_4_p2_x = t.x + t.width /2;
	temp.line_4_p2_y = t.y;



	//cout << "temp.line_1_p1_x: " << temp.line_1_p1_x << "temp.line_1_p1_y" << temp.line_1_p1_y << endl;

	return temp;
}


inline tile_triangles getTileTriangles(Rectangle &t)
{
	tile_triangles temp;

	temp.tri_1_line_1_x = t.x + t.width / 2;
	temp.tri_1_line_1_y = t.y;

	temp.tri_1_line_2_x = t.x;
	temp.tri_1_line_2_y = t.y + t.height / 2;

	temp.tri_1_line_3_x = t.x + t.width  / 2 + 1;
	temp.tri_1_line_3_y = t.y + t.height / 2 + 1;

	temp.tri_2_line_1_x = t.x;
	temp.tri_2_line_1_y = t.y + t.height / 2;

	temp.tri_2_line_2_x = t.x + t.width / 2;
	temp.tri_2_line_2_y = t.y + t.height - 1;

	temp.tri_2_line_3_x = t.x + t.width  / 2 - 1;
	temp.tri_2_line_3_y = t.y + t.height / 2 - 1;

	temp.tri_3_line_1_x = t.x + t.width / 2;
	temp.tri_3_line_1_y = t.y + t.height - 1;

	temp.tri_3_line_2_x = t.x + t.width;
	temp.tri_3_line_2_y = t.y + t.height / 2;

	temp.tri_3_line_3_x = t.x + t.width  / 2 - 1;
	temp.tri_3_line_3_y = t.y + t.height / 2 - 1;

	temp.tri_4_line_1_x = t.x + t.width;
	temp.tri_4_line_1_y = t.y + t.height / 2;

	temp.tri_4_line_2_x = t.x + t.width / 2;
	temp.tri_4_line_2_y = t.y;

	temp.tri_4_line_3_x = t.x + t.width / 2 + 1;
	temp.tri_4_line_3_y = t.y + t.height / 2 + 1;

	return temp;
}


inline tile_rect getTileInnerRect(Rectangle &t)
{
	tile_rect temp;

	temp.line_1_p1_x = t.x + t.width / 2;
	temp.line_1_p1_y = t.y + 1;

	temp.line_1_p2_x = t.x + 2;
	temp.line_1_p2_y = t.y + t.height / 2;

	temp.line_2_p1_x = t.x + 2;
	temp.line_2_p1_y = t.y + t.height / 2;

	temp.line_2_p2_x = t.x + t.width / 2;
	temp.line_2_p2_y = t.y + t.height - 1;

	temp.line_3_p1_x = t.x + t.width / 2;
	temp.line_3_p1_y = t.y + t.height - 1;

	temp.line_3_p2_x = t.x + t.width -2 ;
	temp.line_3_p2_y = t.y + t.height / 2;

	temp.line_4_p1_x = t.x + t.width - 2;
	temp.line_4_p1_y = t.y + t.height / 2;

	temp.line_4_p2_x = t.x + t.width / 2;
	temp.line_4_p2_y = t.y + 1;

	//cout << "temp.line_1_p1_x: " << temp.line_1_p1_x << "temp.line_1_p1_y" << temp.line_1_p1_y << endl;

	return temp;
}




inline void drawIsoTriangles( entity * e)
{

	//temp3 = getTileRect(e->entity_tile);

	//DrawLine(temp3.line_1_p1_x, temp3.line_1_p1_y, temp3.line_1_p2_x, temp3.line_1_p2_y, BLUE);
	//DrawLine(temp3.line_2_p1_x, temp3.line_2_p1_y, temp3.line_2_p2_x, temp3.line_2_p2_y, RED);
	//DrawLine(temp3.line_3_p1_x, temp3.line_3_p1_y, temp3.line_3_p2_x, temp3.line_3_p2_y, GREEN);
	//DrawLine(temp3.line_4_p1_x, temp3.line_4_p1_y, temp3.line_4_p2_x, temp3.line_4_p2_y, ORANGE);

	temp4 = getTileTriangles(e->entity_tile);

	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	p1.x = temp4.tri_1_line_1_x;
	p1.y = temp4.tri_1_line_1_y;

	p2.x = temp4.tri_1_line_2_x;
	p2.y = temp4.tri_1_line_2_y;

	p3.x = temp4.tri_1_line_3_x ;
	p3.y = temp4.tri_1_line_3_y;

	DrawTriangle( p1,  p2,  p3, BLUE);

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

inline void drawInnerIsoRect(entity * e)
{

	//temp3 = getTileInnerRect(e->entity_tile);

	//DrawLine(temp3.line_1_p1_x, temp3.line_1_p1_y, temp3.line_1_p2_x, temp3.line_1_p2_y, YELLOW);
	//DrawLine(temp3.line_2_p1_x, temp3.line_2_p1_y, temp3.line_2_p2_x, temp3.line_2_p2_y, YELLOW);
	//DrawLine(temp3.line_3_p1_x, temp3.line_3_p1_y, temp3.line_3_p2_x, temp3.line_3_p2_y, YELLOW);
	//DrawLine(temp3.line_4_p1_x, temp3.line_4_p1_y, temp3.line_4_p2_x, temp3.line_4_p2_y, YELLOW);
}



inline void CollisionIsoRect(entity * e)
{
	Vector2 mouse;

	Vector2 p1;
	Vector2 p2;

	bool coll_line1;
	bool coll_line2;
	bool coll_line3;
	bool coll_line4;

	bool inner_coll_line1;
	bool inner_coll_line2;
	bool inner_coll_line3;
	bool inner_coll_line4;


	tile_rect temp3 = getTileRect(e->entity_tile);

	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	p1.x = temp3.line_1_p1_x;
	p1.y = temp3.line_1_p1_y;

	p2.x = temp3.line_1_p2_x;
	p2.y = temp3.line_1_p2_y;

	coll_line1 = CheckCollisionPointLine(mouse, p1, p2, 1);

	p1.x = temp3.line_2_p1_x;
	p1.y = temp3.line_2_p1_y;

	p2.x = temp3.line_2_p2_x;
	p2.y = temp3.line_2_p2_y;

	coll_line2 = CheckCollisionPointLine(mouse, p1, p2, 1);

	p1.x = temp3.line_3_p1_x;
	p1.y = temp3.line_3_p1_y;

	p2.x = temp3.line_3_p2_x;
	p2.y = temp3.line_3_p2_y;

	coll_line3 = CheckCollisionPointLine(mouse, p1, p2, 1);

	p1.x = temp3.line_4_p1_x;
	p1.y = temp3.line_4_p1_y;

	p2.x = temp3.line_4_p2_x;
	p2.y = temp3.line_4_p2_y;

	coll_line4 = CheckCollisionPointLine(mouse, p1, p2, 1);

	temp3 = getTileInnerRect(e->entity_tile);

	p1.x = temp3.line_1_p1_x;
	p1.y = temp3.line_1_p1_y;

	p2.x = temp3.line_1_p2_x;
	p2.y = temp3.line_1_p2_y;

	inner_coll_line1 = CheckCollisionPointLine(mouse, p1, p2, 1);

	p1.x = temp3.line_2_p1_x;
	p1.y = temp3.line_2_p1_y;

	p2.x = temp3.line_2_p2_x;
	p2.y = temp3.line_2_p2_y;

	inner_coll_line2 = CheckCollisionPointLine(mouse, p1, p2, 1);

	p1.x = temp3.line_3_p1_x;
	p1.y = temp3.line_3_p1_y;

	p2.x = temp3.line_3_p2_x;
	p2.y = temp3.line_3_p2_y;

	inner_coll_line3 = CheckCollisionPointLine(mouse, p1, p2, 1);

	p1.x = temp3.line_4_p1_x;
	p1.y = temp3.line_4_p1_y;

	p2.x = temp3.line_4_p2_x;
	p2.y = temp3.line_4_p2_y;

	inner_coll_line4 = CheckCollisionPointLine(mouse, p1, p2, 1);



	if ( (coll_line1 || coll_line2 || coll_line3 || coll_line4)  ||  (inner_coll_line1 || inner_coll_line2 || inner_coll_line3 || inner_coll_line4)  )
	{

		cout << "Collission line "  << endl;

	}

}

//tile_triangles temp4;

inline bool CollisionIsoTrianglesMouse(entity * e)
{
	Vector2 mouse;

	bool coll_tri1;
	bool coll_tri2;
	bool coll_tri3;
	bool coll_tri4;

	bool collision = false;

	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	temp4 = getTileTriangles(e->entity_tile);

	mouse.x = GetMouseX();
	mouse.y = GetMouseY();


	p1.x = temp4.tri_1_line_1_x;
	p1.y = temp4.tri_1_line_1_y;

	p2.x = temp4.tri_1_line_2_x;
	p2.y = temp4.tri_1_line_2_y;

	p3.x = temp4.tri_1_line_3_x;
	p3.y = temp4.tri_1_line_3_y;


	coll_tri1 = CheckCollisionPointTriangle( mouse,  p1,  p2,  p3);

	p1.x = temp4.tri_2_line_1_x;
	p1.y = temp4.tri_2_line_1_y;

	p2.x = temp4.tri_2_line_2_x;
	p2.y = temp4.tri_2_line_2_y;

	p3.x = temp4.tri_2_line_3_x;
	p3.y = temp4.tri_2_line_3_y;


	coll_tri2 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

	p1.x = temp4.tri_3_line_1_x;
	p1.y = temp4.tri_3_line_1_y;

	p2.x = temp4.tri_3_line_2_x;
	p2.y = temp4.tri_3_line_2_y;

	p3.x = temp4.tri_3_line_3_x;
	p3.y = temp4.tri_3_line_3_y;


	coll_tri3 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

	p1.x = temp4.tri_4_line_1_x;
	p1.y = temp4.tri_4_line_1_y;

	p2.x = temp4.tri_4_line_2_x;
	p2.y = temp4.tri_4_line_2_y;

	p3.x = temp4.tri_4_line_3_x;
	p3.y = temp4.tri_4_line_3_y;


	coll_tri4 = CheckCollisionPointTriangle(mouse, p1, p2, p3);


	if ((coll_tri1 || coll_tri2 || coll_tri3 || coll_tri4))
	{
		collision = true;
	}

	return collision;

}

inline bool CollisionIsoTrianglesMouse(Rectangle  &e)
{
	Vector2 mouse;

	bool coll_tri1;
	bool coll_tri2;
	bool coll_tri3;
	bool coll_tri4;

	bool collision = false;

	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	temp4 = getTileTriangles(e);

	mouse.x = GetMouseX();
	mouse.y = GetMouseY();


	p1.x = temp4.tri_1_line_1_x;
	p1.y = temp4.tri_1_line_1_y;

	p2.x = temp4.tri_1_line_2_x;
	p2.y = temp4.tri_1_line_2_y;

	p3.x = temp4.tri_1_line_3_x;
	p3.y = temp4.tri_1_line_3_y;


	coll_tri1 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

	p1.x = temp4.tri_2_line_1_x;
	p1.y = temp4.tri_2_line_1_y;

	p2.x = temp4.tri_2_line_2_x;
	p2.y = temp4.tri_2_line_2_y;

	p3.x = temp4.tri_2_line_3_x;
	p3.y = temp4.tri_2_line_3_y;


	coll_tri2 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

	p1.x = temp4.tri_3_line_1_x;
	p1.y = temp4.tri_3_line_1_y;

	p2.x = temp4.tri_3_line_2_x;
	p2.y = temp4.tri_3_line_2_y;

	p3.x = temp4.tri_3_line_3_x;
	p3.y = temp4.tri_3_line_3_y;


	coll_tri3 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

	p1.x = temp4.tri_4_line_1_x;
	p1.y = temp4.tri_4_line_1_y;

	p2.x = temp4.tri_4_line_2_x;
	p2.y = temp4.tri_4_line_2_y;

	p3.x = temp4.tri_4_line_3_x;
	p3.y = temp4.tri_4_line_3_y;


	coll_tri4 = CheckCollisionPointTriangle(mouse, p1, p2, p3);


	if ((coll_tri1 || coll_tri2 || coll_tri3 || coll_tri4))
	{
		collision = true;
	}

	return collision;

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