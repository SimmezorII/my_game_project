#pragma once

#ifndef combat_cpp
#define combat_cpp

#include <iostream>

#include "../header_files/globals.h"
#include "raylib.h"
#include "game_engine.cpp"

using namespace std;

/////----------------------------------------------------------------------------------------------------

inline void setSquareField(vector<sprite>& sprite_list, field& fieldRef, int nx,
                           int ny, int tile_color) {
  int targetRange = fieldRef.range;

  int fx = nx - (GAME_TILE_WIDTH / 2);
  int fy = ny + (GAME_TILE_HEIGHT / 2);

  int row = 0;
  int line = 0;

  int x = 0;
  int y = 0;

  int n = 1;
  int m = 1;

  int numRect = 0;
  int tilecount = 0;

  int start = 0;

  int sum1 = (targetRange - 1) * (targetRange - 1);
  int sum2 = (targetRange * targetRange);

  int fieldx = 0;
  int fieldy = 0;

  fieldRef.sum_of_field_tiles = sum1 + sum2;

  for (int i = 0; i < sum1; i++) {
    // cout << "i:" << i << endl;

    if (numRect == (n * n)) {
      n += 1;
      row += 1;
    }

    x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
        row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
        (targetRange * (GAME_TILE_WIDTH / 2));
    y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
        row * ((GAME_TILE_HEIGHT / 2) * row) +
        (targetRange * (GAME_TILE_HEIGHT / 2));

    // field.fieldRects[i] = [x, y]

    fieldRef.tiles[i].w = GAME_TILE_WIDTH;
    fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

    fieldRef.tiles[i].x = x;
    fieldRef.tiles[i].y = y;

    if (i == 0) {
      fieldy = fieldRef.tiles[i].y;
      fieldx = fieldRef.tiles[i].x;

    } else {
      if (fieldRef.tiles[i].y < fieldy) {
        fieldy = fieldRef.tiles[i].y;
      }

      if (fieldRef.tiles[i].x < fieldx) {
        fieldx = fieldRef.tiles[i].x;
      }
    }

    //	cout << "fieldtile y: "<<fieldRef.tiles[i].y << endl;
    //	cout << "fieldtile x: " << fieldRef.tiles[i].x << endl;

    fieldRef.tiles[i].sprite = &getSprite(sprite_list, tile_color);
    fieldRef.tiles[i].render = true;

    tilecount += 1;
    numRect += 1;
  }

  numRect = 0;

  start = sum1;

  while (start < (sum1 + sum2)) {
    if (numRect == (m * m)) {
      m += 1;
      line += 1;
    }

    x = fx + ((GAME_TILE_WIDTH / 2) * (start - sum1)) -
        line * ((GAME_TILE_WIDTH / 2) * line) - (line * GAME_TILE_WIDTH) +
        (targetRange * (GAME_TILE_WIDTH / 2));
    y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
        line * ((GAME_TILE_HEIGHT / 2) * line) -
        (targetRange * (GAME_TILE_HEIGHT / 2));

    fieldRef.tiles[start].w = GAME_TILE_WIDTH;
    fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

    fieldRef.tiles[start].x = x;
    fieldRef.tiles[start].y = y;

    //	cout << "fieldtile y: " << fieldRef.tiles[start].y << endl;
    //	cout << "fieldtile x: " << fieldRef.tiles[start].x << endl;

    if (fieldRef.tiles[start].y < fieldy) {
      fieldy = fieldRef.tiles[start].y;
    }

    if (fieldRef.tiles[start].x < fieldx) {
      fieldx = fieldRef.tiles[start].x;
    }

    fieldRef.tiles[start].sprite = &getSprite(sprite_list, tile_color);
    fieldRef.tiles[start].render = true;

    tilecount += 1;
    numRect += 1;
    start += 1;
  }

  fieldRef.x = fieldx + 32;
  fieldRef.y = fieldy + 16;
  fieldRef.w = (64 * (targetRange - 1));
  fieldRef.h = (32 * (targetRange - 1));
}

