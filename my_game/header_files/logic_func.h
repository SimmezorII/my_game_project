#pragma once

#if !defined(LOGIC_FUNC)

#include <iostream>

#include "../header_files/globals.h"
#include "raylib.h"

using namespace std;

inline tile_rect getTileRect(Rectangle& t) {
  tile_rect temp;

  temp.line_1_p1_x = t.x + t.width / 2;
  temp.line_1_p1_y = t.y;

  temp.line_1_p2_x = t.x;
  temp.line_1_p2_y = t.y + t.height / 2;

  temp.line_2_p1_x = t.x;
  temp.line_2_p1_y = t.y + t.height / 2;

  temp.line_2_p2_x = t.x + t.width / 2;
  temp.line_2_p2_y = t.y + t.height;

  temp.line_3_p1_x = t.x + t.width / 2;
  temp.line_3_p1_y = t.y + t.height;

  temp.line_3_p2_x = t.x + t.width;
  temp.line_3_p2_y = t.y + t.height / 2;

  temp.line_4_p1_x = t.x + t.width;
  temp.line_4_p1_y = t.y + t.height / 2;

  temp.line_4_p2_x = t.x + t.width / 2;
  temp.line_4_p2_y = t.y;

  // cout << "temp.line_1_p1_x: " << temp.line_1_p1_x << "temp.line_1_p1_y" <<
  // temp.line_1_p1_y << endl;

  return temp;
}

inline tile_rect SetIsoRect(pos t, int width, int height) {
  tile_rect temp;

  t.x = t.x - width / 2;
  t.y = t.y - height / 2;

  temp.line_1_p1_x = t.x + width / 2 + GAME_TILE_WIDTH / 2;
  temp.line_1_p1_y = t.y + GAME_TILE_HEIGHT / 2;

  temp.line_1_p2_x = t.x + GAME_TILE_WIDTH / 2;
  temp.line_1_p2_y = t.y + height / 2 + GAME_TILE_HEIGHT / 2;

  temp.line_2_p1_x = t.x + GAME_TILE_WIDTH / 2;
  temp.line_2_p1_y = t.y + height / 2 + GAME_TILE_HEIGHT / 2;

  temp.line_2_p2_x = t.x + width / 2 + GAME_TILE_WIDTH / 2;
  temp.line_2_p2_y = t.y + height + GAME_TILE_HEIGHT / 2;

  temp.line_3_p1_x = t.x + width / 2 + GAME_TILE_WIDTH / 2;
  temp.line_3_p1_y = t.y + height + GAME_TILE_HEIGHT / 2;

  temp.line_3_p2_x = t.x + width + GAME_TILE_WIDTH / 2;
  temp.line_3_p2_y = t.y + height / 2 + GAME_TILE_HEIGHT / 2;

  temp.line_4_p1_x = t.x + width + GAME_TILE_WIDTH / 2;
  temp.line_4_p1_y = t.y + height / 2 + GAME_TILE_HEIGHT / 2;

  temp.line_4_p2_x = t.x + width / 2 + GAME_TILE_WIDTH / 2;
  temp.line_4_p2_y = t.y + GAME_TILE_HEIGHT / 2;

  // cout << "temp.line_1_p1_x: " << temp.line_1_p1_x << "temp.line_1_p1_y" <<
  // temp.line_1_p1_y << endl;

  return temp;
}

inline void DrawIsoRect(tile_rect& rect) {
  DrawLineEx({rect.line_1_p1_x + GAMESCREEN_OFFSET_X,
              rect.line_1_p1_y + GAMESCREEN_OFFSET_Y},
             {rect.line_1_p2_x + GAMESCREEN_OFFSET_X,
              rect.line_1_p2_y + GAMESCREEN_OFFSET_Y},
             3, ORANGE);

  DrawLineEx({rect.line_2_p1_x + GAMESCREEN_OFFSET_X,
              rect.line_2_p1_y + GAMESCREEN_OFFSET_Y},
             {rect.line_2_p2_x + GAMESCREEN_OFFSET_X,
              rect.line_2_p2_y + GAMESCREEN_OFFSET_Y},
             3, ORANGE);

  DrawLineEx({rect.line_3_p1_x + GAMESCREEN_OFFSET_X,
              rect.line_3_p1_y + GAMESCREEN_OFFSET_Y},
             {rect.line_3_p2_x + GAMESCREEN_OFFSET_X,
              rect.line_3_p2_y + GAMESCREEN_OFFSET_Y},
             3, ORANGE);

  DrawLineEx({rect.line_4_p1_x + GAMESCREEN_OFFSET_X,
              rect.line_4_p1_y + GAMESCREEN_OFFSET_Y},
             {rect.line_4_p2_x + GAMESCREEN_OFFSET_X,
              rect.line_4_p2_y + GAMESCREEN_OFFSET_Y},
             3, ORANGE);
}

