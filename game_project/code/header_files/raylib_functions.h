
#pragma once
#if !defined(RAYLIB_FUNCTIONS_H)
/* ========================================================================
 Some of the functions cannot be found even if they are included
======================================================================== */
#include "globals.h"



// Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
inline bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold)
{
	bool collision = false;
	float dxc = point.x - p1.x;
	float dyc = point.y - p1.y;
	float dxl = p2.x - p1.x;
	float dyl = p2.y - p1.y;
	float cross = dxc * dyl - dyc * dxl;

	if (fabsf(cross) < (threshold*fmaxf(fabsf(dxl), fabsf(dyl))))
	{
		if (fabsf(dxl) >= fabsf(dyl)) collision = (dxl > 0) ? ((p1.x <= point.x) && (point.x <= p2.x)) : ((p2.x <= point.x) && (point.x <= p1.x));
		else collision = (dyl > 0) ? ((p1.y <= point.y) && (point.y <= p2.y)) : ((p2.y <= point.y) && (point.y <= p1.y));
	}

	return collision;
}





#define RAYLIB_FUNCTIONS_H
#endif
#pragma once
