/* ========================================================================

======================================================================== */

#pragma once

#ifndef logic_cpp
#define logic_cpp


#include <iostream>
#include "../header_files/raylib.h"
#include "../header_files/globals.h"
#include "../header_files/game_entities.h"
#include "../header_files/Logic_func.h"
#include "game_engine.cpp"
#include "combat.cpp"
//#include "gui.cpp"
#include "file_handler.cpp"

using namespace std;

//========================================================================

#define internal static 
#define local_persist static 
#define global_variable static


//========================================================================


static int mouse_x, mouse_y;

//========================================================================

static float time1;

static float time2;

 bool on_field = false;

 bool moved_combatant = false;

 bool moved_target = false;

 static double last = 0;

 static double last2 = 0;

inline void UpdateTargetFieldRange()
{

	if (target_field.range >= 1 && combatant_list[combatant_selected].current_movecount != 0) {

		target_field.range = combatant_list[combatant_selected].move_range - (combatant_list[combatant_selected].current_movecount - 1);

		if (target_field.range <= 0)
		{
			target_field.range = 1;
		}
	}
	else
	{
		target_field.range = 1;
	}

}

inline void EnemyLogic()
{
	Log("Enemy Passed, turn ended");

	PLAYER_TURN = true;
}



inline void CheckKeyboardInput() 
{
	if (IsKeyPressed(KEY_Z))
	{
		cout << "CheckKeyboardInput Z PRESSED" << endl;
		Z_pressed_count++;


	}

	if (IsKeyPressed(KEY_X))
	{
		cout << "X PRESSED" << endl;
		X_pressed_count++;

		//printf("%d", GetRandomValue(0, 99));

	}

	if (IsKeyPressed(KEY_L))
	{
		cout << "L PRESSED" << endl;

		SetFieldTileColors(target_field, 2);

		//printf("%d", GetRandomValue(0, 99));

	}

	if (IsKeyPressed(KEY_K))
	{
		cout << "K PRESSED" << endl;

		//setLayers();

		//cout << entity_list.size() + sum_of_field_tiles << endl;

		//for (size_t i = 0; i < entity_list.size(); i++)
		//{
		//	cout << "entity x: " << entity_list[i].x << " y: " << entity_list[i].y << endl;
		//	cout << "entity ID: " << entity_list[i].ID << endl;
		//}

		cout << "objects_to_render[0]: " << objects_to_render[0] << endl;

		cout << "objects_to_render[1]: " << objects_to_render[1] << endl;
		//cout << "SortedRenderObject_list: " << SortedRenderObject_list.size() << endl;

		randomSpawnTile(position_field, spawn_field);
		
		cout << "objects_to_render: " << objects_to_render[0] << endl;
		cout << "gui_entity_list: " << gui_entity_list.size() << endl;
		cout << "map_entity_list: " << map_entity_list.size() << endl;

		cout << "target_field.sum_of_field_tiles " << target_field.sum_of_field_tiles<< endl;

		cout << "render_list[0].List.size(): " << render_list[0].List.size() << endl;
		cout << "render_list[1].List.size(): " << render_list[1].List.size() << endl;

		cout << "SortedRenderObject_list.size(): " << SortedRenderObject_list.size() << endl;
	
	
		for (size_t i = 0; i < 100; i++)
		{
			cout << AllRenderObjects->texture.id << " ";
		}
		cout << endl;
	}

	if (IsKeyPressed(KEY_F5))
	{

		cout << "WriteSpriteDataRaw" << endl;
		WriteSpriteDataRaw(MAPS_PATH + "game_sprite_data_raw.txt");
	}


}

inline bool CheckColoredTileCollission(vector<tile> &colored_tiles, Rectangle  &temptarget)
{
	bool col = false;

	if (colored_tiles.empty() != true)
	{
		for (size_t i = 0; i < colored_tiles.size(); i++)
		{
			// Check if any tile has already been crossed
			if (CheckCollisionRecs(
				{ (float)(temptarget.x - 1 + (tile_width / 2)), (float)(temptarget.y - 1 + (tile_height / 2)), 2 ,2 },
				{ (float)(colored_tiles[i].x - 1 + (tile_width / 2)), (float)(colored_tiles[i].y - 1 + (tile_height / 2)), 2, 2 }))
			{
				//if (last_tile.x != temptarget.x || last_tile.y != temptarget.y)

				col = true;

				//Log("Colored tile ", (int)i);

				return col;



				break;
			}
			else
			{
				///moved = true;
			}
		}
	}


	return col;
}