inline void DrawRectLines(entity* e, int LINE) {
  bool collision = false;
  tile_rect temp = getTileRect(e->entity_tile);

  float line_start_x = 0;
  float line_start_y = 0;
  float line_end_x = 0;
  float line_end_y = 0;

  if (LINE == LINE_UP) {
    line_start_x = temp.line_1_p1_x;
    line_start_y = temp.line_1_p1_y;
    line_end_x = temp.line_1_p2_x;
    line_end_y = temp.line_1_p2_y;
  }

  if (LINE == LINE_LEFT) {
    line_start_x = temp.line_2_p1_x;
    line_start_y = temp.line_2_p1_y;
    line_end_x = temp.line_2_p2_x;
    line_end_y = temp.line_2_p2_y;
  }

  if (LINE == LINE_DOWN) {
    line_start_x = temp.line_3_p1_x;
    line_start_y = temp.line_3_p1_y;
    line_end_x = temp.line_3_p2_x;
    line_end_y = temp.line_3_p2_y;
  }

  if (LINE == LINE_RIGHT) {
    line_start_x = temp.line_4_p1_x;
    line_start_y = temp.line_4_p1_y;
    line_end_x = temp.line_4_p2_x;
    line_end_y = temp.line_4_p2_y;
  }

  if (LINE == LINE_DIAG) {
    line_start_x = temp.line_3_p1_x;
    line_start_y = temp.line_3_p1_y;
    line_end_x = temp.line_3_p2_x;
    line_end_y = temp.line_3_p2_y - GAME_TILE_HEIGHT;
  }

  if (LINE == TRIPLE_LINE_RIGHT) {
    // line_start_x = temp.line_2_p1_x + GAME_TILE_WIDTH / 2 + GAME_TILE_WIDTH /
    // 8; line_start_y = GAME_TILE_HEIGHT / 2 + temp.line_2_p1_y -
    //                GAME_TILE_HEIGHT * 2 + GAME_TILE_HEIGHT / 8;
    // line_end_x = temp.line_2_p2_x + GAME_TILE_WIDTH / 2 - GAME_TILE_WIDTH /
    // 8; line_end_y = GAME_TILE_HEIGHT / 2 + temp.line_2_p2_y -
    //              GAME_TILE_HEIGHT * 2 - GAME_TILE_HEIGHT / 8;

    // DrawLineEx(
    //     {line_start_x + GAMESCREEN_OFFSET_X,
    //      line_start_y + GAMESCREEN_OFFSET_Y},
    //     {line_end_x + GAMESCREEN_OFFSET_X, line_end_y + GAMESCREEN_OFFSET_Y},
    //     2, RED);

    line_start_x = temp.line_2_p1_x + GAME_TILE_WIDTH / 8;
    line_start_y = temp.line_2_p1_y + GAME_TILE_HEIGHT / 8;
    line_end_x = temp.line_2_p2_x - GAME_TILE_WIDTH / 8;
    line_end_y = temp.line_2_p2_y - GAME_TILE_HEIGHT / 8;

    DrawLineEx(
        {line_start_x + GAMESCREEN_OFFSET_X,
         line_start_y + GAMESCREEN_OFFSET_Y},
        {line_end_x + GAMESCREEN_OFFSET_X, line_end_y + GAMESCREEN_OFFSET_Y}, 2,
        YELLOW);

  } else {
    DrawLineEx(
        {line_start_x + GAMESCREEN_OFFSET_X,
         line_start_y + GAMESCREEN_OFFSET_Y},
        {line_end_x + GAMESCREEN_OFFSET_X, line_end_y + GAMESCREEN_OFFSET_Y}, 2,
        ORANGE);
  }
}

inline bool CollisionRectLines(entity* e, point& ref_point, int LINE) {
  bool collision = false;
  tile_rect temp = getTileRect(e->entity_tile);

  float line_start_x;
  float line_start_y;
  float line_end_x;
  float line_end_y;

  if (LINE == LINE_UP) {
    line_start_x = temp.line_1_p1_x;
    line_start_y = temp.line_1_p1_y;
    line_end_x = temp.line_1_p2_x;
    line_end_y = temp.line_1_p2_y;
  }

  if (LINE == LINE_LEFT) {
    line_start_x = temp.line_2_p1_x;
    line_start_y = temp.line_2_p1_y;
    line_end_x = temp.line_2_p2_x;
    line_end_y = temp.line_2_p2_y;
  }

  if (LINE == LINE_DOWN) {
    line_start_x = temp.line_3_p1_x;
    line_start_y = temp.line_3_p1_y;
    line_end_x = temp.line_3_p2_x;
    line_end_y = temp.line_3_p2_y;
  }

  if (LINE == LINE_RIGHT) {
    line_start_x = temp.line_4_p1_x;
    line_start_y = temp.line_4_p1_y;
    line_end_x = temp.line_4_p2_x;
    line_end_y = temp.line_4_p2_y;
  }

  if (LINE == LINE_DIAG) {
    line_start_x = temp.line_3_p1_x;
    line_start_y = temp.line_3_p1_y;
    line_end_x = temp.line_3_p2_x;
    line_end_y = temp.line_3_p2_y - GAME_TILE_HEIGHT;
  }

  if (LINE == TRIPLE_LINE_RIGHT) {
    line_start_x = temp.line_2_p1_x + GAME_TILE_WIDTH / 8;
    line_start_y = temp.line_2_p1_y + GAME_TILE_HEIGHT / 8;
    line_end_x = temp.line_2_p2_x - GAME_TILE_WIDTH / 8;
    line_end_y = temp.line_2_p2_y - GAME_TILE_HEIGHT / 8;
  }

  collision = CheckCollisionPointLine({ref_point.x, ref_point.y},
                                      {line_start_x, line_start_y},
                                      {line_end_x, line_end_y}, 1);

  return collision;
}

