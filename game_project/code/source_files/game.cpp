/* ========================================================================

======================================================================== */


//#include "file_handler.cpp" // included in logic.cpp
//#include "game_engine.cpp" // included in logic.cpp

#include "logic.cpp"
#include "combat.cpp"
#include "gui.cpp"
#include "../header_files/raylib.h"

#include "../header_files/raylib_functions.h"


//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

static int framesCounter;
static int finishScreen;

//----------------------------------------------------------------------------------
//  Variables Definition 
//----------------------------------------------------------------------------------

Rectangle panelRec2 = { 20, 40, 200, 150 };
Rectangle panelContentRec2 = { 0, 0, 340, 340 };
Vector2 panelScroll2 = { 99, -20 };

Rectangle ctrlvalue = { 0, 0, 0, 0 };

float offset_x = 0;
float offset_y = 0;

//----------------------------------------------------------------------------------
// Function Definitions
//----------------------------------------------------------------------------------


inline void Load()
{
	int sprite_count;

	png_list = GetPNG_FilesInDir(GAME_ASSET_PATH.c_str());

	//Loads all png files into textures
	if (!GAME_CreateTextures())
	{
		printf("Failed to load GUI media!\n");
	}
	else
	{

	}

	sprite_count = ReadSpriteData(MAPS_PATH + "game_sprite_data.txt");

	if (sprite_count > 0)
	{
		printf("LoadSpriteData(sprite_count), sprite_count was %d\n", sprite_count);
		LoadSpriteData(sprite_count);
	}
	else
	{
		printf("LoadSpriteData(sprite_count), sprite_count was %d\n", sprite_count);
	}

	entity_count = ReadEntityData(MAPS_PATH + "game_entity_data_temp.txt");

	if (sprite_count > 0)
	{
		printf("LoadEntityData(entity_count), entity_count was %d\n", entity_count);
		LoadEntityData(entity_count);
	}
	else
	{
		printf("LoadEntityData(entity_count), entity_count was %d\n", entity_count);
	}

	SetSpriteTextures();

	if (ReadMapData(MAPS_PATH + "map2.txt"))
	{
		setMapCords();
	}
	else
	{
		printf("\n");
	}

	setPosCords();

	setEntityCords();

	// Loads entities seperate from game entities that need to be present on a map
	setGuiEntities();

	player_entity_ID = 9;

	setPlayer();

	printf("Sprite string:%s\n", sprite_png_list.c_str());

	printf("Load done\n");

}


inline void Init()
{
	Load();

	InitLog();
	InitDebugLog();

	game_entity = &entity_list[0];

	target = &getEntityByID("target", gui_entity_list);

	target->render_this = false;

	player.move_range = 0;

	for (size_t i = 0; i < game_entity_list.size(); i++)
	{
		cout << "entity in init " << game_entity_list[i]->ID << endl;
	}

	player.pEntity = getEntityByID(8, game_entity_list);

	world_player.pEntity = getEntityByID(9, game_entity_list);

	player.pEntity->sprite->offset_x = (-0 * (player.pEntity->w / 4));
	player.pEntity->sprite->offset_y = (-0 * player.pEntity->h / 2);

	world_player.move_range = 4;

	world_player.attack_range = 2;

	target_field.range = 4;  

	combatant e1;

	combatant e2;

	e1.move_range = 2;

	e2.move_range = 2;

	e1.move_field.range = 2;

	e2.move_field.range = 2;

	e1.pEntity = &getEntityByID(24, map_entity_list);

	e2.pEntity = &getEntityByID(25, map_entity_list);

	setField(target_field, entity_list[0].x, entity_list[0].y, SQUARE, (Col)GREEN_TILE);

	fields.push_back(&target_field);

	combatant_list.push_back(world_player);

	combatant_list.push_back(player);

	enemy_list.push_back(e1);

	enemy_list.push_back(e2);

	action_target = &action_target_rect;

	//AddDebugText();

	Render_List temp1;
	Render_List temp2;

	render_list.push_back(temp1);

	render_list.push_back(temp1);

	objects_to_render.push_back(0);
	objects_to_render.push_back(0);

	printf("before init combat\n");

	InitCombat();

	Log("test 1");

	for (size_t i = 0; i < 15; i++)
	{
		Log("Log");
	}

	Log("Init");

	//render_entity_boxes = true;

	// Init seed used for randomness
	rng.seed(time(0));

	setField(enemy_list[0].move_field, enemy_list[0].pEntity->x, enemy_list[0].pEntity->y, SQUARE, (Col)RED_TILE);

	cout << "target tiles:" << target_field.sum_of_field_tiles << endl;

	cout << "e1 tiles:" << enemy_list[0].move_field.sum_of_field_tiles << endl;

	fields.push_back(&enemy_list[0].move_field);
}

