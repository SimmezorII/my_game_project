/* ========================================================================

======================================================================== */

#pragma once

#ifndef logic_cpp
#define logic_cpp

#include <iostream>

#include "../header_files/game_entities.h"
#include "../header_files/globals.h"
#include "../header_files/logic_func.h"
#include "raylib.h"
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

//========================================================================

static float time1;

static float time2;

static bool moved_combatant = false;

static bool moved_target = false;

static double last = 0;

//bool collision = false;

static Rectangle temptarget;

//================================== RANDOMNESS
//======================================
typedef std::mt19937
    MyRNG;  // the Mersenne Twister with a popular choice of parameters
static uint32_t seed_val;  // populate somehow

static std::uniform_int_distribution<uint32_t> uint_dist;  // by default range [0, MAX]
static std::uniform_int_distribution<uint32_t> uint_dist20(1, 20);  // range [1,20]

static std::uniform_int_distribution<uint32_t> uint_dist12(1, 12);  // range [1,12]

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

inline void EntityMoveLogic(vector<entity>& entities, combatant& enemy,
                            combatant& player, vel v, bool towards) {
  int moved_right = -1, moved_left = -1, moved_up = -1, moved_down = -1;
  int mov_count[4] = {0, 0, 0, 0};
  int right_vel = v.right;
  int left_vel = v.left;
  int up_vel = v.up;
  int down_vel = v.down;

  int random = 0;

  float diff_x;
  float diff_y;

  bool LEFT_OF_PLAYER = false;   // 1
  bool RIGHT_OF_PLAYER = false;  // 2
  bool BELOW_OF_PLAYER = false;  // 10
  bool ABOVE_OF_PLAYER = false;  // 20
  bool YLINE_OF_PLAYER = false;
  bool XLINE_OF_PLAYER = false;

  float enemy_temp_x = enemy.pEntity->x;
  float enemy_temp_y = enemy.pEntity->y;

  int current_movecount = 0;
  int dir_moved;
  int direction;

  int roll_count = 0;
  int dir_swap = -99;

  if (towards == true) {
    direction = 1;
  } else {
    direction = -1;
  }

  // for (size_t i = 0; i < enemy.move_range; i++) {

  while (current_movecount < enemy.move_range) {
    roll_count++;

    random = (int)uint_dist20(rng);

    moved_right = -1, moved_left = -1, moved_up = -1, moved_down = -1;

    dir_moved = 0;
    LEFT_OF_PLAYER = false;
    RIGHT_OF_PLAYER = false;
    BELOW_OF_PLAYER = false;
    ABOVE_OF_PLAYER = false;
    YLINE_OF_PLAYER = false;
    XLINE_OF_PLAYER = false;

    if (enemy_temp_x < player.pEntity->x) {
      diff_x = (player.pEntity->x - enemy_temp_x) / 64;
      LEFT_OF_PLAYER = true;
    } else if (enemy_temp_x == player.pEntity->x) {
      YLINE_OF_PLAYER = true;
    } else {
      diff_x = (player.pEntity->x - enemy_temp_x) / 64;
      RIGHT_OF_PLAYER = true;
    }

    if (enemy_temp_y < player.pEntity->y) {
      diff_y = (player.pEntity->y - enemy_temp_y) / 32;
      ABOVE_OF_PLAYER = true;
    } else if (enemy_temp_y == player.pEntity->y) {
      XLINE_OF_PLAYER = true;
    } else {
      diff_y = (player.pEntity->y - enemy_temp_y) / 32;
      BELOW_OF_PLAYER = true;
    }

    if (LEFT_OF_PLAYER && BELOW_OF_PLAYER) {
      if (diff_y + diff_x == 0) {
        if (random % 3 == 0) {
          dir_moved = RIGHT * direction;

        } else {
          if (random % 2 == 0) {
            dir_moved = DOWN * direction;

          } else {
            dir_moved = UP * direction;
          }
        }
      } else if (diff_x + diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;

        } else {
          dir_moved = UP * direction;
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;

        } else {
          dir_moved = DOWN * direction;
        }
      }
    }

    if (LEFT_OF_PLAYER && ABOVE_OF_PLAYER) {
      if (diff_y == diff_x) {
        if (random % 3 == 0) {
          dir_moved = DOWN * direction;

        } else {
          if (random % 2 == 0) {
            dir_moved = RIGHT * direction;

          } else {
            dir_moved = LEFT * direction;
          }
        }
      } else if (diff_x - diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;

        } else {
          dir_moved = DOWN * direction;
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;

        } else {
          dir_moved = DOWN * direction;
        }
      }
    }

    if (RIGHT_OF_PLAYER && ABOVE_OF_PLAYER) {
      if (diff_x + diff_y == 0) {
        if (random % 3 == 0) {
          dir_moved = LEFT * direction;

        } else {
          if (random % 2 == 0) {
            dir_moved = DOWN * direction;

          } else {
            dir_moved = UP * direction;
          }
        }
      } else if (diff_x + diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;

        } else {
          dir_moved = (UP * direction);
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;

        } else {
          dir_moved = DOWN * direction;
        }
      }
    }

    if (RIGHT_OF_PLAYER && BELOW_OF_PLAYER) {
      if (diff_y == diff_x) {
        if (diff_y == diff_x) {
          if (random % 3 == 0) {
            dir_moved = UP * direction;

          } else {
            if (random % 2 == 0) {
              dir_moved = RIGHT * direction;

            } else {
              dir_moved = LEFT * direction;
            }
          }
        }
      } else if (diff_x - diff_y < 0) {
        if (random % 2 == 0) {
          dir_moved = LEFT * direction;

        } else {
          dir_moved = UP * direction;
        }
      } else {
        if (random % 2 == 0) {
          dir_moved = RIGHT * direction;

        } else {
          dir_moved = UP * direction;
        }
      }
    }

    if (YLINE_OF_PLAYER && BELOW_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = RIGHT * direction;

      } else {
        dir_moved = UP * direction;
      }
    }

    if (YLINE_OF_PLAYER && ABOVE_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = DOWN * direction;

      } else {
        dir_moved = LEFT * direction;
      }
    }

    if (XLINE_OF_PLAYER && LEFT_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = DOWN * direction;

      } else {
        dir_moved = RIGHT * direction;
      }
    }

    if (XLINE_OF_PLAYER && RIGHT_OF_PLAYER) {
      if (random % 2 == 0) {
        dir_moved = UP * direction;

      } else {
        dir_moved = LEFT * direction;
      }
    }

    if (dir_swap != -99) {
      if (current_movecount != 0) {
        dir_swap = dir_moved;
      } else {
        direction = direction * -1;
      }
    }

    if (dir_moved == RIGHT) {
      if (CheckIsoMoveCol(entities, enemy, RIGHT, UP, enemy_temp_x,
                          enemy_temp_y) != COLLISION) {
        moved_right = 1;
      } else {
        moved_right = 0;
      }
      mov_count[0]++;
    } else if (dir_moved == LEFT) {
      if (CheckIsoMoveCol(entities, enemy, LEFT, DOWN, enemy_temp_x,
                          enemy_temp_y) != COLLISION) {
        moved_left = 1;
      } else {
        moved_left = 0;
      }
      mov_count[1]++;
    } else if (dir_moved == UP) {
      if (CheckIsoMoveCol(entities, enemy, LEFT, UP, enemy_temp_x,
                          enemy_temp_y) != COLLISION) {
        moved_up = 1;
      } else {
        moved_up = 0;
      }
      mov_count[2]++;
    } else if (dir_moved == DOWN) {
      if (CheckIsoMoveCol(entities, enemy, RIGHT, DOWN, enemy_temp_x,
                          enemy_temp_y) != COLLISION) {
        moved_down = 1;
      } else {
        moved_down = 0;
      }
      mov_count[3]++;
    }

    if (moved_right == 1 || moved_left == 1 || moved_up == 1 ||
        moved_down == 1 && (dir_swap != dir_moved) ) {
      if (dir_moved == LEFT) {
        printf("ID:%d, [LEFT1]\n", enemy.pEntity->ID);
        enemy_temp_x = enemy_temp_x + (left_vel / 1);
        enemy_temp_y = enemy_temp_y + (down_vel / 1);
      }
      if (dir_moved == RIGHT) {
        printf("ID:%d, [RIGHT1]\n", enemy.pEntity->ID);
        enemy_temp_x = enemy_temp_x + (right_vel / 1);
        enemy_temp_y = enemy_temp_y + (up_vel / 1);
      }
      if (dir_moved == UP) {
        printf("ID:%d, [UP1]\n", enemy.pEntity->ID);
        enemy_temp_x = enemy_temp_x + (left_vel / 1);
        enemy_temp_y = enemy_temp_y + (up_vel / 1);
      }
      if (dir_moved == DOWN) {
        printf("ID:%d, [DOWN1]\n", enemy.pEntity->ID);
        enemy_temp_x = enemy_temp_x + (right_vel / 1);
        enemy_temp_y = enemy_temp_y + (down_vel / 1);
      }

      enemy.movelist.push_back(dir_moved);
      current_movecount++;

    } else if (moved_right == 0 && moved_left == 0 && moved_up == 0 &&
               moved_down == 0) {
      break;
    } else {
      int check = 0;

      if (roll_count > 20) {
        for (size_t i = 0; i < 4; i++) {
          if (mov_count[i] > 3) {
            check++;
          }
        }
      }

      if (check >= 2 && current_movecount == 0) {
        direction = direction * -1;
        dir_swap = dir_moved;
      }

      if (roll_count > 30) {
        break;
      }
    }

  }  // end of while
}

