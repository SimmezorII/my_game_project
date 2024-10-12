
#include "../header_files/globals.h"
#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"

#include "../header_files/file_handler_func.h"
#include "../header_files/game_engine_func.h"
#include "../header_files/logic_func.h"

#define RAYGUI_IMPLEMENTATION
#include "../header_files/raygui.h"

Rectangle gui_temp = { 0, 0, 100, 18 };

Rectangle SpriteGroupBoxRect = { (float)(gamescreen_offset_x + GRID_WIDTH + 60), 20, 200,800 };

entity gui_temp_entity;

Rectangle temp_sprite_rec;

entity new_e;

int temp_w;
int temp_h;

int selected_sprite = 1;

inline void InitGui()
{
	new_game_entity = &new_e;

}

static int GUItempx;

static int GUItempy;


inline void RenderEntityInfo()
{
	string s;
	string name;
	Rectangle temp;

	if (combatant_selected > -1) {

		DebugLog(combatant_list[combatant_selected].pEntity->sprite->name);

		temp.x = combatant_list[combatant_selected].pEntity->offset_rect.x;
		temp.y = combatant_list[combatant_selected].pEntity->offset_rect.y - FONT_SIZE;
		temp.width = 100; // Size of max string
		temp.height = FONT_SIZE;

		GuiLabel(temp, combatant_list[combatant_selected].pEntity->sprite->name.c_str());

		s = to_string(player_current_hp) + "/" + to_string(player_max_hp);
		temp.x = temp.x + s.size() * 6;
		GuiLabel(temp, s.c_str());


		for (size_t i = 0; i < enemy_list.size(); i++)
		{
			if (combatant_selected > -1) {

				DebugLog(enemy_list[i].pEntity->sprite->name);

				temp.x = enemy_list[i].pEntity->offset_rect.x;
				temp.y = enemy_list[i].pEntity->offset_rect.y - FONT_SIZE;
				temp.width = 100; // Size of max string
				temp.height = FONT_SIZE;

				name = enemy_list[i].pEntity->sprite->name;

				GuiLabel(temp, name.c_str());

				s = to_string((int)enemy_list[i].pEntity->entity_stats.current_hp) + "/" + to_string((int)enemy_list[i].pEntity->entity_stats.max_hp);
				temp.x = temp.x + (name.size() * 6) + 6;
				//temp.y = temp.y + FONT_SIZE;	
				GuiLabel(temp, s.c_str());
			}
			else
			{

			}
		}

	}
	else
	{

	}

}

