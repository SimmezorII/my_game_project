#include <string>
#include <iostream>
#include <fstream>

#include "raylib.h"
#include "code/header_files/globals.h"



using namespace std;


inline void ReadAllFilesInDir(const char * path)
{
	int count = 0;

	char **DirectoryFiles;

	char empty1[] = ".";
	char empty2[] = "..";

	if (DirectoryExists(path)) {
		
		//printf("Directory exists\n");


		DirectoryFiles = GetDirectoryFiles(path, &count);

		//printf("%d\n", count);

		for (size_t i = 0; i < count; i++)
		{

			if ( (strcmp(DirectoryFiles[i],empty1) == 0)  || (strcmp(DirectoryFiles[i], empty2) == 0))
			{
					// Do nothing with . and .. paths
			}
			else {

				printf("%s\n", DirectoryFiles[i]);
			}

			
		}



	}
	else 
	{
		printf("Directory does not exist\n");
	}

	ClearDirectoryFiles();
}


inline vector <string> GetPNG_FilesInDir(const char * path)
{

	vector <  string > png_list;

	all_png_list = "";

	int count = 0;

	char **DirectoryFiles;

	char empty1[] = ".";
	char empty2[] = "..";

	if (DirectoryExists(path)) {

		//printf("Directory exists\n");


		DirectoryFiles = GetDirectoryFiles(path, &count);

		//printf("%d\n", count);

		for (size_t i = 0; i < count; i++)
		{

			if ((strcmp(DirectoryFiles[i], empty1) == 0) || (strcmp(DirectoryFiles[i], empty2) == 0))
			{
				// Do nothing with . and .. paths
			}
			else 
			{

				if (IsFileExtension(DirectoryFiles[i], ".png")){
					
					png_list.push_back(DirectoryFiles[i]);


					if (!all_png_list.compare(""))
					{
						all_png_list = all_png_list + DirectoryFiles[i];
					}
					else 
					{
						all_png_list = all_png_list + ";" + DirectoryFiles[i] ;
					}
					

				}
				else 
				{
				
				}

			}
		}



	}
	else
	{
		printf("Directory does not exist\n");
	}

	ClearDirectoryFiles();

	printf("Png list: %s\n", all_png_list.c_str());

	return png_list;
}

inline void AddIntegerFromString(vector <string> *LinesInFile,string str)
{

	size_t i = 0;

	for (; i < str.length(); i++) 
	{ 
		if (isdigit(str[i]))
			break; 
	}

	str = str.substr(i, (str.length()-1) - i);

	if (str != "") {
		LinesInFile->push_back(str);
	}
	else {

	}

}

inline int GetIntegerFromString( string str)
{

	size_t i = 0;

	for (; i < str.length(); i++)
	{
		if (isdigit(str[i]))
			break;
	}

	str = str.substr(i, (str.length() - 1) - i);

	if (str != "") {
		return stoi(str);
	}
	else {
		return -1;
	}

}

inline int GetIntegerFromStringTwo(string str)
{

	size_t i = 0;

	for (; i < str.length(); i++)
	{
		if (isdigit(str[i]))
			break;
	}

	str = str.substr(i, (str.length() - 1) - i);

	if (str != "") {
		return stoi(str);
	}
	else {
		return -1;
	}

}

inline string GetDataFromReadline(string line)
{

	// entity sprite w:	[64] <-- example this functions reads and returns what is inside []

	string start = "["; 
	
	string end = "]";

	size_t start_at = line.find(start);

	if (start_at != string::npos) {
		//cout << "[ occurrence is " << start_at << endl;
	}
	else {
		start_at = -1;
	}

	size_t end_at = line.find(end);

	if (end_at != string::npos) {
		//cout << "] occurrence is " << end_at << endl;
	}
	else {
		end_at = 0;
	}

	if (line != "") {
		line = line.substr(start_at + 1, (end_at-1 - start_at));
	}


	return line;

}

