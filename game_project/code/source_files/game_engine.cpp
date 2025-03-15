/* ========================================================================

======================================================================== */

#pragma once

#ifndef game_engine_cpp
#define game_engine_cpp

#include <iostream>

#include "../header_files/raylib.h"
#include "../header_files/raylib_functions.h"

// #include "code/header_files/raygui.h"
#include "../header_files/game_engine_func.h"
#include "../header_files/game_entities.h"
#include "../header_files/globals.h"
#include "../header_files/logic_func.h"

// #include "code/header_files/screens.h"

using namespace std;

//========================================================================

#define internal static
#define local_persist static
#define global_variable static

// Used by ColorFieldTileEntityList, reset with MovePressed
static bool enemy_colored = false;
static int entity_checked = 0;

inline bool Init(int width, int height, char title[]) {
  InitWindow(width, height, title);

  return 0;
}

inline texture myLoadTexture(std::string path) {
  Texture2D temp = {0};

  texture myTemp = {0, 0, 0, 0};

  temp = LoadTexture(path.c_str());
  if (temp.id != 0) {
    myTemp.tex = temp;
    myTemp.w = temp.width;
    myTemp.h = temp.height;
    myTemp.path = path;
  } else {
    printf("Unable to create texture from %s\n", path.c_str());
  }

  return myTemp;
}

inline texture myLoadTextureFromImage(vector<Image>& image_list,
                                      std::string path) {
  texture myTemp = {0, 0, 0, 0};

  Image imOrigin = LoadImage(path.c_str());  // Loaded in CPU memory (RAM)

  ImageFormat(&imOrigin,
              PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);  // Format image to RGBA 32bit
                                                   // (required for texture
                                                   // update) <-- ISSUE

  Texture2D temp = LoadTextureFromImage(
      imOrigin);  // Image converted to texture, GPU memory (VRAM)

  Image imCopy = ImageCopy(imOrigin);

  image_list.push_back(imOrigin);

  temp = LoadTextureFromImage(imOrigin);
  if (temp.id != 0) {
    myTemp.tex = temp;
    myTemp.w = temp.width;
    myTemp.h = temp.height;
    myTemp.path = path;
    myTemp.img_array_index = image_list.size() - 1;
  } else {
    printf("Unable to create texture from %s\n", path.c_str());
  }

  return myTemp;
}

inline void CreateTextTexture_No_GlobalFont(Font font, std::string TextureText,
                                            Color TextColor) {
  // texture temp;
  // return temp;
}

inline void CreateTextTexture(std::string TextureText) {
  // texture temp;

  //

  ////Return success
  // return temp;
}

inline void AddText(std::string msg, int x, int y) {
  // text txt;

  // txt.fontsize = FONT_SIZE;
  // txt.x = x;
  // txt.y = y;

  // txt.tex = CreateTextTexture(msg);

  // text_list.push_back(txt);
}

inline int GetIndexForTexture(string pngname, vector<string>& PNGList) {
  // return -1 if no texture found;
  int index = -1;

  for (size_t i = 0; i < PNGList.size(); i++) {
    if (!PNGList[i].find(pngname)) {
      index = i;
      break;
    }
  }

  return index;
}

inline bool LoadFont(Font font) {
  bool success = true;

  return success;
}

inline bool GUI_CreateTextures(vector<string>& png_list,
                               vector<texture>& texture_list) {
  bool success = true;

  for (size_t i = 0; i < png_list.size(); i++) {
    texture temp = myLoadTexture(GUI_ASSET_PATH + png_list[i]);

    texture_list.push_back(temp);
  }

  if (DEBUG_PRINT) {
    cout << "entity texture list: " << texture_list.size() << endl;
  }
  return success;
}

inline bool GAME_CreateTextures(vector<string>& png_list,
                                vector<texture>& texture_list) {
  bool success = true;

  for (size_t i = 0; i < png_list.size(); i++) {
    texture temp = myLoadTexture(GAME_ASSET_PATH + png_list[i]);

    texture_list.push_back(temp);
  }
  if (DEBUG_PRINT) {
    cout << "entity texture list: " << texture_list.size() << endl;
  }
  return success;
}

inline bool GAME_CreateTexturesFromImage(vector<Image>& image_list,
                                         vector<string>& png_list,
                                         vector<texture>& texture_list,
                                         string& asset_path) {
  bool success = true;

  for (size_t i = 0; i < png_list.size(); i++) {
    if (DEBUG_PRINT) {
      cout << "Reading " << png_list[i] << endl;
    }
    texture temp = myLoadTextureFromImage(image_list, asset_path + png_list[i]);

    texture_list.push_back(temp);
  }
  if (DEBUG_PRINT) {
    cout << "entity texture list: " << texture_list.size() << endl;
  }
  return success;
}

inline void SetSpriteTextures(vector<sprite>& sprite_list,
                              vector<texture>& texture_list) {
  for (size_t n = 0; n < sprite_list.size(); n++) {
    for (size_t i = 0; i < texture_list.size(); i++) {
      if (texture_list[i].path.find(sprite_list[n].img) != std::string::npos) {
        sprite_list[n].index = i;
        break;
      } else {
      }
    }
  }
}

inline void SetSprite(vector<sprite>& sprite_list, entity& e,
                      string sprite_name) {
  for (size_t i = 0; i < sprite_list.size(); i++) {
    if (sprite_name.compare(sprite_list[i].name) == 0) {
      e.sprite = &sprite_list[i];
    }
  }
}
inline void SetSprite(vector<sprite>& sprite_list, entity& e, int sprite_ID) {
  for (size_t i = 0; i < sprite_list.size(); i++) {
    if (sprite_list[i].ID == sprite_ID) {
      e.sprite = &sprite_list[i];
      break;
    }
  }
}

inline void SetSprite(vector<sprite>& sprite_list, entity* e, int sprite_ID) {
  for (size_t i = 0; i < sprite_list.size(); i++) {
    if (sprite_list[i].ID == sprite_ID) {
      e->sprite = &sprite_list[i];
      break;
    }
  }
}

inline sprite& getSprite(vector<sprite>& sprite_list, string sprite_name) {
  for (size_t i = 0; i < sprite_list.size(); i++) {
    if (sprite_name.compare(sprite_list[i].name) == 0) {
      return sprite_list[i];
      break;
    }
  }

  printf(
      "Sprite with name %s could not be found, returned first sprite in list",
      sprite_name.c_str());
  return sprite_list[0];
}

inline sprite& getSprite(vector<sprite>& sprite_list, int sprite_ID) {
  for (size_t i = 0; i < sprite_list.size(); i++) {
    if (sprite_list[i].ID == sprite_ID) {
      // cout << "Sprite found " << sprite_list[i].img << endl;

      return sprite_list[i];
      break;
    }
  }

  return sprite_list[0];
}

// TODO: Checking against entity x/y, perhaps should use entity_tile instead
inline entity* getEntityByPosition(int pos_x, int pos_y,
                                   vector<entity*> entities) {
  cout << "This happens getEntityByPosition star" << endl;

  cout << "pos x" << pos_x;
  cout << "pos y" << pos_y;

  for (size_t i = 0; i < entities.size(); i++) {
    if (entities[i]->entity_tile.x == pos_x &&
        entities[i]->entity_tile.y == pos_y) {
      cout << "---------------------------------------------------------"
           << endl;
      cout << "getEnityByPosition X entity found " << entities[i]->x << endl;
      cout << "getEnityByPosition Y entity found " << entities[i]->y << endl;
      cout << "getEnityByPosition tile X entity found "
           << entities[i]->entity_tile.x << endl;
      cout << "getEnityByPosition tile Y entity found "
           << entities[i]->entity_tile.y << endl;

      return entities[i];
    }
  }

  return entities[0];
}

