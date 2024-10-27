/* ========================================================================

======================================================================== */

#pragma once

#ifndef logic_cpp
#define logic_cpp

#include <iostream>

#include "../header_files/game_entities.h"
#include "../header_files/globals.h"
#include "../header_files/logic_func.h"
#include "../header_files/raylib.h"
#include "combat.cpp"
#include "game_engine.cpp"

// #include "gui.cpp"
#include <cstdlib>
#include <ctime>
#include <random>

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

bool collision = false;

Rectangle temptarget;

//================================== RANDOMNESS
//======================================
typedef std::mt19937
    MyRNG;  // the Mersenne Twister with a popular choice of parameters
static uint32_t seed_val;  // populate somehow

std::uniform_int_distribution<uint32_t> uint_dist;  // by default range [0, MAX]
std::uniform_int_distribution<uint32_t> uint_dist20(0, 20);  // range [1,20]

static MyRNG rng;

//========================================================================

inline void ToggleMoveFields(game_state& GameState) {
  if (DEBUG_TOGGLE_ENEMY_MOVE_FIELDS == true) {
    DEBUG_TOGGLE_ENEMY_MOVE_FIELDS = false;

    SetRenderEnemyFields(GameState.Map.EnemyList, false);
  } else {
    SetRenderEnemyFields(GameState.Map.EnemyList, true);
    DEBUG_TOGGLE_ENEMY_MOVE_FIELDS = true;
  }
}

inline void SetEntityListEllipses(vector<entity>& entities) {
  for (size_t i = 0; i < entities.size(); i++) {
    entities[i].el.center.x = entities[i].x + entities[i].entity_tile.width / 2;
    entities[i].el.center.y =
        entities[i].y + entities[i].entity_tile.height / 2;

    entities[i].el.w = entities[i].entity_tile.width / 8;
    entities[i].el.h = entities[i].entity_tile.height / 2;
  }
}

inline void CalculateDamageEnemy(game_state& GameState, Rectangle& ColRect) {
  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    /* code */

    if (GameState.Map.EnemyList[i].pEntity->x == ColRect.x &&
        GameState.Map.EnemyList[i].pEntity->y == ColRect.y) {
      GameState.Map.EnemyList[i].Stats.CurrentHP--;

      Log("HIT");
    } else {
      Log("NO HIT");
    }
  }
}

inline int GetMoveFieldRange(combatant* combatant) {
  int temp = 1;

  cout << "combatant->current_movecount " << combatant->current_movecount
       << endl;
  cout << "combatant->move_range " << combatant->move_range << endl;

  if (combatant->current_movecount != 0) {
    temp = combatant->move_range - (combatant->current_movecount - 1);

    if (temp <= 0) {
      temp = 1;
    }
  } else {
    combatant->current_movecount = 1;
    temp = combatant->move_range;
  }

  return temp;
}

inline void ResetFieldVariables(combatant* Combatant) {
  Combatant->move_field.track_tiles.clear();
  Combatant->move_field.collision_tiles.clear();

  Combatant->move_field.last_tile_x = -10000;
  Combatant->move_field.last_tile_y = -10000;

  Combatant->move_field.render_field = false;
  SetRenderField(&Combatant->move_field, false);

  enemy_colored = false;
  entity_checked = 0;
  Combatant->attack_field.render_field = false;
}

