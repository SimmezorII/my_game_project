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

static double last2 = 0;

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

inline void SetEntityListEllipses(vector<entity>& entities) {
  for (size_t i = 0; i < entities.size(); i++) {
    entities[i].el.center.x = entities[i].x + entities[i].entity_tile.width / 2;
    entities[i].el.center.y =
        entities[i].y + entities[i].entity_tile.height / 2;

    entities[i].el.w = entities[i].entity_tile.width / 8;
    entities[i].el.h = entities[i].entity_tile.height / 2;
  }
}

inline void CalculateDamageEnemy(map &Map,Rectangle& temp_target) {
  entity& entity_ref =
      getEntityByPosition(temp_target.x, temp_target.y, Map.EntityList);
  entity_ref.entity_stats.current_hp--;
}

inline void UpdateTargetFieldRange() {
  if (target_field.range >= 1 &&
      combatant_list[combatant_selected].current_movecount != 0) {
    target_field.range =
        combatant_list[combatant_selected].move_range -
        (combatant_list[combatant_selected].current_movecount - 1);

    if (target_field.range <= 0) {
      target_field.range = 1;
    }
  } else {
    target_field.range = 1;
  }
}

inline void ResetFieldVariables() {
  move_field_up = false;

  colored_moved_tiles.clear();
  colored_enemy_tiles.clear();
  enemy_colored = false;
  entity_checked = 0;
  attack_target_field.render_field = false;

  X_pressed_count = 0;
  Z_pressed_count = 0;

  last_tile = {-100, -100, 0, 0};

  target_field.render_field = false;
  SetRenderField(&target_field, false);
  UpdateTargetFieldRange();
}