// TODO: Checking against entity x/y, perhaps should use entity_tile instead
inline entity& getEntityByPosition(int pos_x, int pos_y,
                                   vector<entity>& entities) {
  cout << "This happens getEntityByPosition ref" << endl;

  for (size_t i = 0; i < entities.size(); i++) {
    if (entities[i].x == pos_x && entities[i].y == pos_y) {
      cout << "getEnityByPosition entity found " << endl;

      cout << "getEnityByPosition X entity found " << entities[i].x << endl;
      cout << "getEnityByPosition Y entity found " << entities[i].y << endl;
      cout << "getEnityByPosition tile X entity found "
           << entities[i].entity_tile.x << endl;
      cout << "getEnityByPosition tile Y entity found "
           << entities[i].entity_tile.y << endl;

      cout << "sprite name: " << entities[i].sprite->name << endl;

      return entities[i];
    }
  }

  return entities[0];
}

inline entity& GetEntityByID(int entity_ID, vector<entity>& entities) {
  for (size_t i = 0; i < entities.size(); i++) {
    if (entities[i].ID == entity_ID) {
      return entities[i];
    }
  }

  cout << "getEntityByID entity not found " << entity_ID << endl;

  return entities[0];
}

inline entity& GetEntityBySpriteName(string sprite_name,
                                     vector<entity>& entities) {
  for (size_t i = 0; i < entities.size(); i++) {
    if (sprite_name.compare(entities[i].sprite->name) == 0) {
      return entities[i];
    }
  }

  cout << "getEntityByID entity not found, sprite by name:" << sprite_name
       << endl;

  return entities[0];
}

inline entity* GetEntityByID(int entity_ID, vector<entity*> entities) {
  cout << "Trying to find ID: " << entity_ID << endl;

  for (size_t i = 0; i < entities.size(); i++) {
    if (entities[i]->ID == entity_ID) {
      cout << "getEntityByID entity found " << entities[i]->ID << endl;

      return entities[i];
    } else {
      cout << "getEntityByID else entity found " << entities[i]->ID << endl;
    }
  }

  // Log(entities[0]->sprite->name);

  cout << "getEntityByID entity not found, instead set to first with ID: "
       << entities[0]->ID << endl;

  return entities[0];
}

Rectangle tempcheckrect = {0, 0, 0, 0};

Rectangle& getEntityRect(entity& e) {
  tempcheckrect = {(float)(e.x + e.sprite->offset_x),
                   (float)(e.y + e.sprite->offset_y), (float)e.w, (float)e.h};

  return tempcheckrect;
}

Rectangle recSprite2;
Rectangle recEntity2;

global_variable vector<pos> Layer1;
global_variable vector<pos> Layer2;

pos temp = {0, 0};

static int index_counter = 0;

static int added_once = 0;

inline void RenderEntities(game_state& GameState, vector<entity>& entities,
                           int render_list_index) {
  int templayer = 0;

  int lowerlayer = 0;

  int entity_count = 0;

  DebugLog("RenderEntities entities.size(): ", (int)entities.size());

  for (size_t i = 0; i < entities.size(); i++) {
    recSprite2 = {(float)entities[i].sprite->x, (float)entities[i].sprite->y,
                  (float)entities[i].sprite->w, (float)entities[i].sprite->h};

    recEntity2 = {(float)(entities[i].x + entities[i].sprite->offset_x),
                  /*((-GAME_TILE_HEIGHT / 2)*/ (float)entities[i].y +
                      entities[i].sprite->offset_y,
                  (float)entities[i].w, (float)entities[i].h};

    entities[i].entity_tile.x = entities[i].x;
    entities[i].entity_tile.y = entities[i].y;

    if (entities[i].ID == GameState.Target.pEntity->ID) {
      lowerlayer = 1;
    } else {
      lowerlayer = 0;
    }

    templayer = entities[i].y - lowerlayer + (800 * entities[i].layer);

    if (entities[i].ID == 999) {
      //	cout << "99 "<< endl;
      templayer = templayer - 30;
    }

    if (entities[i].ID == GRID_SPRITE_ID) {
      templayer = templayer - 1000;
    }

    GameState.AllRenderObjects[i + GameState.ObjectsToRender[render_list_index]]
                              [render_list_index] = {
        getTexture(GameState.SpriteList, GameState.GameTextureList,
                   entities[i].sprite->ID)
            .tex,
        recSprite2,
        recEntity2,
        {0, 0},
        0,
        Fade(WHITE, entities[i].alpha),
        templayer,
        entities[i].render_this,
        entities[i].use_shader};

    if (GameState.RenderList[render_list_index].List.size() <
        entities.size() + GameState.ObjectsToRender[render_list_index]) {
      GameState.RenderList[render_list_index].List.push_back(
          &GameState
               .AllRenderObjects[i +
                                 GameState.ObjectsToRender[render_list_index]]
                                [render_list_index]);
    } else {
      GameState.RenderList[render_list_index]
          .List[i + GameState.ObjectsToRender[render_list_index]] =
          &GameState
               .AllRenderObjects[i +
                                 GameState.ObjectsToRender[render_list_index]]
                                [render_list_index];
    }

    if (DEBUG_RENDER_BOXES == true) {
      DrawRectangleLines(entities[i].entity_tile.x, entities[i].entity_tile.y,
                         GAME_TILE_WIDTH, GAME_TILE_HEIGHT, BLUE);

      DrawRectangleLines(entities[i].x, entities[i].y, entities[i].w,
                         entities[i].h, RED);

      DrawRectangleLines((float)entities[i].x + entities[i].sprite->offset_x,
                         (float)entities[i].y + entities[i].sprite->offset_y,
                         entities[i].w, entities[i].h, GREEN);
    }
  }

  if (GameState.ObjectsToRender[render_list_index] <
      GameState.ObjectsToRender[render_list_index] + entities.size()) {
    GameState.ObjectsToRender[render_list_index] =
        GameState.ObjectsToRender[render_list_index] + entities.size();
  }
}

inline void RenderEntityBoxes(vector<entity>& entities) {
  int templayer = 0;

  int lowerlayer = 0;

  int offset_x = 0;
  int offset_y = 0;

  for (size_t i = 0; i < entities.size(); i++) {
    recSprite2 = {(float)entities[i].sprite->x, (float)entities[i].sprite->y,
                  (float)entities[i].sprite->w, (float)entities[i].sprite->h};

    recEntity2 = {(float)entities[i].x + entities[i].sprite->offset_x,
                  (float)entities[i].y + entities[i].sprite->offset_y,
                  (float)entities[i].w, (float)entities[i].h};

    entities[i].entity_tile.x = entities[i].x;

    entities[i].entity_tile.y = entities[i].y;

    if (entities[i].w < 500) {
      offset_x = (entities[i].w - GAME_TILE_WIDTH) / 2;
    }

    if (entities[i].h < 500) {
      offset_y = entities[i].h - (GAME_TILE_HEIGHT);
    }

    entities[i].offset_rect = {GAMESCREEN_OFFSET_X + entities[i].x - offset_x,
                               GAMESCREEN_OFFSET_Y + entities[i].y - offset_y,
                               entities[i].w, entities[i].h};

    if (ToggleEntityBoxes == true) {
      DrawRectangleLines(GAMESCREEN_OFFSET_X + entities[i].x - offset_x,
                         GAMESCREEN_OFFSET_Y + entities[i].y - offset_y,
                         entities[i].w, entities[i].h, RED);

      DrawRectangleLines(GAMESCREEN_OFFSET_X + entities[i].entity_tile.x,
                         GAMESCREEN_OFFSET_Y + entities[i].entity_tile.y,
                         GAME_TILE_WIDTH, GAME_TILE_HEIGHT, BLUE);

      DrawEllipse(GAMESCREEN_OFFSET_X + entities[i].el.center.x,
                  GAMESCREEN_OFFSET_Y + entities[i].el.center.y,
                  entities[i].el.h, entities[i].el.w, YELLOW);
    }
  }
}

inline void DrawEllipseCollisionPoints(vector<point>& ellipses_points) {
  for (size_t i = 0; i < ellipses_points.size(); i++) {
    DrawRectangle(GAMESCREEN_OFFSET_X + ellipses_points[i].x,
                  GAMESCREEN_OFFSET_Y + ellipses_points[i].y, 1, 1, BLUE);
  }
}

inline void RenderWholeEntity(texture* Texture) {}

inline void RenderTextTexture(texture* Texture, int x, int y) {}