inline void EntityMoveLogic(combatant& pEnemy, combatant& pPlayer,
                            bool towards) {
  bool moved = false;

  int right_vel = (GAME_TILE_WIDTH / 2);
  int left_vel = -(GAME_TILE_WIDTH / 2);
  int up_vel = -(GAME_TILE_HEIGHT / 2);
  int down_vel = (GAME_TILE_HEIGHT / 2);

  int random = 0;

  Log("Random:", random);
  float diff_x;
  float diff_y;

  bool LEFT_OF_PLAYER = false;
  bool RIGHT_OF_PLAYER = false;
  bool BELOW_OF_PLAYER = false;
  bool ABOVE_OF_PLAYER = false;
  bool YLINE_OF_PLAYER = false;
  bool XLINE_OF_PLAYER = false;

  float enemy_temp_x = pEnemy.pEntity->x;

  float enemy_temp_y = pEnemy.pEntity->y;

  int dir_moved;

  int direction;

  if (towards == true) {
    direction = 1;
  } else {
    direction = -1;
  }
  printf("pEnemy.move_range");
  cout << pEnemy.move_range << endl;
  for (size_t i = 0; i < pEnemy.move_range; i++) {
    random = (int)uint_dist20(rng);

    cout << "random: " << random << endl;

    dir_moved = 0;
    LEFT_OF_PLAYER = false;
    RIGHT_OF_PLAYER = false;
    BELOW_OF_PLAYER = false;
    ABOVE_OF_PLAYER = false;
    YLINE_OF_PLAYER = false;
    XLINE_OF_PLAYER = false;

    cout << "enemy_temp_y: " << enemy_temp_y << endl;

    cout << "enemy_temp_x: " << enemy_temp_x << endl;

    if (enemy_temp_x < pPlayer.pEntity->x) {
      Log("ENEMY LEFT OF PLAYER");

      diff_x = (pPlayer.pEntity->x - enemy_temp_x) / 64;

      Log("Diff in x: ", diff_x);

      LEFT_OF_PLAYER = true;
    } else if (enemy_temp_x == pPlayer.pEntity->x) {
      Log("ENEMY in Y-LINE OF PLAYER");
      YLINE_OF_PLAYER = true;
    } else {
      Log("ENEMY RIGHT OF PLAYER");

      diff_x = (pPlayer.pEntity->x - enemy_temp_x) / 64;

      Log("Diff in x: ", diff_x);

      RIGHT_OF_PLAYER = true;
    }

    if (enemy_temp_y < pPlayer.pEntity->y) {
      Log("ENEMY ABOVE OF PLAYER");

      diff_y = (pPlayer.pEntity->y - enemy_temp_y) / 32;

      Log("Diff in y: ", diff_y);

      ABOVE_OF_PLAYER = true;
    } else if (enemy_temp_y == pPlayer.pEntity->y) {
      Log("ENEMY X-LINE OF PLAYER");
      XLINE_OF_PLAYER = true;
    } else {
      Log("ENEMY BELOW OF PLAYER");

      diff_y = (pPlayer.pEntity->y - enemy_temp_y) / 32;

      Log("Diff in y: ", diff_y);

      BELOW_OF_PLAYER = true;
    }

    if (LEFT_OF_PLAYER && BELOW_OF_PLAYER) {
      if (diff_y + diff_x == 0) {
        if (random % 3 == 0) {
          dir_moved = RIGHT * direction;

          pEnemy.movelist.push_back(dir_moved);
        } else {
          if (random % 2 == 0) {
            dir_moved = DOWN * direction;
            pEnemy.movelist.push_back(dir_moved);
          } else {
            dir_moved = UP * direction;
            pEnemy.movelist.push_back(dir_moved);
          }
        }
      } else if (diff_x + diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = UP * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = DOWN * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      }
    }

    if (LEFT_OF_PLAYER && ABOVE_OF_PLAYER) {
      if (diff_y == diff_x) {
        if (random % 3 == 0) {
          dir_moved = DOWN * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          if (random % 2 == 0) {
            dir_moved = RIGHT * direction;
            pEnemy.movelist.push_back(dir_moved);
          } else {
            dir_moved = LEFT * direction;
            pEnemy.movelist.push_back(dir_moved);
          }
        }
      } else if (diff_x - diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = DOWN * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = DOWN * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      }
    }

    if (RIGHT_OF_PLAYER && ABOVE_OF_PLAYER) {
      if (diff_x + diff_y == 0) {
        if (random % 3 == 0) {
          dir_moved = LEFT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          if (random % 2 == 0) {
            dir_moved = DOWN * direction;
            pEnemy.movelist.push_back(dir_moved);
          } else {
            dir_moved = UP * direction;
            pEnemy.movelist.push_back(dir_moved);
          }
        }
      } else if (diff_x + diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = (UP * direction);
          pEnemy.movelist.push_back(dir_moved);
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = DOWN * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      }
    }

    if (RIGHT_OF_PLAYER && BELOW_OF_PLAYER) {
      if (diff_y == diff_x) {
        if (diff_y == diff_x) {
          if (random % 3 == 0) {
            dir_moved = UP * direction;
            pEnemy.movelist.push_back(dir_moved);
          } else {
            if (random % 2 == 0) {
              dir_moved = RIGHT * direction;
              pEnemy.movelist.push_back(dir_moved);
            } else {
              dir_moved = LEFT * direction;
              pEnemy.movelist.push_back(dir_moved);
            }
          }
        }
      } else if (diff_x - diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = UP * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;
          pEnemy.movelist.push_back(dir_moved);
        } else {
          dir_moved = UP * direction;
          pEnemy.movelist.push_back(dir_moved);
        }
      }
    }

    if (YLINE_OF_PLAYER && BELOW_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = RIGHT * direction;
        pEnemy.movelist.push_back(dir_moved);
      } else {
        dir_moved = UP * direction;
        pEnemy.movelist.push_back(dir_moved);
      }
    }

    if (YLINE_OF_PLAYER && ABOVE_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = DOWN * direction;
        pEnemy.movelist.push_back(dir_moved);
      } else {
        dir_moved = LEFT * direction;
        pEnemy.movelist.push_back(dir_moved);
      }
    }

    if (XLINE_OF_PLAYER && LEFT_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = DOWN * direction;
        pEnemy.movelist.push_back(dir_moved);
      } else {
        dir_moved = RIGHT * direction;
        pEnemy.movelist.push_back(dir_moved);
      }
    }

    if (XLINE_OF_PLAYER && RIGHT_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = UP * direction;
        pEnemy.movelist.push_back(dir_moved);
      } else {
        dir_moved = LEFT * direction;
        pEnemy.movelist.push_back(dir_moved);
      }
    }

    if (dir_moved == LEFT) {
      printf("[LEFT1]");
      enemy_temp_x = enemy_temp_x + (left_vel / 1);
      enemy_temp_y = enemy_temp_y + (down_vel / 1);
    }
    if (dir_moved == RIGHT) {
      printf("[RIGHT1]");
      enemy_temp_x = enemy_temp_x + (right_vel / 1);
      enemy_temp_y = enemy_temp_y + (up_vel / 1);
    }
    if (dir_moved == UP) {
      printf("[UP1]");
      enemy_temp_x = enemy_temp_x + (left_vel / 1);
      enemy_temp_y = enemy_temp_y + (up_vel / 1);
    }
    if (dir_moved == DOWN) {
      printf("[DOWN1]");
      enemy_temp_x = enemy_temp_x + (right_vel / 1);
      enemy_temp_y = enemy_temp_y + (down_vel / 1);
    }
    printf(" ");
  }
}

inline void EnemyLogic(game_state& GameState) {
  Log("Enemy Passed, turn ended");

  SetRenderEnemyFields(GameState.Map.EnemyList, false);

  // enemy_list[0].movelist.push_back(1);

  EntityMoveLogic(GameState.Map.EnemyList[0], GameState.Map.CombatantList[0],
                  false);

  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    if (!GameState.Map.EnemyList[i].movelist.empty()) {
      GameState.AnimatingEnemyMovement = true;
    }
  }

  GameState.PLAYER_TURN = true;
  GameState.GAME_TURN++;
}