inline tile_triangles getTileTriangles(Rectangle& t) {
  tile_triangles temp;

  float padding = 0;

  temp.tri_1_line_1_x = t.x + t.width / 2;
  temp.tri_1_line_1_y = t.y;

  temp.tri_1_line_2_x = t.x;
  temp.tri_1_line_2_y = t.y + t.height / 2;

  temp.tri_1_line_3_x = t.x + t.width / 2 + padding;
  temp.tri_1_line_3_y = t.y + t.height / 2 + padding;

  temp.tri_2_line_1_x = t.x;
  temp.tri_2_line_1_y = t.y + t.height / 2;

  temp.tri_2_line_2_x = t.x + t.width / 2;
  temp.tri_2_line_2_y = t.y + t.height - padding;

  temp.tri_2_line_3_x = t.x + t.width / 2 - padding;
  temp.tri_2_line_3_y = t.y + t.height / 2 - padding;

  temp.tri_3_line_1_x = t.x + t.width / 2;
  temp.tri_3_line_1_y = t.y + t.height - padding;

  temp.tri_3_line_2_x = t.x + t.width;
  temp.tri_3_line_2_y = t.y + t.height / 2;

  temp.tri_3_line_3_x = t.x + t.width / 2 - padding;
  temp.tri_3_line_3_y = t.y + t.height / 2 - padding;

  temp.tri_4_line_1_x = t.x + t.width;
  temp.tri_4_line_1_y = t.y + t.height / 2;

  temp.tri_4_line_2_x = t.x + t.width / 2;
  temp.tri_4_line_2_y = t.y;

  temp.tri_4_line_3_x = t.x + t.width / 2 + padding;
  temp.tri_4_line_3_y = t.y + t.height / 2 + padding;

  return temp;
}

inline tile_rect getTileInnerRect(Rectangle& t) {
  tile_rect temp;

  float padding = 0.25;

  temp.line_1_p1_x = t.x + t.width / 2;
  temp.line_1_p1_y = t.y + padding;

  temp.line_1_p2_x = t.x + 2;
  temp.line_1_p2_y = t.y + t.height / 2;

  temp.line_2_p1_x = t.x + 2;
  temp.line_2_p1_y = t.y + t.height / 2;

  temp.line_2_p2_x = t.x + t.width / 2;
  temp.line_2_p2_y = t.y + t.height - padding;

  temp.line_3_p1_x = t.x + t.width / 2;
  temp.line_3_p1_y = t.y + t.height - padding;

  temp.line_3_p2_x = t.x + t.width - 2;
  temp.line_3_p2_y = t.y + t.height / 2;

  temp.line_4_p1_x = t.x + t.width - 2;
  temp.line_4_p1_y = t.y + t.height / 2;

  temp.line_4_p2_x = t.x + t.width / 2;
  temp.line_4_p2_y = t.y + padding;

  // cout << "temp.line_1_p1_x: " << temp.line_1_p1_x << "temp.line_1_p1_y" <<
  // temp.line_1_p1_y << endl;

  return temp;
}

