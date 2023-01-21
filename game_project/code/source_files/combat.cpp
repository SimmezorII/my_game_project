#pragma once

#ifndef combat_cpp
#define combat_cpp


#include <iostream>
#include "../header_files/raylib.h"
#include "../header_files/globals.h"
#include "game_engine.cpp"



using namespace std;

static field position_field;

static field spawn_field;

/////----------------------------------------------------------------------------------------------------

inline void setSquareField(field &fieldRef, int nx, int ny)
{
	int targetRange = fieldRef.range;

	int	fx = nx - (tile_width / 2);
	int fy = ny + (tile_height / 2);

	int	row = 0;
	int	line = 0;

	int	x = 0;
	int	y = 0;

	int	n = 1;
	int	m = 1;

	int	numRect = 0;
	int tilecount = 0;

	int start = 0;

	int sum1 = (targetRange - 1) * (targetRange - 1);
	int sum2 = (targetRange*targetRange);

	int fieldx = 0;
	int fieldy = 0;


	fieldRef.sum_of_field_tiles = sum1 + sum2;

	for (int i = 0; i < sum1; i++) {

		//cout << "i:" << i << endl;

		if (numRect == (n*n))
		{
			n += 1;
			row += 1;
		}

		x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
		y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

		//field.fieldRects[i] = [x, y]

		fieldRef.tiles[i].w = tile_width;
		fieldRef.tiles[i].h = tile_height;

		fieldRef.tiles[i].x = x;
		fieldRef.tiles[i].y = y;

		if (i == 0) {

			fieldy = fieldRef.tiles[i].y;
			fieldx = fieldRef.tiles[i].x;

		}
		else
		{
			if (fieldRef.tiles[i].y < fieldy)
			{
				fieldy = fieldRef.tiles[i].y;
			}

			if (fieldRef.tiles[i].x < fieldx)
			{
				fieldx = fieldRef.tiles[i].x;
			}

		}

		//	cout << "fieldtile y: "<<fieldRef.tiles[i].y << endl;
		//	cout << "fieldtile x: " << fieldRef.tiles[i].x << endl;

		fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

		tilecount += 1;
		numRect += 1;
	}

	numRect = 0;

	start = sum1;


	while (start < (sum1 + sum2))
	{
		if (numRect == (m*m))
		{
			m += 1;
			line += 1;
		}

		x = fx + ((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2));
		y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

		fieldRef.tiles[start].w = tile_width;
		fieldRef.tiles[start].h = tile_height;

		fieldRef.tiles[start].x = x;
		fieldRef.tiles[start].y = y;


		//	cout << "fieldtile y: " << fieldRef.tiles[start].y << endl;
		//	cout << "fieldtile x: " << fieldRef.tiles[start].x << endl;

		if (fieldRef.tiles[start].y < fieldy)
		{
			fieldy = fieldRef.tiles[start].y;
		}

		if (fieldRef.tiles[start].x < fieldx)
		{
			fieldx = fieldRef.tiles[start].x;
		}


		fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

		tilecount += 1;
		numRect += 1;
		start += 1;
	}

	fieldRef.x = fieldx + 32;
	fieldRef.y = fieldy + 16;
	fieldRef.w = (64 * (targetRange - 1));
	fieldRef.h = (32 * (targetRange - 1));

}

inline void setInverseSquareField(field &fieldRef, int nx, int ny)
{
	int targetRange = fieldRef.range;

	int	fx = nx;
	int fy = ny + (targetRange - 1) * up_vel;

	int	row = 0;
	int	line = 0;

	int	x = 0;
	int	y = 0;

	int	n = 1;
	int	m = 1;

	int	numRect = 0;
	int tilecount = 0;

	int start = 0;

	int sum1 = (targetRange*targetRange);

	int sum2 = ((targetRange-1) *(targetRange - 1));

	int fieldx = 0;
	int fieldy = 0;

	fieldRef.sum_of_field_tiles = sum1;

	int count = 0;
	
	for (size_t i = 0; i < targetRange; i++)
	{
	

		for (size_t j = 0; j < targetRange; j++)
		{
			fieldRef.tiles[count].x = ((right_vel * 1) * i) + fx +(left_vel * j);
			fieldRef.tiles[count].y = ((down_vel * 1) * i) + fy + ((down_vel * 1) * j);

			count++;

		}
	}


	for (size_t i = 0; i < fieldRef.sum_of_field_tiles; i++)
	{
		fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

		fieldRef.tiles[i].w = tile_width;
		fieldRef.tiles[i].h = tile_height;

	}


}

