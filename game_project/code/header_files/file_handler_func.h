#pragma once

#if !defined(FILE_HANDLER_FUNC)

#include <fstream>
#include <iostream>
#include <string>

#include "../header_files/globals.h"
#include "../header_files/raylib.h"


using namespace std;

inline int WriteEntityDataSingle(entity e, string path) {
  ofstream myfile(path, std::ios::app);

  if (myfile.is_open()) {
    myfile << "------"
           << "\n";
    myfile << "entity ID : [" << e.ID << "]"
           << "\n";
    myfile << "entity w : [" << e.w << "]"
           << "\n";
    myfile << "entity h : [" << e.h << "]"
           << "\n";
    myfile << "entity sprite ID : [" << e.sprite->ID << "]"
           << "\n";

    //		myfile << "entity sprite ID : [" << e.sprite_ID << "]" << "\n";
    //		myfile << "entity sprite filename : [" << e.sprite.img << "]" <<
    //"\n"; 		myfile << "entity sprite x : [" << e.sprite.x << "]" << "\n"; 		myfile
    //<< "entity sprite y : [" << e.sprite.y << "]" << "\n"; 		myfile << "entity
    //sprite w : [" << e.sprite.w << "]" << "\n"; 		myfile << "entity sprite h :
    //[" << e.sprite.h << "\n";

    myfile << "------"
           << "\n";

    myfile.close();
    return 1;
  } else
    cout << "Unable to open file";
  return 0;
}

inline int WriteUpdatedMap(string path) {
  // ofstream myfile(path, std::ios::app); // adds edits to existing file

  ofstream myfile(path);

  string temp = "";

  if (myfile.is_open()) {
    myfile << "Map2"
           << "\n";
    myfile << "------"
           << "\n";

    for (size_t i = 0; i < Y_TILES; i++) {
      for (size_t j = 0; j < 20; j++) {
        if (to_string(cords[i][j][CURRENT_LAYER]).size() == 1) {
          temp = "00";
          temp.append(to_string(cords[i][j][CURRENT_LAYER]));

          myfile << "[" << temp << "]";
        } else if ((to_string(cords[i][j][CURRENT_LAYER]).size() == 2)) {
          temp = "0";
          temp.append(to_string(cords[i][j][CURRENT_LAYER]));

          myfile << "[" << temp << "]";
        } else {
          myfile << "[" << cords[i][j][CURRENT_LAYER] << "]";
        }
      }

      if (i % 2 == 0) {
        myfile << "\n  ";
      } else {
        myfile << "\n";
      }
    }

    myfile << "------"
           << "\n";
    myfile << "------"
           << "\n";
    myfile << "END"
           << "\n";

    myfile.close();
    return 1;
  } else
    cout << "Unable to open file";
  return 0;
}

inline sprite& getSpriteEx(vector<sprite>& sprite_list, int sprite_ID) {
  for (size_t i = 0; i < sprite_list.size(); i++) {
    if (sprite_list[i].ID == sprite_ID) {
      return sprite_list[i];
      break;
    }
  }

  return sprite_list[0];
}

#define FILE_HANDLER_FUNC
#endif