inline bool CollisionIsoTriangles(entity* e, point& ref_point) {
  Vector2 p4;

  p4.x = ref_point.x;
  p4.y = ref_point.y;

  bool coll_tri1;
  bool coll_tri2;
  bool coll_tri3;
  bool coll_tri4;

  bool collision = false;

  Vector2 p1;
  Vector2 p2;
  Vector2 p3;

  tile_triangles temp_rect = getTileTriangles(e->entity_tile);

  p1.x = temp_rect.tri_1_line_1_x;
  p1.y = temp_rect.tri_1_line_1_y;

  p2.x = temp_rect.tri_1_line_2_x;
  p2.y = temp_rect.tri_1_line_2_y;

  p3.x = temp_rect.tri_1_line_3_x;
  p3.y = temp_rect.tri_1_line_3_y;

  coll_tri1 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  p1.x = temp_rect.tri_2_line_1_x;
  p1.y = temp_rect.tri_2_line_1_y;

  p2.x = temp_rect.tri_2_line_2_x;
  p2.y = temp_rect.tri_2_line_2_y;

  p3.x = temp_rect.tri_2_line_3_x;
  p3.y = temp_rect.tri_2_line_3_y;

  coll_tri2 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  p1.x = temp_rect.tri_3_line_1_x;
  p1.y = temp_rect.tri_3_line_1_y;

  p2.x = temp_rect.tri_3_line_2_x;
  p2.y = temp_rect.tri_3_line_2_y;

  p3.x = temp_rect.tri_3_line_3_x;
  p3.y = temp_rect.tri_3_line_3_y;

  coll_tri3 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  p1.x = temp_rect.tri_4_line_1_x;
  p1.y = temp_rect.tri_4_line_1_y;

  p2.x = temp_rect.tri_4_line_2_x;
  p2.y = temp_rect.tri_4_line_2_y;

  p3.x = temp_rect.tri_4_line_3_x;
  p3.y = temp_rect.tri_4_line_3_y;

  coll_tri4 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  if ((coll_tri1 || coll_tri2 || coll_tri3 || coll_tri4)) {
    collision = true;
  }

  return collision;
}

inline bool CollisionIsoTriangles(Rectangle& r, point& ref_point) {
  Vector2 p4;

  p4.x = ref_point.x;
  p4.y = ref_point.y;

  bool coll_tri1;
  bool coll_tri2;
  bool coll_tri3;
  bool coll_tri4;

  bool collision = false;

  Vector2 p1;
  Vector2 p2;
  Vector2 p3;

  tile_triangles temp_rect = getTileTriangles(r);

  p1.x = temp_rect.tri_1_line_1_x;
  p1.y = temp_rect.tri_1_line_1_y;

  p2.x = temp_rect.tri_1_line_2_x;
  p2.y = temp_rect.tri_1_line_2_y;

  p3.x = temp_rect.tri_1_line_3_x;
  p3.y = temp_rect.tri_1_line_3_y;

  coll_tri1 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  p1.x = temp_rect.tri_2_line_1_x;
  p1.y = temp_rect.tri_2_line_1_y;

  p2.x = temp_rect.tri_2_line_2_x;
  p2.y = temp_rect.tri_2_line_2_y;

  p3.x = temp_rect.tri_2_line_3_x;
  p3.y = temp_rect.tri_2_line_3_y;

  coll_tri2 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  p1.x = temp_rect.tri_3_line_1_x;
  p1.y = temp_rect.tri_3_line_1_y;

  p2.x = temp_rect.tri_3_line_2_x;
  p2.y = temp_rect.tri_3_line_2_y;

  p3.x = temp_rect.tri_3_line_3_x;
  p3.y = temp_rect.tri_3_line_3_y;

  coll_tri3 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  p1.x = temp_rect.tri_4_line_1_x;
  p1.y = temp_rect.tri_4_line_1_y;

  p2.x = temp_rect.tri_4_line_2_x;
  p2.y = temp_rect.tri_4_line_2_y;

  p3.x = temp_rect.tri_4_line_3_x;
  p3.y = temp_rect.tri_4_line_3_y;

  coll_tri4 = CheckCollisionPointTriangle(p4, p1, p2, p3);

  if ((coll_tri1 || coll_tri2 || coll_tri3 || coll_tri4)) {
    collision = true;
  }

  return collision;
}

inline bool CollisionIsoRect(entity* e, point& ref_point) {
  Vector2 p3;

  Vector2 p1;
  Vector2 p2;

  bool collision = false;

  bool coll_line1;
  bool coll_line2;
  bool coll_line3;
  bool coll_line4;

  bool inner_coll_line1;
  bool inner_coll_line2;
  bool inner_coll_line3;
  bool inner_coll_line4;

  tile_rect temp3 = getTileRect(e->entity_tile);

  p3.x = ref_point.x;
  p3.y = ref_point.y;

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  coll_line1 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  coll_line2 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  coll_line3 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  coll_line4 = CheckCollisionPointLine(p3, p1, p2, 1);

  temp3 = getTileInnerRect(e->entity_tile);

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  inner_coll_line1 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  inner_coll_line2 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  inner_coll_line3 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  inner_coll_line4 = CheckCollisionPointLine(p3, p1, p2, 1);

  if ((coll_line1 || coll_line2 || coll_line3 || coll_line4) ||
      (inner_coll_line1 || inner_coll_line2 || inner_coll_line3 ||
       inner_coll_line4)) {
    collision = true;
  }
  return collision;
}

