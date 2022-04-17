
#include "../header_files/globals.h"
#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"

#define RAYGUI_IMPLEMENTATION
#include "../header_files/raygui.h"




inline void DrawGui()
{

	int n = 0;
	Rectangle temp = { 1360, 20, 100, 24 };
	int BoxHeight2 = 32;
	Rectangle SpriteGroupBoxRect = { 1360, 20, 200,800};

	bool ToggleSpriteOffsetX = false;
	bool ToggleSpriteX = false;
	bool ToggleSpriteOffsetY = false;
	bool ToggleSpriteY = false;

	bool dropDown001EditMode = false;
	bool ToggleEntityBoxes = false;

	 Rectangle SaveRect2 = { SpriteGroupBoxRect.x, SpriteGroupBoxRect.y - 40 , 40 , 20 };

	 SaveButton002 = GuiButton({ SpriteGroupBoxRect.x + SpriteGroupBoxRect.width - SaveRect2.width, SpriteGroupBoxRect.y, SaveRect2.width, SaveRect2.height }, "Save");


	 temp.y = 10 + SpriteGroupBoxRect.y + (n * 20);

	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "sprite id", &game_entity->sprite->ID, 1, sprite_list.size(), false); 
	 n++;

	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	 GuiLabel({ temp.x - 45, temp.y, temp.width, temp.height }, "sprite name");
	 GuiTextBox({ temp.x + 22, temp.y, temp.width - 10, temp.height }, strdup(game_entity->sprite->name.c_str()), 12, false); 
	 n++;


	 temp.y = 10 + SpriteGroupBoxRect.y + (n * 20);

	 temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);
	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "sprite x", &game_entity->sprite->x, 0, 2000, ToggleSpriteX); 
	 n++;
	 ToggleSpriteX = GuiToggle({ temp.x + temp.width + 2, temp.y, 40, temp.height }, "Edit", ToggleSpriteX);


	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "sprite y", &game_entity->sprite->y, 0, 2000, ToggleSpriteY);
	 n++;
	 ToggleSpriteY = GuiToggle({ temp.x + temp.width + 2, temp.y, 40, temp.height }, "Edit", ToggleSpriteY);

	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "sprite w", &game_entity->sprite->w, 0, 2000, false); n++;
	 game_entity->sprite->w = GuiSliderBar({ temp.x + 92, temp.y,temp.width,temp.height }, "", TextFormat("%i", game_entity->sprite->w), game_entity->sprite->w, 0, 2000);

	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "sprite h", &game_entity->sprite->h, 0, 2000, false); n++;
	 game_entity->sprite->h = GuiSliderBar({ temp.x + 92, temp.y,temp.width,temp.height }, "", TextFormat("%i", game_entity->sprite->h), game_entity->sprite->h, 0, 2000);

	 temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);
	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "offset_x", &game_entity->sprite->offset_x, -800, 2000, ToggleSpriteOffsetX);
	 n++;
	 ToggleSpriteOffsetX = GuiToggle({ temp.x + temp.width + 2, temp.y, 40, temp.height }, "Edit", ToggleSpriteOffsetX);


	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	 GuiSpinner({ temp.x, temp.y, temp.width, temp.height }, "offset_y", &game_entity->sprite->offset_y, -800, 2000, ToggleSpriteOffsetY);
	 n++;

	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
	 GuiLabel({ temp.x - 40, temp.y + 2, temp.width, temp.height }, "file img");
	 if (GuiDropdownBox({ temp.x, temp.y + 2, temp.width + 80, temp.height }, all_png_list.c_str(), &game_entity->sprite->index, dropDown001EditMode)) {
		 dropDown001EditMode = !dropDown001EditMode;
	 }
	 n++;

	 temp.y = 12 + SpriteGroupBoxRect.y + (n * 24);

	 Rectangle OptionsGroupBoxRect = { temp.x - 60, temp.y, 280, BoxHeight2 };

	 GuiGroupBox({ OptionsGroupBoxRect.x, OptionsGroupBoxRect.y , OptionsGroupBoxRect.width , OptionsGroupBoxRect.height }, "Gui Options");

	 temp.y = 26 + SpriteGroupBoxRect.y + (n * 24);
	 //temp.x = GameGui.x - 40;

	 char str[12] = "Show Boxes";

	 ToggleEntityBoxes = GuiToggle({ temp.x + 2, temp.y, sizeof(str)/sizeof(str[0])*6 , temp.height }, str, ToggleEntityBoxes);

	 n++;

	 char str2[12] = "Combat";

	 temp.y = 26 + SpriteGroupBoxRect.y + (n * 24);

	 combat = GuiToggle({ temp.x + 2, temp.y, sizeof(str2) / sizeof(str2[0]) * 6 , temp.height }, str2, combat);

	 n++;

	 char str3[12] = "Field up";

	 temp.y = 26 + SpriteGroupBoxRect.y + (n * 24);

	 draw_fields = GuiToggle({ temp.x + 2, temp.y, sizeof(str3) / sizeof(str3[0]) * 6 , temp.height }, str3, draw_fields);
 }



inline void DrawActionGui()
{
	GuiUnlock();

	GuiEnable();

	action_target_rect.height = GUI_ACTION_BUTTON_HEIGHT;

	action_target_rect.width = GUI_ACTION_BUTTON_WIDTH;

	GuiPanel(ActionMenuRects[0], "");

	GuiGroupBox(ActionMenuRects[0], "Action Menu");

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
	debug_info_lines.push_back("player.move_range = 7");
	debug_info_lines.push_back("target_field.range = 5");
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

Rectangle ScrollBar = { 8 , GAMEWINDOW_HEIGHT - 200 - 16, 10, 16 * 11 };



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
					GuiLabel({ LogInfoRect.x, LogInfoRect.y + ((i - LogScrollCounter) * LogInfoRect.height) - (LogInfoRect.height * 1), LogInfoRect.width, LogInfoRect.height }, log_lines[(currentline_log - 1 - rendernum)].c_str());
					rendernum++;
				}
				else
				{
					rendernum++;
				}

			}
			else
			{
				GuiLabel({ LogInfoRect.x, LogInfoRect.y + ((i - LogScrollCounter) * LogInfoRect.height) - (LogInfoRect.height * 1), LogInfoRect.width, LogInfoRect.height }, log_lines[(currentline_log - 1 - rendernum)].c_str());

				rendernum++;
			}
		}
	}

	LogScrollCounter = GuiScrollBar(ScrollBar, LogScrollCounter, 100 - currentline_log, 89);

}



