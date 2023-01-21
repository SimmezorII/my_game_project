#pragma once

#if !defined(GAME_ENGINE_FUNC)
/* ========================================================================

======================================================================== */

#include <string>
#include <iostream>
#include <fstream>

#include "../header_files/raylib.h"
#include "../header_files/globals.h"

using namespace std;

inline void Log(string text, float value)
{
	if (currentline_log != 0)
	{
		if (log_lines[currentline_log - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}
	else
	{
		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}


	if (currentline_log >= 100)
	{
		logreset++;
		currentline_log = 0;
	}

	//tempint = currentline_log;
}


inline void Log(string text, int value)
{
	if (currentline_log != 0)
	{
		if (log_lines[currentline_log - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}
	else
	{
		log_lines[currentline_log] = text;
		log_lines[currentline_log].append(to_string(value));

		currentline_log++;
	}


	if (currentline_log >= 100)
	{
		logreset++;
		currentline_log = 0;
	}

	//tempint = currentline_log;
}

inline void Log(string text)
{
	if (currentline_log != 0)
	{
		if (log_lines[currentline_log - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		log_lines[currentline_log] = text;


		currentline_log++;
	}
	else
	{
		log_lines[currentline_log] = text;


		currentline_log++;
	}


	if (currentline_log >= 100)
	{
		logreset++;
		currentline_log = 0;
	}

	//tempint = currentline_log;
}



inline void DebugLog(string text)
{
	bool stringfound = false;
	int tempindex = -1;

	if (currentline_debuglog != 0)
	{
		for (size_t i = 0; i < currentline_debuglog; i++)
		{
			if (debuglog_lines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			debuglog_lines[tempindex] = text;
		}
		else
		{
			debuglog_lines[currentline_debuglog] = text;
			currentline_debuglog++;
		}

	}
	else
	{
		debuglog_lines[currentline_debuglog] = text;
		currentline_debuglog++;
	}


}

inline void DebugLog(string text, float value)
{
	bool stringfound = false;
	int tempindex = -1;

	if (currentline_debuglog != 0)
	{
		for (size_t i = 0; i < currentline_debuglog; i++)
		{
			if (debuglog_lines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			debuglog_lines[tempindex] = text;
			debuglog_lines[tempindex].append(to_string(value));
		}
		else
		{
			debuglog_lines[currentline_debuglog] = text;
			debuglog_lines[currentline_debuglog].append(to_string(value));
			currentline_debuglog++;
		}

	}
	else
	{
		debuglog_lines[currentline_debuglog] = text;
		debuglog_lines[currentline_debuglog].append(to_string(value));
		currentline_debuglog++;
	}


}


inline void DebugLog(string text, int value)
{
	bool stringfound = false;
	int tempindex = -1;

	if (currentline_debuglog != 0)
	{
		for (size_t i = 0; i < currentline_debuglog; i++)
		{
			if (debuglog_lines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			debuglog_lines[tempindex] = text;
			debuglog_lines[tempindex].append(to_string(value));
		}
		else
		{
			debuglog_lines[currentline_debuglog] = text;
			debuglog_lines[currentline_debuglog].append(to_string(value));
			currentline_debuglog++;
		}

	}
	else
	{
		debuglog_lines[currentline_debuglog] = text;
		debuglog_lines[currentline_debuglog].append(to_string(value));
		currentline_debuglog++;
	}


}




#define GAME_ENGINE_FUNC
#endif
