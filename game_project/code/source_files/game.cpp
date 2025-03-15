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
  int entity_count = 0;
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

  sprite_count = ReadSpriteData(GameState, MAPS_PATH + "game_sprite_data.txt");

  if (sprite_count > 0) {
    printf("LoadSpriteData(sprite_count), sprite_count was %d\n", sprite_count);
    LoadSpriteData(GameState, sprite_count);
  } else {
    printf("LoadSpriteData(sprite_count), sprite_count was %d\n", sprite_count);
  }

  entity_count =
      ReadEntityData(GameState, MAPS_PATH + "game_entity_data_temp.txt");

  if (entity_count > 0) {
    printf("LoadEntityData(entity_count), entity_count was %d\n", entity_count);
    LoadEntityData(GameState, entity_count);
  } else {
    printf("LoadEntityData(entity_count), entity_count was %d\n", entity_count);
  }

  SetSpriteTextures(GameState.SpriteList, GameState.GameTextureList);

  if (ReadMapDataTiledMap(GameState, TILED_MAPS_PATH + "untitled.tmx")) {
    SetMapCordsTiled(GameState);
  }

  SetPosCords(GameState.Map.PosCords);

  // for (size_t i = 0; i < 40; i++)
  // {
  //   for (size_t j = 0; j < 20; j++)
  //   {
  //     cout << " " << GameState.Map.PosCords[i][j].x << "." <<
  //     GameState.Map.PosCords[i][j].y;
  //   }
  //   cout << endl;
  // }

  SetEntityCords(GameState.Map, GameState.EntityList, 0);
  SetEntityCords(GameState.Map, GameState.EntityList, 1);
  SetEntityCords(GameState.Map, GameState.EntityList, 2);
  SetEntityCords(GameState.Map, GameState.EntityList, 4);
  SetEntityCords(GameState.Map, GameState.EntityList, 5);

  // Loads entities seperate from game entities that need to be present on a map
  SetGuiEntities(GameState.Gui, GameState.EntityList);

  SetPlayer(GameState, PLAYER_SPRITE_ID);

  printf("Load done\n");
}

inline void Init(game_state &GameState) {
  Load(GameState);

  InitLog();
  InitDebugLog();

  // Init seed used for randomness
  rng.seed(time(0));

  Render_List temp1;
  Render_List temp2;

  GameState.RenderList.push_back(temp1);

  GameState.RenderList.push_back(temp2);

  // Init this with the first entity, used to render entity info
  GameState.Editor.GameEntity = &GameState.EntityList[0];

  ////////////////////   TARGET //////////////////////////////////

  GameState.Target.pEntity =
      &GetEntityByID(TARGET_ID, GameState.Gui.EntityList);

  GameState.Target.pEntity->render_this = false;

  GameState.Target.right_vel = (GAME_TILE_WIDTH / 2);
  GameState.Target.left_vel = -(GAME_TILE_WIDTH / 2);
  GameState.Target.up_vel = -(GAME_TILE_HEIGHT / 2);
  GameState.Target.down_vel = (GAME_TILE_HEIGHT / 2);

  ////////////////////   PLAYER(Julius) //////////////////////////////////

  cout << "PLAYER this happens " << endl;

  GameState.WorldPlayer.pEntity =
      &GetEntityByID(PLAYER_ID, GameState.Map.EntityList);

  cout << "PLAYER ID " << GameState.WorldPlayer.pEntity->ID << endl;

  GameState.WorldPlayer.move_range = 9;
  GameState.WorldPlayer.attack_range = 4;
  GameState.WorldPlayer.pEntity->use_shader = true;

  GameState.WorldPlayer.attack_field.range = 4;
  GameState.WorldPlayer.attack_field.field_alpha = 0.5;
  GameState.WorldPlayer.pEntity->render_this = true;

  SetField(GameState, GameState.WorldPlayer.attack_field,
           GameState.WorldPlayer.pEntity->x, GameState.WorldPlayer.pEntity->y,
           SQUARE, BLUE_TILE);

  GameState.FieldList.push_back(&GameState.WorldPlayer.attack_field);

  GameState.CombatantSelected = GameState.WorldPlayer;
  GameState.Map.CombatantList.push_back(GameState.CombatantSelected);

  ////////////////////   ENEMIES  //////////////////////////////////

  cout << "ENEMIES this happens 2" << endl;

  combatant e1;

  e1.move_range = 2;
  e1.move_field.range = 3;

  e1.pEntity = &GetEntityByID(SLIME_ID, GameState.Map.EntityList);
  e1.pEntity->render_this = true;

  e1.x_vel = ROAMING_VEL.right;
  e1.y_vel = ROAMING_VEL.down;

  InitUniqueSprite(GameState, e1, 1000);

  GameState.Map.EnemyList.push_back(e1);

  e1.pEntity = &GetEntityByID(SLIME_ID2, GameState.Map.EntityList);

  InitUniqueSprite(GameState, e1, 1001);
  GameState.Map.EnemyList.push_back(e1);

  InitEnemyFields(GameState);

  ////////////////////   LOG  //////////////////////////////////
  Log("Init");
  Log("test 1");

  for (size_t i = 0; i < 15; i++) {
    Log("Log");
  }

  CAMERA.offset =
      Vector2{(float)GAMEWINDOW_WIDTH / 2, (float)GAMEWINDOW_HEIGHT / 2};
  CAMERA.rotation = 0;
  CAMERA.zoom = CAMERA_ZOOM;
}

