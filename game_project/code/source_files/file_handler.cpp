#include <fstream>
#include <iostream>
#include <string>

#include "../header_files/globals.h"
#include "../header_files/raylib.h"
#include "game_engine.cpp"

using namespace std;

inline void ReadAllFilesInDir(const char* path) {
  int count = 0;

  char** DirectoryFiles;

  char empty1[] = ".";
  char empty2[] = "..";

  if (DirectoryExists(path)) {
    // printf("Directory exists\n");

    DirectoryFiles = GetDirectoryFiles(path, &count);

    // printf("%d\n", count);

    for (size_t i = 0; i < count; i++) {
      if ((strcmp(DirectoryFiles[i], empty1) == 0) ||
          (strcmp(DirectoryFiles[i], empty2) == 0)) {
        // Do nothing with . and .. paths
      } else {
        printf("%s\n", DirectoryFiles[i]);
      }
    }

  } else {
    printf("Directory does not exist\n");
  }

  ClearDirectoryFiles();
}

inline int GetPNG_FilesInDir(const char* path, vector<string>& StringVector,
                             string& StringList) {
  int result = -1;

  StringList = "";

  int count = 0;

  char** DirectoryFiles;

  char empty1[] = ".";
  char empty2[] = "..";

  if (DirectoryExists(path)) {
    printf("Directory exists\n");

    DirectoryFiles = GetDirectoryFiles(path, &count);

    // printf("%d\n", count);

    for (size_t i = 0; i < count; i++) {
      if ((strcmp(DirectoryFiles[i], empty1) == 0) ||
          (strcmp(DirectoryFiles[i], empty2) == 0)) {
        // Do nothing with . and .. paths
      } else {
        if (IsFileExtension(DirectoryFiles[i], ".png")) {
          StringVector.push_back(DirectoryFiles[i]);

          if (!StringList.compare("")) {
            StringList = StringList + DirectoryFiles[i];
          } else {
            StringList = StringList + ";" + DirectoryFiles[i];
          }

        } else {
        }
      }
    }
    result = 1;
  } else {
    printf("Directory does not exist\n");
    result = 0;
  }

  ClearDirectoryFiles();
  return result;
}

inline void AddIntegerFromString(vector<string>* LinesInFile, string str) {
  size_t i = 0;

  for (; i < str.length(); i++) {
    if (isdigit(str[i])) break;
  }

  str = str.substr(i, (str.length() - 1) - i);

  if (str != "") {
    LinesInFile->push_back(str);
  } else {
  }
}

inline int GetIntegerFromString(string str) {
  size_t i = 0;

  for (; i < str.length(); i++) {
    if (isdigit(str[i])) break;
  }

  str = str.substr(i, (str.length() - 1) - i);

  if (str != "") {
    return stoi(str);
  } else {
    return -1;
  }
}

inline int GetIntegerFromStringTwo(string str) {
  size_t i = 0;

  for (; i < str.length(); i++) {
    if (isdigit(str[i])) break;
  }

  str = str.substr(i, (str.length() - 1) - i);

  if (str != "") {
    return stoi(str);
  } else {
    return -1;
  }
}

inline string GetDataFromReadline(string line) {
  // entity sprite w:	[64] <-- example this functions reads and returns what
  // is inside []

  string start = "[";

  string end = "]";

  size_t start_at = line.find(start);

  if (start_at != string::npos) {
    // cout << "[ occurrence is " << start_at << endl;
  } else {
    start_at = -1;
  }

  size_t end_at = line.find(end);

  if (end_at != string::npos) {
    // cout << "] occurrence is " << end_at << endl;
  } else {
    end_at = 0;
  }

  if (line != "") {
    line = line.substr(start_at + 1, (end_at - 1 - start_at));
  }

  return line;
}