inline void setInverseSquareField(vector<sprite>& sprite_list, field& fieldRef,
                                  int nx, int ny) {
  int right_vel = (GAME_TILE_WIDTH / 2);
  int left_vel = -(GAME_TILE_WIDTH / 2);
  int up_vel = -(GAME_TILE_HEIGHT / 2);
  int down_vel = (GAME_TILE_HEIGHT / 2);

  int targetRange = fieldRef.range;

  int fx = nx;
  int fy = ny + (targetRange - 1) * up_vel;

  int row = 0;
  int line = 0;

  int x = 0;
  int y = 0;

  int n = 1;
  int m = 1;

  int numRect = 0;
  int tilecount = 0;

  int start = 0;

  int sum1 = (targetRange * targetRange);

  int sum2 = ((targetRange - 1) * (targetRange - 1));

  int fieldx = 0;
  int fieldy = 0;

  fieldRef.sum_of_field_tiles = sum1;

  int count = 0;

  for (size_t i = 0; i < targetRange; i++) {
    for (size_t j = 0; j < targetRange; j++) {
      fieldRef.tiles[count].x = ((right_vel * 1) * i) + fx + (left_vel * j);
      fieldRef.tiles[count].y =
          ((down_vel * 1) * i) + fy + ((down_vel * 1) * j);

      count++;
    }
  }

  for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++) {
    fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
    fieldRef.tiles[i].render = true;
    fieldRef.tiles[i].w = GAME_TILE_WIDTH;
    fieldRef.tiles[i].h = GAME_TILE_HEIGHT;
  }
}

