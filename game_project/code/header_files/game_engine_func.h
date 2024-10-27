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

inline void Log( string text, float value)
{
	if (GAME_LOG.CurrentLineLog != 0)
	{
		if (GAME_LOG.LogLines[GAME_LOG.CurrentLineLog - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		GAME_LOG.LogLines[GAME_LOG.CurrentLineLog] = text;
		GAME_LOG.LogLines[GAME_LOG.CurrentLineLog].append(to_string(value));

		GAME_LOG.CurrentLineLog++;
	}
	else
	{
		GAME_LOG.LogLines[GAME_LOG.CurrentLineLog] = text;
		GAME_LOG.LogLines[GAME_LOG.CurrentLineLog].append(to_string(value));

		GAME_LOG.CurrentLineLog++;
	}


	if (GAME_LOG.CurrentLineLog >= 100)
	{
		GAME_LOG.LogReset++;
		GAME_LOG.CurrentLineLog = 0;
	}

	//tempint = GAME_LOG.CurrentLineLog;
}


inline void Log(string text, int value)
{
	if (GAME_LOG.CurrentLineLog != 0)
	{
		if (	GAME_LOG.LogLines[GAME_LOG.CurrentLineLog - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

			GAME_LOG.LogLines[GAME_LOG.CurrentLineLog] = text;
			GAME_LOG.LogLines[GAME_LOG.CurrentLineLog].append(to_string(value));

		GAME_LOG.CurrentLineLog++;
	}
	else
	{
			GAME_LOG.LogLines[GAME_LOG.CurrentLineLog] = text;
			GAME_LOG.LogLines[GAME_LOG.CurrentLineLog].append(to_string(value));

		GAME_LOG.CurrentLineLog++;
	}


	if (GAME_LOG.CurrentLineLog >= 100)
	{
		GAME_LOG.LogReset++;
		GAME_LOG.CurrentLineLog = 0;
	}

	//tempint = GAME_LOG.CurrentLineLog;
}

inline void Log( string text)
{
	if (GAME_LOG.CurrentLineLog != 0)
	{
		if (GAME_LOG.LogLines[GAME_LOG.CurrentLineLog - 1].find(text) != 0)
		{
			//log_lines[currentline] = text;
			//currentline++;
		}

		GAME_LOG.LogLines[GAME_LOG.CurrentLineLog] = text;


		GAME_LOG.CurrentLineLog++;
	}
	else
	{
		GAME_LOG.LogLines[GAME_LOG.CurrentLineLog] = text;


		GAME_LOG.CurrentLineLog++;
	}


	if (GAME_LOG.CurrentLineLog >= 100)
	{
		GAME_LOG.LogReset++;
		GAME_LOG.CurrentLineLog = 0;
	}

	//tempint = GAME_LOG.CurrentLineLog;
}



inline void DebugLog(string text)
{
	bool stringfound = false;
	int tempindex = -1;

	if (GAME_LOG.CurrentLineDebuglog != 0)
	{
		for (size_t i = 0; i < GAME_LOG.CurrentLineDebuglog; i++)
		{
			if (GAME_LOG.DebugLogLines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			GAME_LOG.DebugLogLines[tempindex] = text;
		}
		else
		{
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
			GAME_LOG.CurrentLineDebuglog++;
		}

	}
	else
	{
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
		GAME_LOG.CurrentLineDebuglog++;
	}


}

inline void DebugLog(string text, float value)
{
	bool stringfound = false;
	int tempindex = -1;

	if (GAME_LOG.CurrentLineDebuglog != 0)
	{
		for (size_t i = 0; i < GAME_LOG.CurrentLineDebuglog; i++)
		{
			if (GAME_LOG.DebugLogLines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			GAME_LOG.DebugLogLines[tempindex] = text;
			GAME_LOG.DebugLogLines[tempindex].append(to_string(value));
		}
		else
		{
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog].append(to_string(value));
			GAME_LOG.CurrentLineDebuglog++;
		}

	}
	else
	{
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog].append(to_string(value));
		GAME_LOG.CurrentLineDebuglog++;
	}


}


inline void DebugLog(string text, int value)
{
	bool stringfound = false;
	int tempindex = -1;

	if (GAME_LOG.CurrentLineDebuglog != 0)
	{
		for (size_t i = 0; i < GAME_LOG.CurrentLineDebuglog; i++)
		{
			if (GAME_LOG.DebugLogLines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			GAME_LOG.DebugLogLines[tempindex] = text;
			GAME_LOG.DebugLogLines[tempindex].append(to_string(value));
		}
		else
		{
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog].append(to_string(value));
			GAME_LOG.CurrentLineDebuglog++;
		}

	}
	else
	{
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog].append(to_string(value));
		GAME_LOG.CurrentLineDebuglog++;
	}


}


inline void DebugLog(string text, bool bValue)
{
	bool stringfound = false;
	int tempindex = -1;

	int value = -1;	
	if(bValue)
	{
		value = 1;
	}else 
	{
		value = 0;
	}

	if (GAME_LOG.CurrentLineDebuglog != 0)
	{
		for (size_t i = 0; i < GAME_LOG.CurrentLineDebuglog; i++)
		{
			if (GAME_LOG.DebugLogLines[i].find(text) == 0)
			{
				stringfound = true;
				tempindex = i;
				break;
			}

		}

		if (stringfound == true)
		{
			GAME_LOG.DebugLogLines[tempindex] = text;
			GAME_LOG.DebugLogLines[tempindex].append(to_string(value));
		}
		else
		{
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
			GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog].append(to_string(value));
			GAME_LOG.CurrentLineDebuglog++;
		}

	}
	else
	{
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog] = text;
		GAME_LOG.DebugLogLines[GAME_LOG.CurrentLineDebuglog].append(to_string(value));
		GAME_LOG.CurrentLineDebuglog++;
	}


}


#define GAME_ENGINE_FUNC
#endif