inline string GetDataFromReadlineTwo(string line) {
  // entity sprite w:	[64] <-- example this functions reads and returns what
  // is inside []

  string start = "[";

  string end = "]";

  size_t start_at = line.find(start);

  if (start_at != string::npos) {
    // cout << "[ occurrence is " << start_at << endl;
  } else {
    start_at = -1;
  }

  size_t end_at = line.find(end);

  if (end_at != string::npos) {
    // cout << "] occurrence is " << end_at << endl;
  } else {
    end_at = 0;
  }

  if (line != "") {
    line = line.substr(start_at + 1, (end_at - 1 - start_at));
  }

  return line;
}

inline string GetDataFromReadlineThree(string line, int layer) {
  global_variable int row = 0;

  // entity sprite w:	[64] <-- example this functions reads and returns what
  // is inside []

  size_t loop;

  string temp = "";

  string start = "[";

  string end = "]";

  size_t start_at = line.find(start);

  // line.find_last_of(start);

  if (start_at != string::npos) {
    // cout << "[ occurrence is " << start_at << endl;
  } else {
    start_at = -1;
  }

  size_t end_at = line.find(end);

  if (end_at != string::npos) {
    // cout << "] occurrence is " << end_at << endl;
  } else {
    end_at = 0;
  }

  if (line != "" && start_at != -1) {
    // cout << "line size " << line.size() << endl;

    loop = (line.size() - start_at) / (end_at - start_at + 1);

    // cout << "loop " << loop << endl;

    string_cords[row][0] = (line.substr(start_at + 1, (end_at - 1 - start_at)));

    cords[row][0][layer] = stoi(string_cords[row][0]);

    temp = line.substr((end_at + 1), line.size());

    for (size_t i = 1; i < loop; i++) {
      start_at = temp.find(start);

      // line.find_last_of(start);

      if (start_at != string::npos) {
        // cout << "[ occurrence is " << start_at << endl;
      } else {
        start_at = -1;
      }

      end_at = temp.find(end);

      if (end_at != string::npos) {
        // cout << "] occurrence is " << end_at << endl;
      } else {
        end_at = 0;
      }

      string_cords[row][i] =
          (temp.substr(start_at + 1, (end_at - 1 - start_at)));

      cords[row][i][layer] = stoi(string_cords[row][i]);

      temp = temp.substr((end_at + 1), temp.size());
    }

    row++;
  }

  return line;
}

inline string GetDataFromReadlineTiledMap(string line, int layer) {
  // entity sprite w:	[64] <-- example this functions reads and returns what
  // is inside []

  size_t loop;

  string temp = "";

  string start = "";

  string end = ",";

  size_t start_at = line.find(start);

  // line.find_last_of(start);

  if (start_at != string::npos) {
  } else {
    start_at = -1;
  }

  size_t end_at = line.find(end);

  if (end_at != string::npos) {
  } else {
    end_at = 0;
  }

  if (line != "" && start_at != -1) {
    // cout << "line size " << line.size() << endl;

    loop = (line.size() - start_at) / (end_at - start_at + 1);

    string_cords[row][0] = (line.substr(start_at, (end_at - start_at)));

    // cout << " | " << string_cords[row][0] << " | ";

    cords[row][0][layer] = stoi(string_cords[row][0]);

    temp = line.substr((end_at + 1), line.size());

    for (size_t i = 1; i < 19; i++) {
      start_at = temp.find(start);

      // line.find_last_of(start);

      if (start_at != string::npos) {
        // cout << "[ occurrence is " << start_at << endl;
      } else {
        start_at = -1;
      }

      end_at = temp.find(end);

      if (end_at != string::npos) {
        // cout << "] occurrence is " << end_at << endl;
      } else {
        end_at = 0;
      }

      string_cords[row][i] = (temp.substr(start_at, (end_at - start_at)));

      // cout << " | " << string_cords[row][i] << " | ";

      cords[row][i][layer] = stoi(string_cords[row][i]);

      temp = temp.substr((end_at + 1), temp.size());
    }

    cords[row][19][layer] = stoi(temp);

    cout << "layer: " << layer << endl;

    row++;
  }
  return line;
}

inline string GetPropertyNameFromReadline(string line) {
  // entity sprite w:	[64] <-- example this functions reads and returns
  // "entity sprite w:"

  string end = ":";

  size_t start_at = -1;

  size_t end_at = line.find(end);

  if (end_at != string::npos) {
    // cout << "] occurrence is " << end_at << endl;
  } else {
    end_at = 0;
  }

  if (line != "") {
    line = line.substr(start_at + 1, (end_at - 1 - start_at));
  }

  return line;
}

