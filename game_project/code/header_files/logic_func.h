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

  int padding = 1;

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

  int padding = 1;

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

Rectangle cTemp = {0, 0, 64, 32};

inline void CheckCordsCollision(pos** pos_cords, Rectangle e,
                                point& ref_point) {
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

inline bool CheckCollisionPoints(bool* collision, vector<point>& epoints,
                                 vector<entity>& entities, entity* self,
                                 bool check_layered) {
  bool any_collision = false;

  int coll_array_size = sizeof(collision) / sizeof(collision[0]);

  for (size_t i = 0; i < coll_array_size; i++) {
    collision[i] = false;
  }

  for (size_t i = 0; i < epoints.size(); i++) {
    for (size_t entity = 0; entity < entities.size(); entity++) {
      if (self != &entities[entity]) {
        if (self->layer == entities[entity].layer || check_layered == false) {
          switch (entities[entity].coll_check_type) {
            case TILE:
              if (CollisionIsoTriangles(&entities[entity], epoints[i])) {
                collision[i] = true;
              }
              break;
            case ELLIPSE:
              if (entities[entity].el.is_inside_ellipse(epoints[i])) {
                collision[i] = true;
              }
              break;
            case POINT:
              cout << "NOT IMPLEMENTED" << endl;
              break;
            default:
              cout << "NO DEFAULT CHECK" << endl;
              break;
          }
        }
      }
    }
  }

  return any_collision;
}

#define LOGIC_FUNC
#endif