inline bool CollisionIsoRect(Rectangle& r, point& ref_point) {
  Vector2 p1;
  Vector2 p2;

  Vector2 p3;

  p3.x = ref_point.x;
  p3.y = ref_point.y;

  bool collision = false;

  bool coll_line1;
  bool coll_line2;
  bool coll_line3;
  bool coll_line4;

  bool inner_coll_line1;
  bool inner_coll_line2;
  bool inner_coll_line3;
  bool inner_coll_line4;

  tile_rect temp3 = getTileRect(r);

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  coll_line1 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  coll_line2 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  coll_line3 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  coll_line4 = CheckCollisionPointLine(p3, p1, p2, 1);

  temp3 = getTileInnerRect(r);

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  inner_coll_line1 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  inner_coll_line2 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  inner_coll_line3 = CheckCollisionPointLine(p3, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  inner_coll_line4 = CheckCollisionPointLine(p3, p1, p2, 1);

  if ((coll_line1 || coll_line2 || coll_line3 || coll_line4) ||
      (inner_coll_line1 || inner_coll_line2 || inner_coll_line3 ||
       inner_coll_line4)) {
    collision = true;
  }

  return collision;
}

inline void CheckCordsCollision(pos** pos_cords, Rectangle e,
                                point& ref_point) {
  static Rectangle cTemp = {0, 0, 64, 32};

  // cout << "Testing setEntityCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      cTemp.x = pos_cords[i][j].x;
      cTemp.y = pos_cords[i][j].y;

      if (CollisionIsoTriangles(cTemp, ref_point)) {
        cout << "CheckCordsCollision " << cTemp.x << " " << cTemp.y << endl;
        break;
      }
    }
  }
}

inline pos GetCordsCollisionXY(pos** pos_cords, Rectangle e, point& ref_point) {
  Rectangle cTemp = {0, 0, 64, 32};
  pos temp = {0, 0, 0};
  // cout << "Testing setEntityCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      cTemp.x = pos_cords[i][j].x;
      cTemp.y = pos_cords[i][j].y;

      if (CollisionIsoTriangles(cTemp, ref_point)) {
        cout << "CheckCordsCollision " << cTemp.x << " " << cTemp.y << endl;
        temp.x = cTemp.x;
        temp.y = cTemp.y;
        break;
      }
    }
  }

  return temp;
}

inline pos GetCordsCollisionIndex(pos pos_cords[40][20], Rectangle e,
                                  point& ref_point) {
  Rectangle cTemp = {0, 0, 64, 32};
  pos temp = {-1, -1, 0};
  // cout << "Testing setEntityCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      cTemp.x = pos_cords[i][j].x;
      cTemp.y = pos_cords[i][j].y;

      if (CollisionIsoTriangles(cTemp, ref_point)) {
        temp.screen_x = cTemp.x;
        temp.screen_y = cTemp.y;

        cout << "CheckCordsCollision i j:" << i << " " << j << endl;
        temp.x = i;
        temp.y = j;
        break;
      }
    }
  }

  return temp;
}

inline void SetEllipsesColPointArray(ellipse& e, vector<point>& epoints) {
  point point_up1;
  point point_up2;
  point point_upright;
  point point_right1;
  point point_right2;
  point point_downright;
  point point_down1;
  point point_down2;
  point point_downleft;
  point point_left1;
  point point_left2;
  point point_upleft;

  int pixel = 1;

  point_up1.x = e.center.x;
  point_up1.y = e.center.y - e.h / 2;

  point_up2.x = -pixel + e.center.x;
  point_up2.y = e.center.y - e.h / 2;

  point_upright.x = e.center.x + 0.66666 * (e.w + e.w);
  point_upright.y = e.center.y - 0.75 * (e.h / 2);

  point_right1.x = -pixel + e.center.x + e.w + e.w;
  point_right1.y = e.center.y;

  point_right2.x = -pixel + e.center.x + e.w + e.w;
  point_right2.y = -pixel + e.center.y;

  point_downright.x = e.center.x + 0.66666 * (e.w + e.w);
  point_downright.y = -pixel + e.center.y - (-1 * (0.75 * (e.h / 2)));

  point_down1.x = e.center.x;
  point_down1.y = -pixel + e.center.y - 1 * (-e.h / 2);

  point_down2.x = -pixel + e.center.x;
  point_down2.y = -pixel + e.center.y - 1 * (-e.h / 2);

  point_downleft.x = e.center.x + (-1 * (0.66666 * (e.w + e.w)));
  point_downleft.y = -pixel + e.center.y - (-1 * (0.75 * (e.h / 2)));

  point_left1.x = e.center.x - e.w - e.w;
  point_left1.y = e.center.y;

  point_left2.x = e.center.x - e.w - e.w;
  point_left2.y = -pixel + e.center.y;

  point_upleft.x = e.center.x + (-1 * (0.66666 * (e.w + e.w)));
  point_upleft.y = e.center.y - 0.75 * (e.h / 2);

  if (epoints.empty()) {
    epoints.push_back(point_up1);
    epoints.push_back(point_up2);
    epoints.push_back(point_upright);
    epoints.push_back(point_right1);
    epoints.push_back(point_right2);
    epoints.push_back(point_downright);
    epoints.push_back(point_down1);
    epoints.push_back(point_down2);
    epoints.push_back(point_downleft);
    epoints.push_back(point_left1);
    epoints.push_back(point_left2);
    epoints.push_back(point_upleft);
  } else {
    epoints[0] = (point_up1);
    epoints[1] = (point_up2);
    epoints[2] = (point_upright);
    epoints[3] = (point_right1);
    epoints[4] = (point_right2);
    epoints[5] = (point_downright);
    epoints[6] = (point_down1);
    epoints[7] = (point_down2);
    epoints[8] = (point_downleft);
    epoints[9] = (point_left1);
    epoints[10] = (point_left2);
    epoints[11] = (point_upleft);
  }
}