inline void setSprite(vector<sprite>& sprite_list, entity* e, int ID) {
  //	printf("Searching for: %d \n", ID);
  for (size_t i = 0; i < sprite_list.size(); i++) {
    // printf("Compare: %d vs %d \n", sprite_list[i].ID, ID);

    if (sprite_list[i].ID == ID) {
      e->sprite = &sprite_list[i];

      //	printf("Match! %s\n", sprite_list[i].img.c_str());
      break;
    } else {
      //	printf("Didn't find: %d \n", ID);
    }
  }
}

inline void LoadSpriteData(game_state & GameState, int sprite_count) {
  //------
  // entity sprite ID : [0]
  // entity sprite filename : []
  // entity sprite x : [0]
  // entity sprite y : [0]
  // entity sprite w : [64]
  // entity sprite h : [32
  //------

  // strcpy(temp.sprite.img, &tmp_str[0]);
  // temp.sprite.img = &tmp_str[0];
  // printf("Loadentity: %s\n", temp.sprite.img);

  sprite temp;
  int index = 0;
  size_t i = 1;

  string tmp_str = "";

  for (; i <= sprite_count; i++) {
    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.ID = atoi(tmp_str.c_str());
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.name = tmp_str;
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.img = tmp_str;
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.x = atoi(tmp_str.c_str());
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.y = atoi(tmp_str.c_str());
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.w = atoi(tmp_str.c_str());
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.h = atoi(tmp_str.c_str());
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.offset_x = atoi(tmp_str.c_str());
    index++;

    tmp_str = GetDataFromReadline(sprite_lines[index]);
    temp.offset_y = atoi(tmp_str.c_str());
    index++;

    GameState.SpriteList.push_back(temp);
  }
  cout << "this happend 1" << endl;
}

inline void LoadEntityData(game_state & GameState, int entity_count) {
  //------
  // entity sprite ID : [0]
  // entity sprite filename : []
  // entity sprite x : [0]
  // entity sprite y : [0]
  // entity sprite w : [64]
  // entity sprite h : [32
  //------

  // strcpy(temp.sprite.img, &tmp_str[0]);
  // temp.sprite.img = &tmp_str[0];
  // printf("Loadentity: %s\n", temp.sprite.img);

  entity temp;

  int index = 0;
  size_t i = 1;

  string tmp_str = "";
  int tempSpriteID;

  for (; i <= entity_count; i++) {
    tmp_str = GetDataFromReadline(entity_lines[index]);
    temp.ID = atoi(tmp_str.c_str());  // entity ID : [n]
    index++;

    // tmp_str = GetDataFromReadline(entity_lines[index]);
    // temp.x = atoi(tmp_str.c_str());;
    // index++;

    // tmp_str = GetDataFromReadline(entity_lines[index]);
    // temp.y = atoi(tmp_str.c_str());
    // index++;

    tmp_str = GetDataFromReadline(entity_lines[index]);
    temp.w = atoi(tmp_str.c_str());  // entity w : [n]
    index++;

    tmp_str = GetDataFromReadline(entity_lines[index]);
    temp.h = atoi(tmp_str.c_str());  // entity h : [n]
    index++;

    tmp_str = GetDataFromReadline(entity_lines[index]);
    tempSpriteID = atoi(tmp_str.c_str());  // entity sprite ID : [n]

    setSprite(GameState.SpriteList,&temp, tempSpriteID);

    index++;

    temp.entity_tile = {(float)temp.x, (float)temp.y, (float)tile_width,
                        (float)tile_height};

    GameState.EntityList.push_back(temp);
  }
}

