/*******************************************************************************************
 *
 *
 ********************************************************************************************/

#include "../header_files/raylib.h"

#include "../header_files/globals.h"
#include "game.cpp"


// Update and draw game frame
static void GameUpdateAndRender(game_state &GameState, int CurrentScreen) {
  switch (CurrentScreen) {
    case GAMEPLAY: {
      UpdateGameplayScreen(GameState);

    } break;

    case GUI: {
      printf("Not implemented ");

    } break;

    default:
      break;
  }

  //----------------------------------------------------------------------------------
  // Draw
  //----------------------------------------------------------------------------------



  BeginDrawing();

  ClearBackground(WHITE);


  switch (CurrentScreen) {
    case GAMEPLAY:
      DrawGameplayScreen(GameState);
      break;
    case GUI:
      printf("Not implemented ");
      break;

    default:
      break;
  }

  EndDrawing();
}

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void) {
  // Initialization

  win32_window_dimension Window;

  Window.Width = GAMEWINDOW_WIDTH;
  Window.Height = GAMEWINDOW_HEIGHT;

  InitWindow(Window.Width, Window.Height, "game_project");

  // Create GameState struct to hold game state info
  struct game_state GameState;

  // Setup and Init first screen
  int CurrentScreen = GAMEPLAY;

  InitGameplayScreen(GameState);

  // Main game loop
  while (!WindowShouldClose())  // Detect window close button or ESC key
  {
    GameUpdateAndRender(GameState, CurrentScreen);
  }

  //--------------------------------------------------------------------------------------
  // De-Initialization
  //--------------------------------------------------------------------------------------

  // Unload current screen data before closing
  switch (CurrentScreen) {
    case GAMEPLAY:
      UnloadGameplayScreen(GameState);
      break;
      // case GUI: UnloadGuiScreen(); break;
    default:
      break;
  }

  CloseWindow();  // Close window and OpenGL context
  
  //--------------------------------------------------------------------------------------

  return 0;
}