inline bool CheckEllipsesColPoints(bool* collision, vector<point>& epoints,
                                   ellipse e) {
  bool any_collision = false;

  for (size_t i = 0; i < epoints.size(); i++) {
    if (e.is_inside_ellipse(epoints[i])) {
      collision[i] = true;
    } else {
      collision[i] = false;
    }
  }

  return any_collision;
}

inline void CheckCollisionType(bool* collision, int* collision_type,
                               vector<entity>& entities,
                               vector<entity*>& ref_entities, int entity_index,
                               int epoints_index) {
  bool found = false;

  if (!ref_entities.empty()) {
    for (size_t j = 0; j < ref_entities.size(); j++) {
      if (&entities[entity_index] == ref_entities[j]) {
        found = true;
      } else {
      }
    }
    if (!found) {
      ref_entities.push_back(&entities[entity_index]);
      collision_type[epoints_index] = entities[entity_index].collision_effect;
    }

  } else {
    ref_entities.push_back(&entities[entity_index]);
    collision_type[epoints_index] = entities[entity_index].collision_effect;
  }
}

inline void CheckCollisionType(bool* collision, int* collision_type,
                               vector<entity*>& entities,
                               vector<entity*>& ref_entities, int entity_index,
                               int epoints_index) {
  bool found = false;

  if (!ref_entities.empty()) {
    for (size_t j = 0; j < ref_entities.size(); j++) {
      if (entities[entity_index] == ref_entities[j]) {
        found = true;
      } else {
      }
    }
    if (!found) {
      ref_entities.push_back(entities[entity_index]);
      collision_type[epoints_index] = entities[entity_index]->collision_effect;
    }

  } else {
    ref_entities.push_back(entities[entity_index]);
    collision_type[epoints_index] = entities[entity_index]->collision_effect;
  }
}

inline bool CheckCollisionPoints(bool* collision, int* collision_type,
                                 vector<point>& epoints,
                                 vector<entity*> entities, entity* self,
                                 vector<entity*> ref_entities,
                                 bool check_layered) {
  bool any_collision = false;
  bool found = false;

  for (size_t i = 0; i < epoints.size(); i++) {
    collision[i] = false;
    collision_type[i] = -1;

    for (size_t entity_index = 0; entity_index < entities.size();
         entity_index++) {
      if (self != entities[entity_index]) {
        if (self->layer == entities[entity_index]->layer ||
            check_layered == false) {
          switch (entities[entity_index]->coll_check_type) {
            case TILE:

              if (CollisionIsoTriangles(entities[entity_index], epoints[i])) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;
            case ELLIPSE:
              if (entities[entity_index]->el.is_inside_ellipse(epoints[i])) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }

              break;
            case POINT:
              cout << "NOT IMPLEMENTED" << endl;
              break;

            case LINE_UP:
              if (CollisionRectLines(entities[entity_index], epoints[i],
                                     LINE_UP)) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;
            case LINE_LEFT:
              if (CollisionRectLines(entities[entity_index], epoints[i],
                                     LINE_LEFT)) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;
            case LINE_DOWN:
              if (CollisionRectLines(entities[entity_index], epoints[i],
                                     LINE_DOWN)) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;
            case LINE_RIGHT:
              if (CollisionRectLines(entities[entity_index], epoints[i],
                                     LINE_RIGHT)) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;

            case LINE_DIAG:
              if (CollisionRectLines(entities[entity_index], epoints[i],
                                     LINE_DIAG)) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;
            case TRIPLE_LINE_RIGHT:
              if (CollisionRectLines(entities[entity_index], epoints[i],
                                     TRIPLE_LINE_RIGHT)) {
                collision[i] = true;
                any_collision = true;

                CheckCollisionType(collision, collision_type, entities,
                                   ref_entities, entity_index, i);
              }
              break;
            default:

              break;
          }
        }
      }
    }

    if (!any_collision) {
      ref_entities.clear();
    }
  }

  return any_collision;
}



