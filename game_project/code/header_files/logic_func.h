#pragma once

#if !defined(LOGIC_FUNC)

#include <iostream>

#include "../header_files/globals.h"
#include "../header_files/raylib.h"

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

inline tile_triangles getTileTriangles(Rectangle& t) {
  tile_triangles temp;

  temp.tri_1_line_1_x = t.x + t.width / 2;
  temp.tri_1_line_1_y = t.y;

  temp.tri_1_line_2_x = t.x;
  temp.tri_1_line_2_y = t.y + t.height / 2;

  temp.tri_1_line_3_x = t.x + t.width / 2 + 1;
  temp.tri_1_line_3_y = t.y + t.height / 2 + 1;

  temp.tri_2_line_1_x = t.x;
  temp.tri_2_line_1_y = t.y + t.height / 2;

  temp.tri_2_line_2_x = t.x + t.width / 2;
  temp.tri_2_line_2_y = t.y + t.height - 1;

  temp.tri_2_line_3_x = t.x + t.width / 2 - 1;
  temp.tri_2_line_3_y = t.y + t.height / 2 - 1;

  temp.tri_3_line_1_x = t.x + t.width / 2;
  temp.tri_3_line_1_y = t.y + t.height - 1;

  temp.tri_3_line_2_x = t.x + t.width;
  temp.tri_3_line_2_y = t.y + t.height / 2;

  temp.tri_3_line_3_x = t.x + t.width / 2 - 1;
  temp.tri_3_line_3_y = t.y + t.height / 2 - 1;

  temp.tri_4_line_1_x = t.x + t.width;
  temp.tri_4_line_1_y = t.y + t.height / 2;

  temp.tri_4_line_2_x = t.x + t.width / 2;
  temp.tri_4_line_2_y = t.y;

  temp.tri_4_line_3_x = t.x + t.width / 2 + 1;
  temp.tri_4_line_3_y = t.y + t.height / 2 + 1;

  return temp;
}

inline tile_rect getTileInnerRect(Rectangle& t) {
  tile_rect temp;

  temp.line_1_p1_x = t.x + t.width / 2;
  temp.line_1_p1_y = t.y + 1;

  temp.line_1_p2_x = t.x + 2;
  temp.line_1_p2_y = t.y + t.height / 2;

  temp.line_2_p1_x = t.x + 2;
  temp.line_2_p1_y = t.y + t.height / 2;

  temp.line_2_p2_x = t.x + t.width / 2;
  temp.line_2_p2_y = t.y + t.height - 1;

  temp.line_3_p1_x = t.x + t.width / 2;
  temp.line_3_p1_y = t.y + t.height - 1;

  temp.line_3_p2_x = t.x + t.width - 2;
  temp.line_3_p2_y = t.y + t.height / 2;

  temp.line_4_p1_x = t.x + t.width - 2;
  temp.line_4_p1_y = t.y + t.height / 2;

  temp.line_4_p2_x = t.x + t.width / 2;
  temp.line_4_p2_y = t.y + 1;

  // cout << "temp.line_1_p1_x: " << temp.line_1_p1_x << "temp.line_1_p1_y" <<
  // temp.line_1_p1_y << endl;

  return temp;
}

inline bool CollisionIsoTrianglesMouse(entity* e) {
  Vector2 mouse;

  bool coll_tri1;
  bool coll_tri2;
  bool coll_tri3;
  bool coll_tri4;

  bool collision = false;

  Vector2 p1;
  Vector2 p2;
  Vector2 p3;

  temp4 = getTileTriangles(e->entity_tile);

  mouse.x = GetMouseX() + gamescreen_offset_x;
  mouse.y = GetMouseY() + gamescreen_offset_y;

  p1.x = temp4.tri_1_line_1_x;
  p1.y = temp4.tri_1_line_1_y;

  p2.x = temp4.tri_1_line_2_x;
  p2.y = temp4.tri_1_line_2_y;

  p3.x = temp4.tri_1_line_3_x;
  p3.y = temp4.tri_1_line_3_y;

  coll_tri1 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  p1.x = temp4.tri_2_line_1_x;
  p1.y = temp4.tri_2_line_1_y;

  p2.x = temp4.tri_2_line_2_x;
  p2.y = temp4.tri_2_line_2_y;

  p3.x = temp4.tri_2_line_3_x;
  p3.y = temp4.tri_2_line_3_y;

  coll_tri2 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  p1.x = temp4.tri_3_line_1_x;
  p1.y = temp4.tri_3_line_1_y;

  p2.x = temp4.tri_3_line_2_x;
  p2.y = temp4.tri_3_line_2_y;

  p3.x = temp4.tri_3_line_3_x;
  p3.y = temp4.tri_3_line_3_y;

  coll_tri3 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  p1.x = temp4.tri_4_line_1_x;
  p1.y = temp4.tri_4_line_1_y;

  p2.x = temp4.tri_4_line_2_x;
  p2.y = temp4.tri_4_line_2_y;

  p3.x = temp4.tri_4_line_3_x;
  p3.y = temp4.tri_4_line_3_y;

  coll_tri4 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  if ((coll_tri1 || coll_tri2 || coll_tri3 || coll_tri4)) {
    collision = true;
  }

  return collision;
}