inline string GetDataFromReadlineTwo(string line)
{

	// entity sprite w:	[64] <-- example this functions reads and returns what is inside []

	string start = "[";

	string end = "]";

	size_t start_at = line.find(start);

	if (start_at != string::npos) {
		//cout << "[ occurrence is " << start_at << endl;
	}
	else {
		start_at = -1;
	}

	size_t end_at = line.find(end);

	if (end_at != string::npos) {
		//cout << "] occurrence is " << end_at << endl;
	}
	else {
		end_at = 0;
	}

	if (line != "") {
		line = line.substr(start_at + 1, (end_at - 1 - start_at));
	}


	return line;

}



global_variable string string_cords[40][20];

global_variable int cords[40][20];

global_variable int row = 0;

inline string GetDataFromReadlineThree(string line)
{

	// entity sprite w:	[64] <-- example this functions reads and returns what is inside []

	size_t loop;

	string temp = "";

	string start = "[";

	string end = "]";

	size_t start_at = line.find(start);

	//line.find_last_of(start);

	if (start_at != string::npos) {
		//cout << "[ occurrence is " << start_at << endl;
	}
	else {

		start_at = -1;
	}

	size_t end_at = line.find(end);

	if (end_at != string::npos) {
		//cout << "] occurrence is " << end_at << endl;
	}
	else {
		end_at = 0;
	}

	if (line != ""  && start_at != -1) {

	 	//cout << "line size " << line.size() << endl;

		loop = (line.size() - start_at) / (end_at - start_at + 1);

		//cout << "loop " << loop << endl;

		string_cords[row][0] = (line.substr(start_at + 1, (end_at - 1 - start_at)));

		cords[row][0] = stoi(string_cords[row][0]);

		temp = line.substr((end_at + 1), line.size());


		for (size_t i = 1; i < loop; i++)
		{

			start_at = temp.find(start);

			//line.find_last_of(start);

			if (start_at != string::npos) {
				//cout << "[ occurrence is " << start_at << endl;
			}
			else {

				start_at = -1;
			}

			end_at = temp.find(end);

			if (end_at != string::npos) {
				//cout << "] occurrence is " << end_at << endl;
			}
			else {
				end_at = 0;
			}

			string_cords[row][i] = (temp.substr(start_at + 1, (end_at - 1 - start_at)));

			cords[row][i] = stoi(string_cords[row][i]);

			temp = temp.substr((end_at + 1), temp.size());

		}

		row++;
	}
	

	return line;

}



inline string GetPropertyNameFromReadline(string line)
{

	// entity sprite w:	[64] <-- example this functions reads and returns "entity sprite w:"

	string end = ":";

	size_t start_at = -1;


	size_t end_at = line.find(end);

	if (end_at != string::npos) {
		//cout << "] occurrence is " << end_at << endl;
	}
	else {
		end_at = 0;
	}

	if (line != "") {
		line = line.substr(start_at + 1, (end_at - 1 - start_at));
	}


	return line;

}

inline void setSprite(entity *e, int ID) {

//	printf("Searching for: %d \n", ID);
	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		//printf("Compare: %d vs %d \n", sprite_list[i].ID, ID);

		if (sprite_list[i].ID == ID)
		{
			e->sprite = &sprite_list[i];
			
		//	printf("Match! %s\n", sprite_list[i].img.c_str());
			break;
		}
		else 
		{
		//	printf("Didn't find: %d \n", ID);
		}
	}



}