inline bool CheckColoredMoveTileCollission( Rectangle  &temptarget)
{
	bool collission = false;

	if (colored_moved_tiles.empty() != true)
	{
		DebugLog("colored_moved_tiles.size()", (int)colored_moved_tiles.size());

		for (size_t i = 0; i < colored_moved_tiles.size() - 1; i++)
		{
			// Check if any tile has already been crossed
			if (CheckCollisionRecs(
				{ (float)(temptarget.x - 1 + (tile_width / 2)), (float)(temptarget.y - 1 + (tile_height / 2)), 2 ,2 },
				{ (float)(colored_moved_tiles[i].x - 1 + (tile_width / 2)), (float)(colored_moved_tiles[i].y - 1 + (tile_height / 2)), 2, 2 }))
			{
				//if (last_tile.x != temptarget.x || last_tile.y != temptarget.y)

				collission = true;


				DebugLog("Colored tile ", (int)i);

			    collission;

				break;
			}
			else
			{
				///moved = true;
			}
		}
	}


	return collission;
}

inline void AttackLogic()
{
	if(combatant_selected >= 0 )
	{
		ColorFieldTileEntityList(colored_enemy_tiles, &target_field, map_entity_list);
		if (colored_enemy_tiles.empty() != true)
		{
			Rectangle temp3 = { target->x, target->y, target->w, target->h };

			if ( CheckColoredTileCollission(colored_enemy_tiles, temp3) )
			{
				cout << "Attack collision" << endl;
			}
		}
	}
}

 Rectangle temptarget;

inline void ResetFieldVariables()
{
	move_field_up = false;

	colored_moved_tiles.clear();

	//move_list.clear();

	X_pressed_count = 0;

	Z_pressed_count = 0;

	last_tile = { -100,-100,0,0 };

	target_field.render_field = false;

	UpdateTargetFieldRange();

}

bool static previous_state = false;

inline void UpdateGameTurn()
{
	if (PLAYER_TURN != previous_state)
	{
		previous_state = PLAYER_TURN;

		game_turn++;
		Log("Game Turn ", game_turn);
	}
}

inline void MovePressed()
{
	move_field_up = true;

	ActionMenuUp = false;

	DebugLog("target_field.range action: ", target_field.range);
	DebugLog("current_movecount action: ", combatant_list[combatant_selected].current_movecount);

	UpdateTargetFieldRange();

	setField(target_field, combatant_list[combatant_selected].pEntity->x, combatant_list[combatant_selected].pEntity->y, SQUARE);

	target_field.render_field = true;

	colored_enemy_tiles.clear();

	colored_moved_tiles.clear();

	enemy_colored = false;
	entity_checked = 0;

}

inline void ReadyPressed()
{

	X_pressed_count = 0;

	precombat = false;

	target->x = combatant_list[combatant_selected].pEntity->x;
	target->y = combatant_list[combatant_selected].pEntity->y;

	position_field.render_field = false;

	ActionMenuUp = false;

	PLAYER_TURN = true;

}

inline void EndPressed()
{

	X_pressed_count = 0;
	Z_pressed_count = 0;

	position_field.render_field = false;

	ActionMenuUp = false;

	PLAYER_TURN = false;

	Log("Player ended turn ", game_turn);

	combatant_list[combatant_selected].current_movecount = 1;

	temp_movecount[combatant_selected] = combatant_list[combatant_selected].current_movecount;
}

inline void AttackPressed()
{
	enemy_colored = false;
	entity_checked = 0;

	target_field.range = world_player.attack_range;

	setField(target_field, combatant_list[0].pEntity->x, combatant_list[0].pEntity->y, SQUARE);

	target_field.render_field = true;

	ActionMenuUp = false;

	colored_enemy_tiles.clear();

	attacking = true;

	AttackLogic();
}