inline bool CollisionIsoTrianglesMouse(Rectangle& r) {
  Vector2 mouse;

  bool coll_tri1;
  bool coll_tri2;
  bool coll_tri3;
  bool coll_tri4;

  bool collision = false;

  Vector2 p1;
  Vector2 p2;
  Vector2 p3;

  temp4 = getTileTriangles(r);

  mouse.x = GetMouseX() - gamescreen_offset_x;
  mouse.y = GetMouseY() - gamescreen_offset_y;

  p1.x = temp4.tri_1_line_1_x;
  p1.y = temp4.tri_1_line_1_y;

  p2.x = temp4.tri_1_line_2_x;
  p2.y = temp4.tri_1_line_2_y;

  p3.x = temp4.tri_1_line_3_x;
  p3.y = temp4.tri_1_line_3_y;

  coll_tri1 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  p1.x = temp4.tri_2_line_1_x;
  p1.y = temp4.tri_2_line_1_y;

  p2.x = temp4.tri_2_line_2_x;
  p2.y = temp4.tri_2_line_2_y;

  p3.x = temp4.tri_2_line_3_x;
  p3.y = temp4.tri_2_line_3_y;

  coll_tri2 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  p1.x = temp4.tri_3_line_1_x;
  p1.y = temp4.tri_3_line_1_y;

  p2.x = temp4.tri_3_line_2_x;
  p2.y = temp4.tri_3_line_2_y;

  p3.x = temp4.tri_3_line_3_x;
  p3.y = temp4.tri_3_line_3_y;

  coll_tri3 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  p1.x = temp4.tri_4_line_1_x;
  p1.y = temp4.tri_4_line_1_y;

  p2.x = temp4.tri_4_line_2_x;
  p2.y = temp4.tri_4_line_2_y;

  p3.x = temp4.tri_4_line_3_x;
  p3.y = temp4.tri_4_line_3_y;

  coll_tri4 = CheckCollisionPointTriangle(mouse, p1, p2, p3);

  if ((coll_tri1 || coll_tri2 || coll_tri3 || coll_tri4)) {
    collision = true;
  }

  return collision;
}

inline bool CollisionIsoRect(entity* e) {
  Vector2 mouse;

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

  mouse.x = GetMouseX() + gamescreen_offset_x;
  mouse.y = GetMouseY() + gamescreen_offset_y;

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  coll_line1 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  coll_line2 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  coll_line3 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  coll_line4 = CheckCollisionPointLine(mouse, p1, p2, 1);

  temp3 = getTileInnerRect(e->entity_tile);

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  inner_coll_line1 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  inner_coll_line2 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  inner_coll_line3 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  inner_coll_line4 = CheckCollisionPointLine(mouse, p1, p2, 1);

  if ((coll_line1 || coll_line2 || coll_line3 || coll_line4) ||
      (inner_coll_line1 || inner_coll_line2 || inner_coll_line3 ||
       inner_coll_line4)) {
    collision = true;
  }
  return collision;
}

