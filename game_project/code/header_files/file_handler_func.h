#pragma once

#if !defined(FILE_HANDLER_FUNC)

#include <string>
#include <iostream>
#include <fstream>

#include "../header_files/raylib.h"
#include "../header_files/globals.h"

using namespace std;



inline int WriteEntityDataSingle(entity e, string path) {

	ofstream myfile(path, std::ios::app);

	if (myfile.is_open())
	{	
		myfile << "------" << "\n";
		myfile << "entity ID : [" << e.ID << "]" << "\n";
		myfile << "entity w : [" << e.w << "]" << "\n";
		myfile << "entity h : [" << e.h << "]" << "\n";
		myfile << "entity sprite ID : [" << e.sprite->ID << "]" << "\n";

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




inline int WriteUpdatedMap( string path) {

	//ofstream myfile(path, std::ios::app); // adds edits to existing file

	ofstream myfile(path);

	string temp = "";

	if (myfile.is_open())
	{
		myfile << "Map2" << "\n";
		myfile << "------" << "\n";

		for (size_t i = 0; i < 40; i++)
		{
			for (size_t j = 0; j < 20; j++)
			{
				if (to_string(cords[i][j]).size() == 1)
				{
					temp = "00";
					temp.append(to_string(cords[i][j]));

					myfile << "[" << temp << "]";
				}
				else if ((to_string(cords[i][j]).size() == 2))
				{
					temp = "0";
					temp.append(to_string(cords[i][j]));

					myfile << "[" << temp << "]";
				}
				else 
				{
					myfile << "[" << cords[i][j] << "]";
				}

			}

			if (i % 2 == 0) 
			{
				myfile << "\n  ";
			}
			else
			{
				myfile << "\n";
			}
	
		}


		myfile << "------" << "\n";
		myfile << "------" << "\n";
		myfile << "END" << "\n";

		myfile.close();
		return 1;
	}
	else cout << "Unable to open file";
	return 0;

}





inline sprite& getSpriteEx(int sprite_ID) {

	for (size_t i = 0; i < sprite_list.size(); i++)
	{
		if (sprite_list[i].ID == sprite_ID)
		{
			//cout << "Sprite found " << sprite_list[i].img << endl;

			return sprite_list[i];
			break;
		}
	}

	return sprite_list[0];
}







#define FILE_HANDLER_FUNC
#endif
