
#include "../header_files/file_handler_func.h"
#include "../header_files/game_engine_func.h"
#include "../header_files/globals.h"
#include "../header_files/logic_func.h"
#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"

#define RAYGUI_IMPLEMENTATION
#include "../header_files/raygui.h"

Rectangle gui_temp = {0, 0, 100, 18};

Rectangle SpriteGroupBoxRect = {(float)(GAMESCREEN_OFFSET_X + GRID_WIDTH + 60),
                                20, 200, 800};

entity gui_temp_entity;

Rectangle temp_sprite_rec;

entity new_e;

int temp_w;
int temp_h;

int selected_sprite = 1;

static int GUItempx;

static int GUItempy;

inline void RenderEntityInfo( game_state & GameState) {
  string s;
  string name;
  Rectangle temp;



    DebugLog(GameState.CombatantSelected.pEntity->sprite->name);

    temp.x = GameState.CombatantSelected.pEntity->offset_rect.x;
    temp.y =
        GameState.CombatantSelected.pEntity->offset_rect.y - FONT_SIZE;
    temp.width = 100;  // Size of max string
    temp.height = FONT_SIZE;

    GuiLabel(temp,
             GameState.CombatantSelected.pEntity->sprite->name.c_str());

    s = to_string( (int)GameState.CombatantSelected.Stats.CurrentHP) + "/" + to_string( (int)GameState.CombatantSelected.Stats.MaxHP);
    temp.x = temp.x + s.size() * 6;
    GuiLabel(temp, s.c_str());

    for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {

        DebugLog(GameState.Map.EnemyList[i].pEntity->sprite->name);

        temp.x = GameState.Map.EnemyList[i].pEntity->offset_rect.x;
        temp.y = GameState.Map.EnemyList[i].pEntity->offset_rect.y - FONT_SIZE;
        temp.width = 100;  // Size of max string
        temp.height = FONT_SIZE;

        name = GameState.Map.EnemyList[i].pEntity->sprite->name;

        GuiLabel(temp, name.c_str());

        s = to_string((int)GameState.Map.EnemyList[i].Stats.CurrentHP) +
            "/" + to_string((int)GameState.Map.EnemyList[i].Stats.MaxHP);
        temp.x = temp.x + (name.size() * 6) + 6;
        // temp.y = temp.y + FONT_SIZE;
        GuiLabel(temp, s.c_str());

    }


}

