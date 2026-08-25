#include "Scenes/Tittle.h"
#include "HardcodedStrings.hpp"
#pragma region To other scenes

#pragma endregion

// Constructor
Tittle::Tittle(Font f, int w, int h) : font{f}, screenWidth{w}, screenHeight{h}
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = GREEN;
};

void Tittle::UpdateScreen()
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen();
};

void Tittle::OnMouseDown()
{
    // Handle mouse click events here (e.g., check if buttons are clicked)
    canvas.UpdateScreen(mousePosition);
};

void Tittle::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);

    // Title text
    DrawText(TitleScreenText, 180, 200, 30, BLACK);
    //DrawTextEx(font, TitleScreenText, Vector2{20, 10}, font.baseSize * 3.0f, 4, BLACK);
    // Draw buttons and other UI elements
    canvas.Draw();
};