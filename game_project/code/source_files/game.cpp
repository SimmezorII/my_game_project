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
	
	target = &getEnityByID("target", gui_entity_list);

	target->render_this = false;

	player.move_range = 7;

	for (size_t i = 0; i < game_entity_list.size(); i++)
	{
		cout << "entity in init " << game_entity_list[i]->ID << endl;
	}

	player.pEntity = getEnityByID(8, game_entity_list);

	world_player.pEntity = getEnityByID(9, game_entity_list);


	player.pEntity->sprite->offset_x = (-0 * (player.pEntity->w / 4) );
	player.pEntity->sprite->offset_y = (-0 * player.pEntity->h / 2);

	world_player.move_range = 7;

	world_player.attack_range = 2;

	target_field.range = 5;

	setField(target_field, entity_list[0].x, entity_list[0].y, SQUARE);

	combatant_list.push_back(world_player);

	combatant_list.push_back(player);

	action_target = &action_target_rect;

	//AddDebugText();

	Render_List temp1;
	Render_List temp2;

	render_list.push_back(temp1);

	render_list.push_back(temp1);

	objects_to_render.push_back(0);
	objects_to_render.push_back(0);

	printf("before init combat\n");

	initCombat();


	Log("test 1");

	for (size_t i = 0; i < 15; i++)
	{
		Log("Log");
	}

	Log("Init");

	render_entity_boxes = true;
}


// Gameplay Screen Initialization logic
inline void InitGameplayScreen(void)
{
	framesCounter = 0;
	finishScreen = 0;

	Init();

	//InitGui();

	initActionMenu();

	//for (size_t i = 1; i < 80; i++)
	//{
		//calcDrawLayer(i, Layers[i-1]);
	//}

	render_list[0].render_this = true;

}



// Game logic
inline void UpdateGameplayScreen(void)
{
	CheckKeyboardInput();
	//UpdateDebugText();
	

	for (size_t i = 0; i < map_entity_list.size(); i++)
	{
		if (map_entity_list[i].ID == 6)
		{
			if (CheckCollisionRecs({(float)world_player.pEntity->x, (float)world_player.pEntity->y,  (float)world_player.pEntity->w, (float)world_player.pEntity->h },
				                   {(float)(map_entity_list[i].x),(float)(map_entity_list[i].y), (float)(map_entity_list[i].w) / 2, (float)(map_entity_list[i].h) / 2 }))
			{
			//	cout << "collision sedric" << endl;
				combat = true;
			}
		}
	}


	if (NewEntityButton) 
	{
		printf("NewEntityButton Clicked\n");
		PLACING_ENTITY = true;
		NewEntityButton = false;
	}

	if (setMouseEntity(map_entity_list)  == true) 
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

	render_entity_boxes = ToggleEntityBoxes;

	if (combatant_selected > -1)
	{
		MovementAnimated(combatant_list[combatant_selected].pEntity);
	}

}


// Gameplay Screen Rendering
inline void DrawGameplayScreen(void)
{
	DrawFPS(GameGui.x - 200, 0);

	//ClearBackground(WHITE);


	for (size_t i = 0; i < objects_to_render.size(); i++)
	{
		objects_to_render[i] = 0;
	
	}

	RenderEntities(map_entity_list);

	RenderEntities(gui_entity_list);

	RenderField(position_field);

	RenderField(spawn_field);

	RenderField(target_field);

	//RendedDebugInfo();

	SortLayerRenderObjectList();

	RenderAllLayers();



	DrawGui();

	RenderSelectedSprite();

	if (ActionMenuUp == true)
	{
		DrawActionGui();
	}


	if (PLACING_ENTITY == true)
	{
		RenderNewEntity();
	}

	RenderEntityBoxes(gui_entity_list);
	RenderEntityBoxes(map_entity_list);

	//drawIsoTriangles(target);
	
	//DebugLog("test 14: ", LogScrollCounter);


	RenderLog();

	//RenderDebugLog();
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