inline void AnimateMovement(entity* en, int d) {
  static int current_frame = 0;

  switch (d) {
    case UP:
      en->sprite->x = (current_frame * en->sprite->w);
      en->sprite->y = en->sprite->h * 2;
      current_frame++;

      if (current_frame >= 4) {
        current_frame = 0;
      }

      break;

    case DOWN:

      en->sprite->x = (current_frame * en->sprite->w);
      en->sprite->y = 0;
      current_frame++;

      if (current_frame >= 4) {
        current_frame = 0;
      }

      break;

    case LEFT:

      en->sprite->x = (current_frame * en->sprite->w);
      en->sprite->y = en->sprite->h * 3;
      current_frame++;

      if (current_frame >= 4) {
        current_frame = 1;
      }

      break;

    case RIGHT:

      en->sprite->x = (current_frame * en->sprite->w);
      en->sprite->y = en->sprite->h;
      current_frame++;

      if (current_frame >= 4) {
        current_frame = 1;
      }

      break;
  }
}

static float timer = 0.0f;

static int loop = 0;

inline void PrintMoveList(vector<int>& move_list) {
  for (size_t i = 0; i < move_list.size(); i++) {
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

inline void Animate(entity* en, vel v) {
  static int current_frame2 = 0;

  int right_vel = v.right;
  int left_vel = v.left;
  int up_vel = v.up;
  int down_vel = v.down;

  timer += GetFrameTime();

  if (timer >= ANIMATION_SPEED) {
    timer = 0.0;

    en->sprite->x = (current_frame2 * en->sprite->w);

    // en->sprite->y = en->sprite->h * 2;

    en->sprite->y = 0;

    current_frame2++;

    en->x = en->x + left_vel / 4;
    en->y = en->y + down_vel / 4;

    if (current_frame2 > 5) {
      current_frame2 = 0;
    }

    loop++;
  }

  if (loop >= 20) {
    en->x = 480;
    en->y = 208;

    loop = 0;
  }
}

inline void MovementAnimated(game_state& GameState, entity* en, vel v) {
  static int current_frame2 = 0;
  static int movecount = 0;

  static int steps = 0;

  int steps_to_move = 2;

  int right_vel = v.right;
  int left_vel = v.left;
  int up_vel = v.up;
  int down_vel = v.down;

  if (GameState.AnimatingMovement == true) {
    if (movecount < GameState.MoveList.size()) {
      if (GameState.MoveList[movecount] == RIGHT) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          /// Animation
          en->sprite->x = (current_frame2 * en->sprite->w);
          en->sprite->y = 2 * en->sprite->h;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }
          /// Movement
          steps++;

          en->x = en->x + (right_vel / steps_to_move);
          en->y = en->y + (up_vel / steps_to_move);

          if (steps == steps_to_move) {
            movecount++;
            steps = 0;
            printf("[RIGHT]");
          }
        }
      }

      else if (GameState.MoveList[movecount] == LEFT) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          en->sprite->x = (current_frame2 * en->sprite->w);
          en->sprite->y = 0;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          steps++;

          en->x = en->x + (left_vel / steps_to_move);
          en->y = en->y + (down_vel / steps_to_move);

          if (steps == steps_to_move) {
            movecount++;
            steps = 0;
            printf("[LEFT]");
          }
        }
      } else if (GameState.MoveList[movecount] == UP) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          en->sprite->x = (current_frame2 * en->sprite->w);
          en->sprite->y = 3 * en->sprite->h;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          steps++;

          en->x = en->x + (left_vel / steps_to_move);
          en->y = en->y + (up_vel / steps_to_move);

          if (steps == steps_to_move) {
            movecount++;
            steps = 0;
            printf("[UP]");
          }
        }
      } else if (GameState.MoveList[movecount] == DOWN) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          en->sprite->x = (current_frame2 * en->sprite->w);
          en->sprite->y = 1 * en->sprite->h;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          steps++;

          en->x = en->x + (right_vel / steps_to_move);
          en->y = en->y + (down_vel / steps_to_move);

          if (steps == steps_to_move) {
            movecount++;
            steps = 0;
            printf("[DOWN]");
          }
        }
      }
    } else {
      printf("steps reset movement\n");

      GameState.AnimatingMovement = false;

      // Reset the sprite animate frames
      if (GameState.MoveList.back() == LEFT) {
      } else if (GameState.MoveList.back() == RIGHT) {
        en->sprite->x = 0;
        en->sprite->y = 2 * en->sprite->h;
      } else if (GameState.MoveList.back() == UP) {
        en->sprite->x = 0;
        en->sprite->y = 3 * en->sprite->h;
      } else if (GameState.MoveList.back() == DOWN) {
        en->sprite->x = 0;
        en->sprite->y = 1 * en->sprite->h;
      }

      steps = 0;
      movecount = 0;
      GameState.MoveList.clear();
    }
  }
}

inline void EnemyMovementAnimated(game_state& GameState, vel v) {
  static int current_frame2 = 0;
  // static int movecount = 0;
  static int enemy_checked = 0;

  int steps_to_move = 4;

  // int right_vel = v.right;
  // int left_vel = v.left;
  // int up_vel = v.up;
  // int down_vel = v.down;

  combatant& en = GameState.Map.EnemyList[enemy_checked];

  int right_vel = en.x_vel;
  int left_vel = en.x_vel * (-1);
  int up_vel = en.y_vel * (-1);
  int down_vel = en.y_vel;

  if (!en.movelist.empty()) {
    if (en.current_movecount < en.movelist.size()) {
      if (en.movelist[en.current_movecount] == RIGHT) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          /// Animation
          en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);
          en.pEntity->sprite->y = 2 * en.pEntity->sprite->h;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          //// Movement
          en.current_steps++;
          en.pEntity->x = en.pEntity->x + (right_vel / (2 * steps_to_move));
          en.pEntity->y = en.pEntity->y + (up_vel / (2 * steps_to_move));

          if (en.current_steps == steps_to_move) {
            en.current_movecount++;
            en.current_steps = 0;
          }
        }
      } else if (en.movelist[en.current_movecount] == LEFT) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          /// Animation

          en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);

          en.pEntity->sprite->y = 0;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          //// Movement
          en.current_steps++;
          en.pEntity->x = en.pEntity->x + (left_vel / (2 * steps_to_move));
          en.pEntity->y = en.pEntity->y + (down_vel / (2 * steps_to_move));

          if (en.current_steps == steps_to_move) {
            en.current_movecount++;
            en.current_steps = 0;
          }
        }
      }

      else if (en.movelist[en.current_movecount] == UP) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          /// Animation
          en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);
          en.pEntity->sprite->y = 3 * en.pEntity->sprite->h;

          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          //// Movement
          en.current_steps++;
          en.pEntity->x = en.pEntity->x + (left_vel / (2 * steps_to_move));
          en.pEntity->y = en.pEntity->y + (up_vel / (2 * steps_to_move));

          if (en.current_steps == steps_to_move) {
            en.current_movecount++;
            en.current_steps = 0;
          }
        }
      } else if (en.movelist[en.current_movecount] == DOWN) {
        timer += GetFrameTime();

        if (timer >= ANIMATION_SPEED) {
          timer = 0.0;

          /// Animation

          en.pEntity->sprite->x = (current_frame2 * en.pEntity->sprite->w);
          en.pEntity->sprite->y = 1 * en.pEntity->sprite->h;
          current_frame2++;

          if (current_frame2 > 5) {
            current_frame2 = 0;
          }

          //// Movement
          en.current_steps++;
          en.pEntity->x = en.pEntity->x + (right_vel / (2 * steps_to_move));
          en.pEntity->y = en.pEntity->y + (down_vel / (2 * steps_to_move));

          if (en.current_steps == steps_to_move) {
            en.current_movecount++;
            en.current_steps = 0;
            printf("[DOWN]\n");
          }
        }
      }
    } else {
      // cout <<  en.pEntity->sprite->x << " " << en.unique_sprite.x << endl;
      // cout <<  en.pEntity->sprite->y << " " << en.unique_sprite.y << endl;

      if (!en.movelist.empty()) {
        if (en.movelist.back() == LEFT) {
          en.pEntity->sprite->x = 0;

          en.pEntity->sprite->y = 0;
        } else if (en.movelist.back() == RIGHT) {
          en.pEntity->sprite->x = 0;

          en.pEntity->sprite->y = 2 * en.pEntity->sprite->h;
        } else if (en.movelist.back() == UP) {
          en.pEntity->sprite->x = 0;

          en.pEntity->sprite->y = 3 * en.pEntity->sprite->h;
        } else if (en.movelist.back() == DOWN) {
          en.pEntity->sprite->x = 0;

          en.pEntity->sprite->y = 1 * en.pEntity->sprite->h;
        }
      }

      en.current_steps = 0;
      en.current_movecount = 0;
      en.movelist.clear();

      enemy_checked++;
    }
  } else {
    enemy_checked++;
  }

  if (enemy_checked >= GameState.Map.EnemyList.size()) {
    enemy_checked = 0;
    GameState.AnimatingEnemyMovement = false;
  }
}