// Gameplay Screen Initialization logic
inline void InitGameplayScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	Init();

	InitGui();

	initActionMenu();

	//render_list[0].render_this = true;

}

// Game logic
inline void UpdateGameplayScreen(void)
{

	static int UpdateGameplayScreen_runonce = 0;

	static int animating = 0;


	if (moving != true && enemy_moving != true)
	{

		CheckKeyboardInput();
		//UpdateDebugText();


		//for (size_t i = 0; i < map_entity_list.size(); i++)
		//{
		//	if (map_entity_list[i].ID == 6)
		//	{
		//		if (CheckCollisionRecs({(float)world_player.pEntity->x, (float)world_player.pEntity->y,  (float)world_player.pEntity->w, (float)world_player.pEntity->h },
		//			                   {(float)(map_entity_list[i].x),(float)(map_entity_list[i].y), (float)(map_entity_list[i].w) / 2, (float)(map_entity_list[i].h) / 2 }))
		//		{
		//			cout << "collision sedric" << endl;
		//			combat = true;
		//		}
		//	}
		//}

		if (UpdateGameplayScreen_runonce == 0)
		{
			printf("UpdateGameplayScreen\n");

			UpdateGameplayScreen_runonce++;
		}

		if (NewEntityButton)
		{
			printf("NewEntityButton Clicked\n");
			PLACING_ENTITY = true;
			NewEntityButton = false;
		}

		if (setMouseEntity(map_entity_list) == true)
		{

		}

		CreateNewEntity();

		MouseLogic();

		CombatLogic();

		if (ActionMenuUp == true)
		{
			ActionGuiLogic();
		}
		else
		{
			target->render_this = true;

			TargetLogic();
		}

		//render_entity_boxes = ToggleEntityBoxes;



	}
	else
	{

		if (moving == true)
		{
			if (combatant_selected > -1)
			{

				MovementAnimated(combatant_list[combatant_selected].pEntity);
				//moving = false;
			}
		}

		if (enemy_moving == true)
		{
			EnemyMovementAnimated();
		}
	}


}

// Gameplay Screen Rendering
inline void DrawGameplayScreen(void)
{
	static int DrawGameplayScreen_runonce = 0;

	if (DrawGameplayScreen_runonce == 0)
	{
		printf("DrawGameplayScreen\n");
	}

	DrawFPS(GameGui.x - 200, 0);

	for (size_t i = 0; i < objects_to_render.size(); i++)
	{
		objects_to_render[i] = 0;
	}

	if (DrawGameplayScreen_runonce == 0)
	{
		printf("This happens 1\n");
	}

	RenderEntities(map_entity_list);

	RenderEntities(gui_entity_list);

	RenderEntities(new_entity_list);

	if (DrawGameplayScreen_runonce == 0)
	{
		printf("This happens 2\n");

	}

	RenderAllFields();

	if (DrawGameplayScreen_runonce == 0)
	{
		printf("This happens 3\n");
	}

	//RendedDebugInfo();

	SortLayerRenderObjectList();

	RenderAllLayers();

	DrawGui();

	RenderSelectedSprite();

	if (DrawGameplayScreen_runonce == 0)
	{
		printf("This happens 4\n");
	}

	if (ActionMenuUp == true)
	{
		DrawActionGui();
	}


	if (PLACING_ENTITY == true)
	{
		RenderNewEntity();
	}

	//RenderEntityBoxes(gui_entity_list);
	RenderEntityBoxes(map_entity_list);

	RenderEntityBoxes(new_entity_list);

	//drawIsoTriangles(target);

	DebugLog("combatant_selected: ", combatant_selected);

	RenderEntityInfo();

	RenderLog();

	RenderDebugLog();

	if (DrawGameplayScreen_runonce == 0)
	{
		printf("This happens 5\n");
	}

	DrawGameplayScreen_runonce++;



}


// Unload logic
inline void UnloadGameplayScreen(void)
{
	// TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen finish
inline int FinishGameplayScreen(void)
{
	return finishScreen;
}