inline void DrawEditorGui(game_state &GameState) {
  int n = 0;

  bool ToggleSpriteOffsetX = false;
  bool ToggleSpriteX = false;
  bool ToggleSpriteOffsetY = false;
  bool ToggleSpriteY = false;

  bool dropDown001EditMode = false;

  Rectangle SaveRect2 = {0, 0, 40, 24};

  SaveButton002 = GuiButton(
      {SaveRect2.x, SaveRect2.y, SaveRect2.width, SaveRect2.height}, "Save");

  GuiLine({SpriteGroupBoxRect.x - 60, SpriteGroupBoxRect.y, 200, 0}, "Sprite");
  //

  gui_temp.x = SpriteGroupBoxRect.x;
  gui_temp.y = 10 + SpriteGroupBoxRect.y + (n * 20);

  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "sprite id", &GameState.Editor.GameEntity->sprite->ID, 1,
             GameState.SpriteList.size(), false);
  n++;

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiLabel({gui_temp.x - 45, gui_temp.y, gui_temp.width, gui_temp.height},
           "sprite name");
  GuiTextBox(
      {gui_temp.x + 22, gui_temp.y, gui_temp.width - 10, gui_temp.height},
      strdup(GameState.Editor.GameEntity->sprite->name.c_str()), 12, false);
  n++;

  gui_temp.y = 10 + SpriteGroupBoxRect.y + (n * 20);

  gui_temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "sprite x", &GameState.Editor.GameEntity->sprite->x, 0, 2000, ToggleSpriteX);
  n++;
  ToggleSpriteX = GuiToggle(
      {gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height},
      "Edit", ToggleSpriteX);

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "sprite y", &GameState.Editor.GameEntity->sprite->y, 0, 2000, ToggleSpriteY);
  n++;
  ToggleSpriteY = GuiToggle(
      {gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height},
      "Edit", ToggleSpriteY);

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "sprite w", &GameState.Editor.GameEntity->sprite->w, 0, 2000, false);
  n++;
  GameState.Editor.GameEntity->sprite->w = GuiSliderBar(
      {gui_temp.x + 92, gui_temp.y, gui_temp.width, gui_temp.height}, "",
      TextFormat("%i", GameState.Editor.GameEntity->sprite->w), GameState.Editor.GameEntity->sprite->w, 0,
      2000);

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "sprite h", &GameState.Editor.GameEntity->sprite->h, 0, 2000, false);
  n++;
  GameState.Editor.GameEntity->sprite->h = GuiSliderBar(
      {gui_temp.x + 92, gui_temp.y, gui_temp.width, gui_temp.height}, "",
      TextFormat("%i", GameState.Editor.GameEntity->sprite->h), GameState.Editor.GameEntity->sprite->h, 0,
      2000);

  gui_temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "offset_x", &GameState.Editor.GameEntity->sprite->offset_x, -800, 2000,
             ToggleSpriteOffsetX);
  n++;
  ToggleSpriteOffsetX = GuiToggle(
      {gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height},
      "Edit", ToggleSpriteOffsetX);

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "offset_y", &GameState.Editor.GameEntity->sprite->offset_y, -800, 2000,
             ToggleSpriteOffsetY);
  n++;
  ToggleSpriteOffsetY = GuiToggle(
      {gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height},
      "Edit", ToggleSpriteOffsetY);

  gui_temp.y = 14 + SpriteGroupBoxRect.y + (n * 20);

  GUItempx = (int)GameState.Editor.GameEntity->x;

  GUItempy = (int)GameState.Editor.GameEntity->y;

  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "entity x", &GUItempx, 0, 2000, ToggleSpriteX);
  n++;
  ToggleSpriteX = GuiToggle(
      {gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height},
      "Edit", ToggleSpriteX);

  GameState.Editor.GameEntity->x = GUItempx;

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiSpinner({gui_temp.x, gui_temp.y, gui_temp.width, gui_temp.height},
             "entity y", &GUItempy, 0, 2000, ToggleSpriteY);
  n++;
  ToggleSpriteY = GuiToggle(
      {gui_temp.x + gui_temp.width + 2, gui_temp.y, 40, gui_temp.height},
      "Edit", ToggleSpriteY);

  GameState.Editor.GameEntity->y = GUItempy;

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 20);
  GuiLabel({gui_temp.x - 40, gui_temp.y + 2, gui_temp.width, gui_temp.height},
           "file img");
  if (GuiDropdownBox(
          {gui_temp.x, gui_temp.y + 2, gui_temp.width + 80, gui_temp.height},
          GameState.AllPNGList.c_str(), &GameState.Editor.GameEntity->sprite->index,
          dropDown001EditMode)) {
    dropDown001EditMode = !dropDown001EditMode;
  }
  n++;

  gui_temp.y = 12 + SpriteGroupBoxRect.y + (n * 24);

  GuiGroupBox({gui_temp.x, gui_temp.y, 100, 100}, "Options");

  Rectangle OptionsGroupBoxRect = {(float)GAMESCREEN_OFFSET_X + 1280,
                                   (float)GAMESCREEN_OFFSET_Y + 640, 280, 400};

  //

  n = 0;

  gui_temp.y = OptionsGroupBoxRect.y + (n * 24);
  gui_temp.x = OptionsGroupBoxRect.x;
  // gui_temp.x = GameGui.x - 40;

  char str[12] = "Show Boxes";

  ToggleEntityBoxes =
      GuiToggle({gui_temp.x + 2, gui_temp.y, sizeof(str) / sizeof(str[0]) * 6,
                 gui_temp.height},
                str, ToggleEntityBoxes);

  n++;

  char str2[12] = "Combat";

  gui_temp.y = OptionsGroupBoxRect.y + (n * 24);

  DEBUG_TOGGLE_COMBAT = GuiToggle({gui_temp.x + 2, gui_temp.y,
                      sizeof(str2) / sizeof(str2[0]) * 6, gui_temp.height},
                     str2, DEBUG_TOGGLE_COMBAT);

  n++;

  char str3[12] = "Unused";

  gui_temp.y = OptionsGroupBoxRect.y + (n * 24);

  DEBUG_TOGGLE_UNUSED = GuiToggle({gui_temp.x + 2, gui_temp.y,
                           sizeof(str3) / sizeof(str3[0]) * 6, gui_temp.height},
                          str3, DEBUG_TOGGLE_UNUSED);
}

static int current_selected = 0;

static int init_done = 0;