inline int ReadEntityData(string path) {
  int temp_entity_count = 0;

  entity_lines.clear();

  string entity_divider = "------";

  string comment_token = "#";

  string line;

  int divider_count = 0;

  ifstream myfile(path);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      if (line.find(comment_token) == string::npos) {
        if (line.find(entity_divider) == string::npos) {
          entity_lines.push_back(line);

        } else {
          divider_count++;
        }
      } else {
        //	cout << line << endl;
      }
    }

    myfile.close();
  } else {
    printf("Unable to open file\n");
  }

  temp_entity_count = divider_count / 2;

  return temp_entity_count;
}

inline bool ReadMapData(string path) {
  // string map_path = path + "map1.txt";

  bool success = false;

  string entity_divider = "------";

  string comment_token = "#";

  string line;

  int divider_count = 0;

  map_lines.clear();

  ifstream myfile(path);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      if (line.find(comment_token) == string::npos) {
        if (line.find(entity_divider) == string::npos) {
          map_lines.push_back(line);
        } else {
          divider_count++;
        }
      } else {
        //	cout << line << endl;
      }
    }

    myfile.close();
    success = true;
  } else {
    printf("Unable to open file\n");
  }

  for (size_t i = 0; i < map_lines.size(); i++) {
    cout << map_lines[i] << endl;
  }

  return success;
}

inline bool ReadMapDataTiledMap(string path) {
  // string map_path = path + "map1.txt";

  bool success = false;

  string entity_divider = "------";

  string comment_token = "<";

  string line;

  string eof = "</map>";

  int divider_count = 0;

  int line_count = 0;

  map_tiled_lines.clear();

  ifstream myfile(path);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      if (line.find(eof) != string::npos) {
        break;
      }

      if (line.find(comment_token) == string::npos) {
        // if (line.find(entity_divider) == string::npos)
        // {
        map_tiled_lines.push_back(line);
        line_count++;
        // }
        // else
        // {
        // 	divider_count++;
        // }
      } else {
        //	cout << line << endl;
      }
    }

    myfile.close();
    success = true;
  } else {
    printf("Unable to open file\n");
  }

  cout << "lines: " << map_tiled_lines.size() << endl;
  for (size_t i = 0; i < map_tiled_lines.size(); i++) {
    if (i % Y_TILES == 0 && i != 0) {
      cout << endl;
    }

    cout << map_tiled_lines[i] << endl;
  }

  return success;
}

inline void setMapCords(int layer) {
  for (size_t i = 0; i < map_lines.size(); i++) {
    // cout << "Data: " << GetDataFromReadlineTwo(map_lines[i]) << endl;
    GetDataFromReadlineThree(map_lines[i], layer);
  }
}

inline void setMapCordsTiled() {
  int layer = 0;

  row = 0;

  for (size_t i = 0; i < map_tiled_lines.size(); i++) {
    if (i % Y_TILES == 0 && i != 0) {
      cout << "layer: " << layer << endl;
      cout << "lines: " << map_tiled_lines.size() << endl;
      cout << "layer switch: " << i << endl;
      layer++;
      row = 0;
    }

    GetDataFromReadlineTiledMap(map_tiled_lines[i], layer);
  }
}
inline void setEntityCords(map & Map, vector<entity> & entity_list ,int layer) {
  cout << "Testing setEntityCords" << endl;

  entity temp;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      for (size_t k = 0; k < entity_list.size(); k++) {
        if (entity_list[k].ID == cords[i][j][layer]) {
          temp.ID = entity_list[k].ID;
          if (i % 2 == 0) {
            temp.x = (j * GAME_TILE_WIDTH);
            temp.y = (i * (GAME_TILE_HEIGHT / 2));
          } else {
            temp.x = (j * GAME_TILE_WIDTH) + (GAME_TILE_WIDTH / 2);
            temp.y = (i * (GAME_TILE_HEIGHT / 2));
          }

          temp.y = temp.y;

          temp.w = entity_list[k].w;
          temp.h = entity_list[k].h;
          temp.entity_tile = entity_list[k].entity_tile;
          temp.sprite = entity_list[k].sprite;

          temp.layer = layer;

          Map.EntityList.push_back(temp);
        }
      }
    }
  }
}

