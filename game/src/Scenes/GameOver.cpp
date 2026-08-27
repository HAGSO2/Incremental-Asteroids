#include "Scenes/GameOver.h"

GameOver::GameOver() : Scene()
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = BLACK;
};

void GameOver::InitScene() {
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
};

void GameOver::UpdateScreen(double deltaTime)
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen(deltaTime);
};

void GameOver::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    // Draw buttons and other UI elements
    canvas.Draw();
};

void GameOver::UnloadScreen() {
    // Unload scene resources here (e.g., textures, sounds, etc.)
};

void GameOver::OnMouseDown()
{
    // Handle mouse click events here (e.g., check if buttons are clicked)
    canvas.UpdateScreen(mousePosition);
};

void GameOver::OnKeyPressed(KeyboardKey k)
{
    // Handle key press events here (e.g., check if specific keys are pressed)
    canvas.UpdateKeyboard(k);
};