inline void CheckKeyboardInput(game_state& GameState) {
  if (IsKeyPressed(KEY_Z)) {
    cout << "CheckKeyboardInput Z PRESSED" << endl;
    GameState.ActionMenu.Z_COUNT++;
  }

  if (IsKeyPressed(KEY_X)) {
    cout << "X PRESSED" << endl;
    GameState.ActionMenu.X_COUNT++;
  }

  if (IsKeyPressed(KEY_L)) {
    cout << "L PRESSED" << endl;

    for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      if (GameState.Map.EntityList[i].layer != 0 )
      {
        GameState.Map.EntityList[i].alpha = 0.2;

      }

  }
  }

  if (IsKeyPressed(KEY_K)) {
    cout << "K PRESSED" << endl;

    // setLayers();

    // cout << entity_list.size() + sum_of_field_tiles << endl;

    // for (size_t i = 0; i < entity_list.size(); i++)
    //{
    //	cout << "entity x: " << entity_list[i].x << " y: " <<
    // entity_list[i].y
    //<< endl; 	cout << "entity ID: " << entity_list[i].ID << endl;
    // }

    // cout << "objects_to_render[0]: " << objects_to_render[0] << endl;

    // cout << "objects_to_render[1]: " << objects_to_render[1] << endl;
    // // cout << "SortedRenderObject_list: " <<
    // SortedRenderObject_list.size()
    // << endl;

    // randomSpawnTile(position_field, spawn_field);

    // cout << "objects_to_render: " << objects_to_render[0] << endl;
    // cout << "gui_entity_list: " << gui_entity_list.size() << endl;
    // cout << "GameState.Map.EntityList: " << GameState.Map.EntityList.size()
    // << endl;

    // cout << "target_field.sum_of_field_tiles " <<
    // target_field.sum_of_field_tiles << endl;

    // cout << "SortedRenderObject_list.size(): " <<
    // SortedRenderObject_list.size() << endl;

    for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      GameState.Map.EntityList[i].layer = 0;
    }
    cout << endl;
  }

  if (IsKeyPressed(KEY_TAB)) {
    cout << "TAB PRESSED" << endl;

    ToggleMoveFields(GameState);
  }

  if (IsKeyPressed(KEY_F5)) {
    cout << "WriteSpriteDataRaw" << endl;
    WriteSpriteDataRaw(MAPS_PATH + "game_sprite_data_raw.txt",
                       GameState.PNGList, GameState.GameTextureList);
  }
}

inline bool CheckColoredTileCollission(vector<tile>& colored_tiles,
                                       Rectangle& temptarget) {
  bool col = false;

  if (colored_tiles.empty() != true) {
    for (size_t i = 0; i < colored_tiles.size(); i++) {
      // Check if any tile has already been crossed
      if (CheckCollisionRecs(
              {(float)(temptarget.x - 1 + (GAME_TILE_WIDTH / 2)),
               (float)(temptarget.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2},
              {(float)(colored_tiles[i].x - 1 + (GAME_TILE_WIDTH / 2)),
               (float)(colored_tiles[i].y - 1 + (GAME_TILE_HEIGHT / 2)), 2,
               2})) {
        // if (last_tile.x != temptarget.x || last_tile.y != temptarget.y)

        col = true;

        // Log("Colored tile ", (int)i);

        return col;

        break;
      } else {
        /// moved = true;
      }
    }
  }

  return col;
}

inline bool CheckColoredTrackTileCollission(field& ref_field,
                                            Rectangle& temptarget) {
  bool collission = false;

  if (ref_field.track_tiles.empty() != true) {
    DebugLog(" ref_field.size()", (int)ref_field.track_tiles.size());

    for (size_t i = 0; i < ref_field.track_tiles.size() - 1; i++) {
      // Check if any tile has already been crossed
      if (CheckCollisionRecs(
              {(float)(temptarget.x - 1 + (GAME_TILE_WIDTH / 2)),
               (float)(temptarget.y - 1 + (GAME_TILE_HEIGHT / 2)), 2, 2},
              {(float)(ref_field.track_tiles[i].x - 1 + (GAME_TILE_WIDTH / 2)),
               (float)(ref_field.track_tiles[i].y - 1 + (GAME_TILE_HEIGHT / 2)),
               2, 2})) {
        collission = true;

        DebugLog("Colored tile ", (int)i);

        collission;

        break;
      } else {
        /// moved = true;
      }
    }
  }

  return collission;
}

// inline void PerformAttack()
//{

//}

inline void AttackLogic(game_state& GameState) {
  Rectangle temp_target = {
      GameState.Target.pEntity->x, GameState.Target.pEntity->y,
      GameState.Target.pEntity->w, GameState.Target.pEntity->h};

  if (ColorFieldCollisionTileEntityList(
          &GameState.CombatantSelected.attack_field, GameState.Map.EnemyList,
          GameState.Map.CombatantList, GameState.SpriteList, GREEN_TILE)) {
    DebugLog(
        "AttackField Collision",
        (int)GameState.CombatantSelected.attack_field.collision_tiles.size());
  } else {
    DebugLog("No Collision");
  }

  if (GameState.CombatantSelected.attack_field.collision_tiles.empty() !=
      true) {
    GameState.Target.pEntity->x =
        GameState.CombatantSelected.attack_field.collision_tiles[0].x;
    GameState.Target.pEntity->y =
        GameState.CombatantSelected.attack_field.collision_tiles[0].y;

    CycleColoredTiles(GameState.Target.pEntity,
                      GameState.CombatantSelected.attack_field.collision_tiles);

    if (CheckColoredTileCollission(
            GameState.CombatantSelected.attack_field.collision_tiles,
            temp_target)) {
      if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z))) {
        cout << "Attack collision and x pressed" << endl;

        CalculateDamageEnemy(GameState, temp_target);

        ResetFieldVariables(&GameState.CombatantSelected);

        GameState.Target.is_on_move_field = false;

        GameState.Target.pEntity->x = GameState.CombatantSelected.pEntity->x;
        GameState.Target.pEntity->y = GameState.CombatantSelected.pEntity->y;

        GameState.ActionMenu.X_COUNT = 0;
        GameState.ActionMenu.Z_COUNT = 0;

        GameState.Target.is_attacking = false;
      }
    }
  }

  if ((IsKeyPressed(KEY_Z) && !IsKeyPressed(KEY_X))) {
    cout << "Attack z pressed" << endl;

    ResetFieldVariables(&GameState.CombatantSelected);

    GameState.Target.is_on_move_field = false;

    GameState.Target.pEntity->x = GameState.CombatantSelected.pEntity->x;
    GameState.Target.pEntity->y = GameState.CombatantSelected.pEntity->y;

    GameState.Target.is_attacking = false;

    GameState.ActionMenu.X_COUNT = 0;
    GameState.ActionMenu.Z_COUNT = 0;
  }
}

