/*******************************************************************************************
*
*   raylib - Advance Game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014-2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "../header_files/raylib.h"
//#include "code/header_files/screens.h"
#include "../header_files/globals.h"
#include "game.cpp"


// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static int transToScreen = -1;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // No transition effect

static void TransitionToScreen(int screen);
static void UpdateTransition(void);
static void DrawTransition(void);

static void UpdateDrawFrame(void);          // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
	// Initialization 


	window.Width = GAMEWINDOW_WIDTH;
	window.Height = GAMEWINDOW_HEIGHT;

	InitWindow(window.Width, window.Height, "game_project");



	// Global data loading (assets that must be available in all screens, i.e. fonts)
	//InitAudioDevice();

	//font = LoadFont("resources/mecha.png");
	//music = LoadMusicStream("resources/ambient.ogg");
	//fxCoin = LoadSound("resources/coin.wav");


	printf("THIS IS RUN\n");

	// SetMusicVolume(music, 1.0f);
	// PlayMusicStream(music);

	 // Setup and Init first screen
	currentScreen = GAMEPLAY;
	InitGameplayScreen();


	SetTargetFPS(120);   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		UpdateDrawFrame();
	}


	// De-Initialization
	//--------------------------------------------------------------------------------------

	// Unload current screen data before closing
	switch (currentScreen)
	{

	case GAMEPLAY: UnloadGameplayScreen(); break;
		//case GUI: UnloadGuiScreen(); break;
	default: break;

	}

	// Unload all global loaded data (i.e. fonts) here!
	UnloadFont(font);
	UnloadMusicStream(music);
	UnloadSound(fxCoin);

	CloseAudioDevice();     // Close audio context

	CloseWindow();          // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------

// Change to next screen, no transition
static void ChangeToScreen(int screen)
{
	// Unload current screen
	switch (currentScreen)
	{
	case GAMEPLAY: UnloadGameplayScreen(); break;
		//case GUI: UnloadGuiScreen(); break;
	default: break;
	}

	// Init next screen
	switch (screen)
	{
	case GAMEPLAY: InitGameplayScreen(); break;
		//case GUI: InitGuiScreen(); break;
	default: break;
	}

	currentScreen = screen;
}

// Define transition to next screen
static void TransitionToScreen(int screen)
{
	onTransition = true;
	transFadeOut = false;
	transFromScreen = currentScreen;
	transToScreen = screen;
	transAlpha = 0.0f;
}

//// Update transition effect
//static void UpdateTransition(void)
//{
//	if (!transFadeOut)
//	{
//		transAlpha += 0.05f;
//
//		// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
//		// For that reason we compare against 1.01f, to avoid last frame loading stop
//		if (transAlpha > 1.01f)
//		{
//			transAlpha = 1.0f;
//
//			// Unload current screen
//			switch (transFromScreen)
//			{
//			case GAMEPLAY: UnloadGameplayScreen(); break;
//			case GUI: UnloadGuiScreen(); break;
//			default: break;
//			}
//
//			// Load next screen
//			switch (transToScreen)
//			{
//			case GAMEPLAY: InitGameplayScreen(); break;
//			case GUI: InitGuiScreen(); break;
//			default: break;
//			}
//
//			currentScreen = transToScreen;
//
//			// Activate fade out effect to next loaded screen
//			transFadeOut = true;
//		}
//	}
//	else  // Transition fade out logic
//	{
//		transAlpha -= 0.02f;
//
//		if (transAlpha < -0.01f)
//		{
//			transAlpha = 0.0f;
//			transFadeOut = false;
//			onTransition = false;
//			transFromScreen = -1;
//			transToScreen = -1;
//		}
//	}
//}
//
//// Draw transition effect (full-screen rectangle)
//static void DrawTransition(void)
//{
//	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
//}

// Update and draw game frame
static void UpdateDrawFrame(void)
{
	// Update
	//----------------------------------------------------------------------------------
	//UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

	if (!onTransition)
	{
		switch (currentScreen)
		{

		case GAMEPLAY:
		{
			UpdateGameplayScreen();


		} break;

		case GUI:
		{
			//UpdateGuiScreen();

			//if (FinishEndingScreen() == 1) TransitionToScreen(TITLE);

		} break;

		default: break;
		}
	}
	else {}
	// Update transition (fade-in, fade-out)
	//----------------------------------------------------------------------------------
	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(WHITE);

	switch (currentScreen)
	{
	case GAMEPLAY: DrawGameplayScreen(); break;
		//case GUI: DrawGuiScreen(); break;

	default: break;
	}


	//

	EndDrawing();
	//----------------------------------------------------------------------------------
}