inline void RenderSelectedSprite(game_state &GameState) {
  int n = 0;
  temp_sprite_rec.height = 60;
  temp_sprite_rec.width = 100;

  temp_sprite_rec.x = GAMESCREEN_OFFSET_X + GRID_WIDTH + 100;
  temp_sprite_rec.y = GAMESCREEN_OFFSET_Y + 400;

  GuiSpinner({temp_sprite_rec.x, temp_sprite_rec.y - 30, 100, 20}, "sprite id",
             &selected_sprite, 1, GameState.SpriteList.size(), false);

  if (current_selected != selected_sprite) {
    current_selected = selected_sprite;
    init_done = 0;
  }

  DrawTexturePro(getTexture(GameState.SpriteList, GameState.GameTextureList,
                            selected_sprite)
                     .tex,
                 {0, 0,
                  (float)getTexture(GameState.SpriteList,
                                    GameState.GameTextureList, selected_sprite)
                      .tex.width,
                  (float)getTexture(GameState.SpriteList,
                                    GameState.GameTextureList, selected_sprite)
                      .tex.height},
                 temp_sprite_rec, {0, 0}, 0, WHITE);

  // ToggleSpriteX = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y,
  // 40, gui_temp.height }, "Edit", ToggleSpriteX);

  // temp_sprite_rec.y = 14 + temp_sprite_rec.y + (n * 20) +
  // temp_sprite_rec.height;

  // GuiSpinner({ temp_sprite_rec.x,temp_sprite_rec.y - 30, 100,20 }, "entity
  // y", &game_entity->sprite->x, 0, 2000, ToggleSpriteX); n++;

  // ToggleSpriteY = GuiToggle({ gui_temp.x + gui_temp.width + 2, gui_temp.y,
  // 40, gui_temp.height }, "Edit", ToggleSpriteY);

  new_e.sprite = &getSpriteEx(GameState.SpriteList, selected_sprite);

  if (init_done == 0) {
    temp_w = new_e.sprite->w;
    temp_h = new_e.sprite->h;

    init_done = 1;
  }

  temp_sprite_rec.y = temp_sprite_rec.y + 100;

  temp_sprite_rec.y = temp_sprite_rec.y + (n * 20);

  GuiSpinner({temp_sprite_rec.x, temp_sprite_rec.y, 100, 20}, "new entity w",
             &temp_w, 0, 2000, ToggleSpriteX);
  n++;

  temp_sprite_rec.y = temp_sprite_rec.y + (n * 20);

  GuiSpinner({temp_sprite_rec.x, temp_sprite_rec.y, 100, 20}, "new entity h",
             &temp_h, 0, 2000, ToggleSpriteX);

  temp_sprite_rec.y = temp_sprite_rec.y + (n * 24);

  NewEntityButton =
      GuiButton({temp_sprite_rec.x, temp_sprite_rec.y, 40, 20}, "New");
}

inline void RenderNewEntity(game_state &GameState) {
  temp_sprite_rec.height = temp_h;
  temp_sprite_rec.width = temp_w;

  if (temp_sprite_rec.height <= 32) {
    temp_sprite_rec.y = GetMousePosition().y - (temp_sprite_rec.height / 2);
  } else {
    temp_sprite_rec.y =
        GetMousePosition().y - (temp_sprite_rec.height) + GAME_TILE_HEIGHT / 2;
  }

  if (temp_sprite_rec.width <= 64) {
    temp_sprite_rec.x = GetMousePosition().x - (temp_sprite_rec.width / 2);
  } else {
    temp_sprite_rec.x = GetMousePosition().x - (temp_sprite_rec.width / 2);
  }

  // sprite_list

  DrawTexturePro(getTexture(GameState.SpriteList, GameState.GameTextureList,
                            selected_sprite)
                     .tex,
                 {0, 0,
                  (float)getTexture(GameState.SpriteList,
                                    GameState.GameTextureList, selected_sprite)
                      .tex.width,
                  (float)getTexture(GameState.SpriteList,
                                    GameState.GameTextureList, selected_sprite)
                      .tex.height},
                 temp_sprite_rec, {0, 0}, 0, CLITERAL(Color){ 255, 255, 255, 0 });
}

inline void AddNewEntity(editor &Editor, map &Map ,vector<entity> &entity_list ,int x, int y, int screen_x, int screen_y) {
  new_e.ID = entity_list[entity_list.size() - 1].ID + Editor.NumOfAdded;

  new_e.render_this = true;

  new_e.w = temp_w;
  new_e.h = temp_h;

  Map.Cords[x][y][Map.CurrentLayer] = new_e.ID;

  new_e.x = screen_x;
  new_e.y = screen_y;

  WriteEntityDataSingle(new_e, MAPS_PATH + "game_entity_data_temp.txt");

  WriteUpdatedMap(Map,MAPS_PATH + "map2.txt");

   Editor.NumOfAdded++;

  cout << "this happens" << endl;

  entity_list.push_back(new_e);
}