inline void ActionGuiLogic()
{
	if ( precombat == true)
	{
		if (ActionButton[0] == true ) {

			Log("Ready");

			ReadyPressed();

			ActionButton[0] = false;
		}
	}
	else 
	{
		if (ActionButton[0] == true && ActionMenuUp == true && X_pressed_count > 1 && combatant_list[combatant_selected].current_movecount < combatant_list[combatant_selected].move_range) {

			Log("Move");

			MovePressed();

			ActionButton[0] = false;
		}

		if (ActionButton[1] == true) {

			printf("Attack\n");

			AttackPressed();

			ActionButton[1] = false;
		}

		if (ActionButton[2] == true && ActionMenuUp == true && X_pressed_count > 1) {

			printf("END\n");

			EndPressed();

			ActionButton[2] = false;
		}

	}

	if (IsKeyPressed(KEY_UP))
	{
		if (currentbutton_index != top_button_index)
		{
			currentbutton_index--;
		}
		else
		{
			currentbutton_index = ActionMenuRects.size() - 1;
		}

		action_target->y = ActionMenuRects[currentbutton_index].y;
	}

	if (IsKeyPressed(KEY_DOWN))
	{
		if (currentbutton_index != ActionMenuRects.size() - 1)
		{
			currentbutton_index++;
		}
		else
		{
			currentbutton_index = top_button_index;
		}

		action_target->y = ActionMenuRects[currentbutton_index].y;
	}

	if (IsKeyPressed(KEY_LEFT))
	{
		//action_target->x = action_target->x + left_vel;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		//action_target->x = action_target->x + right_vel;
	}

	if (IsKeyPressed(KEY_Z))
	{
		cout << "ActionGuiLogic Z PRESSED" << endl;

		Z_pressed_count++;

		X_pressed_count = 0;

		ActionMenuUp = false;
	}
	

}

 bool collision = false;