inline void InitShaders() {
  printf("######################### SHADER ##############################\n");
  GAME_SHADER =
      LoadShader(0, TextFormat("resources/assets/shaders/outline.fs"));

  float outlineSize = 1.75f;
  float outlineColor[4] = {0.0f, 1.0f, 0.0f, 1.0f};  // Normalized Greed color

  // sprite w : [28] sprite h : [40] -> Julius
  float textureSize[2] = {(float)(200), (float)(200)};

  // Get shader locations
  int outlineSizeLoc = GetShaderLocation(GAME_SHADER, "outlineSize");
  int outlineColorLoc = GetShaderLocation(GAME_SHADER, "outlineColor");
  int textureSizeLoc = GetShaderLocation(GAME_SHADER, "textureSize");

  // Set shader values (they can be changed later)
  SetShaderValue(GAME_SHADER, outlineSizeLoc, &outlineSize,
                 SHADER_UNIFORM_FLOAT);
  SetShaderValue(GAME_SHADER, outlineColorLoc, outlineColor,
                 SHADER_UNIFORM_VEC4);
  SetShaderValue(GAME_SHADER, textureSizeLoc, textureSize, SHADER_UNIFORM_VEC2);
}

// Gameplay Screen Initialization logic
inline void InitGameplayScreen(game_state &GameState) {
  framesCounter = 0;
  finishScreen = 0;

  SetTargetFPS(TARGET_FPS);  // Set our game to run at 60 frames-per-second

  Init(GameState);

  InitShaders();
  InitActionMenu(GameState.ActionMenu);

  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    cout << GameState.Map.EnemyList[i].pEntity->sprite->name << endl;

    GameState.Map.EnemyList[i].roaming_ellipse.center = {
        GameState.Map.EnemyList[i].pEntity->x + GAME_TILE_WIDTH / 2,
        GameState.Map.EnemyList[i].pEntity->y + GAME_TILE_HEIGHT / 2};

    GameState.Map.EnemyList[i].roaming_ellipse.w = (GAME_TILE_WIDTH * 8) / 4;
    GameState.Map.EnemyList[i].roaming_ellipse.h = (GAME_TILE_HEIGHT * 8) / 1;
  }

  for (size_t i = 0; i < GameState.EntityList.size(); i++) {
    cout << GameState.EntityList[i].collision_effect << " ";
  }
  cout << endl;


  

}