inline void DrawGui()
{
	int n = 0;

	bool ToggleSpriteOffsetX = false;
	bool ToggleSpriteX = false;
	bool ToggleSpriteOffsetY = false;
	bool ToggleSpriteY = false;

	bool dropDown001EditMode = false;

	Rectangle SaveRect2 = { 0, 0 , 40 , 24 };

	SaveButton002 = GuiButton({ SaveRect2.x,  SaveRect2.y, SaveRect2.width, SaveRect2.height }, "Save");

	GuiLine({ SpriteGroupBoxRect.x - 60, SpriteGroupBoxRect.y, 200, 0 }, "Sprite");
	//

	gui_temp.x = SpriteGroupBoxRect.x;
	gui_temp.y = 10 + SpriteGroupBoxRect.y + (n * 20);

	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "sprite id", &game_entity->sprite->ID, 1, sprite_list.size(), false);
	n++;

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiLabel({ gui_temp.x - 45, gui_temp.y, gui_temp.width, gui_temp.height }, "sprite name");
	GuiTextBox({ gui_temp.x + 22, gui_temp.y, gui_temp.width - 10, gui_temp.height }, strdup(game_entity->sprite->name.c_str()), 12, false);
	n++;

	gui_temp.y = 10 + SpriteGroupBoxRect.y + (n * 20);

	gui_temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "sprite x", &game_entity->sprite->x, 0, 2000, ToggleSpriteX);
	n++;
	ToggleSpriteX = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteX);


	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "sprite y", &game_entity->sprite->y, 0, 2000, ToggleSpriteY);
	n++;
	ToggleSpriteY = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteY);

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "sprite w", &game_entity->sprite->w, 0, 2000, false); n++;
	game_entity->sprite->w = GuiSliderBar({ gui_temp.x + 92, gui_temp.y,gui_temp.width,gui_temp.height }, "", TextFormat("%i", game_entity->sprite->w), game_entity->sprite->w, 0, 2000);

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "sprite h", &game_entity->sprite->h, 0, 2000, false); n++;
	game_entity->sprite->h = GuiSliderBar({ gui_temp.x + 92, gui_temp.y,gui_temp.width,gui_temp.height }, "", TextFormat("%i", game_entity->sprite->h), game_entity->sprite->h, 0, 2000);

	gui_temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "offset_x", &game_entity->sprite->offset_x, -800, 2000, ToggleSpriteOffsetX);
	n++;
	ToggleSpriteOffsetX = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteOffsetX);

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "offset_y", &game_entity->sprite->offset_y, -800, 2000, ToggleSpriteOffsetY);
	n++;
	ToggleSpriteOffsetY = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteOffsetY);

	gui_temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);

	GUItempx = (int)game_entity->x;

	GUItempy = (int)game_entity->y;

	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "entity x", &GUItempx, 0, 2000, ToggleSpriteX);
	n++;
	ToggleSpriteX = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteX);

	game_entity->x = GUItempx;

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiSpinner({ gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height }, "entity y", &GUItempy, 0, 2000, ToggleSpriteY);
	n++;
	ToggleSpriteY = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteY);

	game_entity->y = GUItempy;

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	GuiLabel({ gui_temp.x - 40, gui_temp.y + 2, gui_temp.width, gui_temp.height }, "file img");
	if (GuiDropdownBox({ gui_temp.x, gui_temp.y + 2, gui_temp.width + 80, gui_temp.height }, all_png_list.c_str(), &game_entity->sprite->index, dropDown001EditMode)) {
		dropDown001EditMode = !dropDown001EditMode;
	}
	n++;

	gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 24);

	GuiGroupBox({ gui_temp.x, gui_temp.y , 100 , 100 }, "Options");



	Rectangle OptionsGroupBoxRect = { (float)gamescreen_offset_x + 1280, (float)gamescreen_offset_y + 640, 280, 400 };

	//

	n = 0;

	gui_temp.y = OptionsGroupBoxRect.y + (n * 24);
	gui_temp.x = OptionsGroupBoxRect.x;
	//gui_temp.x = GameGui.x - 40;

	char str[12] = "Show Boxes";

	ToggleEntityBoxes = GuiToggle({ gui_temp.x + 2,  gui_temp.y, sizeof(str) / sizeof(str[0]) * 6 , gui_temp.height }, str, ToggleEntityBoxes);

	n++;

	char str2[12] = "Combat";

	gui_temp.y = OptionsGroupBoxRect.y + (n * 24);

	combat = GuiToggle({ gui_temp.x + 2, gui_temp.y, sizeof(str2) / sizeof(str2[0]) * 6 , gui_temp.height }, str2, combat);

	n++;

	char str3[12] = "Field up";

	gui_temp.y = OptionsGroupBoxRect.y + (n * 24);

	draw_fields = GuiToggle({ gui_temp.x + 2, gui_temp.y, sizeof(str3) / sizeof(str3[0]) * 6 , gui_temp.height }, str3, draw_fields);
}


static int current_selected = 0;

static int init_done = 0;

inline void RenderSelectedSprite()
{
	int n = 0;
	temp_sprite_rec.height = 60;
	temp_sprite_rec.width = 100;

	temp_sprite_rec.x = gamescreen_offset_x + GRID_WIDTH + 100;
	temp_sprite_rec.y = gamescreen_offset_y + 400;


	GuiSpinner({ temp_sprite_rec.x,temp_sprite_rec.y - 30, 100,20 }, "sprite id", &selected_sprite, 1, sprite_list.size(), false);

	if (current_selected != selected_sprite)
	{
		current_selected = selected_sprite;
		init_done = 0;
	}

	DrawTexturePro(getTexture(selected_sprite).tex, { 0, 0, (float)getTexture(selected_sprite).tex.width, (float)getTexture(selected_sprite).tex.height }, temp_sprite_rec, { 0,0 }, 0, WHITE);

	//ToggleSpriteX = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteX);

	//temp_sprite_rec.y = 14 + temp_sprite_rec.y + (n * 20) + temp_sprite_rec.height;

	//GuiSpinner({ temp_sprite_rec.x,temp_sprite_rec.y - 30, 100,20 }, "entity y", &game_entity->sprite->x, 0, 2000, ToggleSpriteX);
	//n++;

	//ToggleSpriteY = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height }, "Edit", ToggleSpriteY);


	new_e.sprite = &getSpriteEx(selected_sprite);

	if (init_done == 0)
	{
		temp_w = new_e.sprite->w;
		temp_h = new_e.sprite->h;

		init_done = 1;
	}

	temp_sprite_rec.y = temp_sprite_rec.y + 100;

	temp_sprite_rec.y = temp_sprite_rec.y + (n * 20);

	GuiSpinner({ temp_sprite_rec.x,temp_sprite_rec.y, 100,20 }, "new entity w", &temp_w, 0, 2000, ToggleSpriteX);
	n++;

	temp_sprite_rec.y = temp_sprite_rec.y + (n * 20);

	GuiSpinner({ temp_sprite_rec.x,temp_sprite_rec.y, 100,20 }, "new entity h", &temp_h, 0, 2000, ToggleSpriteX);

	temp_sprite_rec.y = temp_sprite_rec.y + (n * 24);

	NewEntityButton = GuiButton({ temp_sprite_rec.x,temp_sprite_rec.y, 40,20 }, "New");
}