inline void TargetLogic() {

	temptarget = { 0,0,0,0 };

	for (size_t i = 0; i < combatant_list.size(); i++)
	{
		if (target->ID == combatant_list[i].pEntity->ID)
		{
			
		}
		else
		{
			// Check if target is on combat entity position and X pressed, not on movefield, not moveing
			if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) && (target->x == combatant_list[i].pEntity->x) && (target->y == combatant_list[i].pEntity->y) && move_field_up == false && ActionMenuUp != true && !moving)
			{
				cout << "First Press X " << X_pressed_count << endl;

				cout << "Collision" << endl;
				setField(target_field, target->x, target->y, 0);

				//field_up = true;

				Z_pressed_count = 0;

				combatant_selected = i;

				action_target->x = (float)(combatant_list[i].pEntity->x + combatant_list[i].pEntity->w) + 16;
				action_target->y = (float)(combatant_list[i].pEntity->y - combatant_list[i].pEntity->h) + 20;

			    setActionMenu();

				ActionMenuUp = true;

				break;
			}

		}
	}

	if (move_field_up == true)
	{
		temptarget = { (float)target->x,(float)target->y,(float)target->w,(float)target->h };

		ColorFieldTileEntityList(colored_enemy_tiles, &target_field, map_entity_list);

		ColorFieldTile(target_field, target);

	

		//if ((GetTime() - last) > input_delay) // Needed to limit target movespeed
		//{
		//	last = (float)GetTime();

		if (combatant_list[combatant_selected].current_movecount < combatant_list[combatant_selected].move_range && !moving &&  on_field == true)
		{

			if (IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT))
			{
				temptarget.y = temptarget.y + up_vel;
				temptarget.x = temptarget.x + left_vel;

				moved_target = true;

				combatant_list[combatant_selected].current_movecount++;
				DebugLog("Up", combatant_list[combatant_selected].current_movecount);
				move_list.push_back(UP);
			}

			if (IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT))
			{
				temptarget.y = temptarget.y + down_vel;
				temptarget.x = temptarget.x + right_vel;

				moved_target = true;

				combatant_list[combatant_selected].current_movecount++;
				DebugLog("Down", combatant_list[combatant_selected].current_movecount);
				move_list.push_back(DOWN);
			}
			if (IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_RIGHT))
			{
				temptarget.y = temptarget.y + down_vel;
				temptarget.x = temptarget.x + left_vel;

				moved_target = true;

				combatant_list[combatant_selected].current_movecount++;
				DebugLog("Left", combatant_list[combatant_selected].current_movecount);
				move_list.push_back(LEFT);

			}
			if (IsKeyPressed(KEY_RIGHT) && !IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_LEFT))
			{
				temptarget.y = temptarget.y + up_vel;
				temptarget.x = temptarget.x + right_vel;

				moved_target = true;

				combatant_list[combatant_selected].current_movecount++;
				DebugLog("Right", combatant_list[combatant_selected].current_movecount);
				move_list.push_back(RIGHT);

			}
		}

		for (size_t i = 0; i < target_field.sum_of_field_tiles; i++)
		{
			if (CheckCollisionRecs(
				{ (float)temptarget.x,   (float)temptarget.y,   (float)temptarget.width, (float)temptarget.height },
				{ (float)target_field.x, (float)target_field.y, (float)target_field.w,   (float)target_field.h }))
			{

				DebugLog("Field Collision", 0);

				on_field = true;

				break;
			}
			else
			{
				DebugLog("Field Collision", 1);

				if (combatant_list[combatant_selected].current_movecount > 0)
				{
					combatant_list[combatant_selected].current_movecount--;
				}

				if (move_list.empty() != true) 
				{
					move_list.pop_back();
				}
		
				on_field = false;
				break;
			}
		}



		if (moved_target == true)
		{
			if ( CheckColoredTileCollission(colored_enemy_tiles, temptarget) || CheckColoredMoveTileCollission(temptarget))
			{
				moved_target = false;

				if (combatant_list[combatant_selected].current_movecount > 0)
				{
					combatant_list[combatant_selected].current_movecount--;
				}

				if (move_list.empty() != true)
				{

					move_list.pop_back();

					collision = true;

				}
			}
		}

		if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) && move_field_up == true && X_pressed_count != 1 && !moving)
		{
			cout << "Second Press X " << X_pressed_count << endl;

			//PrintMoveList();

			if (move_list.empty() != true) 
			{
				moving = true; 
				moved_target = false;
				temp_movecount[combatant_selected] = combatant_list[combatant_selected].current_movecount;
				//Log("current_movecount ", temp_movecount[combatant_selected]);

				ResetFieldVariables();
			}
			else 
			{
				cout << "move_list.empty() == true"  << endl;
			}

		}

		if ((IsKeyPressed(KEY_Z) && !IsKeyPressed(KEY_X)) && move_field_up == true && !moving)
		{

			if (Z_pressed_count == 1 && moved_target == true )
			{
				target->x = combatant_list[combatant_selected].pEntity->x;

				target->y = combatant_list[combatant_selected].pEntity->y;



				ResetMovedTilesColor(target_field, 3);

				colored_moved_tiles.clear();

				combatant_list[combatant_selected].current_movecount = temp_movecount[combatant_selected];

				moved_target = false;

				move_list.clear();

				Z_pressed_count = 0;

				//Log("Z_pressed_count == 1 && moved_target == true");

				//enemy_colored = false;
				//entity_checked = 0;

			}

			if (Z_pressed_count == 1 && moved_target == false && collision == false)
			{
				moved_target = false;

				cout << collision << endl;
				
				Log("(Z_pressed_count == 1 && (moved_target == false) && collision == false)");

				ResetFieldVariables();

				enemy_colored = false;
				entity_checked = 0;

			}

			if (Z_pressed_count == 1 && collision == true)
			{
				target->x = combatant_list[combatant_selected].pEntity->x;

				target->y = combatant_list[combatant_selected].pEntity->y;

				if (move_list.empty() == false)
				{
					ResetMovedTilesColor(target_field, 3);
				}

				colored_moved_tiles.clear();

				combatant_list[combatant_selected].current_movecount = temp_movecount[combatant_selected];

				moved_target = false;

				collision = false;

				move_list.clear();

				Z_pressed_count = 0;

				//Log("Z_pressed_count == 1 && moved_target == true");

				//enemy_colored = false;
				//entity_checked = 0;

			}



		}

		if (on_field == true && moved_target == true)
		{
			target->x = temptarget.x;
			target->y = temptarget.y;
		}
		else 
		{
		
		}

	}
	else // Not on a movefield
	{
		if (ActionMenuUp != true)
		{
			if ((GetTime() - last2) > input_delay) // Needed to limit target movespeed
			{
				last2 = (float)GetTime();

				if (IsKeyDown(KEY_UP))
				{
					target->y = target->y + up_vel;
				}

				if (IsKeyDown(KEY_DOWN))
				{
					target->y = target->y + down_vel;
				}
				if (IsKeyDown(KEY_LEFT))
				{
					target->x = target->x + left_vel;
				}
				if (IsKeyDown(KEY_RIGHT))
				{
					target->x = target->x + right_vel;
				}
			}

			//colored_tiles.clear();

			last_tile = { -100,-100,0,0 };

		}

	}

	if (attacking == true) 
	{
		AttackLogic();
	}



}



