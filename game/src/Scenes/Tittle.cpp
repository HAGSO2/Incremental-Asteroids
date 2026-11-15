#include "Scenes/Tittle.h"
#include "Scenes/Gameplay.h"
#include "Scenes/ChangeToScenes.h"
#include "HardcodedStrings.hpp"

// Constructor
Tittle::Tittle(Font f, Music m, int w, int h) : Scene(TITTLE, m), font{f}, screenWidth{w}, screenHeight{h}
{
    backgroundColor = BLUE;
    canvas.AddButton(300, 400, 100, 50, 30, TittleButtonText, GREEN, ToGameplay, this);
};

void Tittle::UpdateScreen(double deltaTime)
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen(deltaTime);
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
    // DrawTextEx(font, TitleScreenText, Vector2{20, 10}, font.baseSize * 3.0f, 4, BLACK);
    //  Draw buttons and other UI elements
    canvas.Draw();
};