inline void EntityMoveLogic(combatant& pEnemy, combatant& pPlayer,
                            bool towards) {
  bool moved = false;

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

inline void EnemyLogic() {
  Log("Enemy Passed, turn ended");

  SetRenderEnemyFields(false);

  // enemy_list[0].movelist.push_back(1);

  EntityMoveLogic(enemy_list[1], combatant_list[0], false);

  for (size_t i = 0; i < enemy_list.size(); i++) {
    if (!enemy_list[i].movelist.empty()) {
      enemy_moving = true;
    }
  }

  PLAYER_TURN = true;
  game_turn++;
}

inline void CheckKeyboardInput(game_state& GameState) {
  if (IsKeyPressed(KEY_Z)) {
    cout << "CheckKeyboardInput Z PRESSED" << endl;
    Z_pressed_count++;
  }

  if (IsKeyPressed(KEY_X)) {
    cout << "X PRESSED" << endl;
    X_pressed_count++;

    // printf("%d", GetRandomValue(0, 99));
  }

  if (IsKeyPressed(KEY_L)) {
    cout << "L PRESSED" << endl;

    for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      GameState.Map.EntityList[i].layer = 1;
    }
    cout << endl;
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
    // cout << "GameState.Map.EntityList: " << GameState.Map.EntityList.size() << endl;

    // cout << "target_field.sum_of_field_tiles " <<
    // target_field.sum_of_field_tiles << endl;

    cout << "render_list[0].List.size(): " << render_list[0].List.size()
         << endl;
    cout << "render_list[1].List.size(): " << render_list[1].List.size()
         << endl;

    cout << "new_entity_list.size: " << new_entity_list.size() << endl;

    // cout << "SortedRenderObject_list.size(): " <<
    // SortedRenderObject_list.size() << endl;

    for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      GameState.Map.EntityList[i].layer = 0;
    }
    cout << endl;
  }

  if (IsKeyPressed(KEY_TAB)) {
    cout << "TAB PRESSED" << endl;
    if (toggle_enemy_movefields == true) {
      toggle_enemy_movefields = false;
      cout << "toggle_enemy_movefields  false" << endl;

      SetRenderEnemyFields(false);
    } else {
      toggle_enemy_movefields = true;
      cout << "toggle_enemy_movefields  true" << endl;
    }
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
              {(float)(temptarget.x - 1 + (tile_width / 2)),
               (float)(temptarget.y - 1 + (tile_height / 2)), 2, 2},
              {(float)(colored_tiles[i].x - 1 + (tile_width / 2)),
               (float)(colored_tiles[i].y - 1 + (tile_height / 2)), 2, 2})) {
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

inline bool CheckColoredMoveTileCollission(Rectangle& temptarget) {
  bool collission = false;

  if (colored_moved_tiles.empty() != true) {
    DebugLog("colored_moved_tiles.size()", (int)colored_moved_tiles.size());

    for (size_t i = 0; i < colored_moved_tiles.size() - 1; i++) {
      // Check if any tile has already been crossed
      if (CheckCollisionRecs(
              {(float)(temptarget.x - 1 + (tile_width / 2)),
               (float)(temptarget.y - 1 + (tile_height / 2)), 2, 2},
              {(float)(colored_moved_tiles[i].x - 1 + (tile_width / 2)),
               (float)(colored_moved_tiles[i].y - 1 + (tile_height / 2)), 2,
               2})) {
        // if (last_tile.x != temptarget.x || last_tile.y != temptarget.y)

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
  Rectangle temp_target = {target->x, target->y, target->w, target->h};

  if (combatant_selected >= 0) {
    if (ColorFieldTileEntityList(colored_enemy_tiles, &attack_target_field,
                                 enemy_list, GameState.SpriteList,
                                 GREEN_TILE)) {
      DebugLog("AttackField Collision", (int)colored_enemy_tiles.size());
    } else {
      DebugLog("AttackField Collision", (int)colored_enemy_tiles.size());
    }

    if (colored_enemy_tiles.empty() != true) {
      target->x = colored_enemy_tiles[0].x;
      target->y = colored_enemy_tiles[0].y;

      CycleColoredTiles(target, colored_enemy_tiles);

      if (CheckColoredTileCollission(colored_enemy_tiles, temp_target)) {
        if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z))) {
          cout << "Attack collision and x pressed" << endl;

          CalculateDamageEnemy(GameState.Map ,temp_target);

          attacking = false;

          ResetFieldVariables();

          target->x = combatant_list[combatant_selected].pEntity->x;
          target->y = combatant_list[combatant_selected].pEntity->y;
        }
      }
    }
  }

  if ((IsKeyPressed(KEY_Z) && !IsKeyPressed(KEY_X))) {
    cout << "Attack z pressed" << endl;

    ResetFieldVariables();

    target->x = combatant_list[combatant_selected].pEntity->x;
    target->y = combatant_list[combatant_selected].pEntity->y;

    attacking = false;
  }
}

int static previous_turn = 1;
bool static previous_state = false;

inline void UpdateGameTurn() {
  if (PLAYER_TURN != previous_state) {
    previous_state = PLAYER_TURN;

    if (game_turn == previous_turn) {
      Log("Game Turn ", game_turn);

      previous_turn = game_turn + 1;
    }
  }
}

void InitMoveLogic(game_state& GameState) {
  move_field_up = true;
  action_menu_up = false;

  target_field.render_field = false;

  UpdateTargetFieldRange();

  SetField(GameState, target_field,
           combatant_list[combatant_selected].pEntity->x,
           combatant_list[combatant_selected].pEntity->y, SQUARE, GREEN_TILE);

  // cout << "target_field " << target_field.sum_of_field_tiles << endl;

  colored_enemy_tiles.clear();
  colored_moved_tiles.clear();

  enemy_colored = false;
  entity_checked = 0;

  target_field.render_field = true;
}

void InitAttackLogic(game_state& GameState) {
  Log("ATTACK!");
  enemy_colored = false;
  entity_checked = 0;

  attack_target_field.range =
      8;  // combatant_list[combatant_selected].attack_range;

  SetField(GameState, attack_target_field,
           combatant_list[combatant_selected].pEntity->x,
           combatant_list[combatant_selected].pEntity->y, SQUARE, BLUE_TILE);

  attack_target_field.render_field = true;
  SetRenderField(&attack_target_field, attack_target_field.render_field);
  action_menu_up = false;

  attacking = true;
}

inline void MovePressed(game_state& GameState) {
  /// Init move logic
  InitMoveLogic(GameState);
}

inline void ReadyPressed() {
  X_pressed_count = 0;

  precombat = false;

  target->x = combatant_list[combatant_selected].pEntity->x;
  target->y = combatant_list[combatant_selected].pEntity->y;

  position_field.render_field = false;
  SetRenderField(&position_field, false);

  action_menu_up = false;

  PLAYER_TURN = true;
}

inline void EndPressed() {
  X_pressed_count = 0;
  Z_pressed_count = 0;

  position_field.render_field = false;
  SetRenderField(&position_field, false);

  action_menu_up = false;

  PLAYER_TURN = false;

  Log("Player ended turn ", game_turn);

  combatant_list[combatant_selected].current_movecount = 1;

  temp_movecount[combatant_selected] =
      combatant_list[combatant_selected].current_movecount;
}

inline void AttackPressed(game_state& GameState) {
  // Init Attack Logic
  InitAttackLogic(GameState);
}

inline void ActionGuiLogic(game_state& GameState) {
  if (precombat == true) {
    if (ActionButton[0] == true) {
      Log("Ready");

      ReadyPressed();

      ActionButton[0] = false;
    }
  } else {
    if (ActionButton[0] == true && action_menu_up == true &&
        X_pressed_count > 1 &&
        combatant_list[combatant_selected].current_movecount <
            combatant_list[combatant_selected].move_range) {
      Log("Move");

      MovePressed(GameState);

      ActionButton[0] = false;
    }

    if (ActionButton[1] == true && action_menu_up == true &&
        X_pressed_count > 1) {
      printf("Attack\n");

      AttackPressed(GameState);

      ActionButton[1] = false;
    }

    if (ActionButton[2] == true && action_menu_up == true &&
        X_pressed_count > 1) {
      printf("END\n");

      EndPressed();

      ActionButton[2] = false;
    }
  }

  if (IsKeyPressed(KEY_UP)) {
    if (currentbutton_index != top_button_index) {
      currentbutton_index--;
    } else {
      currentbutton_index = ActionMenuRects.size() - 1;
    }

    action_target->y = ActionMenuRects[currentbutton_index].y;
  }

  if (IsKeyPressed(KEY_DOWN)) {
    if (currentbutton_index != ActionMenuRects.size() - 1) {
      currentbutton_index++;
    } else {
      currentbutton_index = top_button_index;
    }

    action_target->y = ActionMenuRects[currentbutton_index].y;
  }

  if (IsKeyPressed(KEY_LEFT)) {
    // action_target->x = action_target->x + left_vel;
  }
  if (IsKeyPressed(KEY_RIGHT)) {
    // action_target->x = action_target->x + right_vel;
  }

  if (IsKeyPressed(KEY_Z)) {
    cout << "ActionGuiLogic Z PRESSED" << endl;

    Z_pressed_count++;

    X_pressed_count = 0;

    action_menu_up = false;
  }
}

inline void MoveLogic(game_state& GameState) {
  if (move_field_up == true) {
    temptarget = {(float)target->x, (float)target->y, (float)target->w,
                  (float)target->h};

    ColorFieldTileEntityList(colored_enemy_tiles, &target_field,
                             GameState.Map.EntityList, GameState.SpriteList, RED_TILE);

    ColorFieldTile(target_field, GameState.SpriteList, target);

    // if ((GetTime() - last) > input_delay) // Needed to limit target
    // movespeed
    //{
    //	last = (float)GetTime();

    if (combatant_list[combatant_selected].current_movecount <
            combatant_list[combatant_selected].move_range &&
        !moving && on_field == true) {
      if (IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_DOWN) &&
          !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT)) {
        temptarget.y = temptarget.y + up_vel;
        temptarget.x = temptarget.x + left_vel;

        moved_target = true;

        combatant_list[combatant_selected].current_movecount++;
        DebugLog("Up", combatant_list[combatant_selected].current_movecount);
        move_list.push_back(UP);
      }

      if (IsKeyPressed(KEY_DOWN) && !IsKeyPressed(KEY_UP) &&
          !IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_RIGHT)) {
        temptarget.y = temptarget.y + down_vel;
        temptarget.x = temptarget.x + right_vel;

        moved_target = true;

        combatant_list[combatant_selected].current_movecount++;
        DebugLog("Down", combatant_list[combatant_selected].current_movecount);
        move_list.push_back(DOWN);
      }
      if (IsKeyPressed(KEY_LEFT) && !IsKeyPressed(KEY_DOWN) &&
          !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_RIGHT)) {
        temptarget.y = temptarget.y + down_vel;
        temptarget.x = temptarget.x + left_vel;

        moved_target = true;

        combatant_list[combatant_selected].current_movecount++;
        DebugLog("Left", combatant_list[combatant_selected].current_movecount);
        move_list.push_back(LEFT);
      }
      if (IsKeyPressed(KEY_RIGHT) && !IsKeyPressed(KEY_DOWN) &&
          !IsKeyPressed(KEY_UP) && !IsKeyPressed(KEY_LEFT)) {
        temptarget.y = temptarget.y + up_vel;
        temptarget.x = temptarget.x + right_vel;

        moved_target = true;

        combatant_list[combatant_selected].current_movecount++;
        DebugLog("Right", combatant_list[combatant_selected].current_movecount);
        move_list.push_back(RIGHT);
      }
    }

    //	for (size_t i = 0; i < target_field.sum_of_field_tiles; i++)
    //	{
    if (CheckCollisionRecs({(float)temptarget.x, (float)temptarget.y,
                            (float)temptarget.width, (float)temptarget.height},
                           {(float)target_field.x, (float)target_field.y,
                            (float)target_field.w, (float)target_field.h})) {
      DebugLog("Field Collision", 0);

      on_field = true;

      // break;
    } else {
      DebugLog("Field Collision", 1);

      if (combatant_list[combatant_selected].current_movecount > 0) {
        combatant_list[combatant_selected].current_movecount--;
      }

      if (move_list.empty() != true) {
        move_list.pop_back();
      }

      on_field = false;
      // break;
    }
    //	}

    if (moved_target == true) {
      if (CheckColoredTileCollission(colored_enemy_tiles, temptarget) ||
          CheckColoredMoveTileCollission(temptarget)) {
        moved_target = false;

        if (combatant_list[combatant_selected].current_movecount > 0) {
          combatant_list[combatant_selected].current_movecount--;
        }

        if (move_list.empty() != true) {
          move_list.pop_back();

          collision = true;
        }
      }
    }

    if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) &&
        move_field_up == true && X_pressed_count != 1 && !moving) {
      // cout << "Second Press X " << X_pressed_count << endl;

      // PrintMoveList();

      if (move_list.empty() != true) {
        moving = true;
        moved_target = false;
        temp_movecount[combatant_selected] =
            combatant_list[combatant_selected].current_movecount;
        // Log("current_movecount ", temp_movecount[combatant_selected]);

        ResetFieldVariables();

        player_animation = true;
      } else {
        cout << "move_list.empty() == true" << endl;
      }
    }

    if ((IsKeyPressed(KEY_Z) && !IsKeyPressed(KEY_X)) &&
        move_field_up == true && !moving) {
      if (Z_pressed_count == 1 && moved_target == true) {
        target->x = combatant_list[combatant_selected].pEntity->x;

        target->y = combatant_list[combatant_selected].pEntity->y;

        ResetMovedTilesColor(target_field, GameState.SpriteList, 2);

        colored_moved_tiles.clear();

        combatant_list[combatant_selected].current_movecount =
            temp_movecount[combatant_selected];

        moved_target = false;

        move_list.clear();

        Z_pressed_count = 0;

        // Log("Z_pressed_count == 1 && moved_target == true");

        // enemy_colored = false;
        // entity_checked = 0;
      }

      if (Z_pressed_count == 1 && moved_target == false && collision == false) {
        moved_target = false;

        cout << collision << endl;

        // Log("(Z_pressed_count == 1 && (moved_target == false) && collision
        // == false) moving");

        ResetFieldVariables();

        enemy_colored = false;
        entity_checked = 0;
      }

      if (Z_pressed_count == 1 && collision == true) {
        target->x = combatant_list[combatant_selected].pEntity->x;

        target->y = combatant_list[combatant_selected].pEntity->y;

        if (move_list.empty() == false) {
          ResetMovedTilesColor(target_field, GameState.SpriteList, 2);
        }

        colored_moved_tiles.clear();

        combatant_list[combatant_selected].current_movecount =
            temp_movecount[combatant_selected];

        moved_target = false;

        collision = false;

        move_list.clear();

        Z_pressed_count = 0;

        // Log("Z_pressed_count == 1 && moved_target == true");

        // enemy_colored = false;
        // entity_checked = 0;
      }
    }

    if (on_field == true && moved_target == true) {
      target->x = temptarget.x;
      target->y = temptarget.y;
    } else {
    }
  }
}