inline void MoveUnit()
{
	if (ActionMenuUp != true)
	{
		if ((GetTime() - last) > 0.08) // Needed to limit target movespeed
		{
			last = (float)GetTime();

			if (IsKeyDown(KEY_W))
			{
				AnimateMovement(combatant_list[0].pEntity, UP);
				combatant_list[0].pEntity->y = combatant_list[0].pEntity->y - (right_vel / 2);
			}

			if (IsKeyDown(KEY_S))
			{
				AnimateMovement(combatant_list[0].pEntity, DOWN);
				combatant_list[0].pEntity->y = combatant_list[0].pEntity->y + (right_vel / 2);
			}
			if (IsKeyDown(KEY_A))
			{
				AnimateMovement(combatant_list[0].pEntity, LEFT);
				combatant_list[0].pEntity->x = combatant_list[0].pEntity->x - (right_vel / 2);

			}
			if (IsKeyDown(KEY_D))
			{
				AnimateMovement(combatant_list[0].pEntity, RIGHT);

				combatant_list[0].pEntity->x = combatant_list[0].pEntity->x + (right_vel / 2);


			}
		}


	}
}

 static bool startset = false;

inline bool HoverSelect(field &fieldRef, entity *e)
{
	bool ret = false;

	int mouseX = GetMouseX();
	int mouseY = GetMouseY();

	Rectangle mouseRect = { mouseX,mouseY,1,1 };
	//	Rectangle tempEntityRect;

	//Rectangle tempEntityRect = { 0,0,0,0 };

	combatant_list[combatant_selected].pEntity->render_this = true;

	Rectangle tempEntityRect;

	if (startset == false) 
	{
		tempEntityRect = { (float)fieldRef.tiles[0].x, (float)fieldRef.tiles[0].y,(float)fieldRef.tiles[0].w, (float)fieldRef.tiles[0].h };

		combatant_list[combatant_selected].pEntity->x = tempEntityRect.x;

		combatant_list[combatant_selected].pEntity->y = tempEntityRect.y;

		cout << (float)fieldRef.tiles[10].x << endl;

		cout << (float)fieldRef.tiles[10].y << endl;

		startset = true;

		ret = true;
	}



	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		tempEntityRect = { (float)fieldRef.tiles[i].x, (float)fieldRef.tiles[i].y,(float)fieldRef.tiles[i].w, (float)fieldRef.tiles[i].h };

		if (CollisionIsoTrianglesMouse( tempEntityRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			printf("Collision with tile: x:%.0f y:%.0f \n", tempEntityRect.x, tempEntityRect.y);

			combatant_list[combatant_selected].pEntity->x = tempEntityRect.x;

			combatant_list[combatant_selected].pEntity->y = tempEntityRect.y;

			ret = true;
		}


	}

	

	return ret;

}

inline void MouseLogic() 
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && true)
	{
		//	printf("Button LEFT is pressed and Entity one clicked");

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

inline void EditorGuiLogic() 
{
	if (SaveButton001 == true) {

		printf("Saved entitiy data\n");

		WriteEntityData(GAME_ASSET_PATH + "game_entity_data.txt");

		SaveButton001 = false;
	}

	if (SaveButton002 == true) {

		printf("Saved Sprite data\n");

		WriteSpriteData(GAME_ASSET_PATH + "game_sprite_data.txt");

		SaveButton002 = false;
	}

	if (ReloadButton == true) {

		printf("Reload");

		

		ReloadButton = false;
	}
}

 bool run_init = false;



inline void CombatLogic() 
{
	if (combat == true)
	{
		UpdateGameTurn();

		if (run_init == false)
		{
			initCombat();

			run_init = true;

			precombat = true;

			combatant_selected = 0;

			position_field.render_field = true;
		
			ActionMenuUp = true;
		}

		if (precombat == true)
		{
			if (HoverSelect(position_field, combatant_list[combatant_selected].pEntity) == true )
			{
				setActionMenu();
			}
		}

		if ( PLAYER_TURN == true )
		{


		}
		else 
		{
			EnemyLogic();
		}


	}
	else
	{
		// Overworld Logic
		gui_entity_list[0].render_this = true;
		world_player.pEntity->render_this = true;

		player.pEntity->render_this = true;
		MoveUnit();
	}

}



#endif