int static previous_turn = 1;
bool static previous_state = false;

inline void UpdateGameTurn(game_state& GameState) {
  if (GameState.PLAYER_TURN != previous_state) {
    previous_state = GameState.PLAYER_TURN;

    if (GameState.GAME_TURN == previous_turn) {
      Log("Game Turn ", GameState.GAME_TURN);

      previous_turn = GameState.GAME_TURN + 1;
    }
  }
}

void InitMoveLogic(game_state& GameState) {
  bool field_found = false;

  GameState.Target.is_on_move_field = true;
  GameState.ActionMenu.is_menu_up = false;

  GameState.CombatantSelected.move_field.range =
      GetMoveFieldRange(&GameState.CombatantSelected);

  GameState.CombatantSelected.move_field.track_tiles.clear();
  GameState.CombatantSelected.move_field.track_tiles.clear();

  GameState.CombatantSelected.attack_field.collision_tiles.clear();
  GameState.CombatantSelected.attack_field.collision_tiles.clear();

  enemy_colored = false;
  entity_checked = 0;

  GameState.CombatantSelected.move_field.render_field = true;

  for (size_t i = 0; i < GameState.FieldList.size(); i++) {
    if (GameState.FieldList[i] == &GameState.CombatantSelected.move_field) {
      GameState.FieldList[i]->range =
          GetMoveFieldRange(&GameState.CombatantSelected);

      SetField(GameState, *GameState.FieldList[i],
               GameState.CombatantSelected.pEntity->x,
               GameState.CombatantSelected.pEntity->y, SQUARE, GREEN_TILE);

      field_found = true;
      cout << "field_found" << endl;

      break;
    }
  }

  if (field_found == false) {
    SetField(GameState, GameState.CombatantSelected.move_field,
             GameState.CombatantSelected.pEntity->x,
             GameState.CombatantSelected.pEntity->y, SQUARE, GREEN_TILE);

    GameState.FieldList.push_back(&GameState.CombatantSelected.move_field);

    cout << "not field_found" << endl;
  }
}

void InitAttackLogic(game_state& GameState) {
  Log("ATTACK!");

  bool field_found = false;

  GameState.ActionMenu.is_menu_up = false;
  GameState.Target.is_attacking = true;

  enemy_colored = false;
  entity_checked = 0;

  GameState.CombatantSelected.attack_field.render_field = true;

  GameState.CombatantSelected.attack_field.range =
      GameState.CombatantSelected.attack_range;

  for (size_t i = 0; i < GameState.FieldList.size(); i++) {
    if (GameState.FieldList[i] == &GameState.CombatantSelected.attack_field) {
      SetField(GameState, *GameState.FieldList[i],
               GameState.CombatantSelected.pEntity->x,
               GameState.CombatantSelected.pEntity->y, SQUARE, BLUE_TILE);

      field_found = true;
      break;
    }
  }

  if (field_found == false) {
    SetField(GameState, GameState.CombatantSelected.attack_field,
             GameState.CombatantSelected.pEntity->x,
             GameState.CombatantSelected.pEntity->y, SQUARE, BLUE_TILE);

    GameState.FieldList.push_back(&GameState.CombatantSelected.attack_field);
  }

  GameState.CombatantSelected.attack_field.render_field = true;
  SetRenderField(&GameState.CombatantSelected.attack_field,
                 GameState.CombatantSelected.attack_field.render_field);
}

inline void MovePressed(game_state& GameState) {
  /// Init move logic

  InitMoveLogic(GameState);
}

inline void ReadyPressed(game_state& GameState) {
  GameState.ActionMenu.is_pre_state = false;
  GameState.ActionMenu.X_COUNT = 0;

  GameState.Target.pEntity->x = GameState.CombatantSelected.pEntity->x;
  GameState.Target.pEntity->y = GameState.CombatantSelected.pEntity->y;

  GameState.CombatantSelected.position_field.render_field = false;
  SetRenderField(&GameState.CombatantSelected.position_field, false);

  GameState.ActionMenu.is_menu_up = false;

  GameState.PLAYER_TURN = true;
}

inline void EndPressed(game_state& GameState) {
  GameState.ActionMenu.X_COUNT = 0;
  GameState.ActionMenu.Z_COUNT = 0;

  GameState.CombatantSelected.position_field.render_field = false;
  SetRenderField(&GameState.CombatantSelected.position_field, false);

  GameState.ActionMenu.is_menu_up = false;

  GameState.PLAYER_TURN = false;

  Log("Player ended turn ", GameState.GAME_TURN);

  GameState.CombatantSelected.current_movecount = 1;

  GameState.ActionMenu.MOVE_COUNT =
      GameState.CombatantSelected.current_movecount;
}

inline void AttackPressed(game_state& GameState) {
  // Init Attack Logic
  InitAttackLogic(GameState);
}