inline void EnemyLogic(game_state& GameState) {
  Log("Enemy Passed, turn ended");

  SetRenderEnemyFields(GameState.Map.EnemyList, false);

  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    EntityMoveLogic(GameState.Map.EntityList, GameState.Map.EnemyList[i],
                    GameState.WorldPlayer, COMBAT_VEL, false);

    if (!GameState.Map.EnemyList[i].movelist.empty()) {
      GameState.AnimatingEnemyMovement = true;
    }
  }

  GameState.PLAYER_TURN = true;
  GameState.GAME_TURN++;
}

inline void ChangeZoom(bool increase) {
  if (increase) {
    if (CAMERA_ZOOM < 4) {
      CAMERA_ZOOM++;
    }
  } else {
    if (CAMERA_ZOOM > 1) {
      CAMERA_ZOOM--;
    }
  }
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

  if (IsKeyPressed(KEY_O)) {
    cout << "O PRESSED" << endl;

    for (size_t i = 0; i < GameState.Map.EntityList.size(); i++) {
      if (GameState.Map.EntityList[i].layer != 0) {
        GameState.Map.EntityList[i].alpha = 0.2;
      }
    }
  }

  if (IsKeyPressed(KEY_K)) {
    cout << "K PRESSED" << endl;
  }
  if (IsKeyPressed(KEY_J)) {
    cout << "J PRESSED" << endl;
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

  if (IsKeyPressed(KEY_ZERO)) {
    cout << "KEY_ZERO" << endl;
    ChangeZoom(true);
  }

  if (IsKeyPressed(KEY_NINE)) {
    cout << "KEY_NINE" << endl;
    ChangeZoom(false);
  
  }

  if (IsKeyPressed(KEY_EIGHT)) {
    cout << "KEY_EIGHT" << endl;

    if (TOGGLE_CAMERA_MODE) {
      TOGGLE_CAMERA_MODE = false;
    } else {
      TOGGLE_CAMERA_MODE = true;
    }
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

inline void InitMoveLogic(game_state& GameState) {
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

inline void InitAttackLogic(game_state& GameState) {
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

        MoveLogic_collision = true;
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
      MoveLogic_collision == false) {
      moved_target = false;

      cout << "this collistion " << MoveLogic_collision << endl;

      ResetFieldVariables(&GameState.CombatantSelected);

      GameState.Target.is_on_move_field = false;

      enemy_colored = false;
      entity_checked = 0;

      GameState.ActionMenu.X_COUNT = 0;
      GameState.ActionMenu.Z_COUNT = 0;
    }

    if (GameState.ActionMenu.Z_COUNT == 1 && MoveLogic_collision == true) {
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

      MoveLogic_collision = false;

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
      if ((GetTime() - static_last_input_time) > TARGET_INPUT_DELAY) {
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

inline void MoveUnit(game_state& GameState, vel v) {
  int static frame_count = 0;
  static int last_move = -99;
  static double static_last_input_time = 0;

  int animating_speed = 8;

  int act_vel = 0;

  static bool jumping = false;

  bool check_layered = true;

  //  static int temp_offset = GameState.WorldPlayer.pEntity->sprite->offset_y;

  // SetEllipsesColPointArray(GameState.WorldPlayer.pEntity->el,
  //                          GameState.WorldPlayer.EllipsePoints);

  if (GameState.ActionMenu.is_menu_up != true) {
    // if (IsKeyPressed(KEY_SPACE) && !jumping) {
    //   // GameState.WorldPlayer.pEntity->layer++;
    //   jumping = true;
    //   GameState.WorldPlayer.pEntity->sprite->offset_y =
    //       GameState.WorldPlayer.pEntity->sprite->offset_y - 48;
    //   x_vel = x_vel + 24;
    // }

    if ((GetTime() - static_last_input_time) >
        PLAYER_INPUT_DELAY)  // Needed to limit target movespeed
    {
      static_last_input_time = (float)GetTime();

      SetEllipsesColPointArray(GameState.WorldPlayer.pEntity->el,
                               GameState.WorldPlayer.EllipsePoints);

      GameState.WorldPlayer.EntitiesVicinity.clear();

      VicinityCheck(GameState.WorldPlayer, GameState.Map.EntityList);

      DebugLog("EntitiesVicinity ",
               (int)GameState.WorldPlayer.EntitiesVicinity.size());

      GameState.WorldPlayer.x_vel = v.right;
      GameState.WorldPlayer.y_vel = v.up;

      if (IsKeyDown(KEY_D) && IsKeyUp(KEY_S) && IsKeyUp(KEY_W)) {
        GameState.WorldPlayer.x_vel = GameState.WorldPlayer.x_vel / 2;

        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, RIGHT);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, RIGHT);
        }
      }

      if (IsKeyDown(KEY_D) && (IsKeyDown(KEY_S))) {
        GameState.WorldPlayer.x_vel = GameState.WorldPlayer.x_vel / 2;
        GameState.WorldPlayer.y_vel = GameState.WorldPlayer.y_vel / 2;

        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, RIGHT);
        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, DOWN);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, RIGHT);
        }
      }

      if (IsKeyDown(KEY_D) && (IsKeyDown(KEY_W))) {
        GameState.WorldPlayer.x_vel = GameState.WorldPlayer.x_vel / 2;
        GameState.WorldPlayer.y_vel = GameState.WorldPlayer.y_vel / 2;

        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, RIGHT);
        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, UP);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, RIGHT);
        }
      }

      if (IsKeyDown(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_W)) {
        GameState.WorldPlayer.x_vel = GameState.WorldPlayer.x_vel / 2;

        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, LEFT);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, LEFT);
        }
      }

      if (IsKeyDown(KEY_A) && (IsKeyDown(KEY_S))) {
        GameState.WorldPlayer.x_vel = GameState.WorldPlayer.x_vel / 2;
        GameState.WorldPlayer.y_vel = GameState.WorldPlayer.y_vel / 2;

        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, LEFT);
        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, DOWN);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, LEFT);
        }
      }

      if (IsKeyDown(KEY_A) && (IsKeyDown(KEY_W))) {
        GameState.WorldPlayer.x_vel = GameState.WorldPlayer.x_vel / 2;
        GameState.WorldPlayer.y_vel = GameState.WorldPlayer.y_vel / 2;

        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, LEFT);
        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, UP);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, LEFT);
        }
      }

      if (IsKeyDown(KEY_W) && IsKeyUp(KEY_D) && IsKeyUp(KEY_A)) {
        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, UP);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, UP);
        }
      }

      if (IsKeyDown(KEY_S) && IsKeyUp(KEY_D) && IsKeyUp(KEY_A)) {
        ApplyCollissionEffect(GameState, GameState.WorldPlayer, true, DOWN);
        if (frame_count % animating_speed == 0) {
          AnimateMovement(GameState.WorldPlayer.pEntity, DOWN);
        }
      }

      frame_count++;

      // if (frame_count % 4 == 0 && jumping) {
      //   if (temp_offset > GameState.WorldPlayer.pEntity->sprite->offset_y) {
      //     GameState.WorldPlayer.pEntity->sprite->offset_y =
      //         GameState.WorldPlayer.pEntity->sprite->offset_y + 12;
      //   }
      //   {
      //     if (temp_offset == GameState.WorldPlayer.pEntity->sprite->offset_y)
      //     {
      //       jumping = false;
      //     }
      //   }
      // }
    }
  }
}