inline int DirCollisionCheck(game_state& GameState, combatant& combatant,
                             bool check_layered, int dir, int effect_index,
                             int& set_vel, bool& ref_trigger) {
  ellipse temp_el = combatant.pEntity->el;

  int x_vel = combatant.x_vel;
  int y_vel = combatant.y_vel;

  int act_vel;

  int n_vel;

  int* DIR_CHECK[4];

  int collision_effect = -1;

  if (dir == DOWN || dir == DOWNUP) {
    DIR_CHECK[0] = &combatant.EllipsePointsCollisionsType[INDEX_DOWN];
    DIR_CHECK[1] = &combatant.EllipsePointsCollisionsType[INDEX_DOWN2];
    DIR_CHECK[2] = &combatant.EllipsePointsCollisionsType[INDEX_DOWN_RIGHT];
    DIR_CHECK[3] = &combatant.EllipsePointsCollisionsType[INDEX_DOWN_LEFT];

    n_vel = y_vel;
  } else if (dir == UP || dir == UPDOWN) {
    DIR_CHECK[0] = &combatant.EllipsePointsCollisionsType[INDEX_UP];
    DIR_CHECK[1] = &combatant.EllipsePointsCollisionsType[INDEX_UP2];
    DIR_CHECK[2] = &combatant.EllipsePointsCollisionsType[INDEX_UP_RIGHT];
    DIR_CHECK[3] = &combatant.EllipsePointsCollisionsType[INDEX_UP_LEFT];

    n_vel = y_vel;
  } else if (dir == RIGHT || dir == RIGHTLEFT) {
    DIR_CHECK[0] = &combatant.EllipsePointsCollisionsType[INDEX_RIGHT];
    DIR_CHECK[1] = &combatant.EllipsePointsCollisionsType[INDEX_RIGHT2];
    DIR_CHECK[2] = &combatant.EllipsePointsCollisionsType[INDEX_UP_RIGHT];
    DIR_CHECK[3] = &combatant.EllipsePointsCollisionsType[INDEX_DOWN_RIGHT];

    n_vel = x_vel;
  } else if (dir == LEFT || dir == LEFTRIGHT) {
    DIR_CHECK[0] = &combatant.EllipsePointsCollisionsType[INDEX_LEFT];
    DIR_CHECK[1] = &combatant.EllipsePointsCollisionsType[INDEX_LEFT2];
    DIR_CHECK[2] = &combatant.EllipsePointsCollisionsType[INDEX_UP_LEFT];
    DIR_CHECK[3] = &combatant.EllipsePointsCollisionsType[INDEX_DOWN_LEFT];

    n_vel = x_vel;
  } else {
    int temp = -1;
    DIR_CHECK[0] = &temp;
    DIR_CHECK[1] = &temp;
    DIR_CHECK[2] = &temp;
    DIR_CHECK[3] = &temp;
  }

  for (size_t i = 0; i <= n_vel; i++) {
    act_vel = i;

    SetEllipsesColPointArray(temp_el, combatant.EllipsePoints);

    // MUST IMPROVE PERFORMANCE HERE
    CheckCollisionPoints(combatant.EllipsePointsCollisions,
                         combatant.EllipsePointsCollisionsType,
                         combatant.EllipsePoints, combatant.EntitiesVicinity,
                         combatant.pEntity, GameState.EntitiesCollision,
                         check_layered);

    if ((*DIR_CHECK[0] == GameState.CollisionEffects[effect_index]) ||
        (*DIR_CHECK[1] == GameState.CollisionEffects[effect_index]) ||
        (*DIR_CHECK[2] == GameState.CollisionEffects[effect_index]) ||
        (*DIR_CHECK[3] == GameState.CollisionEffects[effect_index])) {
      ref_trigger = true;
      collision_effect = GameState.CollisionEffects[effect_index];
      break;
    }
    if (dir == DOWN || dir == UPDOWN) {
      temp_el.center.y = temp_el.center.y + 1;

    } else if (dir == UP || dir == DOWNUP) {
      temp_el.center.y = temp_el.center.y - 1;

    } else if (dir == RIGHT || dir == LEFTRIGHT) {
      temp_el.center.x = temp_el.center.x + 1;

    } else if (dir == LEFT || dir == RIGHTLEFT) {
      temp_el.center.x = temp_el.center.x - 1;

    } else {
    }
  }
  set_vel = act_vel;
  return collision_effect;
}