inline void VicinityCheck(combatant& combatant, vector<entity>& entities) {
  Rectangle temp;

  temp.height = GAME_TILE_HEIGHT * 2;
  temp.width = GAME_TILE_WIDTH * 2;
  temp.x = combatant.pEntity->x - temp.width / 2 + (GAME_TILE_WIDTH / 2);
  temp.y = combatant.pEntity->y - temp.height / 2 + (GAME_TILE_HEIGHT / 2);

  combatant.EntitiesVicinity.clear();

  if (ToggleEntityBoxes) {
    DrawRectangle(temp.x + GAMESCREEN_OFFSET_X, temp.y + GAMESCREEN_OFFSET_Y,
                  temp.width, temp.height, ORANGE);
  }

  for (size_t entity_index = 0; entity_index < entities.size();
       entity_index++) {
    if (combatant.pEntity->ID != entities[entity_index].ID) {
      if (CheckCollisionRecs(temp, entities[entity_index].entity_tile)) {
        combatant.EntitiesVicinity.push_back(&entities[entity_index]);
      }
    }
  }
}

inline bool CheckIsoMoveCol(vector<entity>& entities, combatant& en, int dir1,
                            int dir2) {
  bool trigger_effect = false;
  int collision_effect1 = -1;

  int steps_to_move = 2;

  bool collision = false;

  float temp_en_x = en.pEntity->x;
  float temp_en_y = en.pEntity->y;

  VicinityCheck(en, entities);
  DebugLog("Check:", (int)en.EntitiesVicinity.size());

  temp_en_x = temp_en_x - (en.x_vel * (dir1 / 2)) / 2;
  temp_en_y = temp_en_y - (en.y_vel * dir2) / 2;

  for (size_t i = 0; i < en.EntitiesVicinity.size(); i++) {
    if (en.EntitiesVicinity[i]->x == temp_en_x &&
        en.EntitiesVicinity[i]->y == temp_en_y) {
      collision_effect1 = en.EntitiesVicinity[i]->collision_effect;
      cout << "collision " << en.EntitiesVicinity[i]->x << " "
           << en.EntitiesVicinity[i]->y << endl;
      break;
    }
  }

  return collision_effect1;
}

inline int CheckIsoMoveCol(vector<entity>& entities, combatant& en, int dir1,
                           int dir2, float x, float y) {
  bool trigger_effect = false;

  int collision_effect1 = -1;
  int steps_to_move = 2;

  bool collision = false;

  float temp_en_x = x;
  float temp_en_y = y;

  VicinityCheck(en, entities);
  DebugLog("Check:", (int)en.EntitiesVicinity.size());

  temp_en_x = temp_en_x - (en.x_vel * (dir1 / 2)) / 2;
  temp_en_y = temp_en_y - (en.y_vel * dir2) / 2;

  for (size_t i = 0; i < en.EntitiesVicinity.size(); i++) {
    if (en.EntitiesVicinity[i]->x == temp_en_x &&
        en.EntitiesVicinity[i]->y == temp_en_y) {
      collision_effect1 = en.EntitiesVicinity[i]->collision_effect;
      cout << "collision " << en.EntitiesVicinity[i]->x << " "
           << en.EntitiesVicinity[i]->y << endl;
      break;
    }
  }

  return collision_effect1;
}

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
//		GuiLabel({ infoRect.x, infoRect.y +( i * infoRect.height),
// infoRect.width, infoRect.height }, debug_info_lines[i].c_str());
//		//GuiTextBox({ infoRect.x, infoRect.y + (i * infoRect.height)
//+12, infoRect.width, infoRect.height }, strdup(debug_info_lines[i].c_str()),
// 12, false);
//	}
//
//	debug_info_lines[6] = "tempint : ";
//	debug_info_lines[6].append(to_string(LogScrollCounter));
// }

inline void DisplayEntityInfo(entity game_entity, int x, int y) {
  // AddText("Entity ID: " + to_string(game_entity.ID), x, y + (1 * FONT_SIZE));
  // AddText("Entity x:" + to_string(game_entity.x), x, y + (2 * FONT_SIZE));
  // AddText("Entity y:" + to_string(game_entity.y), x, y + (3 * FONT_SIZE));
  // AddText("Entity w:" + to_string(game_entity.w), x, y + (4 * FONT_SIZE));
  // AddText("Entity h:" + to_string(game_entity.h), x, y + (5 * FONT_SIZE));

  // AddText("sprite ID:" + to_string(game_entity.sprite.img_ID), x, y + (6 *
  // FONT_SIZE)); AddText("sprite name:", x, y + (7 * FONT_SIZE)); AddText("" +
  // (game_entity.sprite.img), x, y + (8 * FONT_SIZE)); AddText("sprite x:" +
  // to_string(game_entity.sprite.x), x, y + (9 * FONT_SIZE)); AddText("sprite
  // y:" + to_string(game_entity.sprite.y), x, y + (10 * FONT_SIZE));
  // AddText("sprite w:" + to_string(game_entity.sprite.w), x, y + (11 *
  // FONT_SIZE)); AddText("sprite h:" + to_string(game_entity.sprite.h), x, y +
  // (12 * FONT_SIZE));
}

inline bool CheckCollisionRects(Rectangle a, Rectangle b) {
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
  if (bottomA <= topB) {
    return false;
  }

  if (topA >= bottomB) {
    return false;
  }

  if (rightA <= leftB) {
    return false;
  }

  if (leftA >= rightB) {
    return false;
  }

  // If none of the sides from A are outside B
  return true;
}

inline bool CheckCollisionMouseEntity(vector<entity>& entity_list) {
  bool ret = false;

  float mouseX = GetMouseX();  // Returns mouse position X
  float mouseY = GetMouseY();

  Rectangle mouseRect = {mouseX, mouseY, 1, 1};
  //	Rectangle tempEntityRect;

  for (size_t i = 0; i < entity_list.size(); i++) {
    Rectangle tempEntityRect = {entity_list[i].x, entity_list[i].y,
                                entity_list[i].w, entity_list[i].h};

    if (CheckCollisionRects(mouseRect, tempEntityRect)) {
      printf("Collision with Entity: %d", entity_list[i].ID);

      ret = true;
    }
  }

  return ret;
}

float offset = 4;

inline void InitActionMenu(menu& ActionMenu) {
  Rectangle temp;

  ActionMenu.MaxButtons = ACTION_MENU_BUTTONS_MAX;

  temp = {0, 0, (float)((GUI_ACTION_BUTTON_WIDTH)*1.5),
          ((GUI_ACTION_BUTTON_HEIGHT) + offset / 2) * ActionMenu.MaxButtons};

  ActionMenu.MenuRects.push_back(temp);

  temp = {0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT};

  ActionMenu.MenuRects.push_back(temp);

  temp = {0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT};

  ActionMenu.MenuRects.push_back(temp);

  temp = {0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT};

  ActionMenu.MenuRects.push_back(temp);

  temp = {0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT};

  ActionMenu.MenuRects.push_back(temp);

  temp = {0, 0, GUI_ACTION_BUTTON_WIDTH, GUI_ACTION_BUTTON_HEIGHT};

  ActionMenu.MenuRects.push_back(temp);

  ActionMenu.MenuTarget.height = GUI_ACTION_BUTTON_HEIGHT;
  ActionMenu.MenuTarget.width = GUI_ACTION_BUTTON_WIDTH;

  ActionMenu.MenuTarget.x = temp.x;
  ActionMenu.MenuTarget.x = temp.y;
}