inline void SyncEnemyPosition(game_state& GameState, vel v) {
  bool x_synced = false;
  bool y_synced = false;

  for (size_t e = 0; e < GameState.Map.EnemyList.size(); e++) {
    int temp_x = GameState.Map.EnemyList[e].pEntity->x;
    int temp_y = GameState.Map.EnemyList[e].pEntity->y;

    int mod = temp_x % 64;
    if (mod < 32) {
      temp_x = temp_x - mod;
    } else {
      mod = 64 - mod;
      temp_x = temp_x + mod;
    }
    mod = temp_y % 32;
    if (mod < 16) {
      temp_y = temp_y - mod;
    } else {
      mod = 32 - mod;
      temp_y = temp_y + mod;
    }

    GameState.Map.EnemyList[e].pEntity->x = temp_x;
    GameState.Map.EnemyList[e].pEntity->y = temp_y;
    GameState.Map.EnemyList[e].movelist.clear();
    GameState.Map.EnemyList[e].current_movecount = 0;
    GameState.Map.EnemyList[e].current_steps = 0;
  }
}

inline void EnemyRoaming2(game_state& GameState, vel v) {
  int static enemy_frame_count = 0;
  static double enemy_static_last_input_time = 0;

  static int last_move = -99;
  static int first_move = -99;
  static int second_move = -99;

  static int count = 0;
  double time = GetTime();

  if (GameState.ActionMenu.is_menu_up != true) {
    if ((time - enemy_static_last_input_time) >
        ENEMY_INPUT_DELAY)  // Needed to limit target movespeed
    {
      enemy_static_last_input_time = (float)GetTime();

      for (size_t enemy_index = 0; enemy_index < GameState.Map.EnemyList.size();
           enemy_index++) {
        GameState.Map.EnemyList[enemy_index].x_vel = ROAMING_VEL.right;
        GameState.Map.EnemyList[enemy_index].y_vel = ROAMING_VEL.down;

        SetEllipsesColPointArray(
            GameState.Map.EnemyList[enemy_index].pEntity->el,
            GameState.Map.EnemyList[enemy_index].EllipsePoints);

        point temp_p = {GameState.Map.EnemyList[enemy_index].pEntity->x +
                            GAME_TILE_WIDTH / 2,
                        GameState.Map.EnemyList[enemy_index].pEntity->y +
                            GAME_TILE_HEIGHT / 2};

        ellipse temp_e = GameState.Map.EnemyList[enemy_index].roaming_ellipse;

        bool moved = false;

        static int right_count = 0;
        static int left_count = 0;
        static int up_count = 0;
        static int down_count = 0;

        DebugLog("right_count ", right_count);
        DebugLog("left_count ", left_count);
        DebugLog("up_count ", up_count);
        DebugLog("down_count ", down_count);

        if (enemy_frame_count == 5) {
          enemy_frame_count = 0;
          first_move = -99;
          second_move = -99;
        }

        int random = (int)uint_dist12(rng);

        if (enemy_frame_count < 3) {
          if (random <= 3) {
            if (first_move == LEFT || second_move == LEFT) {
              if (random == 1) {
                last_move = LEFT;
                cout << "FIRST LEFT - LEFT" << endl;
              }
              if (random == 2) {
                last_move = UP;
                cout << "FIRST LEFT - UP" << endl;
              }
              if (random == 3) {
                cout << "FIRST LEFT - DOWN" << endl;
                last_move = DOWN;
              }

            } else {
              last_move = RIGHT;
              temp_p.x = temp_p.x + (v.right);
              temp_p.y = temp_p.y + (v.up);

              right_count++;
            }
          }
          if (random > 3 && random <= 6) {
            if (first_move == RIGHT || second_move == RIGHT) {
              if (random == 4) {
                last_move = RIGHT;
                cout << "FIRST RIGHT - RIGHT" << endl;
              }
              if (random == 5) {
                last_move = UP;
                cout << "FIRST RIGHT - UP" << endl;
              }
              if (random == 6) {
                cout << "FIRST RIGHT - DOWN" << endl;
                last_move = DOWN;
              }

            } else {
              last_move = LEFT;
              temp_p.x = temp_p.x + (v.left);
              temp_p.y = temp_p.y + (v.down);

              left_count++;
            }
          }

          if (random > 6 && random <= 9) {
            if (first_move == DOWN || second_move == DOWN) {
              if (random == 7) {
                last_move = RIGHT;
                cout << "FIRST DOWN - RIGHT" << endl;
              }
              if (random == 8) {
                last_move = LEFT;
                cout << "FIRST DOWN - LEFT" << endl;
              }
              if (random == 9) {
                cout << "FIRST DOWN - DOWN" << endl;
                last_move = DOWN;
              }
            } else {
              last_move = UP;
              temp_p.x = temp_p.x + (v.left);
              temp_p.y = temp_p.y + (v.up);

              up_count++;
            }
          }
          if (random > 9 && random <= 12) {
            if (first_move == UP || second_move == UP) {
              if (random == 10) {
                last_move = RIGHT;
                cout << "FIRST UP - RIGHT" << endl;
              }
              if (random == 11) {
                last_move = LEFT;
                cout << "FIRST UP - LEFT" << endl;
              }
              if (random == 12) {
                cout << "FIRST UP - UP" << endl;
                last_move = UP;
              }

            } else {
              last_move = DOWN;
              temp_p.x = temp_p.x + (v.right);
              temp_p.y = temp_p.y + (v.down);

              down_count++;
            }
          }

          if (enemy_frame_count == 0) {
            first_move = last_move;

          } else {
            if (second_move == -99 && last_move != first_move) {
              second_move = last_move;
            }
          }

          if (last_move == RIGHT) {
            if (CheckIsoMoveCol(GameState.Map.EntityList,
                                GameState.Map.EnemyList[enemy_index], RIGHT,
                                UP) != COLLISION) {
              moved = true;
            }
          } else if (last_move == LEFT) {
            if (CheckIsoMoveCol(GameState.Map.EntityList,
                                 GameState.Map.EnemyList[enemy_index], LEFT,
                                 DOWN) != COLLISION) {
              moved = true;
            }
          } else if (last_move == UP) {
            if (CheckIsoMoveCol(GameState.Map.EntityList,
                                GameState.Map.EnemyList[enemy_index], LEFT,
                                UP) != COLLISION) {
              moved = true;
            }
          } else if (last_move == DOWN) {
            if (CheckIsoMoveCol(GameState.Map.EntityList,
                                GameState.Map.EnemyList[enemy_index], RIGHT,
                                DOWN) != COLLISION) {
              moved = true;
            }
          }

        } else {
          moved = false;
        }

        if (moved) {
          if (temp_e.is_inside_ellipse(temp_p)) {
            if (moved) {
              GameState.Map.EnemyList[enemy_index].movelist.push_back(
                  last_move);
              GameState.AnimatingEnemyMovement = true;
            }

          }

          else {
            if (last_move == RIGHT) {
              temp_p.x = temp_p.x + (v.left / 1);
              temp_p.y = temp_p.y + (v.down / 1);

              temp_p.x = temp_p.x + (v.left / 2);
              temp_p.y = temp_p.y + (v.down / 2);

              if (temp_e.is_inside_ellipse(temp_p)) {
                last_move = LEFT;

              } else {
                cout << "RIGHT EDGE" << endl;
              }
            } else if (last_move == LEFT) {
              temp_p.x = temp_p.x + (v.right / 1);
              temp_p.y = temp_p.y + (v.up / 1);

              temp_p.x = temp_p.x + (v.right / 2);
              temp_p.y = temp_p.y + (v.up / 2);

              if (temp_e.is_inside_ellipse(temp_p)) {
                last_move = RIGHT;
              } else {
                cout << "LEFT EDGE" << endl;
              }
            } else if (last_move == UP) {
              temp_p.x = temp_p.x + (v.right / 1);
              temp_p.y = temp_p.y + (v.down / 1);

              temp_p.x = temp_p.x + (v.right / 2);
              temp_p.y = temp_p.y + (v.down / 2);

              if (temp_e.is_inside_ellipse(temp_p)) {
                last_move = DOWN;

              } else {
                cout << "UP EDGE" << endl;
              }
            } else if (last_move == DOWN) {
              temp_p.x = temp_p.x + (v.left / 1);
              temp_p.y = temp_p.y + (v.up / 1);

              temp_p.x = temp_p.x + (v.left / 2);
              temp_p.y = temp_p.y + (v.up / 2);

              if (temp_e.is_inside_ellipse(temp_p)) {
                last_move = UP;
              } else {
                cout << "DOWN EDGE" << endl;
              }
            }
          }
        }

        enemy_frame_count++;
      }

    } else {
      // cout << "Timmer" << (time - enemy_static_last_input_time) << endl;
    }
  }
}