inline void LoadSpriteData(int sprite_count){

		//------
		//entity sprite ID : [0]
		//entity sprite filename : []
		//entity sprite x : [0]
		//entity sprite y : [0]
		//entity sprite w : [64]
		//entity sprite h : [32
		//------	

		//strcpy(temp.sprite.img, &tmp_str[0]);
		//temp.sprite.img = &tmp_str[0];
		//printf("Loadentity: %s\n", temp.sprite.img);


	sprite temp;
	int index = 0;
	size_t i = 1;

	string tmp_str = "";

	for (; i <= sprite_count; i++)
	{

		tmp_str = GetDataFromReadline(sprite_lines[index]);
		temp.ID = atoi(tmp_str.c_str());
		index++;

		tmp_str = GetDataFromReadline(sprite_lines[index]);
		temp.name = tmp_str;
		index++;


		tmp_str = GetDataFromReadline(sprite_lines[index]);
		temp.img = tmp_str;
		index++;

		if (!sprite_png_list.compare(""))
		{
			sprite_png_list = sprite_png_list + tmp_str;

		}
		else
		{
			sprite_png_list = sprite_png_list + ";" + tmp_str;
		}



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
		
		sprite_list.push_back(temp);

	}
	cout << "this happend 1" << endl;
}

inline void LoadEntityData(int entity_count) {

	//------
	//entity sprite ID : [0]
	//entity sprite filename : []
	//entity sprite x : [0]
	//entity sprite y : [0]
	//entity sprite w : [64]
	//entity sprite h : [32
	//------	

	//strcpy(temp.sprite.img, &tmp_str[0]);
	//temp.sprite.img = &tmp_str[0];
	//printf("Loadentity: %s\n", temp.sprite.img);

	entity temp;

	int index = 0;
	size_t i = 1;

	string tmp_str = "";
	int tempSpriteID;

	for (; i <= entity_count; i++)
	{

		tmp_str = GetDataFromReadline(entity_lines[index]);
		temp.ID = atoi(tmp_str.c_str());
		index++;

		//tmp_str = GetDataFromReadline(entity_lines[index]);
		//temp.x = atoi(tmp_str.c_str());;
		//index++;

		//tmp_str = GetDataFromReadline(entity_lines[index]);
		//temp.y = atoi(tmp_str.c_str());
		//index++;

		tmp_str = GetDataFromReadline(entity_lines[index]);
		temp.w = atoi(tmp_str.c_str());
		index++;

		tmp_str = GetDataFromReadline(entity_lines[index]);
		temp.h = atoi(tmp_str.c_str());
		index++;

		tmp_str = GetDataFromReadline(entity_lines[index]);

		tempSpriteID = atoi(tmp_str.c_str());

		setSprite(&temp,tempSpriteID);

		index++;

		temp.entity_tile = { (float)temp.x,(float)temp.y, (float)tile_width, (float)tile_height };

		entity_list.push_back(temp);



	}

}

inline bool ReadEntityData(string path) {

	bool success = false;

	entity_lines.clear();

	string entity_divider = "------";

	string comment_token = "#";

	string line;

	int divider_count = 0;

	ifstream myfile(path);
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			if (line.find(comment_token) == string::npos) {


				if (line.find(entity_divider) == string::npos) {


					entity_lines.push_back(line);

				}

				else {
					divider_count++;
				}

			}
			else {
				//	cout << line << endl;

			}

		}


		myfile.close();
	}
	else
	{
		printf("Unable to open file\n");
	}

	//for (size_t i = 0; i < lines.size(); i++)
	//{

	//	cout << lines[i] << endl;
	//}


	entity_count = divider_count / 2;

	printf("entity count: %d \n", entity_count);


	LoadEntityData(entity_count);

	return success;


}

inline bool ReadMapData(string path) {

	//string map_path = path + "map1.txt";
	

	bool success = false;

	string entity_divider = "------";

	string comment_token = "#";

	string line;

	int divider_count = 0;


	map_lines.clear();

	ifstream myfile(path);
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			if (line.find(comment_token) == string::npos) {


				if (line.find(entity_divider) == string::npos) {


					map_lines.push_back(line);

				}

				else {
					divider_count++;
				}

			}
			else {
				//	cout << line << endl;

			}

		}


		myfile.close();
	}
	else
	{
		printf("Unable to open file\n");
	}


	for (size_t i = 0; i < map_lines.size(); i++)
	{

			cout << map_lines[i] << endl;
	}

	//entity_count = divider_count / 2;

	//printf("entity count: %d \n", entity_count);
	return success;


}