inline bool SetCollisionEffect(game_state& GameState, combatant& combatant,
                               bool movement, int act_vel_x, int act_vel_y,
                               int& x_vel, int& y_vel, bool trigger_effect,
                               int collision_effect) {
  static int apply_once = -1;

  bool set_effect = false;

  if (collision_effect == COLLISION && trigger_effect) {
    combatant.pEntity->x = combatant.pEntity->x + act_vel_x;
    combatant.pEntity->y = combatant.pEntity->y + act_vel_y;

    combatant.x_vel = act_vel_x;
    combatant.y_vel = act_vel_y;

  } else if (collision_effect == NO_COLLISION && trigger_effect) {
  }

  else if (collision_effect == UP_LAYER && trigger_effect) {
    if (y_vel < 0) {
      cout << "UP LAYER - UP " << combatant.x_vel << " " << combatant.y_vel
           << endl;
      combatant.pEntity->layer = combatant.pEntity->layer + 2;

      apply_once = 1;
      set_effect = true;
      return set_effect;

    } else if (x_vel > 0) {
      cout << "UP LAYER - RIGHT " << combatant.x_vel << " " << combatant.y_vel
           << endl;

      combatant.pEntity->layer = combatant.pEntity->layer + 2;

      apply_once = 1;
      set_effect = true;
      return set_effect;

    }

    else {
    }

  }

  else if (collision_effect == DOWN_LAYER && trigger_effect &&
           apply_once == 1) {
    if (y_vel > 0) {
      cout << "DOWN LAYER - DOWN " << combatant.x_vel << " " << combatant.y_vel
           << endl;

      combatant.pEntity->layer = combatant.pEntity->layer - 2;

      apply_once = -1;
      set_effect = true;
      return set_effect;

    } else if (x_vel < 0) {
      cout << "DOWN LAYER - LEFT " << combatant.x_vel << " " << combatant.y_vel
           << endl;

      combatant.pEntity->layer = combatant.pEntity->layer - 2;

      apply_once = -1;
      set_effect = true;
      return set_effect;
    }

    else {
    }

  }

  else if (collision_effect == UP_TWO_LAYER && trigger_effect &&
           apply_once == 1) {
    combatant.pEntity->layer = combatant.pEntity->layer + 1;
    cout << "TWO UP_LAYER" << endl;
    apply_once = 2;

  }

  else if (collision_effect == DOWN_TWO_LAYER && trigger_effect &&
           apply_once == 2) {
    cout << "TWO DOWN_LAYER" << endl;

    combatant.pEntity->layer = combatant.pEntity->layer - 2;

    apply_once = -1;
  }

  else {
    if (movement) {
      combatant.pEntity->x = combatant.pEntity->x + x_vel;
      combatant.pEntity->y = combatant.pEntity->y + y_vel;
    }
  }
  return set_effect;
}

inline void ApplyCollissionEffect(game_state& GameState, combatant& combatant,
                                  bool check_layered, int direction) {
  bool movement = false;
  int act_vel = 0;
  bool trigger_effect = false;

  bool set_effect = false;
  int collision_effect = -1;

  int zero_vel = 0;

  for (size_t eff = 0; eff < GameState.CollisionEffects.size(); eff++) {
    if (eff == 0) {
      movement = true;
    } else {
      movement = false;
    }
    if (direction == UP) {
      if (GameState.CollisionEffects[eff] == UP_LAYER) {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, DOWNUP, eff,
                              act_vel, trigger_effect);
      } else {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, UP, eff,
                              act_vel, trigger_effect);
      }

      combatant.y_vel = -1 * combatant.y_vel;
      act_vel = -1 * act_vel;

      SetCollisionEffect(GameState, combatant, movement, 0, act_vel, zero_vel,
                         combatant.y_vel, trigger_effect, collision_effect);

      combatant.y_vel = -1 * combatant.y_vel;
      act_vel = -1 * act_vel;
    }

    if (direction == DOWN) {
      if (GameState.CollisionEffects[eff] == DOWN_LAYER) {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, UPDOWN, eff,
                              act_vel, trigger_effect);
      } else {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, DOWN, eff,
                              act_vel, trigger_effect);
      }

      SetCollisionEffect(GameState, combatant, movement, 0, act_vel, zero_vel,
                         combatant.y_vel, trigger_effect, collision_effect);
    }

    if (direction == RIGHT) {
      if (GameState.CollisionEffects[eff] == UP_LAYER) {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, LEFTRIGHT,
                              eff, act_vel, trigger_effect);
      } else {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, RIGHT, eff,
                              act_vel, trigger_effect);
      }

      SetCollisionEffect(GameState, combatant, movement, act_vel, 0,
                         combatant.x_vel, zero_vel, trigger_effect,
                         collision_effect);
    }
    if (direction == LEFT) {
      if (GameState.CollisionEffects[eff] == DOWN_LAYER) {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, RIGHTLEFT,
                              eff, act_vel, trigger_effect);
      } else {
        collision_effect =
            DirCollisionCheck(GameState, combatant, check_layered, LEFT, eff,
                              act_vel, trigger_effect);
      }

      combatant.x_vel = -1 * combatant.x_vel;
      act_vel = -1 * act_vel;

      SetCollisionEffect(GameState, combatant, movement, act_vel, 0,
                         combatant.x_vel, zero_vel, trigger_effect,
                         collision_effect);

      combatant.x_vel = -1 * combatant.x_vel;
      act_vel = -1 * act_vel;

    }

    else {
    }
  }
}

#define LOGIC_FUNC
#endif