// }

inline bool HoverSelect(game_state& GameState, field& fieldRef,
                        entity* entity) {
  static bool startset = false;
  bool ret = false;

  entity->render_this = true;

  Rectangle tempEntityRect;

  if (startset == false) {
    tempEntityRect = {(float)fieldRef.tiles[0].x, (float)fieldRef.tiles[0].y,
                      (float)fieldRef.tiles[0].w, (float)fieldRef.tiles[0].h};

    entity->x = tempEntityRect.x;
    entity->y = tempEntityRect.y;

    startset = true;
    ret = true;
  }

  for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++) {
    tempEntityRect = {(float)fieldRef.tiles[i].x, (float)fieldRef.tiles[i].y,
                      (float)fieldRef.tiles[i].w, (float)fieldRef.tiles[i].h};

    if (CollisionIsoTriangles(tempEntityRect, MOUSE_POINT)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        printf("Collision with tile: x:%.0f y:%.0f \n", tempEntityRect.x,
               tempEntityRect.y);

        entity->x = tempEntityRect.x;

        entity->y = tempEntityRect.y;

        ret = true;
      }
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
    if (HoverSelect(GameState, GameState.CombatantSelected.position_field,
                    GameState.CombatantSelected.pEntity) == true) {
      SetActionMenu(GameState.ActionMenu, &GameState.CombatantSelected);
      SyncEnemyPosition(GameState, ROAMING_VEL);
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