static int DrawGameplayScreen_runonce = 0;
// Game logic
inline void UpdateGameplayScreen(game_state &GameState) {
  static int UpdateGameplayScreen_runonce = 0;

  static int animating = 0;
  CAMERA.zoom = CAMERA_ZOOM;
  // TODO Optimize this seem ineffieicent
  SetEntityListEllipses(GameState.Map.EntityList);

  if (UpdateGameplayScreen_runonce == 0) {
    printf("UpdateGameplayScreen\n");

    UpdateGameplayScreen_runonce++;
  }

  if (NewEntityButton) {
    printf("NewEntityButton Clicked\n");
    PLACING_ENTITY = true;
    NewEntityButton = false;
  }

  CheckKeyboardInput(GameState);
  MouseLogic();

  MOUSE_POINT= GetCameraMousePosition(GameState);


  // if (setMouseEntity(GameState.Map.EntityList) == true) {
  // }

  // CreateNewEntity(GameState.Editor,GameState.Map,GameState.EntityList);

  if (DEBUG_TOGGLE_COMBAT == true) {
    CombatLogic(GameState);

    if (GameState.CombatantSelected.pEntity != 0) {
      MovementAnimated(GameState, GameState.CombatantSelected.pEntity,
                       COMBAT_VEL);
      // moving = false;
    }

    EnemyMovementAnimated(GameState, ROAMING_VEL);

  } else {
    // Overworld Logic

    if (GameState.AnimatingMovement == false) {
      MoveUnit(GameState, PLAYER_VEL);
    } else {
    }

    if (DrawGameplayScreen_runonce != 0) {
      if (GameState.AnimatingEnemyMovement == false &&
          GameState.AnimatingMovement == false) {
      //  EnemyRoaming2(GameState, ROAMING_VEL);
      } else {
       // EnemyMovementAnimated(GameState, ROAMING_VEL);
      }
    }
  }

  if (GameState.ActionMenu.is_menu_up == true) {
    ActionGuiLogic(GameState);
  } else {
    GameState.Target.pEntity->render_this = true;

    TargetLogic(GameState);
  }

  CAMERA.target =
      Vector2{(GameState.WorldPlayer.pEntity->x) ,
              (GameState.WorldPlayer.pEntity->y) };

}

// Gameplay Screen Rendering
inline void DrawGameplayScreen(game_state &GameState) {
  if (DrawGameplayScreen_runonce == 0) {
    printf("DrawGameplayScreen\n");
    for (size_t i = 0; i < 10; i++)
    {
      cout << 64*i << " ";
    }

  }

  DrawFPS(GRID_WIDTH- GAME_TILE_WIDTH*1, 0);

  // Zero out the render objects array
  memset(GameState.ObjectsToRender, 0, sizeof(GameState.ObjectsToRender));

  if (DrawGameplayScreen_runonce == 0) {
    printf("memset GameState.ObjectsToRender\n");
  }

  RenderEntities(GameState, GameState.Gui.EntityList, GameState.RENDER_INDEX);

  RenderEntities(GameState, GameState.Map.EntityList, GameState.RENDER_INDEX);

  if (DrawGameplayScreen_runonce == 0) {
    printf("RenderEntities GameState.Map.EntityList\n");
  }

  RenderAllFields(GameState, GameState.RENDER_INDEX);

  if (DrawGameplayScreen_runonce == 0) {
    printf("RenderAllFields\n");
  }

  SortLayerRenderObjectList(GameState.RenderList[GameState.RENDER_INDEX],
                            GameState.SortedRenderObjectList,
                            GameState.CurrentLayerList);

  // ############################### BEGIN CAMERA
  // ###############################
  if (TOGGLE_CAMERA_MODE) {
    BeginMode2D(CAMERA);
  }

  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    DrawEllipse(GameState.Map.EnemyList[i].roaming_ellipse.center.x +
                    GAMESCREEN_OFFSET_X,
                GameState.Map.EnemyList[i].roaming_ellipse.center.y +
                    GAMESCREEN_OFFSET_Y,
                GameState.Map.EnemyList[i].roaming_ellipse.h,
                GameState.Map.EnemyList[i].roaming_ellipse.w, BLUE);
  }

  RenderAllLayers(GameState, GameState.SortedRenderObjectList);



  if (GameState.ActionMenu.is_menu_up == true) {
    DrawActionGui(GameState.ActionMenu);
  }

  if (DEBUG_TOGGLE_COMBAT) {
    RenderEntityInfo(GameState);
  }

  RenderEntityBoxes(GameState.Map.EntityList);

  if (PLACING_ENTITY == true) {
    RenderNewEntity(GameState);
  }

  RenderSelectedSprite(GameState);

  //DrawCircle(MOUSE_POINT.x + GAME_TILE_WIDTH, MOUSE_POINT.y+ GAME_TILE_HEIGHT, 10, RED);

  // ############################### END CAMERA ###############################
  if (TOGGLE_CAMERA_MODE) {
    EndMode2D();
  }

  //DrawLineEx( {(float)GAMEWINDOW_WIDTH/2, 0},{(float)GAMEWINDOW_WIDTH/2, (float)GAMEWINDOW_HEIGHT}, 3,BLACK );

  DrawEditorGui(GameState);

  RenderLog();
  RenderDebugLog();

  DrawGameplayScreen_runonce++;
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