inline void CheckEnemy() {
  for (size_t i = 0; i < enemy_list.size(); i++) {
    // Check if target is on enemy entity position and X pressed, not on
    // movefield, not moveing
    if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) &&
        (target->x == enemy_list[i].pEntity->x) &&
        (target->y == enemy_list[i].pEntity->y) && move_field_up == false &&
        action_menu_up != true && !moving) {
      cout << "Enemy checked" << endl;
      enemy_list[i].move_field.render_field = true;
    }

    // Check if target is on enemy entity position and X pressed, not on
    // movefield, not moveing
    if ((!IsKeyPressed(KEY_X) && IsKeyPressed(KEY_Z)) &&
        (target->x == enemy_list[i].pEntity->x) &&
        (target->y == enemy_list[i].pEntity->y) && move_field_up == false &&
        action_menu_up != true && !moving) {
      cout << "Enemy checked" << endl;
      enemy_list[i].move_field.render_field = false;
    }
  }
}

inline void TargetLogic(game_state& GameState) {
  temptarget = {0, 0, 0, 0};

  for (size_t i = 0; i < combatant_list.size(); i++) {
    if (target->ID == combatant_list[i].pEntity->ID) {
    } else {
      // Check if target is on combat entity position and X pressed, not on
      // movefield, not moveing
      if ((IsKeyPressed(KEY_X) && !IsKeyPressed(KEY_Z)) &&
          (target->x == combatant_list[i].pEntity->x) &&
          (target->y == combatant_list[i].pEntity->y) &&
          move_field_up == false && action_menu_up != true && !moving) {
        cout << "First Press X " << X_pressed_count << endl;

        cout << "Collision" << endl;
        SetField(GameState, target_field, target->x, target->y, 0, GREEN_TILE);

        // field_up = true;

        Z_pressed_count = 0;

        X_pressed_count = 1;

        combatant_selected = i;

        action_target->x = (float)(combatant_list[i].pEntity->x +
                                   combatant_list[i].pEntity->w) +
                           16;
        action_target->y = (float)(combatant_list[i].pEntity->y -
                                   combatant_list[i].pEntity->h) +
                           20;

        setActionMenu();

        action_menu_up = true;

        break;
      }
    }
  }

  if (move_field_up == true) {
    MoveLogic(GameState);
  } else if (attacking == true) {
    AttackLogic(GameState);
  } else  // Not on a movefield
  {
    if (action_menu_up != true) {
      CheckEnemy();

      if ((GetTime() - last2) >
          input_delay)  // Needed to limit target movespeed
      {
        last2 = (float)GetTime();

        if (IsKeyDown(KEY_UP)) {
          target->y = target->y + up_vel;
        }

        if (IsKeyDown(KEY_DOWN)) {
          target->y = target->y + down_vel;
        }
        if (IsKeyDown(KEY_LEFT)) {
          target->x = target->x + left_vel;
        }
        if (IsKeyDown(KEY_RIGHT)) {
          target->x = target->x + right_vel;
        }
      }

      // colored_tiles.clear();

      last_tile = {-100, -100, 0, 0};
    }
  }
}