inline void setTriangleField(field &fieldRef, int nx, int ny, Direction dir)
{
	int targetRange = fieldRef.range;

	int	fx = 0;
    int fy = 0;

	int	row = 0;
	int	line = 0;

	int	x = 0;
	int	y = 0;

	int	n = 1;
	int	m = 1;

	int	numRect = 0;
	int tilecount = 0;

	int start = 0;

	int sum1 = 0;
	int sum2 = 0;

	int fieldx = 0;
	int fieldy = 0;

	if (dir == UP)
	{

		fx = nx + right_vel;
		fy = ny + down_vel;


		//int sum1 = (targetRange - 1) * (targetRange - 1);
		sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + -1 * (((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2)));
			y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;
			start += 1;
		}

		fieldRef.x = fieldx + 32;
		fieldRef.y = fieldy + 16;
		fieldRef.w = (64 * (targetRange - 1));
		fieldRef.h = (32 * (targetRange - 1));

	}

	if (dir == DOWN)
	{

		fx = nx + left_vel;
		fy = ny + up_vel;


		//int sum1 = (targetRange - 1) * (targetRange - 1);
		sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + 1 * (((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2)));
			y = fy + -1 * (((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2)));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;
			start += 1;
		}

		fieldRef.x = fieldx + 32;
		fieldRef.y = fieldy + 16;
		fieldRef.w = (64 * (targetRange - 1));
		fieldRef.h = (32 * (targetRange - 1));

	}

	if (dir == RIGHT) 
	{
		fx = nx - (tile_width / 2);
		fy = ny + (tile_height / 2);

		 sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {


			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;

			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}


			//	cout << "fieldtile y: "<<fieldRef.tiles[i].y << endl;
			//	cout << "fieldtile x: " << fieldRef.tiles[i].x << endl;


			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);


			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;


		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + ((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2));
			y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;


			//	cout << "fieldtile y: " << fieldRef.tiles[start].y << endl;
			//	cout << "fieldtile x: " << fieldRef.tiles[start].x << endl;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}


			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;
			start += 1;
		}

		fieldRef.x = fieldx + 32;
		fieldRef.y = fieldy + 16;
		fieldRef.w = (64 * (targetRange - 1));
		fieldRef.h = (32 * (targetRange - 1));

	
	}

	if (dir == LEFT)
	{

		fx = nx + left_vel;
		fy = ny + down_vel;

		sum1 = (targetRange) * (targetRange);
		//sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + ((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2));
			y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

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

inline void setConeField(field &fieldRef, int nx, int ny, Direction dir)
{
	int targetRange = fieldRef.range;

	int	fx = 0;
	int fy = 0;

	int	row = 0;
	int	line = 0;

	int	x = 0;
	int	y = 0;

	int	n = 1;
	int	m = 1;

	int	numRect = 0;
	int tilecount = 0;

	int start = 0;

	int sum1 = 0;
	int sum2 = 0;

	int fieldx = 0;
	int fieldy = 0;

	numRect = 0;

	start = 0;


	if( dir == LEFT)
	{

		fx = nx - (tile_width / 2) + (left_vel * (targetRange - 1));
		fy = ny + (tile_height / 2) + (down_vel * (targetRange - 1));


		//int sum1 = (targetRange - 1) * (targetRange - 1);
		sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + ((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2));
			y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;
			start += 1;
		}

		fieldRef.x = fieldx + 32;
		fieldRef.y = fieldy + 16;
		fieldRef.w = (64 * (targetRange - 1));
		fieldRef.h = (32 * (targetRange - 1));

	}

	if (dir == RIGHT)
	{

		fx = nx - (tile_width / 2) + (right_vel * (targetRange - 1));
		fy = ny + (tile_height / 2) + (up_vel * (targetRange - 1));

	    sum1 = (targetRange ) * (targetRange );
		//sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + ((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2));
			y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;
			start += 1;
		}

		fieldRef.x = fieldx + 32;
		fieldRef.y = fieldy + 16;
		fieldRef.w = (64 * (targetRange - 1));
		fieldRef.h = (32 * (targetRange - 1));

	}

	if (dir == UP)
	{

		fx = nx + left_vel + (left_vel * (targetRange - 1));
		fy = ny + up_vel + (up_vel * (targetRange - 1));


		//int sum1 = (targetRange - 1) * (targetRange - 1);
		sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + 1 * (( (tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2)));
			y = fy + -1 * (((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2)));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;
			start += 1;
		}

		fieldRef.x = fieldx + 32;
		fieldRef.y = fieldy + 16;
		fieldRef.w = (64 * (targetRange - 1));
		fieldRef.h = (32 * (targetRange - 1));

	}

	if (dir == DOWN)
	{

		fx = nx + right_vel+ (right_vel * (targetRange - 1));
		fy = ny + down_vel+ (down_vel * (targetRange - 1));


		//int sum1 = (targetRange - 1) * (targetRange - 1);
		sum2 = (targetRange*targetRange);

		fieldRef.sum_of_field_tiles = sum1 + sum2;

		for (int i = 0; i < sum1; i++) {

			//cout << "i:" << i << endl;

			if (numRect == (n*n))
			{
				n += 1;
				row += 1;
			}

			x = (tile_width)+fx - ((tile_width / 2) * (i)) + row * ((tile_width / 2) * row) + (row * tile_width) - (targetRange * (tile_width / 2));
			y = (-tile_height) + fy - ((tile_height / 2) * (i)) + row * ((tile_height / 2) * row) + (targetRange * (tile_height / 2));

			fieldRef.tiles[i].w = tile_width;
			fieldRef.tiles[i].h = tile_height;

			fieldRef.tiles[i].x = x;
			fieldRef.tiles[i].y = y;

			if (i == 0) {
				fieldy = fieldRef.tiles[i].y;
				fieldx = fieldRef.tiles[i].x;
			}
			else
			{
				if (fieldRef.tiles[i].y < fieldy)
				{
					fieldy = fieldRef.tiles[i].y;
				}

				if (fieldRef.tiles[i].x < fieldx)
				{
					fieldx = fieldRef.tiles[i].x;
				}

			}

			fieldRef.tiles[i].sprite = &getSprite(GREEN_TILE);

			tilecount += 1;
			numRect += 1;

		}

		numRect = 0;

		start = sum1;

		while (start < (sum1 + sum2))
		{
			if (numRect == (m*m))
			{
				m += 1;
				line += 1;
			}

			x = fx + -1 * (((tile_width / 2) * (start - sum1)) - line * ((tile_width / 2) * line) - (line * tile_width) + (targetRange * (tile_width / 2)));
			y = fy + ((tile_height / 2) * (start - sum1)) - line * ((tile_height / 2) * line) - (targetRange * (tile_height / 2));

			fieldRef.tiles[start].w = tile_width;
			fieldRef.tiles[start].h = tile_height;

			fieldRef.tiles[start].x = x;
			fieldRef.tiles[start].y = y;

			if (fieldRef.tiles[start].y < fieldy)
			{
				fieldy = fieldRef.tiles[start].y;
			}

			if (fieldRef.tiles[start].x < fieldx)
			{
				fieldx = fieldRef.tiles[start].x;
			}

			fieldRef.tiles[start].sprite = &getSprite(GREEN_TILE);

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

inline void setField(field &fieldRef, int nx, int ny, int field_type)
{

	if (field_type == SQUARE)
	{
		setSquareField(fieldRef, nx, ny);
	}

	if (field_type == NON_ISO_SQUARE)
	{
		setInverseSquareField(fieldRef, nx, ny);
	}

	if (field_type == TRIANGLE + UP)
	{
		setTriangleField(fieldRef, nx, ny, UP);
	}

	if (field_type == TRIANGLE + DOWN)
	{
		setTriangleField(fieldRef, nx, ny, DOWN);
	}

	if (field_type == TRIANGLE + LEFT)
	{
		setTriangleField(fieldRef, nx, ny, LEFT);
	}

	if (field_type == TRIANGLE + RIGHT)
	{
		setTriangleField(fieldRef, nx, ny, RIGHT);
	}

	if (field_type == CONE + UP)
	{
		setConeField(fieldRef, nx, ny, UP);
	}


	if (field_type == CONE + DOWN)
	{
		setConeField(fieldRef, nx, ny, DOWN);
	}


	if (field_type == CONE + LEFT)
	{
		setConeField(fieldRef, nx, ny, LEFT);
	}

	if (field_type == CONE + RIGHT)
	{
		setConeField(fieldRef, nx, ny, RIGHT);
	}

}

inline void initCombat()
{
	//Log("InitCombat");

	gui_entity_list[0].render_this = true;

	world_player.pEntity->render_this = false;

	//target->render_this = true;

	//setField(position_field, 512, 512, TRIANGLE + UP);

	position_field.range = 5;

	setField(position_field, 512, 512, NON_ISO_SQUARE);
}

inline void SelectStartingTile()
{
	int pos_tile_num = 10;

	for (size_t i = 0; i < pos_tile_num; i++)
	{

	}
}




#endif