inline void SetActionMenu(menu& ActionMenu, combatant* Combatant) {
  float EntityX = 0;
  float EntityY = 0;
  float EntityW = 0;
  float EntityH = 0;

  EntityX = Combatant->pEntity->x;
  EntityY = Combatant->pEntity->y;
  EntityW = Combatant->pEntity->w;
  EntityH = Combatant->pEntity->h;

  // This is the Action menu box/panel
  ActionMenu.MenuRects[0].x = (float)(EntityX + (EntityW * 2.5)) + 20;
  ActionMenu.MenuRects[0].y = (float)(EntityY - (EntityH * 0.5)) + 16;

  for (size_t i = 1; i < ActionMenu.MenuRects.size(); i++) {
    ActionMenu.MenuRects[i].x = (float)(EntityX + (EntityW * 2.5)) + 4 + 20;
    ActionMenu.MenuRects[i].y =
        (float)(EntityY - (EntityH * 0.5)) + (i * GUI_ACTION_BUTTON_HEIGHT);
  }

  ActionMenu.MenuTarget.x =
      ActionMenu.MenuRects[ActionMenu.CurrentButtonIndex].x;
  ActionMenu.MenuTarget.y =
      ActionMenu.MenuRects[ActionMenu.CurrentButtonIndex].y;
}

inline bool SetMouseEntity(editor& Editor, vector<entity> entity_list) {
  bool ret = false;

  float mouseX = GetMouseX();
  float mouseY = GetMouseY();

  Rectangle mouseRect = {mouseX, mouseY, 1, 1};
  //	Rectangle tempEntityRect;

  for (size_t i = 0; i < entity_list.size(); i++) {
    if (CheckCollisionRects(mouseRect, getEntityRect(entity_list[i])) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      // printf("Collision with Entity: %d", entity_list[i].ID);

      Editor.GameEntity = &entity_list[i];

      ret = true;
    }
  }

  return ret;
}

inline bool SetMouseEntity(editor& Editor, vector<entity>& entities) {
  bool ret = false;

  float mouseX = GetMouseX() - GAMESCREEN_OFFSET_X;
  float mouseY = GetMouseY() - GAMESCREEN_OFFSET_Y;

  Rectangle mouseRect = {mouseX, mouseY, 1, 1};
  //	Rectangle tempEntityRect;

  for (size_t i = 0; i < entities.size(); i++) {
    Rectangle tempEntityRect = {
        (float)entities[i].x + entities[i].sprite->offset_x,
        (float)entities[i].y + entities[i].sprite->offset_y, entities[i].w,
        entities[i].h};

    if (CheckCollisionRects(mouseRect, tempEntityRect) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      // printf("Collision with Entity: %d", entity_list[i].ID);

      Editor.GameEntity = &entities[i];

      ret = true;
    }
  }

  return ret;
}

/////-------------------------------------------------  RenderField
///-------------------------------------------

Rectangle recSprite = {64, 0, 64, 32};

Rectangle recEntity = {0, 0, 0, 0};

Vector2 vec = {0, 0};

bool render = false;

inline void SetRenderField(field* fieldRef, bool render) {
  int tiles = *(&fieldRef->tiles + 1) - fieldRef->tiles;
  for (size_t i = 0; i < tiles; i++) {
    fieldRef->tiles[i].render = render;
  }
}

inline void RenderAllFields(game_state& GameState, int render_list_index) {
  int diff = 0;

  for (size_t n = 0; n < GameState.FieldList.size(); n++) {
    for (size_t i = 0; i < GameState.FieldList[n]->sum_of_field_tiles; i++) {
      recEntity = {(float)(GameState.FieldList[n]->tiles[i].x),
                   (float)(GameState.FieldList[n]->tiles[i].y),
                   (float)GAME_TILE_WIDTH, (float)GAME_TILE_HEIGHT};

      recSprite = {(float)(GameState.FieldList[n]->tiles[i].sprite->x),
                   (float)(GameState.FieldList[n]->tiles[i].sprite->y),
                   (float)GameState.FieldList[n]->tiles[i].sprite->w,
                   (float)GameState.FieldList[n]->tiles[i].sprite->h};

      if ((GameState.FieldList[n]->tiles[i].render == true) &&
          (GameState.FieldList[n]->render_field == true)) {
        render = true;
      } else {
        render = false;
      }

      GameState
          .AllRenderObjects[i + GameState.ObjectsToRender[render_list_index]]
                           [render_list_index] = {
          getTexture(GameState.SpriteList, GameState.GameTextureList,
                     GameState.FieldList[n]->tiles[i].sprite->ID)
              .tex,
          recSprite,
          recEntity,
          vec,
          0,
          Fade(WHITE, GameState.FieldList[n]->field_alpha),
          -60,
          render};

      if (GameState.RenderList[render_list_index].List.size() <
          GameState.FieldList[n]->sum_of_field_tiles +
              GameState.ObjectsToRender[render_list_index]) {
        GameState.RenderList[render_list_index].List.push_back(
            &GameState
                 .AllRenderObjects[i +
                                   GameState.ObjectsToRender[render_list_index]]
                                  [render_list_index]);
      } else {
        GameState.RenderList[render_list_index]
            .List[i + GameState.ObjectsToRender[render_list_index]] =
            &GameState
                 .AllRenderObjects[i +
                                   GameState.ObjectsToRender[render_list_index]]
                                  [render_list_index];
        diff = (int)GameState.RenderList[render_list_index].List.size() -
               (GameState.FieldList[n]->sum_of_field_tiles +
                GameState.ObjectsToRender[render_list_index]);
      }
    }

    if (GameState.ObjectsToRender[render_list_index] <
        GameState.ObjectsToRender[render_list_index] +
            GameState.FieldList[n]->sum_of_field_tiles) {
      GameState.ObjectsToRender[render_list_index] =
          GameState.ObjectsToRender[render_list_index] +
          GameState.FieldList[n]->sum_of_field_tiles;
    }
  }

  for (size_t j = 0; j < diff; j++) {
    GameState.RenderList[render_list_index]
        .List[((GameState.RenderList[render_list_index].List.size()) - diff) +
              j]
        ->render_this = false;
  }
}

inline void swap(RenderObject xp, RenderObject yp) {
  RenderObject temp = xp;
  xp = yp;
  yp = temp;
}

static bool sorted = false;

static int firstround = 0;

static int secondround = 0;
inline void SortLayerRenderObjectList(vector<Render_List>& render_list,
                                      vector<RenderObject*>& sorted_list,
                                      int* last_sorted_list) {
  RenderObject temp;

  int i = 0;
  int j = 0;
  int n = sorted_list.size();

  int num_of_lists = 0;
  int list_index = 0;
  int count = 0;

  int newlist_size = 0;

  for (num_of_lists = 0; num_of_lists < render_list.size(); num_of_lists++) {
    for (list_index = 0; list_index < render_list[num_of_lists].List.size();
         list_index++) {
      newlist_size++;
    }
  }

  DebugLog(" sorted_list.size():", (int)sorted_list.size());
  DebugLog("newlist_size:", newlist_size);

  for (num_of_lists = 0; num_of_lists < render_list.size(); num_of_lists++) {
    for (list_index = 0; list_index < render_list[num_of_lists].List.size();
         list_index++) {
      if (sorted_list.size() < newlist_size) {
        sorted_list.push_back(render_list[num_of_lists].List[list_index]);

        last_sorted_list[i] = sorted_list[i]->layer;
        i++;
      } else {
        sorted_list[count] = render_list[num_of_lists].List[list_index];
        count++;
      }
    }
  }

  if (sorted == false) {
    // cout << "start sorting" << endl;

    for (i = 0; i < n - 1; i++) {
      for (j = 0; j < n - i - 1; j++) {
        if (sorted_list[j]->layer > sorted_list[j + 1]->layer) {
          swap(sorted_list[j], sorted_list[j + 1]);
        } else {
        }
      }
    }

    for (i = 0; i < sorted_list.size(); i++) {
      last_sorted_list[i] = sorted_list[i]->layer;
    }

  } else {
    for (i = 0; i < sorted_list.size(); i++) {
      if (sorted_list.empty() != true) {
        if (last_sorted_list[i] != sorted_list[i]->layer) {
          sorted = false;

          break;
        }
      }
    }
  }

  for (i = 0; i < sorted_list.size(); i++) {
    if (sorted_list.empty() != true) {
      last_sorted_list[i] = sorted_list[i]->layer;
    }
  }

  if (firstround == 0) {
    firstround++;
  } else if (firstround == 1) {
    firstround++;
    sorted = true;
  } else {
  }
  if (sorted == false) {
  }
}

