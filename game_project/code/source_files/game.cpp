/* ========================================================================

======================================================================== */

//#include "file_handler.cpp" // included in logic.cpp
//#include "game_engine.cpp" // included in logic.cpp

#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"
#include "combat.cpp"
#include "gui.cpp"
#include "logic.cpp"

//----------------------------------------------------------------------------------
// Global Variables Definition (local to this module)
//----------------------------------------------------------------------------------

static int framesCounter;
static int finishScreen;

//----------------------------------------------------------------------------------
//  Variables Definition
//----------------------------------------------------------------------------------

Rectangle panelRec2 = {20, 40, 200, 150};
Rectangle panelContentRec2 = {0, 0, 340, 340};
Vector2 panelScroll2 = {99, -20};

Rectangle ctrlvalue = {0, 0, 0, 0};

float offset_x = 0;
float offset_y = 0;

//----------------------------------------------------------------------------------
// Function Definitions
//----------------------------------------------------------------------------------

inline void Load(game_state &GameState) {
  int sprite_count = 0;
  int result;
  // old png_list = GetPNG_FilesInDir(GAME_ASSET_PATH.c_str());

  result = GetPNG_FilesInDir(GAME_ASSET_PATH.c_str(), GameState.PNGList,
                             GameState.AllPNGList);

  // Loads all png files into textures
  if (!GAME_CreateTexturesFromImage(GameState.GameImageList, GameState.PNGList,
                                    GameState.GameTextureList,
                                    GAME_ASSET_PATH)) {
    printf("Failed to load GUI media!\n");
  } else {
  }

  sprite_count = ReadSpriteData(MAPS_PATH + "game_sprite_data.txt");

  if (sprite_count > 0) {
    printf("LoadSpriteData(sprite_count), sprite_count was %d\n", sprite_count);
    LoadSpriteData(GameState, sprite_count);
  } else {
    printf("LoadSpriteData(sprite_count), sprite_count was %d\n", sprite_count);
  }

  entity_count = ReadEntityData(MAPS_PATH + "game_entity_data_temp.txt");

  if (entity_count > 0) {
    printf("LoadEntityData(entity_count), entity_count was %d\n", entity_count);
    LoadEntityData(GameState, entity_count);
  } else {
    printf("LoadEntityData(entity_count), entity_count was %d\n", entity_count);
  }

  SetSpriteTextures(GameState.SpriteList, GameState.GameTextureList);

  if (ReadMapDataTiledMap(TILED_MAPS_PATH + "untitled.tmx")) {
    setMapCordsTiled();
  }

  // if (ReadMapData(MAPS_PATH + "map2.txt"))
  // {
  // 	setMapCords();
  // }
  // else
  // {
  // 	printf("\n");
  // }

  setPosCords();

  setEntityCords(GameState.Map, GameState.EntityList, 0);
  setEntityCords(GameState.Map, GameState.EntityList, 1);
  setEntityCords(GameState.Map, GameState.EntityList, 2);

  // Loads entities seperate from game entities that need to be present on a map
  SetGuiEntities(GameState.EntityList);

  setPlayer(GameState);

  printf("Load done\n");
}

inline void Init(game_state &GameState) {
  player_entity_ID = 9;

  Load(GameState);

  InitLog();
  InitDebugLog();

  // Init seed used for randomness
  rng.seed(time(0));

  Render_List temp1;
  Render_List temp2;

  render_list.push_back(temp1);

  render_list.push_back(temp1);

  objects_to_render.push_back(0);
  objects_to_render.push_back(0);

  // Init this with the first entity, used to render entity info
  game_entity = &GameState.EntityList[0];

  ////////////////////   TARGET //////////////////////////////////

  target = &getEntityByID("target", gui_entity_list);

  target->render_this = false;

  ////////////////////   TARGET FIELD //////////////////////////////////

  target_field.range = 4;

  SetField(GameState, target_field, GameState.EntityList[0].x,
           GameState.EntityList[0].y, SQUARE, GREEN_TILE);

  fields.push_back(&target_field);

  ////////////////////  ATTACK TARGET FIELD //////////////////////////////////

  attack_target_field.range = 4;

  attack_target_field.field_alpha = 0.5;

  SetField(GameState, attack_target_field, GameState.EntityList[0].x,
           GameState.EntityList[0].y, SQUARE, BLUE_TILE);

  fields.push_back(&attack_target_field);

  ////////////////////   PLAYER(Julius) //////////////////////////////////

  cout << "PLAYER this happens " << endl;

  world_player.pEntity =
      &getEntityByID(player_entity_ID, GameState.Map.EntityList);

  world_player.move_range = 8;

  world_player.attack_range = 2;

  world_player.pEntity->use_shader = true;

  world_player.pEntity->render_this = false;

  combatant_list.push_back(world_player);

  ////////////////////   ENEMIES  //////////////////////////////////

  cout << "ENEMIES this happens 2" << endl;

  combatant e1;

  combatant e2;

  e1.move_range = 2;

  e2.move_range = 2;

  e1.move_field.range = 3;

  e2.move_field.range = 3;

  e1.pEntity = &getEntityByID(24, GameState.Map.EntityList);

  e2.pEntity = &getEntityByID(25, GameState.Map.EntityList);

  enemy_list.push_back(e1);

  enemy_list.push_back(e2);

  InitEnemyFields(GameState);

  ////////////////////   LOG  //////////////////////////////////

  Log("Init");

  Log("test 1");

  for (size_t i = 0; i < 15; i++) {
    Log("Log");
  }
}