inline void ActionGuiLogic(game_state& GameState) {
  if (GameState.ActionMenu.is_pre_state == true) {
    if (ActionButton[0] == true) {
      Log("Ready");

      ReadyPressed(GameState);
      ActionButton[0] = false;
    }
  } else {
    if (ActionButton[0] == true && GameState.ActionMenu.is_menu_up == true &&
        GameState.ActionMenu.X_COUNT > 1 &&
        GameState.CombatantSelected.current_movecount <
            GameState.CombatantSelected.move_range) {
      Log("Move");

      MovePressed(GameState);

      ActionButton[0] = false;
    }

    if (ActionButton[1] == true && GameState.ActionMenu.is_menu_up == true &&
        GameState.ActionMenu.X_COUNT > 1) {
      Log("Attack\n");

      AttackPressed(GameState);

      ActionButton[1] = false;
    }

    if (ActionButton[2] == true && GameState.ActionMenu.is_menu_up == true &&
        GameState.ActionMenu.X_COUNT > 1) {
      Log("END\n");

      EndPressed(GameState);

      ActionButton[2] = false;
    }
  }

  if (IsKeyPressed(KEY_UP)) {
    if (GameState.ActionMenu.CurrentButtonIndex !=
        GameState.ActionMenu.TopButtonIndex) {
      GameState.ActionMenu.CurrentButtonIndex--;
    } else {
      GameState.ActionMenu.CurrentButtonIndex =
          GameState.ActionMenu.MenuRects.size() - 1;
    }

    GameState.ActionMenu.MenuTarget.y =
        GameState.ActionMenu.MenuRects[GameState.ActionMenu.CurrentButtonIndex]
            .y;
  }

  if (IsKeyPressed(KEY_DOWN)) {
    if (GameState.ActionMenu.CurrentButtonIndex !=
        GameState.ActionMenu.MenuRects.size() - 1) {
      GameState.ActionMenu.CurrentButtonIndex++;
    } else {
      GameState.ActionMenu.CurrentButtonIndex =
          GameState.ActionMenu.TopButtonIndex;
    }

    GameState.ActionMenu.MenuTarget.y =
        GameState.ActionMenu.MenuRects[GameState.ActionMenu.CurrentButtonIndex]
            .y;
  }

  if (IsKeyPressed(KEY_LEFT)) {
  }
  if (IsKeyPressed(KEY_RIGHT)) {
  }

  if (IsKeyPressed(KEY_Z)) {
    cout << "ActionGuiLogic Z PRESSED" << endl;

    GameState.ActionMenu.Z_COUNT++;

    GameState.ActionMenu.X_COUNT = 0;

    GameState.ActionMenu.is_menu_up = false;
  }
}

