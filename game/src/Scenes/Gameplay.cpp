#include <raylib.h>
#include "Scenes/Gameplay.h"

#pragma region To other scenes
/*
void ToGameplay(void *ptr)
{
    // Just change the finishScreen to the Gameplay
    ((OtherScene *)ptr)->ChangeScene(OtherScene);
    TraceLog(LOG_DEBUG, "Transitioning to OtherScene scene...");
};
*/
#pragma endregion

// Constructor
Gameplay::Gameplay(): Scene()
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = GRAY;
    player = Player();
};

void Gameplay::InitScene() {
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
};

void Gameplay::UpdateScreen(double deltaTime)
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen(deltaTime);
};

void Gameplay::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    // Draw buttons and other UI elements
    canvas.Draw();
    //Draw Gameplay elements (e.g., player, enemies, etc.)
    player.Draw();
};

void Gameplay::UnloadScreen() {
    // Unload scene resources here (e.g., textures, sounds, etc.)
};

void Gameplay::OnMouseDown()
{
    // Handle mouse click events here (e.g., check if buttons are clicked)
    canvas.UpdateScreen(mousePosition);
};

void Gameplay::OnKeyPressed(KeyboardKey k)
{
    // Handle key press events here (e.g., check if specific keys are pressed)
    canvas.UpdateKeyboard(k);
};