inline bool CollisionIsoRect(Rectangle& r) {
  Vector2 mouse;

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

  tile_rect temp3 = getTileRect(r);

  mouse.x = GetMouseX() - gamescreen_offset_x;
  mouse.y = GetMouseY() - gamescreen_offset_y;

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  coll_line1 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  coll_line2 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  coll_line3 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  coll_line4 = CheckCollisionPointLine(mouse, p1, p2, 1);

  temp3 = getTileInnerRect(r);

  p1.x = temp3.line_1_p1_x;
  p1.y = temp3.line_1_p1_y;

  p2.x = temp3.line_1_p2_x;
  p2.y = temp3.line_1_p2_y;

  inner_coll_line1 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_2_p1_x;
  p1.y = temp3.line_2_p1_y;

  p2.x = temp3.line_2_p2_x;
  p2.y = temp3.line_2_p2_y;

  inner_coll_line2 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_3_p1_x;
  p1.y = temp3.line_3_p1_y;

  p2.x = temp3.line_3_p2_x;
  p2.y = temp3.line_3_p2_y;

  inner_coll_line3 = CheckCollisionPointLine(mouse, p1, p2, 1);

  p1.x = temp3.line_4_p1_x;
  p1.y = temp3.line_4_p1_y;

  p2.x = temp3.line_4_p2_x;
  p2.y = temp3.line_4_p2_y;

  inner_coll_line4 = CheckCollisionPointLine(mouse, p1, p2, 1);

  if ((coll_line1 || coll_line2 || coll_line3 || coll_line4) ||
      (inner_coll_line1 || inner_coll_line2 || inner_coll_line3 ||
       inner_coll_line4)) {
    collision = true;
  }

  return collision;
}

Rectangle cTemp = {0, 0, 64, 32};

inline void CheckCordsCollision(Rectangle e) {
  // cout << "Testing setEntityCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      cTemp.x = pos_cords[i][j].x;
      cTemp.y = pos_cords[i][j].y;

      if (CollisionIsoTrianglesMouse(cTemp)) {
        cout << "CheckCordsCollision " << cTemp.x << " " << cTemp.y << endl;
        break;
      }
    }
  }
}

inline pos GetCordsCollisionXY(Rectangle e) {
  pos temp = {0, 0, 0};
  // cout << "Testing setEntityCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      cTemp.x = pos_cords[i][j].x;
      cTemp.y = pos_cords[i][j].y;

      if (CollisionIsoTrianglesMouse(cTemp)) {
        cout << "CheckCordsCollision " << cTemp.x << " " << cTemp.y << endl;
        temp.x = cTemp.x;
        temp.y = cTemp.y;
        break;
      }
    }
  }

  return temp;
}

inline pos GetCordsCollisionIndex(Rectangle e) {
  pos temp = {-1, -1, 0};
  // cout << "Testing setEntityCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      cTemp.x = pos_cords[i][j].x;
      cTemp.y = pos_cords[i][j].y;

      if (CollisionIsoTrianglesMouse(cTemp)) {
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
  point point_up;
  point point_upright;
  point point_right;
  point point_downright;
  point point_down;
  point point_downleft;
  point point_left;
  point point_upleft;

  epoints.clear();

  int pixel = 0;

  point_up.x = e.center.x;
  point_up.y = e.center.y - e.h / 2;
  epoints.push_back(point_up);

  point_upright.x = e.center.x + 0.66666 * (e.w + e.w);
  point_upright.y = e.center.y - 0.75 * (e.h / 2);
  epoints.push_back(point_upright);

  point_right.x = -pixel + e.center.x + e.w + e.w;
  point_right.y = e.center.y;
  epoints.push_back(point_right);

  point_downright.x = e.center.x + 0.66666 * (e.w + e.w);
  point_downright.y = -pixel + e.center.y - (-1 * (0.75 * (e.h / 2)));
  epoints.push_back(point_downright);

  point_down.x = e.center.x;
  point_down.y = -pixel + e.center.y - 1 * (-e.h / 2);
  epoints.push_back(point_down);

  point_downleft.x = e.center.x + (-1 * (0.66666 * (e.w + e.w)));
  point_downleft.y = -pixel + e.center.y - (-1 * (0.75 * (e.h / 2)));
  epoints.push_back(point_downleft);

  point_left.x = e.center.x - e.w - e.w;
  point_left.y = e.center.y;
  epoints.push_back(point_left);

  point_upleft.x = e.center.x + (-1 * (0.66666 * (e.w + e.w)));
  point_upleft.y = e.center.y - 0.75 * (e.h / 2);
  epoints.push_back(point_upleft);
}

inline void GetEllipsesColPoint(vector<bool>& collision, ellipse e,
                                vector<point>& epoints) {
  if (collision.size() == 0) {
	cout << " this happens" << endl;

    for (size_t i = 0; i < epoints.size(); i++) {
      if (e.is_inside_ellipse(epoints[i])) {
        collision.push_back(true);
      } else {
        collision.push_back(false);
      }
    }

  } else {
    for (size_t i = 0; i < epoints.size(); i++) {
      if (e.is_inside_ellipse(epoints[i])) {
        collision[i] = true;
      } else {
        collision[i] = false;
      }
    }
  }
}

#define LOGIC_FUNC
#endif