inline void MoveLogic(game_state& GameState) {
  temptarget = {
      (float)GameState.Target.pEntity->x, (float)GameState.Target.pEntity->y,
      (float)GameState.Target.pEntity->w, (float)GameState.Target.pEntity->h};

  ColorFieldCollisionTileEntityList(
      GameState.CombatantSelected.move_field, GameState.Map.EntityList,
      GameState.Map.CombatantList, GameState.SpriteList, RED_TILE);

  ColorFieldTrackTile(GameState.CombatantSelected.move_field,
                      GameState.SpriteList, GameState.Target.pEntity,
                      YELLOW_TILE);

  // if ((GetTime() - last) > input_delay) // Needed to limit target
  // movespeed
  //{
  //	last = (float)GetTime();

  if (GameState.CombatantSelected.current_movecount <
          GameState.CombatantSelected.move_range &&
      !GameState.AnimatingMovement && on_field == true) {
    if (IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_DOWN) &&
        !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT)) {
      temptarget.y = temptarget.y + GameState.Target.up_vel;
      temptarget.x = temptarget.x + GameState.Target.left_vel;

      moved_target = true;

      GameState.CombatantSelected.current_movecount++;
      DebugLog("Up", GameState.CombatantSelected.current_movecount);
      GameState.MoveList.push_back(UP);
    }

    if (IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) &&
        !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT)) {
      temptarget.y = temptarget.y + GameState.Target.down_vel;
      temptarget.x = temptarget.x + GameState.Target.right_vel;

      moved_target = true;

      GameState.CombatantSelected.current_movecount++;
      DebugLog("Down", GameState.CombatantSelected.current_movecount);
      GameState.MoveList.push_back(DOWN);
    }
    if (IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_DOWN) &&
        !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_RIGHT)) {
      temptarget.y = temptarget.y + GameState.Target.down_vel;
      temptarget.x = temptarget.x + GameState.Target.left_vel;

      moved_target = true;

      GameState.CombatantSelected.current_movecount++;
      DebugLog("Left", GameState.CombatantSelected.current_movecount);
      GameState.MoveList.push_back(LEFT);
    }
    if (IsKeyPressed(KEY_RIGHT) && !IsKeyPressed(KEY_DOWN) &&
        !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_LEFT)) {
      temptarget.y = temptarget.y + GameState.Target.up_vel;
      temptarget.x = temptarget.x + GameState.Target.right_vel;

      moved_target = true;

      GameState.CombatantSelected.current_movecount++;
      DebugLog("Right", GameState.CombatantSelected.current_movecount);
      GameState.MoveList.push_back(RIGHT);
    }
  }

  //	for (size_t i = 0; i < target_field.sum_of_field_tiles; i++)
  //	{
  if (CheckCollisionRecs({(float)temptarget.x, (float)temptarget.y,
                          (float)temptarget.width, (float)temptarget.height},
                         {(float)GameState.CombatantSelected.move_field.x,
                          (float)GameState.CombatantSelected.move_field.y,
                          (float)GameState.CombatantSelected.move_field.w,
                          (float)GameState.CombatantSelected.move_field.h})) {
    DebugLog("Field Collision", 0);

    on_field = true;

    // break;
  } else {
    DebugLog("Field Collision", 1);

    if (GameState.CombatantSelected.current_movecount > 0) {
      GameState.CombatantSelected.current_movecount--;
    }

    if (GameState.MoveList.empty() != true) {
      GameState.MoveList.pop_back();
    }

    on_field = false;
    // break;
  }
  //	}

  if (moved_target == true) {
    if (CheckColoredTileCollission(
            GameState.CombatantSelected.move_field.collision_tiles,
            temptarget) ||
        CheckColoredTrackTileCollission(GameState.CombatantSelected.move_field,
                                        temptarget)) {
      moved_target = false;

      if (GameState.CombatantSelected.current_movecount > 0) {
        GameState.CombatantSelected.current_movecount--;
      }

      if (GameState.MoveList.empty() != true) {
        GameState.MoveList.pop_back();

        collision = true;
      }
    }
  }

  if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) &&
      GameState.ActionMenu.X_COUNT != 1 && !GameState.AnimatingMovement) {
    if (GameState.MoveList.empty() != true) {
      GameState.AnimatingMovement = true;
      moved_target = false;
      GameState.ActionMenu.MOVE_COUNT =
          GameState.CombatantSelected.current_movecount;
      Log("current_movecount ", GameState.ActionMenu.MOVE_COUNT);

      DebugLog("Movecount: ", GameState.CombatantSelected.current_movecount);
      ResetFieldVariables(&GameState.CombatantSelected);

      GameState.Target.is_on_move_field = false;

      GameState.ActionMenu.X_COUNT = 0;
      GameState.ActionMenu.Z_COUNT = 0;

    } else {
      Log("GameState.Map.MoveList.empty() == true :",
          GameState.ActionMenu.MOVE_COUNT);
    }
  }

  if ((IsKeyPressed(KEY_Z) && !IsKeyPressed(KEY_X)) &&
      !GameState.AnimatingMovement) {
    if (GameState.ActionMenu.Z_COUNT == 1 && moved_target == true) {
      GameState.Target.pEntity->x = GameState.CombatantSelected.pEntity->x;
      GameState.Target.pEntity->y = GameState.CombatantSelected.pEntity->y;

      ResetTrackTilesColor(GameState.CombatantSelected.move_field,
                           GameState.SpriteList, GREEN_TILE);

      GameState.CombatantSelected.move_field.track_tiles.clear();

      GameState.CombatantSelected.current_movecount =
          GameState.ActionMenu.MOVE_COUNT;

      moved_target = false;

      GameState.MoveList.clear();

      GameState.ActionMenu.Z_COUNT = 0;
    }

    if (GameState.ActionMenu.Z_COUNT == 1 && moved_target == false &&
        collision == false) {
      moved_target = false;

      cout << "this collistion " << collision << endl;

      ResetFieldVariables(&GameState.CombatantSelected);

      GameState.Target.is_on_move_field = false;

      enemy_colored = false;
      entity_checked = 0;

      GameState.ActionMenu.X_COUNT = 0;
      GameState.ActionMenu.Z_COUNT = 0;
    }

    if (GameState.ActionMenu.Z_COUNT == 1 && collision == true) {
      GameState.Target.pEntity->x = GameState.CombatantSelected.pEntity->x;

      GameState.Target.pEntity->y = GameState.CombatantSelected.pEntity->y;

      if (GameState.MoveList.empty() == false) {
        ResetTrackTilesColor(GameState.CombatantSelected.move_field,
                             GameState.SpriteList, GREEN_TILE);
      }

      GameState.CombatantSelected.move_field.track_tiles.clear();

      GameState.CombatantSelected.current_movecount =
          GameState.ActionMenu.MOVE_COUNT;

      moved_target = false;

      collision = false;

      GameState.MoveList.clear();

      GameState.ActionMenu.Z_COUNT = 0;
    }
  }

  if (on_field == true && moved_target == true) {
    GameState.Target.pEntity->x = temptarget.x;
    GameState.Target.pEntity->y = temptarget.y;
  } else {
  }
}

inline void CheckEnemyMoveField(vector<combatant>& enemy_list, target& Target) {
  for (size_t i = 0; i < enemy_list.size(); i++) {
    // Check if target is on enemy entity position and X pressed, not on
    // movefield, not moveing
    if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) &&
        (Target.pEntity->x == enemy_list[i].pEntity->x) &&
        (Target.pEntity->y == enemy_list[i].pEntity->y)) {
      cout << "Enemy checked" << endl;
      enemy_list[i].move_field.render_field = true;
    }

    // Check if target is on enemy entity position and X pressed, not on
    // movefield, not moveing
    if ((!IsKeyPressed(KEY_X) && IsKeyPressed(KEY_Z)) &&
        (Target.pEntity->x == enemy_list[i].pEntity->x) &&
        (Target.pEntity->y == enemy_list[i].pEntity->y)) {
      cout << "Enemy checked" << endl;
      enemy_list[i].move_field.render_field = false;
    }
  }
}