inline void MoveUnit() {
  int speed_adjustment = 8;
  int static frame_count = 0;
  if (action_menu_up != true) {
    if ((GetTime() - last) > 0.1)  // Needed to limit target movespeed
    {
      last = (float)GetTime();

      SetEllipsesColPointArray(world_player.pEntity->el, ellipses_point);

      // for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      //   //     if (GameState.Map.EntityList[i] != world_player.pEntity->ID) {
      //   //       GetEllipsesColPoint(collision_arry, GameState.Map.EntityList[i].el,
      //   //                           ellipses_point);
      //   //     }

      //   //     for (size_t i = 0; i < collision_arry.size(); i++) {
      //   //       if (collision_arry[i]) {
      //   //         cout << "true"
      //   //              << " ";
      //   //       } else {
      //   //         cout << "false"
      //   //              << " ";
      //   //       }
      //   //     }

      //   //     cout << endl;
      // }

      if (IsKeyDown(KEY_W)) {
        // if (CheckCollisionRecs(
        // 	{ (float)combatant_list[0].pEntity->x,
        // (float)combatant_list[0].pEntity->y,
        // (float)combatant_list[0].pEntity->w,
        // (float)combatant_list[0].pEntity->h }, 	{ (float)target_field.x,
        // (float)target_field.y, (float)target_field.w, (float)target_field.h
        // }))
        // {
        // }

        if (frame_count % 8 == 0) {
          AnimateMovement(combatant_list[0].pEntity, UP);
        }

        combatant_list[0].pEntity->y = combatant_list[0].pEntity->y -
                                       (speed_adjustment / speed_adjustment);
      }

      if (IsKeyDown(KEY_S)) {
        if (frame_count % 4 == 0) {
          AnimateMovement(combatant_list[0].pEntity, DOWN);
        }
        combatant_list[0].pEntity->y = combatant_list[0].pEntity->y +
                                       (speed_adjustment / speed_adjustment);
      }

      if (IsKeyDown(KEY_A)) {
        if (frame_count % 4 == 0) {
          AnimateMovement(combatant_list[0].pEntity, LEFT);
        }
        combatant_list[0].pEntity->x = combatant_list[0].pEntity->x -
                                       (speed_adjustment / speed_adjustment);
      }
      if (IsKeyDown(KEY_D)) {
        if (frame_count % 4 == 0) {
          AnimateMovement(combatant_list[0].pEntity, RIGHT);
        }
        if (collision_map) {
          ///

        } else {
          combatant_list[0].pEntity->x = combatant_list[0].pEntity->x +
                                         (speed_adjustment / speed_adjustment);
        }
      }
      frame_count++;

      if (frame_count == 41) {
        frame_count = 0;
      }
    }
  }
}