inline void InitShaders() {
  printf("######################### SHADER ##############################\n");
  shader = LoadShader(0, TextFormat("resources/assets/shaders/outline.fs"));

  float outlineSize = 1.75f;
  float outlineColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};  // Normalized Greed color

  // sprite w : [28] sprite h : [40] -> Julius
  float textureSize[2] = {(float)(140), (float)(158)};

  // Get shader locations
  int outlineSizeLoc = GetShaderLocation(shader, "outlineSize");
  int outlineColorLoc = GetShaderLocation(shader, "outlineColor");
  int textureSizeLoc = GetShaderLocation(shader, "textureSize");

  // Set shader values (they can be changed later)
  SetShaderValue(shader, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);
  SetShaderValue(shader, outlineColorLoc, outlineColor, SHADER_UNIFORM_VEC4);
  SetShaderValue(shader, textureSizeLoc, textureSize, SHADER_UNIFORM_VEC2);
}

// Gameplay Screen Initialization logic
inline void InitGameplayScreen(game_state &GameState) {
  framesCounter = 0;
  finishScreen = 0;

  SetTargetFPS(TARGET_FPS);  // Set our game to run at 60 frames-per-second

  Init(GameState);

  InitShaders();

  InitGui();

  InitActionMenu();
}

// Game logic
inline void UpdateGameplayScreen(game_state &GameState) {
  static int UpdateGameplayScreen_runonce = 0;

  static int animating = 0;

  SetEntityListEllipses(GameState.Map.EntityList);

  if (moving != true && enemy_moving != true) {
    CheckKeyboardInput(GameState);
    // UpdateDebugText();

    for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      if (GameState.Map.EntityList[i].ID == 1) {
        // if (({(float)world_player.pEntity->x, (float)world_player.pEntity->y,
        // (float)world_player.pEntity->w, (float)world_player.pEntity->h },
        // 	                   {(float)(GameState.Map.EntityList[i].x),(float)(GameState.Map.EntityList[i].y),
        // (float)(GameState.Map.EntityList[i].w) / 2,
        // (float)(GameState.Map.EntityList[i].h) / 2
        // }))
        // {
        // 	cout << "collision sedric" << endl;
        // //combat = true;
        // 	collision_map = true;
        // 	break;

        // }else
        // {
        // 	collision_map = false;
        // }
      }
    }

    if (UpdateGameplayScreen_runonce == 0) {
      printf("UpdateGameplayScreen\n");

      UpdateGameplayScreen_runonce++;
    }

    if (NewEntityButton) {
      printf("NewEntityButton Clicked\n");
      PLACING_ENTITY = true;
      NewEntityButton = false;
    }

    // if (setMouseEntity(GameState.Map.EntityList) == true) {
    // }

    CreateNewEntity(GameState.EntityList);

    MouseLogic();

    CombatLogic(GameState);

    if (action_menu_up == true) {
      ActionGuiLogic(GameState);
    } else {
      target->render_this = true;

      TargetLogic(GameState);
    }

    // render_entity_boxes = ToggleEntityBoxes;

  } else {
    if (moving == true) {
      if (combatant_selected > -1) {
        MovementAnimated(combatant_list[combatant_selected].pEntity);
        // moving = false;
      }
    }

    if (enemy_moving == true) {
      EnemyMovementAnimated();
    }
  }
}

// Gameplay Screen Rendering
inline void DrawGameplayScreen(game_state &GameState) {
  static int DrawGameplayScreen_runonce = 0;

  if (DrawGameplayScreen_runonce == 0) {
    printf("DrawGameplayScreen\n");
  }

  DrawFPS(GameGui.x - 200, 0);

  for (size_t i = 0; i < objects_to_render.size(); i++) {
    objects_to_render[i] = 0;
  }

  if (DrawGameplayScreen_runonce == 0) {
    printf("This happens 1\n");
  }

  RenderEntities(GameState, gui_entity_list, RENDER_INDEX);

  RenderEntities(GameState, GameState.Map.EntityList, RENDER_INDEX);

  RenderEntities(GameState, new_entity_list, RENDER_INDEX);

  if (DrawGameplayScreen_runonce == 0) {
    printf("This happens 2\n");
  }

  RenderAllFields(GameState);

  if (DrawGameplayScreen_runonce == 0) {
    printf("This happens 3\n");
  }

  SortLayerRenderObjectList(render_list[RENDER_INDEX], SortedRenderObject_list);

  RenderAllLayers(GameState, SortedRenderObject_list);

  DrawGui(GameState);

  RenderSelectedSprite(GameState);

  if (DrawGameplayScreen_runonce == 0) {
    printf("This happens 4\n");
  }

  if (action_menu_up == true) {
    DrawActionGui();
  }

  if (PLACING_ENTITY == true) {
    RenderNewEntity(GameState);
  }

  // RenderEntityBoxes(gui_entity_list);
  RenderEntityBoxes(GameState.Map.EntityList);

  // RenderEntityBoxes(new_entity_list);

  // drawIsoTriangles(target);

  DebugLog("combatant_selected: ", combatant_selected);

  RenderEntityInfo();

  RenderLog();

  RenderDebugLog();

  if (DrawGameplayScreen_runonce == 0) {
    printf("This happens 5\n");
  }

  DrawGameplayScreen_runonce++;

  // for(int i : last_sorted_list)
  // {
  // 	last_sorted_list[i] = 0;
  // }
}

// Unload logic
inline void UnloadGameplayScreen(game_state &GameState) {
  for (size_t i = 0; i < GameState.GameTextureList.size(); i++) {
    UnloadTexture(GameState.GameTextureList[i].tex);
  }

  // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen finish
inline int FinishGameplayScreen(game_state &GameState) { return finishScreen; }