inline void CreateNewEntity(editor &Editor,map &Map, vector<entity> & entity_list) {
  pos p;

  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    //	printf("Button LEFT is pressed and Entity one clicked");
  }

  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    //	printf("Button LEFT is pressed and Entity one clicked");

    cout << "NOT IMPLEMENTED" << endl;
    // if (PLACING_ENTITY) {
    //   p = GetCordsCollisionIndex(Map.PosCords,
    //       {GetMousePosition().x, GetMousePosition().y, 1, 1}, {(int)GetMousePosition().x,(int)GetMousePosition().y});

    //   if (p.x != -1 && p.y != -1) {
    //     // CURRENT_LAYER = 1;

    //     cout << "This happens clicked" << endl;

    //     AddNewEntity(Editor,Map,entity_list,p.x, p.y, p.screen_x,
    //                  p.screen_y - (Map.CurrentLayer * (GAME_TILE_HEIGHT / 2)));

    //     PLACING_ENTITY = false;
    //   }
    // }
  }

  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    // printf("Button RIGHT is pressed");

    if (PLACING_ENTITY) {
      PLACING_ENTITY = false;
      // printf("Button RIGHT is pressed");
    }
  }
}

inline void DrawActionGui(menu &ActionMenu) {
  GuiUnlock();

  GuiEnable();

  // This is the action menu box
  DrawRectangle(ActionMenu.MenuRects[0].x, ActionMenu.MenuRects[0].y,
                ActionMenu.MenuRects[0].width + 24, ActionMenu.MenuRects[0].height,
                WHITE);

  GuiGroupBox({ActionMenu.MenuRects[0].x, ActionMenu.MenuRects[0].y,
               ActionMenu.MenuRects[0].width + 24, ActionMenu.MenuRects[0].height},
              "Action Menu");

  if (ActionMenu.is_pre_state == true) {
    ActionButton[0] =
        GuiButtonEx(ActionMenu.MenuRects[1], "Ready", ActionMenu.MenuTarget, KEY_X);

    ActionButton[1] =
        GuiButtonEx(ActionMenu.MenuRects[2], "Escape", ActionMenu.MenuTarget, KEY_X);

    ActionButton[2] =
        GuiButtonEx(ActionMenu.MenuRects[3], "End", ActionMenu.MenuTarget, KEY_X);


    DrawRectangleLinesEx(ActionMenu.MenuTarget, 2, RED);

    // DrawRectangleLines(action_target_rect.x, action_target_rect.y,
    //                    action_target_rect.width, action_target_rect.height,
    //                    RED);

  } else {
    ActionButton[0] =
        GuiButtonEx(ActionMenu.MenuRects[1], "Move", ActionMenu.MenuTarget, KEY_X);

    ActionButton[1] =
        GuiButtonEx(ActionMenu.MenuRects[2], "Attack", ActionMenu.MenuTarget, KEY_X);

    ActionButton[2] =
        GuiButtonEx(ActionMenu.MenuRects[3], "End", ActionMenu.MenuTarget, KEY_X);

    DrawRectangleLinesEx(ActionMenu.MenuTarget, 2, RED);
  }
}

inline void AddDebugText( ) {
  GAME_LOG.DebugInfoLines.push_back("temp1");
  GAME_LOG.DebugInfoLines.push_back("temp2");
  GAME_LOG.DebugInfoLines.push_back("temp3");
  GAME_LOG.DebugInfoLines.push_back("temp4");
  GAME_LOG.DebugInfoLines.push_back("temp5");
  GAME_LOG.DebugInfoLines.push_back("temp6");
}

inline void UpdateDebugText(game_state &GameState) {
  GAME_LOG.DebugInfoLines[2] = "Z_pressed_count: ";
  GAME_LOG.DebugInfoLines[2].append(to_string(GameState.ActionMenu.Z_COUNT));

  GAME_LOG.DebugInfoLines[3] = "X_pressed_count: ";
  GAME_LOG.DebugInfoLines[3].append(to_string(GameState.ActionMenu.X_COUNT));

  GAME_LOG.DebugInfoLines[4] = "Target x: ";
  GAME_LOG.DebugInfoLines[4].append(to_string(GameState.Target.pEntity->x));

  GAME_LOG.DebugInfoLines[5] = "Target Y: ";
  GAME_LOG.DebugInfoLines[5].append(to_string(GameState.Target.pEntity->y));
}