inline void TargetLogic(game_state& GameState) {
  temptarget = {0, 0, 0, 0};

  static double static_last_input_time = 0;

  if (GameState.Target.is_on_move_field == true) {
    MoveLogic(GameState);

  } else if (GameState.Target.is_attacking == true) {
    AttackLogic(GameState);

  } else  // Not on a movefield
  {
    for (size_t i = 0; i < GameState.Map.CombatantList.size(); i++) {
      if (GameState.Target.pEntity->ID ==
          GameState.Map.CombatantList[i].pEntity->ID) {
      } else {
        // Check if target is on combat entity position and X pressed, not on
        // movefield, not moveing
        if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) &&
            (GameState.Target.pEntity->x ==
             GameState.Map.CombatantList[i].pEntity->x) &&
            (GameState.Target.pEntity->y ==
             GameState.Map.CombatantList[i].pEntity->y) &&
            !GameState.AnimatingMovement) {
          cout << "else First Press X " << GameState.ActionMenu.X_COUNT << endl;

          GameState.ActionMenu.Z_COUNT = 0;

          GameState.ActionMenu.X_COUNT = 1;

          SetActionMenu(GameState.ActionMenu, &GameState.CombatantSelected);

          GameState.ActionMenu.is_menu_up = true;

          if (GameState.CombatantSelected.pEntity->ID !=
              GameState.Map.CombatantList[i].pEntity->ID) {
            cout << "UPDATED SELECTED COMBATANT" << endl;
            GameState.CombatantSelected = GameState.Map.CombatantList[i];
          }

          break;
        }
      }
    }

    if (GameState.ActionMenu.is_menu_up != true) {
      if (GameState.AnimatingMovement != true) {
        // CheckEnemyMoveField(GameState.Map.EnemyList, GameState.Target);
      }

      // Needed to limit target movespeed
      if ((GetTime() - static_last_input_time) > INPUT_DELAY) {
        static_last_input_time = (float)GetTime();

        if (IsKeyDown(KEY_UP)) {
          GameState.Target.pEntity->y =
              GameState.Target.pEntity->y + GameState.Target.up_vel;
        }

        if (IsKeyDown(KEY_DOWN)) {
          GameState.Target.pEntity->y =
              GameState.Target.pEntity->y + GameState.Target.down_vel;
        }
        if (IsKeyDown(KEY_LEFT)) {
          GameState.Target.pEntity->x =
              GameState.Target.pEntity->x + GameState.Target.left_vel;
        }
        if (IsKeyDown(KEY_RIGHT)) {
          GameState.Target.pEntity->x =
              GameState.Target.pEntity->x + GameState.Target.right_vel;
        }
      }

      // colored_tiles.clear();

      // ref_field.last_tile_x =-10000;
      //  ref_field.last_tile_y =-10000;
    }
  }
}

inline void MoveUnit(game_state& GameState) {
  int speed_adjustment = 8;
  int static frame_count = 0;

  static double static_last_input_time = 0;

  int x_vel = (GAME_TILE_WIDTH / speed_adjustment);
  int y_vel = (GAME_TILE_HEIGHT / speed_adjustment);

  int act_vel = 0;

  bool check_layered = true;

  ellipse temp_el = GameState.WorldPlayer.pEntity->el;

  DebugLog("Player X: ", GameState.WorldPlayer.pEntity->x);
  DebugLog("Player Y: ", GameState.WorldPlayer.pEntity->y);

  SetEllipsesColPointArray(temp_el, GameState.WorldPlayer.EllipsePoints);

  if (GameState.ActionMenu.is_menu_up != true) {
    if ((GetTime() - static_last_input_time) >
        INPUT_DELAY)  // Needed to limit target movespeed
    {
      static_last_input_time = (float)GetTime();

      if (DEBUG_PRINT) {
        DebugLog("UP ",
                 GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP]);
        DebugLog("UP_RIGHT ",
                 GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP_RIGHT]);
        DebugLog("RIGHT ",
                 GameState.WorldPlayer.EllipsePointsCollisions[INDEX_RIGHT]);
        DebugLog(
            "DOWN_RIGHT ",
            GameState.WorldPlayer.EllipsePointsCollisions[INDEX_DOWN_RIGHT]);
        DebugLog("DOWN ",
                 GameState.WorldPlayer.EllipsePointsCollisions[INDEX_DOWN]);
        DebugLog(
            "DOWN_LEFT ",
            GameState.WorldPlayer.EllipsePointsCollisions[INDEX_DOWN_LEFT]);
        DebugLog("LEFT ",
                 GameState.WorldPlayer.EllipsePointsCollisions[INDEX_LEFT]);
        DebugLog("UP_LEFT ",
                 GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP_LEFT]);
      }

      if (IsKeyDown(KEY_W)) {
        if (frame_count % 8 == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, UP);
        }

        for (size_t i = 0; i < y_vel; i++) {
          SetEllipsesColPointArray(temp_el,
                                   GameState.WorldPlayer.EllipsePoints);

          act_vel = i;

          CheckCollisionPoints(GameState.WorldPlayer.EllipsePointsCollisions,
                               GameState.WorldPlayer.EllipsePoints,
                               GameState.Map.EntityList,
                               GameState.WorldPlayer.pEntity, check_layered);

          if ((GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP]) ||
              (GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP_RIGHT]) ||
              (GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP_LEFT])) {
            break;
          }
          temp_el.center.y++;
        }

        GameState.WorldPlayer.pEntity->y =
            GameState.WorldPlayer.pEntity->y - act_vel;
      }

      if (IsKeyDown(KEY_S)) {
        if (frame_count % 4 == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, DOWN);
        }

        for (size_t i = 0; i < y_vel; i++) {
          SetEllipsesColPointArray(temp_el,
                                   GameState.WorldPlayer.EllipsePoints);

          act_vel = i;

          CheckCollisionPoints(GameState.WorldPlayer.EllipsePointsCollisions,
                               GameState.WorldPlayer.EllipsePoints,
                               GameState.Map.EntityList,
                               GameState.WorldPlayer.pEntity, check_layered);

          if ((GameState.WorldPlayer.EllipsePointsCollisions[INDEX_DOWN]) ||
              (GameState.WorldPlayer
                   .EllipsePointsCollisions[INDEX_DOWN_RIGHT]) ||
              (GameState.WorldPlayer
                   .EllipsePointsCollisions[INDEX_DOWN_LEFT])) {
            break;
          }
          temp_el.center.y++;
        }
        GameState.WorldPlayer.pEntity->y =
            GameState.WorldPlayer.pEntity->y + act_vel;
      }

      if (IsKeyDown(KEY_A)) {
        if (frame_count % 4 == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, LEFT);
        }

        for (size_t i = 0; i < x_vel; i++) {
          SetEllipsesColPointArray(temp_el,
                                   GameState.WorldPlayer.EllipsePoints);

          act_vel = i;

          CheckCollisionPoints(GameState.WorldPlayer.EllipsePointsCollisions,
                               GameState.WorldPlayer.EllipsePoints,
                               GameState.Map.EntityList,
                               GameState.WorldPlayer.pEntity, check_layered);

          if ((GameState.WorldPlayer.EllipsePointsCollisions[INDEX_LEFT]) ||
              (GameState.WorldPlayer
                   .EllipsePointsCollisions[INDEX_DOWN_LEFT]) ||
              (GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP_LEFT])) {
            break;
          }
          temp_el.center.x++;
        }

        GameState.WorldPlayer.pEntity->x =
            GameState.WorldPlayer.pEntity->x - act_vel;
      }
      if (IsKeyDown(KEY_D)) {
        if (frame_count % 4 == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, RIGHT);
        }

        for (size_t i = 0; i < x_vel; i++) {
          SetEllipsesColPointArray(temp_el,
                                   GameState.WorldPlayer.EllipsePoints);

          act_vel = i;

          CheckCollisionPoints(GameState.WorldPlayer.EllipsePointsCollisions,
                               GameState.WorldPlayer.EllipsePoints,
                               GameState.Map.EntityList,
                               GameState.WorldPlayer.pEntity, check_layered);

          if ((GameState.WorldPlayer.EllipsePointsCollisions[INDEX_RIGHT]) ||
              (GameState.WorldPlayer.EllipsePointsCollisions[INDEX_UP_RIGHT]) ||
              (GameState.WorldPlayer
                   .EllipsePointsCollisions[INDEX_DOWN_RIGHT])) {
            break;
          }
          temp_el.center.x++;
        }

        GameState.WorldPlayer.pEntity->x =
            GameState.WorldPlayer.pEntity->x + act_vel;
      }

      frame_count++;

      if (frame_count == 4) {
        frame_count = 0;
      }

      // for (size_t i = 0; i < 8; i++) {
      //   if (ElipsesPointCollisions[i]) {
      //     cout << "[TRUE]";
      //   } else {
      //     cout << "[FALSE]";
      //   }
      // }
      // cout << endl;
    }
  }
}