inline void SortLayerRenderObjectList(Render_List& render_list,
                                      vector<RenderObject*>& sorted_list,
                                      int* last_sorted_list) {
  RenderObject temp;

  int i = 0;
  int j = 0;
  int n = sorted_list.size();

  int num_of_lists = 0;
  int list_index = 0;
  int count = 0;

  for (list_index = 0; list_index < render_list.List.size(); list_index++) {
    if (sorted_list.size() < render_list.List.size()) {
      sorted_list.push_back(render_list.List[list_index]);

      last_sorted_list[i] = sorted_list[i]->layer;
      i++;
    } else {
      sorted_list[count] = render_list.List[list_index];
      count++;
    }
  }

  if (sorted == false) {
    for (i = 0; i < n - 1; i++) {
      for (j = 0; j < n - i - 1; j++) {
        if (sorted_list[j]->layer > sorted_list[j + 1]->layer) {
          swap(sorted_list[j], sorted_list[j + 1]);
        } else {
        }
      }
    }
    for (i = 0; i < sorted_list.size(); i++) {
      last_sorted_list[i] = sorted_list[i]->layer;
    }
  } else {
    for (i = 0; i < sorted_list.size(); i++) {
      if (sorted_list.empty() != true) {
        if (last_sorted_list[i] != sorted_list[i]->layer) {
          sorted = false;
          break;
        }
      }
    }
  }

  for (i = 0; i < sorted_list.size(); i++) {
    if (sorted_list.empty() != true) {
      last_sorted_list[i] = sorted_list[i]->layer;
    }
  }

  if (firstround == 0) {
    firstround++;
  } else if (firstround == 1) {
    firstround++;
    sorted = true;
  } else {
  }
  if (sorted == false) {
  }
}

inline void RenderAllLayers(game_state& GameState) {
  float offset_x = 0;
  float offset_y = 0;

  float dest_x = 0;

  float dest_y = 0;

  int render_count = 0;

  DebugLog("GameState.SortedRenderObjectList: ",
           (int)GameState.SortedRenderObjectList.size());

  for (size_t i = 0; i < GameState.SortedRenderObjectList.size(); i++) {
    if (GameState.SortedRenderObjectList[i] != NULL) {
      if (GameState.SortedRenderObjectList[i]->render_this == true) {
        render_count++;
        if (GameState.SortedRenderObjectList[i]->dest.width < 500) {
          offset_x = (GameState.SortedRenderObjectList[i]->dest.width -
                      GAME_TILE_WIDTH) /
                     2;
        }
        if (GameState.SortedRenderObjectList[i]->dest.height < 500) {
          offset_y = GameState.SortedRenderObjectList[i]->dest.height -
                     (GAME_TILE_HEIGHT);
        }

        if (GameState.SortedRenderObjectList[i]->texture.id ==
            getSprite(GameState.SpriteList, GRID_SPRITE_ID).tex_ID) {
          offset_x = 0;

          offset_y = 0;
        }

        dest_x = GameState.SortedRenderObjectList[i]->dest.x +
                 GAMESCREEN_OFFSET_X - offset_x;

        dest_y = GameState.SortedRenderObjectList[i]->dest.y +
                 GAMESCREEN_OFFSET_Y - offset_y;

        DrawTexturePro(
            GameState.SortedRenderObjectList[i]->texture,
            GameState.SortedRenderObjectList[i]->source,
            {dest_x, dest_y, GameState.SortedRenderObjectList[i]->dest.width,
             GameState.SortedRenderObjectList[i]->dest.height},
            GameState.SortedRenderObjectList[i]->origin,
            GameState.SortedRenderObjectList[i]->rotation,
            GameState.SortedRenderObjectList[i]->tint);
      }
    }
  }

  DebugLog("render_count: ", render_count);
}

inline void RenderAllLayers(game_state& GameState,
                             vector<RenderObject*>& RenderObjectList) {
  float offset_x = 0;
  float offset_y = 0;

  float dest_x = 0;
  float dest_y = 0;

  int render_count = 0;

  DebugLog("RenderObjectList: ", (int)RenderObjectList.size());

  for (size_t i = 0; i < RenderObjectList.size(); i++) {
    if (RenderObjectList[i] != NULL) {
      if (RenderObjectList[i]->render_this == true) {
        render_count++;

        render_count++;
        // CENTER SPRITES IN THE MIDDLE OF TILE
        if (RenderObjectList[i]->dest.width < 500) {
          offset_x = (RenderObjectList[i]->dest.width - GAME_TILE_WIDTH) / 2;
        }
        if (RenderObjectList[i]->dest.height < 500) {
          offset_y = RenderObjectList[i]->dest.height - (GAME_TILE_HEIGHT);
        }

        if (RenderObjectList[i]->texture.id ==
            getSprite(GameState.SpriteList, GRID_SPRITE_ID).tex_ID) {
          offset_x = 0;

          offset_y = 0;
        }

        dest_x = RenderObjectList[i]->dest.x + GAMESCREEN_OFFSET_X - offset_x;
        dest_y = RenderObjectList[i]->dest.y + GAMESCREEN_OFFSET_Y - offset_y;

        if (RenderObjectList[i]->use_shader == true) {
          BeginShaderMode(GAME_SHADER);
        }

        DrawTexturePro(
            RenderObjectList[i]->texture, RenderObjectList[i]->source,
            {dest_x, dest_y, RenderObjectList[i]->dest.width,
             RenderObjectList[i]->dest.height},
            RenderObjectList[i]->origin, RenderObjectList[i]->rotation,
            RenderObjectList[i]->tint);

        EndShaderMode();

      }
    }
  }

  DebugLog("render_count: ", render_count);
}

/////----------------------------------------------------------------------------------------------------

Rectangle temp1 = {-100, -100, 0, 0};

Rectangle temp2 = {-100, -100, 0, 0};

void CycleColoredTiles(entity* target, vector<tile>& colored_tiles) {
  static int index = 0;

  if (IsKeyPressed(KEY_RIGHT)) {
    if (index < colored_tiles.size() - 1) {
      index++;
    } else {
      index = 0;
    }
  } else if (IsKeyPressed(KEY_LEFT)) {
    if (index > 0) {
      index--;
    } else {
      index = colored_tiles.size() - 1;
    }
  }

  if (IsKeyPressed(KEY_UP)) {
    if (index < colored_tiles.size() - 1) {
      index++;
    } else {
      index = 0;
    }
  } else if (IsKeyPressed(KEY_DOWN)) {
    if (index > 0) {
      index--;
    } else {
      index = colored_tiles.size() - 1;
    }
  }

  // cout << "index:" << index << endl;
  // cout << " colored_tiles[index].x:" << colored_tiles[index].x << endl;

  target->x = colored_tiles[index].x;
  target->y = colored_tiles[index].y;
}

/////-------------------------------------------------  ColorFieldTile
///-------------------------------------------

inline void SetFieldTileColors(field& fieldRef, vector<sprite>& sprite_list,
                               int Sprite_ID) {
  for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++) {
    fieldRef.tiles[i].sprite = &getSprite(sprite_list, Sprite_ID);
  }
}