inline void setMapCords()
{

	for (size_t i = 0; i < map_lines.size(); i++)
	{
		//cout << "Data: " << GetDataFromReadlineTwo(map_lines[i]) << endl;
		GetDataFromReadlineThree(map_lines[i]);

	}

	//cout << "Cords: " << endl;

	//for (size_t j = 0; j < 40; j++)
	//{
	//	for (size_t i = 0; i < 20; i++)
	//	{
	//		cout << cords[j][i] << " ";
	//	}

	//	cout << endl;
	//}
}

inline void setEntityCords()
{

	cout << "Testing setEntityCords" << endl;
	//cords[39][20]

	entity temp;

	for (size_t i = 0; i < 40; i++)
	{
		for (size_t j = 0; j < 20; j++)
		{

			for (size_t k = 0; k < entity_list.size(); k++)
			{
				if (entity_list[k].ID == cords[i][j]) 
				{
					cout << "Found: " << cords[i][j] << endl;


					temp.ID = entity_list[k].ID;
					if (i % 2 == 0)
					{
						temp.x = (j * 64);
						temp.y = (i * 16);
					}
					else 
					{
						temp.x = (j * 64) + 32;
						temp.y = (i * 16);
					}

					temp.w = entity_list[k].w;
					temp.h = entity_list[k].h;
					temp.entity_tile = entity_list[k].entity_tile;
					temp.sprite = entity_list[k].sprite;

					map_entity_list.push_back(temp);
				}
			}

		
		}
	}
}

inline void setGuiEntities()
{
	entity temp;

	for (size_t k = 0; k < entity_list.size(); k++)
	{
		if (entity_list[k].ID == 1)
		{
			temp.ID = entity_list[k].ID;
			temp.x = 0;
			temp.y = 0;
			temp.w = entity_list[k].w;
			temp.h = entity_list[k].h;
			temp.entity_tile = entity_list[k].entity_tile;
			temp.sprite = entity_list[k].sprite;

			gui_entity_list.push_back(temp);
		}

		if (entity_list[k].ID == 7) 
		{
			cout << "target found" << endl;
			temp.ID = entity_list[k].ID;
			temp.x = 32;
			temp.y = 32;
			temp.w = entity_list[k].w;
			temp.h = entity_list[k].h;
			temp.entity_tile = entity_list[k].entity_tile;
			temp.sprite = entity_list[k].sprite;

			gui_entity_list.push_back(temp);
		}

	}
}

inline void setPlayer()
{
	entity temp;

	for (size_t k = 0; k < map_entity_list.size(); k++)
	{
		if (map_entity_list[k].ID == player_entity_ID || map_entity_list[k].ID == 8)
		{
			//temp.ID = map_entity_list[k].ID;
			//temp.x = 0;
			//temp.y = 0;
			//temp.w = map_entity_list[k].w;
			//temp.h = map_entity_list[k].h;
			//temp.entity_tile = map_entity_list[k].entity_tile;
			//temp.sprite = map_entity_list[k].sprite;

			game_entity_list.push_back(&map_entity_list[k]);

			map_entity_list[k].render_this = true;
		}
	}
}


inline bool ReadSpriteData(string path) {

	bool success = false;

	sprite_lines.clear();

	int sprite_count;

	string entity_divider = "------";

	string comment_token = "#";

	string line;

	int divider_count = 0;

	ifstream myfile(path);
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			if (line.find(comment_token) == string::npos) {


				if (line.find(entity_divider) == string::npos) {

					sprite_lines.push_back(line);
				}

				else {
					divider_count++;
				}

			}
			else {
				//	cout << line << endl;

			}
		}

		myfile.close();
	}
	else
	{
		printf("Unable to open file\n");
	}

	sprite_count = divider_count / 2;

	printf("sprite count: %d \n", sprite_count);

	LoadSpriteData(sprite_count);



	return success;
}