inline void setPosCords() {
  cout << "Testing setPosCords" << endl;

  for (size_t i = 0; i < Y_TILES; i++) {
    for (size_t j = 0; j < X_TILES; j++) {
      if (i % 2 == 0) {
        pos_cords[i][j].x = (j * 64);
        pos_cords[i][j].y = (i * 16);
      } else {
        pos_cords[i][j].x = (j * 64) + 32;
        pos_cords[i][j].y = (i * 16);
      }
    }
  }
}

inline void SetGuiEntities( vector<entity> & entity_list) {
  entity temp;

  for (size_t k = 0; k < entity_list.size(); k++) {
    // if (sprite_list[k].ID == 999) // Background
    //{
    //	cout << "ID == 29 found, background set, setGuiEntities" << endl;
    //
    //	temp.ID = 999;
    //	temp.x = 0;
    //	temp.y = 0;
    //	temp.w = sprite_list[k].w;
    //	temp.h = sprite_list[k].h;
    //	//temp.entity_tile = entity_list[k].entity_tile;
    //	temp.sprite = &sprite_list[k];

    //	gui_entity_list.push_back(temp);
    //}

    if (entity_list[k].ID == 7) {
      temp.ID = entity_list[k].ID;
      temp.x = 64;
      temp.y = 32;
      temp.w = entity_list[k].w;
      temp.h = entity_list[k].h;
      temp.entity_tile = entity_list[k].entity_tile;
      temp.sprite = entity_list[k].sprite;

      gui_entity_list.push_back(temp);

      cout << "target found, setGuiEntities" << endl;
    }

    if (entity_list[k].ID == 2)  // Grid
    {
      temp.ID = entity_list[k].ID;
      temp.x = 0;
      temp.y = 0;
      temp.w = entity_list[k].w;
      temp.h = entity_list[k].h;
      temp.entity_tile = entity_list[k].entity_tile;
      temp.sprite = entity_list[k].sprite;

      gui_entity_list.push_back(temp);

      cout << "ID == 2 found, Grid set, setGuiEntities" << endl;
    }

    // cout << " " << k << " ";
  }

  // cout << " " << endl;
}

inline void setPlayer(game_state & GameState) {
  entity temp;

  cout << "setPlayer start " << endl;

  temp.ID = 9;
  temp.x = 64;
  temp.y = 64;

  temp.w = 48;
  temp.h = 64;
  temp.entity_tile = {temp.x, temp.y, (float)GAME_TILE_WIDTH,
                      (float)GAME_TILE_HEIGHT};

  setSprite(GameState.SpriteList,&temp, 67);

  GameState.Map.EntityList.push_back(temp);

  // game_entity_list.push_back(&temp);

  // entity ID : [9] "Julius"
  // entity w : [48]
  // entity h : [64]
  // entity sprite ID : [67]

  // for (size_t k = 0; k < GameState.Map.EntityList.size(); k++)
  // {
  // 	cout << "setPlayer: " << GameState.Map.EntityList[k].ID << endl;

  // 	if (GameState.Map.EntityList[k].ID == player_entity_ID )
  // 	{

  // 		cout << "true setPlayer: "<< GameState.Map.EntityList[k].ID << endl;

  // 		game_entity_list.push_back(&GameState.Map.EntityList[k]);

  // 		GameState.Map.EntityList[k].render_this = true;
  // 	}
  // }
}

inline int ReadSpriteData(string path) {
  sprite_lines.clear();

  int sprite_count = -1;

  string entity_divider = "------";

  string comment_token = "#";

  string line;

  int divider_count = 0;

  ifstream myfile(path);

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      if (line.find(comment_token) == string::npos) {
        if (line.find(entity_divider) == string::npos) {
          sprite_lines.push_back(line);
        } else {
          divider_count++;
        }
      } else {
        //	cout << line << endl;
      }
    }

    myfile.close();
  } else {
    printf("Unable to open file\n");
  }

  sprite_count = divider_count / 2;

  return sprite_count;
}