static bool startset = false;

inline bool HoverSelect(field& fieldRef, entity* entity) {
  bool ret = false;

  float mouseX = GetMouseX();
  float mouseY = GetMouseY();

  Rectangle mouseRect = {mouseX, mouseY, 1, 1};

  entity->render_this = true;

  Rectangle tempEntityRect;

  if (startset == false) {
    tempEntityRect = {(float)fieldRef.tiles[0].x, (float)fieldRef.tiles[0].y,
                      (float)fieldRef.tiles[0].w, (float)fieldRef.tiles[0].h};

    entity->x = tempEntityRect.x;

    entity->y = tempEntityRect.y;

    cout << (float)fieldRef.tiles[10].x << endl;

    cout << (float)fieldRef.tiles[10].y << endl;

    startset = true;

    ret = true;
  }

  for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++) {
    tempEntityRect = {(float)fieldRef.tiles[i].x, (float)fieldRef.tiles[i].y,
                      (float)fieldRef.tiles[i].w, (float)fieldRef.tiles[i].h};

    point temp;
    temp.x = GetMousePosition().x - GAMESCREEN_OFFSET_X;
    temp.y = GetMousePosition().y - GAMESCREEN_OFFSET_Y;

    if (CollisionIsoTriangles(tempEntityRect, temp) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      printf("Collision with tile: x:%.0f y:%.0f \n", tempEntityRect.x,
             tempEntityRect.y);

      entity->x = tempEntityRect.x;

      entity->y = tempEntityRect.y;

      ret = true;
    }
  }

  return ret;
}

inline void MouseLogic() {
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && true) {
    //	printf("Button LEFT is pressed and Entity one clicked");
  }

  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    // printf("Button RIGHT is pressed");

    if (PLACING_ENTITY) {
      PLACING_ENTITY = false;
      // printf("Button RIGHT is pressed");
    }
  }
}

inline void EditorGuiLogic(game_state& GameState) {
  if (SaveButton001 == true) {
    printf("Saved entitiy data\n");

    WriteEntityData(GameState.EntityList,
                    GAME_ASSET_PATH + "game_entity_data.txt");

    SaveButton001 = false;
  }

  if (SaveButton002 == true) {
    printf("Saved Sprite data\n");

    WriteSpriteData(GAME_ASSET_PATH + "game_sprite_data.txt",
                    GameState.SpriteList);

    SaveButton002 = false;
  }

  if (ReloadButton == true) {
    printf("Reload");

    ReloadButton = false;
  }
}

inline void CombatLogic(game_state& GameState) {
  UpdateGameTurn(GameState);

  if (GameState.InitCombat == false) {
    GameState.InitCombat = true;

    InitCombat(GameState);

    GameState.ActionMenu.is_pre_state = true;
    GameState.ActionMenu.is_menu_up = true;
  }

  if (GameState.ActionMenu.is_pre_state == true) {
    if (HoverSelect(GameState.CombatantSelected.position_field,
                    GameState.CombatantSelected.pEntity) == true) {
      SetActionMenu(GameState.ActionMenu, &GameState.CombatantSelected);
    }
  }

  if (GameState.PLAYER_TURN == true) {
    SetEnemyFields(GameState);

    // if (toggle_enemy_movefields == true) {

    // }
  } else {
    EnemyLogic(GameState);
  }
}

#endif