inline void RenderNewEntity()
{

	temp_sprite_rec.height = temp_h;
	temp_sprite_rec.width = temp_w;


	if (temp_sprite_rec.height <= 32)
	{
		temp_sprite_rec.y = GetMousePosition().y - (temp_sprite_rec.height / 2);
	}
	else
	{
		temp_sprite_rec.y = GetMousePosition().y - (temp_sprite_rec.height) + tile_height / 2;
	}

	if (temp_sprite_rec.width <= 64)
	{
		temp_sprite_rec.x = GetMousePosition().x - (temp_sprite_rec.width / 2);
	}
	else
	{
		temp_sprite_rec.x = GetMousePosition().x - (temp_sprite_rec.width / 2);
	}

	//sprite_list

	DrawTexturePro(getTexture(selected_sprite).tex, { 0, 0, (float)getTexture(selected_sprite).tex.width, (float)getTexture(selected_sprite).tex.height }, temp_sprite_rec, { 0,0 }, 0, WHITE);

}




inline void AddNewEntity(int x, int y, int screen_x, int screen_y)
{
	new_e.ID = entity_list[entity_list.size() - 1].ID + num_of_added;

	new_e.render_this = true;

	new_e.w = temp_w;
	new_e.h = temp_h;

	cords[x][y][CURRENT_LAYER] = new_e.ID;

	new_e.x = screen_x;
	new_e.y = screen_y;

	WriteEntityDataSingle(new_e, MAPS_PATH + "game_entity_data_temp.txt");

	WriteUpdatedMap(MAPS_PATH + "map2.txt");

	num_of_added++;

	cout << "this happens" << endl;

	new_entity_list.push_back(new_e);
}


inline void CreateNewEntity()
{
	pos p;

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		//	printf("Button LEFT is pressed and Entity one clicked");
	}

	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		//	printf("Button LEFT is pressed and Entity one clicked");

		if (PLACING_ENTITY)
		{
			p = GetCordsCollisionIndex({ GetMousePosition().x, GetMousePosition().y, 1,1 });

			if (p.x != -1 && p.y != -1)
			{

				//CURRENT_LAYER = 1;

				cout << "This happens clicked" << endl;

				AddNewEntity(p.x, p.y, p.screen_x, p.screen_y - (CURRENT_LAYER * (GAME_TILE_HEIGHT / 2)));

				PLACING_ENTITY = false;
			}
		}
	}

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		//printf("Button RIGHT is pressed");

		if (PLACING_ENTITY)
		{
			PLACING_ENTITY = false;
			//printf("Button RIGHT is pressed");
		}
	}
}




inline void DrawActionGui()
{
	GuiUnlock();

	GuiEnable();

	action_target_rect.height = GUI_ACTION_BUTTON_HEIGHT;

	action_target_rect.width = GUI_ACTION_BUTTON_WIDTH;

	// This is the action menu box
	DrawRectangle(ActionMenuRects[0].x, ActionMenuRects[0].y, ActionMenuRects[0].width + 24, ActionMenuRects[0].height, WHITE);

	GuiGroupBox({ ActionMenuRects[0].x, ActionMenuRects[0].y, ActionMenuRects[0].width + 24, ActionMenuRects[0].height }, "Action Menu");

	if (precombat == true)
	{
		ActionButton[0] = GuiButtonEx(ActionMenuRects[1], "Ready", action_target_rect, KEY_X);

		ActionButton[1] = GuiButtonEx(ActionMenuRects[2], "Escape", action_target_rect, KEY_X);

		ActionButton[2] = GuiButtonEx(ActionMenuRects[3], "End", action_target_rect, KEY_X);

		DrawRectangleLines(action_target_rect.x, action_target_rect.y, action_target_rect.width, action_target_rect.height, RED);

	}
	else
	{

		ActionButton[0] = GuiButtonEx(ActionMenuRects[1], "Move", action_target_rect, KEY_X);

		ActionButton[1] = GuiButtonEx(ActionMenuRects[2], "Attack", action_target_rect, KEY_X);

		ActionButton[2] = GuiButtonEx(ActionMenuRects[3], "End", action_target_rect, KEY_X);

		DrawRectangleLines(action_target_rect.x, action_target_rect.y, action_target_rect.width, action_target_rect.height, RED);
	}



}