inline bool ColorFieldCollisionTileEntityList(field* field_ref,
                                              vector<combatant>& enemies,
                                              vector<combatant>& allies,
                                              vector<sprite>& sprite_list,
                                              int iTileColor) {
  bool colored_tile = false;

  Rectangle temp1 = {-100, -100, 0, 0};
  Rectangle temp2 = {-100, -100, 0, 0};

  tile temptile;

  if (field_ref->collision_tiles.empty()) {
    for (size_t i = 0; i < enemies.size(); i++) {
      temp2 = {enemies[i].pEntity->x, enemies[i].pEntity->y,
               enemies[i].pEntity->w, enemies[i].pEntity->h};

      for (size_t a = 0; a < allies.size(); a++) {
        if (enemies[i].pEntity->x == allies[a].pEntity->x &&
            enemies[i].pEntity->y == allies[a].pEntity->y) {
          // cout << "Player X Y" << endl;
        } else {
          if (enemy_colored == false) {
            for (size_t j = 0; j < field_ref->sum_of_field_tiles; j++) {
              temp1 = {(float)(field_ref->tiles[j].x),
                       (float)(field_ref->tiles[j].y), (float)GAME_TILE_WIDTH,
                       (float)GAME_TILE_HEIGHT};

              if (CheckCollisionRecs(
                      {(float)(temp2.x - 1 + (GAME_TILE_WIDTH / 2)),
                       (float)(temp2.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2},
                      {(float)(temp1.x - 1 + (GAME_TILE_WIDTH / 2)),
                       (float)(temp1.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2})) {
                field_ref->tiles[j].sprite =
                    &getSprite(sprite_list, iTileColor);

                field_ref->collision_tiles.push_back(field_ref->tiles[j]);

                colored_tile = true;

                cout << "collision_tiles 1 " << i << endl;
              } else {
              }
            }

            if (entity_checked >= enemies.size()) {
              enemy_colored = true;
            } else {
              entity_checked++;
            }
          }
        }
      }
    }

  } else {
    for (size_t i = 0; i < enemies.size(); i++) {
      temp2 = {enemies[i].pEntity->x, enemies[i].pEntity->y,
               enemies[i].pEntity->w, enemies[i].pEntity->h};

      for (size_t a = 0; a < allies.size(); a++) {
        if (enemies[i].pEntity->x == allies[a].pEntity->x &&
            enemies[i].pEntity->y == allies[a].pEntity->y) {
          // cout << "Player X Y" << endl;
        } else {
          if (enemy_colored == false) {
            for (size_t j = 0; j < field_ref->sum_of_field_tiles; j++) {
              temp1 = {(float)(field_ref->tiles[j].x),
                       (float)(field_ref->tiles[j].y), (float)GAME_TILE_WIDTH,
                       (float)GAME_TILE_HEIGHT};

              if (CheckCollisionRecs(
                      {(float)(temp2.x - 1 + (GAME_TILE_WIDTH / 2)),
                       (float)(temp2.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2},
                      {(float)(temp1.x - 1 + (GAME_TILE_WIDTH / 2)),
                       (float)(temp1.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2})) {
                field_ref->tiles[j].sprite =
                    &getSprite(sprite_list, iTileColor);

                if (field_ref->tiles[j].x == field_ref->collision_tiles[i].x &&
                    field_ref->tiles[j].y == field_ref->collision_tiles[i].y) {
                  field_ref->collision_tiles[i].sprite =
                      &getSprite(sprite_list, iTileColor);
                } else {
                  field_ref->collision_tiles.push_back(field_ref->tiles[j]);
                }

                colored_tile = true;

                cout << "collision_tiles tile 2 " << i << endl;
              } else {
              }
            }

            if (entity_checked >= enemies.size()) {
              enemy_colored = true;
            } else {
              entity_checked++;
            }
          }
        }
      }
    }
  }

  return colored_tile;
}

inline bool ColorFieldCollisionTileEntityList(field& field_ref,
                                              vector<entity>& entity_list,
                                              vector<combatant>& allies,
                                              vector<sprite>& sprite_list,
                                              int iTileColor) {
  bool colored_tile = false;

  Rectangle temp2;
  tile temptile;

  for (size_t i = 0; i < entity_list.size(); i++) {
    temp2 = {(float)entity_list[i].x, (float)entity_list[i].y,
             (float)entity_list[i].w, (float)entity_list[i].h};

    for (size_t a = 0; a < allies.size(); a++) {
      if (entity_list[i].x == allies[a].pEntity->x &&
          entity_list[i].y == allies[a].pEntity->y) {
        // cout << "Player X Y" << endl;
      } else {
        // Check layer
        if (allies[a].pEntity->layer != entity_list[i].layer) {
        } else {
          if (enemy_colored == false) {
            for (size_t j = 0; j < field_ref.sum_of_field_tiles; j++) {
              temp1 = {(float)(field_ref.tiles[j].x),
                       (float)(field_ref.tiles[j].y), (float)GAME_TILE_WIDTH,
                       (float)GAME_TILE_HEIGHT};

              if (CheckCollisionRecs(
                      {(float)(temp2.x - 1 + (GAME_TILE_WIDTH / 2)),
                       (float)(temp2.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2},
                      {(float)(temp1.x - 1 + (GAME_TILE_WIDTH / 2)),
                       (float)(temp1.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2})) {
                if (field_ref.last_tile_x != temp2.x ||
                    field_ref.last_tile_y != temp2.y) {
                  field_ref.tiles[j].sprite =
                      &getSprite(sprite_list, iTileColor);  // red tile

                  field_ref.collision_tiles.push_back(field_ref.tiles[j]);

                  field_ref.last_tile_x = temp2.x;
                  field_ref.last_tile_y = temp2.y;

                  colored_tile = true;
                } else {
                }
              } else {
              }
            }

            if (entity_checked >= entity_list.size()) {
              enemy_colored = true;
            } else {
              entity_checked++;
            }
          }
        }
      }
    }
  }

  return colored_tile;
}

inline bool ColorFieldTrackTile(field& field_ref, vector<sprite>& sprite_list,
                                entity* target, int color) {
  bool colored_tile = false;

  temp2 = {(float)target->x, (float)target->y, (float)target->w,
           (float)target->h};

  for (size_t i = 0; i < field_ref.sum_of_field_tiles; i++) {
    temp1 = {(float)(field_ref.tiles[i].x), (float)(field_ref.tiles[i].y),
             (float)GAME_TILE_WIDTH, (float)GAME_TILE_HEIGHT};

    if (CheckCollisionRecs(
            {(float)(temp2.x - 1 + (GAME_TILE_WIDTH / 2)),
             (float)(temp2.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2},
            {(float)(temp1.x - 1 + (GAME_TILE_WIDTH / 2)),
             (float)(temp1.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2})) {
      if (field_ref.last_tile_x != temp2.x ||
          field_ref.last_tile_y != temp2.y) {
        field_ref.tiles[i].sprite = &getSprite(sprite_list, color);
        field_ref.tiles[i].render = true;
        field_ref.track_tiles.push_back(field_ref.tiles[i]);

        field_ref.last_tile_x = temp2.x;
        field_ref.last_tile_y = temp2.y;

        colored_tile = true;

        break;
      } else {
      }
    } else {
    }
  }

  return colored_tile;
}

inline void ResetTrackTilesColor(field& field_ref, vector<sprite>& sprite_list,
                                 int Sprite_ID) {
  for (size_t i = 0; i < field_ref.sum_of_field_tiles; i++) {
    for (size_t j = 0; j < field_ref.track_tiles.size(); j++) {
      if (field_ref.tiles[i].x == field_ref.track_tiles[j].x &&
          field_ref.tiles[i].y == field_ref.track_tiles[j].y) {
        field_ref.tiles[i].sprite = &getSprite(sprite_list, Sprite_ID);
        field_ref.tiles[i].render = true;
      }
    }
  }
}

inline bool IsInArray(int* Array, int Size, int number) {
  bool result = false;
  // int arraySize = sizeof(Array) / sizeof(Array[0]);

  for (size_t i = 0; i < Size; i++) {
    if (Array[i] == number) {
      result = true;
      break;
    }
  }

  return result;
}

inline void randomSpawnTile(vector<sprite>& sprite_list, field& fieldRef,
                            field& spawn_field) {
  int numOfTiles = 10;
  int randomTilesIndex[124];

  int temp = -99;

  int temp2 = -99;

  float tempvar;

  if (fieldRef.sum_of_field_tiles != 0) {
    for (size_t i = 0; i < numOfTiles; i++) {
      temp = GetRandomValue(0, (fieldRef.sum_of_field_tiles - 1));

      while (IsInArray(randomTilesIndex, i, temp)) {
        temp2 = GetRandomValue(0, (fieldRef.sum_of_field_tiles - 1));

        temp = temp2;
      }

      randomTilesIndex[i] = temp;
    }

    cout << "fieldRef.sum_of_field_tiles " << fieldRef.sum_of_field_tiles;

    cout << endl;

    for (size_t k = 0; k < numOfTiles; k++) {
      cout << randomTilesIndex[k] << " ";
    }

    cout << endl;

    spawn_field.sum_of_field_tiles = numOfTiles;

    spawn_field.h = 0;
    spawn_field.w = 0;

    spawn_field.x = 0;
    spawn_field.y = 0;

    for (int i = 0; i < numOfTiles; i++) {
      tempvar = fieldRef.tiles[randomTilesIndex[i]].h;

      spawn_field.tiles[i].h = tempvar;
      tempvar = fieldRef.tiles[randomTilesIndex[i]].w;

      spawn_field.tiles[i].w = tempvar;

      tempvar = fieldRef.tiles[randomTilesIndex[i]].x;
      spawn_field.tiles[i].x = tempvar;

      tempvar = fieldRef.tiles[randomTilesIndex[i]].y;
      spawn_field.tiles[i].y = tempvar;

      spawn_field.tiles[i].sprite = &getSprite(sprite_list, BLUE_TILE);
    }

    cout << endl;
    cout << "FieldList set " << fieldRef.sum_of_field_tiles << " "
         << spawn_field.sum_of_field_tiles << endl;
  } else {
    cout << "FieldList not set " << fieldRef.sum_of_field_tiles << " "
         << spawn_field.sum_of_field_tiles << endl;
  }
}

inline void DrawIsoTriangles(entity* e) {
  // temp3 = getTileRect(e->entity_tile);

  // DrawLine(temp3.line_1_p1_x, temp3.line_1_p1_y, temp3.line_1_p2_x,
  // temp3.line_1_p2_y, BLUE); DrawLine(temp3.line_2_p1_x, temp3.line_2_p1_y,
  // temp3.line_2_p2_x, temp3.line_2_p2_y, RED); DrawLine(temp3.line_3_p1_x,
  // temp3.line_3_p1_y, temp3.line_3_p2_x, temp3.line_3_p2_y, GREEN);
  // DrawLine(temp3.line_4_p1_x, temp3.line_4_p1_y, temp3.line_4_p2_x,
  // temp3.line_4_p2_y, ORANGE);

  static tile_triangles temp_rect;

  Rectangle temp;

  temp.x = e->entity_tile.x + GAMESCREEN_OFFSET_X;
  temp.y = e->entity_tile.y + GAMESCREEN_OFFSET_Y;
  temp.width = e->entity_tile.width;
  temp.height = e->entity_tile.height;

  temp_rect = getTileTriangles(temp);

  Vector2 p1;
  Vector2 p2;
  Vector2 p3;

  p1.x = temp_rect.tri_1_line_1_x;
  p1.y = temp_rect.tri_1_line_1_y;

  p2.x = temp_rect.tri_1_line_2_x;
  p2.y = temp_rect.tri_1_line_2_y;

  p3.x = temp_rect.tri_1_line_3_x;
  p3.y = temp_rect.tri_1_line_3_y;

  DrawTriangle(p1, p2, p3, ORANGE);

  p1.x = temp_rect.tri_2_line_1_x;
  p1.y = temp_rect.tri_2_line_1_y;

  p2.x = temp_rect.tri_2_line_2_x;
  p2.y = temp_rect.tri_2_line_2_y;

  p3.x = temp_rect.tri_2_line_3_x;
  p3.y = temp_rect.tri_2_line_3_y;

  DrawTriangle(p1, p2, p3, BLUE);

  p1.x = temp_rect.tri_3_line_1_x;
  p1.y = temp_rect.tri_3_line_1_y;

  p2.x = temp_rect.tri_3_line_2_x;
  p2.y = temp_rect.tri_3_line_2_y;

  p3.x = temp_rect.tri_3_line_3_x;
  p3.y = temp_rect.tri_3_line_3_y;

  DrawTriangle(p1, p2, p3, ORANGE);

  p1.x = temp_rect.tri_4_line_1_x;
  p1.y = temp_rect.tri_4_line_1_y;

  p2.x = temp_rect.tri_4_line_2_x;
  p2.y = temp_rect.tri_4_line_2_y;

  p3.x = temp_rect.tri_4_line_3_x;
  p3.y = temp_rect.tri_4_line_3_y;

  DrawTriangle(p1, p2, p3, BLUE);
}

inline void drawInnerIsoRect(entity* e) {
  // temp3 = getTileInnerRect(e->entity_tile);

  // DrawLine(temp3.line_1_p1_x, temp3.line_1_p1_y, temp3.line_1_p2_x,
  // temp3.line_1_p2_y, YELLOW); DrawLine(temp3.line_2_p1_x, temp3.line_2_p1_y,
  // temp3.line_2_p2_x, temp3.line_2_p2_y, YELLOW); DrawLine(temp3.line_3_p1_x,
  // temp3.line_3_p1_y, temp3.line_3_p2_x, temp3.line_3_p2_y, YELLOW);
  // DrawLine(temp3.line_4_p1_x, temp3.line_4_p1_y, temp3.line_4_p2_x,
  // temp3.line_4_p2_y, YELLOW);
}

inline void InitDebugLog() {
  string temp;

  for (size_t i = 0; i < 100; i++) {
    temp = "Log line " + to_string(i);

    GAME_LOG.DebugLogLines.push_back(temp);
  }
}

inline void InitLog() {
  string temp;

  for (size_t i = 0; i < 100; i++) {
    temp = "Log line " + to_string(i);

    GAME_LOG.LogLines.push_back(temp);
  }
}

inline void InitUniqueSprite(game_state& GameState, combatant& com,
                             int unique_id) {
  com.unique_sprite.h = com.pEntity->sprite->h;
  com.unique_sprite.ID = com.pEntity->sprite->ID + unique_id;
  com.unique_sprite.img = com.pEntity->sprite->img;
  com.unique_sprite.index = com.pEntity->sprite->index;
  com.unique_sprite.name = com.pEntity->sprite->name;
  com.unique_sprite.offset_x = com.pEntity->sprite->offset_x;
  com.unique_sprite.offset_y = com.pEntity->sprite->offset_y;
  com.unique_sprite.tex_ID = com.pEntity->sprite->tex_ID;
  com.unique_sprite.w = com.pEntity->sprite->w;
  com.unique_sprite.x = com.pEntity->sprite->x;
  com.unique_sprite.y = com.pEntity->sprite->y;

  GameState.SpriteList.push_back(com.unique_sprite);

  SetSprite(GameState.SpriteList, com.pEntity, com.unique_sprite.ID);
  // SetSprite(GameState.SpriteList, com.pEntity,  com.unique_sprite.ID);
}

inline void InitCamera(Camera2D& camera) {
  camera.offset =
      Vector2{(float)GAMEWINDOW_WIDTH / 2, (float)GAMEWINDOW_HEIGHT / 2};
  camera.rotation = 0;
  camera.zoom = CAMERA_ZOOM;
}

inline point GetCameraMousePosition(game_state& GameState) {
  point temp;

  temp.x = GetMousePosition().x + GameState.WorldPlayer.pEntity->x -
           CAMERA.offset.x - GAMESCREEN_OFFSET_X;
  temp.y = GetMousePosition().y + GameState.WorldPlayer.pEntity->y -
           CAMERA.offset.y - GAMESCREEN_OFFSET_X;

  return temp;
}

#endif