inline int WriteEntityData( vector<entity> & entity_list,string path) {
  ofstream myfile(path);

  if (myfile.is_open()) {
    for (size_t i = 0; i < entity_list.size(); i++) {
      myfile << "------"
             << "\n";
      myfile << "entity ID : [" << entity_list[i].ID << "]"
             << "\n";
      myfile << "entity x : [" << entity_list[i].x << "]"
             << "\n";
      myfile << "entity y : [" << entity_list[i].y << "]"
             << "\n";
      myfile << "entity w : [" << entity_list[i].w << "]"
             << "\n";
      myfile << "entity h : [" << entity_list[i].h << "]"
             << "\n";

      myfile << "entity sprite ID : [" << entity_list[i].sprite->ID << "]"
             << "\n";
      //		myfile << "entity sprite filename : [" <<
      // entity_list[i].sprite.img << "]" << "\n"; 		myfile <<
      // "entity sprite x :
      //[" << entity_list[i].sprite.x << "]" << "\n"; 		myfile <<
      //"entity sprite y : [" << entity_list[i].sprite.y << "]" << "\n";
      // myfile << "entity sprite w : [" << entity_list[i].sprite.w << "]" <<
      // "\n"; 		myfile << "entity sprite h : [" <<
      // entity_list[i].sprite.h << "]" << "\n";

      myfile << "------"
             << "\n";
    }

    myfile.close();
    return 1;
  } else
    cout << "Unable to open file";
  return 0;
}

inline int WriteSpriteData(string path, vector<sprite>& sprite_list) {
  ofstream myfile(path);

  if (myfile.is_open()) {
    for (size_t i = 0; i < sprite_list.size(); i++) {
      myfile << "------"
             << "\n";
      myfile << "sprite ID : [" << sprite_list[i].ID << "]"
             << "\n";
      myfile << "sprite name : [" << sprite_list[i].name << "]"
             << "\n";
      myfile << "sprite filename : [" << sprite_list[i].img << "]"
             << "\n";
      myfile << "sprite x : [" << sprite_list[i].x << "]"
             << "\n";
      myfile << "sprite y : [" << sprite_list[i].y << "]"
             << "\n";
      myfile << "sprite w : [" << sprite_list[i].w << "]"
             << "\n";
      myfile << "sprite h : [" << sprite_list[i].h << "]"
             << "\n";
      myfile << "sprite offset_x: [" << sprite_list[i].offset_x << "]"
             << "\n";
      myfile << "sprite offset_y: [" << sprite_list[i].offset_y << "]"
             << "\n";

      myfile << "------"
             << "\n";
    }

    myfile.close();
    return 1;
  } else
    cout << "Unable to open file";
  return 0;
}

inline int WriteSpriteDataRaw(string file_path, vector<string> png_list,
                              vector<texture>& texture_list) {
  ofstream myfile(file_path);

  if (DEBUG_PRINT) {
    for (size_t i = 0; i < texture_list.size(); i++) {
      for (size_t j = 0; j < texture_list.size(); j++) {
        if (texture_list[j].path.find(png_list[i]) != std::string::npos) {
          cout << "WriteSpriteDataRaw 2:" << texture_list[j].path << endl;
        }
      }
    }
  }

  if (myfile.is_open()) {
    for (size_t i = 0; i < png_list.size(); i++) {
      myfile << "------"
             << "\n";
      myfile << "sprite ID : [" << i + 1 << "]"
             << "\n";
      myfile << "sprite name : ["
             << png_list[i].substr(0, png_list[i].length() - 4) << "]"
             << "\n";
      myfile << "sprite filename : [" << png_list[i] << "]"
             << "\n";
      myfile << "sprite x : [" << 0 << "]"
             << "\n";
      myfile << "sprite y : [" << 0 << "]"
             << "\n";
      myfile << "sprite w : [" << texture_list[i].tex.width << "]"
             << "\n";
      myfile << "sprite h : [" << texture_list[i].tex.height << "]"
             << "\n";
      myfile << "sprite offset_x: [" << 0 << "]"
             << "\n";
      myfile << "sprite offset_y: [" << 0 << "]"
             << "\n";
      myfile << "------"
             << "\n";
    }

    myfile.close();
    return 1;
  } else
    cout << "Unable to open file";
  return 0;
}