inline int WriteEntityDataSingle(entity e) {

	ofstream myfile("../assets/textfiles/game_data_temp.txt");
	if (myfile.is_open())
	{	
		myfile << "------" << "\n";
		myfile << "entity ID : [" << e.ID << "]" << "\n";
		myfile << "entity x : [" << e.x <<"]" << "\n";
		myfile << "entity y : [" << e.y << "]" << "\n";
		myfile << "entity w : [" << e.w << "]" << "\n";
		myfile << "entity h : [" << e.h << "]" << "\n";

//		myfile << "entity sprite ID : [" << e.sprite_ID << "]" << "\n";
//		myfile << "entity sprite filename : [" << e.sprite.img << "]" << "\n";
//		myfile << "entity sprite x : [" << e.sprite.x << "]" << "\n";
//		myfile << "entity sprite y : [" << e.sprite.y << "]" << "\n";
//		myfile << "entity sprite w : [" << e.sprite.w << "]" << "\n";
//		myfile << "entity sprite h : [" << e.sprite.h << "\n";

		myfile << "------" << "\n";


		myfile.close();
		return 1;
	}
	else cout << "Unable to open file";
	return 0;

}

inline int WriteEntityData(string path) {

	ofstream myfile(path);


	if (myfile.is_open())
	{


		for (size_t i = 0; i < entity_list.size(); i++)
		{

			myfile << "------" << "\n";
			myfile << "entity ID : [" << entity_list[i].ID << "]" << "\n";
			myfile << "entity x : [" << entity_list[i].x << "]" << "\n";
			myfile << "entity y : [" << entity_list[i].y << "]" << "\n";
			myfile << "entity w : [" << entity_list[i].w << "]" << "\n";
			myfile << "entity h : [" << entity_list[i].h << "]" << "\n";

			myfile << "entity sprite ID : [" << entity_list[i].sprite->ID << "]" << "\n";
	//		myfile << "entity sprite filename : [" << entity_list[i].sprite.img << "]" << "\n";
	//		myfile << "entity sprite x : [" << entity_list[i].sprite.x << "]" << "\n";
	//		myfile << "entity sprite y : [" << entity_list[i].sprite.y << "]" << "\n";
	//		myfile << "entity sprite w : [" << entity_list[i].sprite.w << "]" << "\n";
	//		myfile << "entity sprite h : [" << entity_list[i].sprite.h << "]" << "\n";

			myfile << "------" << "\n";

		}




		myfile.close();
		return 1;
	}
	else cout << "Unable to open file";
	return 0;

}

inline int WriteSpriteData(string path) {

	ofstream myfile(path);


	if (myfile.is_open())
	{


		for (size_t i = 0; i < sprite_list.size(); i++)
		{

			myfile << "------" << "\n";
			myfile << "sprite ID : [" << sprite_list[i].ID << "]" << "\n";
			myfile << "sprite name : [" << sprite_list[i].name << "]" << "\n";
		    myfile << "sprite filename : [" << sprite_list[i].img << "]" << "\n";
			myfile << "sprite x : [" << sprite_list[i].x << "]" << "\n";
			myfile << "sprite y : [" << sprite_list[i].y << "]" << "\n";
			myfile << "sprite w : [" << sprite_list[i].w << "]" << "\n";
			myfile << "sprite h : [" << sprite_list[i].h << "]" << "\n";
			myfile << "sprite offset_x: [" << sprite_list[i].offset_x << "]" << "\n";
			myfile << "sprite offset_y: [" << sprite_list[i].offset_y << "]" << "\n";

			myfile << "------" << "\n";

		}




		myfile.close();
		return 1;
	}
	else cout << "Unable to open file";
	return 0;

}