inline void AddDebugText()
{
	debug_info_lines.push_back("temp1");
	debug_info_lines.push_back("temp2");
	debug_info_lines.push_back("temp3");
	debug_info_lines.push_back("temp4");
	debug_info_lines.push_back("temp5");
	debug_info_lines.push_back("temp6");

}


inline void UpdateDebugText()
{
	debug_info_lines[2] = "Z_pressed_count: ";
	debug_info_lines[2].append(to_string(Z_pressed_count));

	debug_info_lines[3] = "X_pressed_count: ";
	debug_info_lines[3].append(to_string(X_pressed_count));

	debug_info_lines[4] = "Target x: ";
	debug_info_lines[4].append(to_string(target->x));

	debug_info_lines[5] = "Target Y: ";
	debug_info_lines[5].append(to_string(target->y));

}

Rectangle LogInfoRect = { 0 , 0 , 100, 16 };

Rectangle ScrollBar = { (float)gamescreen_offset_x + 8 ,(float)gamescreen_offset_y + GAMEWINDOW_HEIGHT - 200 - 16, 10, 16 * 11 };

inline void RenderLog()
{
	LogInfoRect.x = 20;

	LogInfoRect.y = GAMEWINDOW_HEIGHT - 200;

	int rendernum = 0;

	for (size_t i = log_lines.size(); i-- > 0; )
	{
		if (rendernum < currentline_log)
		{
			// Render only 11 lines at the time, as it scrolls
			if (rendernum < 89) {

				if (rendernum > 89 - LogScrollCounter - 1)
				{
					GuiLabel({ gamescreen_offset_x + LogInfoRect.x, gamescreen_offset_y + LogInfoRect.y + ((i - LogScrollCounter) * LogInfoRect.height) - (LogInfoRect.height * 1), LogInfoRect.width, LogInfoRect.height }, log_lines[(currentline_log - 1 - rendernum)].c_str());
					rendernum++;
				}
				else
				{
					rendernum++;
				}

			}
			else
			{
				GuiLabel({ gamescreen_offset_x + LogInfoRect.x, gamescreen_offset_y + LogInfoRect.y + ((i - LogScrollCounter) * LogInfoRect.height) - (LogInfoRect.height * 1), LogInfoRect.width, LogInfoRect.height }, log_lines[(currentline_log - 1 - rendernum)].c_str());

				rendernum++;
			}
		}
	}

	LogScrollCounter = GuiScrollBar(ScrollBar, LogScrollCounter, 100 - currentline_log, 89);

}


Rectangle DebugLogInfoRect = { 0 , 0 , 100, 16 };

Rectangle DebugScrollBar = { 8 + 400, (float)gamescreen_offset_y + (float)GAMEWINDOW_HEIGHT - 200 - 16, 10, 16 * 11 };


inline void RenderDebugLog()
{
	DebugLogInfoRect.x = 20 + 400;

	DebugLogInfoRect.y = (float)gamescreen_offset_y + GAMEWINDOW_HEIGHT - 200;

	int rendernum = 0;

	for (size_t i = debuglog_lines.size(); i-- > 0; )
	{
		if (rendernum < currentline_debuglog)
		{
			// Render only 11 lines at the time, as it scrolls
			if (rendernum < 89) {

				if (rendernum > 89 - DebugLogScrollCounter - 1)
				{
					GuiLabel({ DebugLogInfoRect.x, DebugLogInfoRect.y + ((i - DebugLogScrollCounter) * DebugLogInfoRect.height) - (DebugLogInfoRect.height * 1), DebugLogInfoRect.width, DebugLogInfoRect.height }, debuglog_lines[(currentline_debuglog - 1 - rendernum)].c_str());
					rendernum++;
				}
				else
				{
					rendernum++;
				}
			}
			else
			{
				GuiLabel({ DebugLogInfoRect.x, DebugLogInfoRect.y + ((i - DebugLogScrollCounter) * DebugLogInfoRect.height) - (DebugLogInfoRect.height * 1), DebugLogInfoRect.width, DebugLogInfoRect.height }, debuglog_lines[(currentline_debuglog - 1 - rendernum)].c_str());

				rendernum++;
			}
		}
	}

	DebugLogScrollCounter = GuiScrollBar(DebugScrollBar, DebugLogScrollCounter, 100 - currentline_debuglog, 89);
}