static bool startset = false;

inline bool HoverSelect(field& fieldRef, entity* e) {
  bool ret = false;

  float mouseX = GetMouseX();
  float mouseY = GetMouseY();

  Rectangle mouseRect = {mouseX, mouseY, 1, 1};
  //	Rectangle tempEntityRect;

  // Rectangle tempEntityRect = { 0,0,0,0 };

  combatant_list[combatant_selected].pEntity->render_this = true;

  Rectangle tempEntityRect;

  if (startset == false) {
    tempEntityRect = {(float)fieldRef.tiles[0].x, (float)fieldRef.tiles[0].y,
                      (float)fieldRef.tiles[0].w, (float)fieldRef.tiles[0].h};

    combatant_list[combatant_selected].pEntity->x = tempEntityRect.x;

    combatant_list[combatant_selected].pEntity->y = tempEntityRect.y;

    cout << (float)fieldRef.tiles[10].x << endl;

    cout << (float)fieldRef.tiles[10].y << endl;

    startset = true;

    ret = true;
  }

  for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++) {
    tempEntityRect = {(float)fieldRef.tiles[i].x, (float)fieldRef.tiles[i].y,
                      (float)fieldRef.tiles[i].w, (float)fieldRef.tiles[i].h};

    if (CollisionIsoTrianglesMouse(tempEntityRect) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      printf("Collision with tile: x:%.0f y:%.0f \n", tempEntityRect.x,
             tempEntityRect.y);

      combatant_list[combatant_selected].pEntity->x = tempEntityRect.x;

      combatant_list[combatant_selected].pEntity->y = tempEntityRect.y;

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

bool run_init = false;

inline void CombatLogic(game_state& GameState) {
  if (combat == true) {
    UpdateGameTurn();

    if (run_init == false) {
      InitCombat(GameState);

      run_init = true;

      precombat = true;

      combatant_selected = 0;

      action_menu_up = true;
    }

    if (precombat == true) {
      if (HoverSelect(position_field,
                      combatant_list[combatant_selected].pEntity) == true) {
        setActionMenu();
      }
    }

    if (PLAYER_TURN == true) {
      SetEnemyFields(GameState);

      if (toggle_enemy_movefields == true) {
        SetRenderEnemyFields(true);
      }
    } else {
      EnemyLogic();
    }
  } else {
    // Overworld Logic
    gui_entity_list[0].render_this = true;
    world_player.pEntity->render_this = false;
    MoveUnit();
  }
}

#endif