inline void setTriangleField(vector<sprite>& sprite_list, field& fieldRef,
                             int nx, int ny, Direction dir) {
  int targetRange = fieldRef.range;

  int right_vel = (GAME_TILE_WIDTH / 2);
  int left_vel = -(GAME_TILE_WIDTH / 2);
  int up_vel = -(GAME_TILE_HEIGHT / 2);
  int down_vel = (GAME_TILE_HEIGHT / 2);

  int fx = 0;
  int fy = 0;

  int row = 0;
  int line = 0;

  int x = 0;
  int y = 0;

  int n = 1;
  int m = 1;

  int numRect = 0;
  int tilecount = 0;

  int start = 0;

  int sum1 = 0;
  int sum2 = 0;

  int fieldx = 0;
  int fieldy = 0;

  if (dir == UP) {
    fx = nx + right_vel;
    fy = ny + down_vel;

    // int sum1 = (targetRange - 1) * (targetRange - 1);
    sum2 = (targetRange * targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + -1 * (((GAME_TILE_WIDTH / 2) * (start - sum1)) -
                     line * ((GAME_TILE_WIDTH / 2) * line) -
                     (line * GAME_TILE_WIDTH) +
                     (targetRange * (GAME_TILE_WIDTH / 2)));
      y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
          line * ((GAME_TILE_HEIGHT / 2) * line) -
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }

  if (dir == DOWN) {
    fx = nx + left_vel;
    fy = ny + up_vel;

    // int sum1 = (targetRange - 1) * (targetRange - 1);
    sum2 = (targetRange * targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + 1 * (((GAME_TILE_WIDTH / 2) * (start - sum1)) -
                    line * ((GAME_TILE_WIDTH / 2) * line) -
                    (line * GAME_TILE_WIDTH) +
                    (targetRange * (GAME_TILE_WIDTH / 2)));
      y = fy + -1 * (((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
                     line * ((GAME_TILE_HEIGHT / 2) * line) -
                     (targetRange * (GAME_TILE_HEIGHT / 2)));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }

  if (dir == RIGHT) {
    fx = nx - (GAME_TILE_WIDTH / 2);
    fy = ny + (GAME_TILE_HEIGHT / 2);

    sum2 = (targetRange * targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;

      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      //	cout << "fieldtile y: "<<fieldRef.tiles[i].y << endl;
      //	cout << "fieldtile x: " << fieldRef.tiles[i].x << endl;

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;

      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + ((GAME_TILE_WIDTH / 2) * (start - sum1)) -
          line * ((GAME_TILE_WIDTH / 2) * line) - (line * GAME_TILE_WIDTH) +
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
          line * ((GAME_TILE_HEIGHT / 2) * line) -
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      //	cout << "fieldtile y: " << fieldRef.tiles[start].y << endl;
      //	cout << "fieldtile x: " << fieldRef.tiles[start].x << endl;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }

  if (dir == LEFT) {
    fx = nx + left_vel;
    fy = ny + down_vel;

    sum1 = (targetRange) * (targetRange);
    // sum2 = (targetRange*targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + ((GAME_TILE_WIDTH / 2) * (start - sum1)) -
          line * ((GAME_TILE_WIDTH / 2) * line) - (line * GAME_TILE_WIDTH) +
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
          line * ((GAME_TILE_HEIGHT / 2) * line) -
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }
}

inline void setConeField(vector<sprite>& sprite_list, field& fieldRef, int nx,
                         int ny, Direction dir) {
  int targetRange = fieldRef.range;

  int fx = 0;
  int fy = 0;

  int row = 0;
  int line = 0;

  int x = 0;
  int y = 0;

  int n = 1;
  int m = 1;

  int numRect = 0;
  int tilecount = 0;

  int start = 0;

  int sum1 = 0;
  int sum2 = 0;

  int fieldx = 0;
  int fieldy = 0;

  int right_vel = (GAME_TILE_WIDTH / 2);
  int left_vel = -(GAME_TILE_WIDTH / 2);
  int up_vel = -(GAME_TILE_HEIGHT / 2);
  int down_vel = (GAME_TILE_HEIGHT / 2);

  numRect = 0;

  start = 0;

  if (dir == LEFT) {
    fx = nx - (GAME_TILE_WIDTH / 2) + (left_vel * (targetRange - 1));
    fy = ny + (GAME_TILE_HEIGHT / 2) + (down_vel * (targetRange - 1));

    // int sum1 = (targetRange - 1) * (targetRange - 1);
    sum2 = (targetRange * targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + ((GAME_TILE_WIDTH / 2) * (start - sum1)) -
          line * ((GAME_TILE_WIDTH / 2) * line) - (line * GAME_TILE_WIDTH) +
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
          line * ((GAME_TILE_HEIGHT / 2) * line) -
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }

  if (dir == RIGHT) {
    fx = nx - (GAME_TILE_WIDTH / 2) + (right_vel * (targetRange - 1));
    fy = ny + (GAME_TILE_HEIGHT / 2) + (up_vel * (targetRange - 1));

    sum1 = (targetRange) * (targetRange);
    // sum2 = (targetRange*targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + ((GAME_TILE_WIDTH / 2) * (start - sum1)) -
          line * ((GAME_TILE_WIDTH / 2) * line) - (line * GAME_TILE_WIDTH) +
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
          line * ((GAME_TILE_HEIGHT / 2) * line) -
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }

  if (dir == UP) {
    fx = nx + left_vel + (left_vel * (targetRange - 1));
    fy = ny + up_vel + (up_vel * (targetRange - 1));

    // int sum1 = (targetRange - 1) * (targetRange - 1);
    sum2 = (targetRange * targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + 1 * (((GAME_TILE_WIDTH / 2) * (start - sum1)) -
                    line * ((GAME_TILE_WIDTH / 2) * line) -
                    (line * GAME_TILE_WIDTH) +
                    (targetRange * (GAME_TILE_WIDTH / 2)));
      y = fy + -1 * (((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
                     line * ((GAME_TILE_HEIGHT / 2) * line) -
                     (targetRange * (GAME_TILE_HEIGHT / 2)));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }

  if (dir == DOWN) {
    fx = nx + right_vel + (right_vel * (targetRange - 1));
    fy = ny + down_vel + (down_vel * (targetRange - 1));

    // int sum1 = (targetRange - 1) * (targetRange - 1);
    sum2 = (targetRange * targetRange);

    fieldRef.sum_of_field_tiles = sum1 + sum2;

    for (int i = 0; i < sum1; i++) {
      // cout << "i:" << i << endl;

      if (numRect == (n * n)) {
        n += 1;
        row += 1;
      }

      x = (GAME_TILE_WIDTH) + fx - ((GAME_TILE_WIDTH / 2) * (i)) +
          row * ((GAME_TILE_WIDTH / 2) * row) + (row * GAME_TILE_WIDTH) -
          (targetRange * (GAME_TILE_WIDTH / 2));
      y = (-GAME_TILE_HEIGHT) + fy - ((GAME_TILE_HEIGHT / 2) * (i)) +
          row * ((GAME_TILE_HEIGHT / 2) * row) +
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[i].w = GAME_TILE_WIDTH;
      fieldRef.tiles[i].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[i].x = x;
      fieldRef.tiles[i].y = y;

      if (i == 0) {
        fieldy = fieldRef.tiles[i].y;
        fieldx = fieldRef.tiles[i].x;
      } else {
        if (fieldRef.tiles[i].y < fieldy) {
          fieldy = fieldRef.tiles[i].y;
        }

        if (fieldRef.tiles[i].x < fieldx) {
          fieldx = fieldRef.tiles[i].x;
        }
      }

      fieldRef.tiles[i].sprite = &getSprite(sprite_list, GREEN_TILE);
      fieldRef.tiles[i].render = true;
      tilecount += 1;
      numRect += 1;
    }

    numRect = 0;

    start = sum1;

    while (start < (sum1 + sum2)) {
      if (numRect == (m * m)) {
        m += 1;
        line += 1;
      }

      x = fx + -1 * (((GAME_TILE_WIDTH / 2) * (start - sum1)) -
                     line * ((GAME_TILE_WIDTH / 2) * line) -
                     (line * GAME_TILE_WIDTH) +
                     (targetRange * (GAME_TILE_WIDTH / 2)));
      y = fy + ((GAME_TILE_HEIGHT / 2) * (start - sum1)) -
          line * ((GAME_TILE_HEIGHT / 2) * line) -
          (targetRange * (GAME_TILE_HEIGHT / 2));

      fieldRef.tiles[start].w = GAME_TILE_WIDTH;
      fieldRef.tiles[start].h = GAME_TILE_HEIGHT;

      fieldRef.tiles[start].x = x;
      fieldRef.tiles[start].y = y;

      if (fieldRef.tiles[start].y < fieldy) {
        fieldy = fieldRef.tiles[start].y;
      }

      if (fieldRef.tiles[start].x < fieldx) {
        fieldx = fieldRef.tiles[start].x;
      }

      fieldRef.tiles[start].sprite = &getSprite(sprite_list, GREEN_TILE);

      tilecount += 1;
      numRect += 1;
      start += 1;
    }

    fieldRef.x = fieldx + 32;
    fieldRef.y = fieldy + 16;
    fieldRef.w = (64 * (targetRange - 1));
    fieldRef.h = (32 * (targetRange - 1));
  }
}

inline void SetField(game_state& GameState, field& fieldRef, int nx, int ny,
                     int field_type, int tile_color) {
  SetRenderField(&fieldRef, false);

  if (field_type == SQUARE) {
    setSquareField(GameState.SpriteList, fieldRef, nx, ny, tile_color);
  }

  if (field_type == NON_ISO_SQUARE) {
    setInverseSquareField(GameState.SpriteList, fieldRef, nx, ny);
  }

  if (field_type == TRIANGLE + UP) {
    setTriangleField(GameState.SpriteList, fieldRef, nx, ny, UP);
  }

  if (field_type == TRIANGLE + DOWN) {
    setTriangleField(GameState.SpriteList, fieldRef, nx, ny, DOWN);
  }

  if (field_type == TRIANGLE + LEFT) {
    setTriangleField(GameState.SpriteList, fieldRef, nx, ny, LEFT);
  }

  if (field_type == TRIANGLE + RIGHT) {
    setTriangleField(GameState.SpriteList, fieldRef, nx, ny, RIGHT);
  }

  if (field_type == CONE + UP) {
    setConeField(GameState.SpriteList, fieldRef, nx, ny, UP);
  }

  if (field_type == CONE + DOWN) {
    setConeField(GameState.SpriteList, fieldRef, nx, ny, DOWN);
  }

  if (field_type == CONE + LEFT) {
    setConeField(GameState.SpriteList, fieldRef, nx, ny, LEFT);
  }

  if (field_type == CONE + RIGHT) {
    setConeField(GameState.SpriteList, fieldRef, nx, ny, RIGHT);
  }
}

inline void InitEnemyFields(game_state& GameState) {
  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    GameState.Map.EnemyList[i].move_field.field_alpha = 0.5;

    SetField(GameState, GameState.Map.EnemyList[i].move_field,
             GameState.Map.EnemyList[i].pEntity->x,
             GameState.Map.EnemyList[i].pEntity->y, SQUARE, RED_TILE);

    GameState.FieldList.push_back(&GameState.Map.EnemyList[i].move_field);
  }
}

inline void SetEnemyFields(game_state& GameState) {
  for (size_t i = 0; i < GameState.Map.EnemyList.size(); i++) {
    SetField(GameState, GameState.Map.EnemyList[i].move_field,
             GameState.Map.EnemyList[i].pEntity->x,
             GameState.Map.EnemyList[i].pEntity->y, SQUARE, RED_TILE);
  }
}

inline void SetRenderEnemyFields(vector<combatant>& enemy_list, bool render) {
  for (size_t i = 0; i < enemy_list.size(); i++) {
    enemy_list[i].move_field.render_field = render;
  }
}

inline void InitCombat(game_state& GameState) {
  Log("InitCombat");

  GameState.Gui.EntityList[0].render_this = true;
  
  SetEnemyFields(GameState);

  GameState.CombatantSelected.position_field.range = 5;

  GameState.CombatantSelected.position_field.render_field = true;

  SetField(GameState, GameState.CombatantSelected.position_field, 10 * GAME_TILE_WIDTH, 10 * GAME_TILE_HEIGHT, NON_ISO_SQUARE, GREEN_TILE);

  GameState.FieldList.push_back(&GameState.CombatantSelected.position_field);
}

inline void SelectStartingTile() {
  int pos_tile_num = 10;

  for (size_t i = 0; i < pos_tile_num; i++) {
  }
}

#endif