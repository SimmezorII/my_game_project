
#pragma once
#if !defined(RAYLIB_FUNCTIONS_H)
/* ========================================================================
 Some of the functions cannot be found even if they are included
======================================================================== */
#include "globals.h"


#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION            // Avoid including raygui implementation again




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


 Rectangle LogInfoRect = { 0 , 0 , 100, 16 };

 Rectangle ScrollBar = { 8 , GAMEWINDOW_HEIGHT - 200 - 16, 10, 16 * 11 };


inline void RenderLog()
{
	LogInfoRect.x = 20;

	LogInfoRect.y = GAMEWINDOW_HEIGHT - 200;

	int rendernum = 0;

	for (size_t i = log_lines.size(); i-- > 0; )
	{
		if (rendernum < currentline_log)
		{
			// Render only 11 lines at the time, as it scrolls
			if (rendernum < 89) {

				if (rendernum > 89 - LogScrollCounter - 1)
				{
					GuiLabel({ LogInfoRect.x, LogInfoRect.y + ((i - LogScrollCounter) * LogInfoRect.height) - (LogInfoRect.height * 1), LogInfoRect.width, LogInfoRect.height }, log_lines[(currentline_log - 1 - rendernum)].c_str());
					rendernum++;
				}
				else
				{
					rendernum++;
				}

			}
			else
			{
				//GuiLabel({ LogInfoRect.x, LogInfoRect.y + ((i - LogScrollCounter) * LogInfoRect.height) - (LogInfoRect.height * 1), LogInfoRect.width, LogInfoRect.height }, log_lines[(currentline_log - 1 - rendernum)].c_str());

				rendernum++;
			}
		}
	}

	//LogScrollCounter = GuiScrollBar(ScrollBar, LogScrollCounter, 100 - currentline_log, 89);

}





#define RAYLIB_FUNCTIONS_H
#endif
#pragma once