Rectangle LogInfoRect = {0, 0, 100, 16};

Rectangle ScrollBar = {
    (float)GAMESCREEN_OFFSET_X + 8,
    (float)GAMESCREEN_OFFSET_Y + GAMEWINDOW_HEIGHT - 200 - 16, 10, 16 * 11};

inline void RenderLog() {
  LogInfoRect.x = 20;

  LogInfoRect.y = GAMEWINDOW_HEIGHT - 200;

  int rendernum = 0;

  for (size_t i = GAME_LOG.LogLines.size(); i-- > 0;) {
    if (rendernum < GAME_LOG.CurrentLineLog) {
      // Render only 11 lines at the time, as it scrolls
      if (rendernum < 89) {
        if (rendernum > 89 - GAME_LOG.LogScrollCounter - 1) {
          GuiLabel({GAMESCREEN_OFFSET_X + LogInfoRect.x,
                    GAMESCREEN_OFFSET_Y + LogInfoRect.y +
                        ((i - GAME_LOG.LogScrollCounter) * LogInfoRect.height) -
                        (LogInfoRect.height * 1),
                    LogInfoRect.width, LogInfoRect.height},
                   GAME_LOG.LogLines[(GAME_LOG.CurrentLineLog - 1 - rendernum)].c_str());
          rendernum++;
        } else {
          rendernum++;
        }

      } else {
        GuiLabel({GAMESCREEN_OFFSET_X + LogInfoRect.x,
                  GAMESCREEN_OFFSET_Y + LogInfoRect.y +
                      ((i - GAME_LOG.LogScrollCounter) * LogInfoRect.height) -
                      (LogInfoRect.height * 1),
                  LogInfoRect.width, LogInfoRect.height},
                 GAME_LOG.LogLines[(GAME_LOG.CurrentLineLog - 1 - rendernum)].c_str());

        rendernum++;
      }
    }
  }

  GAME_LOG.LogScrollCounter =
      GuiScrollBar(ScrollBar, GAME_LOG.LogScrollCounter, 100 - GAME_LOG.CurrentLineLog, 89);
}

Rectangle DebugLogInfoRect = {0, 0, 100, 16};

Rectangle DebugScrollBar = {
    8 + 400, (float)GAMESCREEN_OFFSET_Y + (float)GAMEWINDOW_HEIGHT - 200 - 16,
    10, 16 * 11};

inline void RenderDebugLog() {
  DebugLogInfoRect.x = 20 + 400;

  DebugLogInfoRect.y = (float)GAMESCREEN_OFFSET_Y + GAMEWINDOW_HEIGHT - 200;

  int rendernum = 0;

  for (size_t i = GAME_LOG.DebugLogLines.size(); i-- > 0;) {
    if (rendernum < GAME_LOG.CurrentLineDebuglog) {
      // Render only 11 lines at the time, as it scrolls
      if (rendernum < 89) {
        if (rendernum > 89 - GAME_LOG.DebugLogScrollCounter - 1) {
          GuiLabel(
              {DebugLogInfoRect.x,
               DebugLogInfoRect.y +
                   ((i - GAME_LOG.DebugLogScrollCounter) * DebugLogInfoRect.height) -
                   (DebugLogInfoRect.height * 1),
               DebugLogInfoRect.width, DebugLogInfoRect.height},
              GAME_LOG.DebugLogLines[(GAME_LOG.CurrentLineDebuglog - 1 - rendernum)].c_str());
          rendernum++;
        } else {
          rendernum++;
        }
      } else {
        GuiLabel(
            {DebugLogInfoRect.x,
             DebugLogInfoRect.y +
                 ((i - GAME_LOG.DebugLogScrollCounter) * DebugLogInfoRect.height) -
                 (DebugLogInfoRect.height * 1),
             DebugLogInfoRect.width, DebugLogInfoRect.height},
            GAME_LOG.DebugLogLines[(GAME_LOG.CurrentLineDebuglog - 1 - rendernum)].c_str());

        rendernum++;
      }
    }
  }

  GAME_LOG.DebugLogScrollCounter = GuiScrollBar(DebugScrollBar, GAME_LOG.DebugLogScrollCounter,
                                       100 - GAME_LOG.CurrentLineDebuglog, 89);
}
