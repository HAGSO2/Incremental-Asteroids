#include "Scenes/UpgradesScreen.h"

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
UpgradeScreen::UpgradeScreen(vector<Upgrade> upgrades) : Scene(Music{}), upgrades(upgrades)
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = PURPLE;
};

void UpgradeScreen::InitScene() {
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
};

void UpgradeScreen::UpdateScreen(double deltaTime)
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen(deltaTime);
};

void UpgradeScreen::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    // Draw buttons and other UI elements
    canvas.Draw();
};

void UpgradeScreen::UnloadScreen() {
    // Unload scene resources here (e.g., textures, sounds, etc.)
};

void UpgradeScreen::OnMouseDown()
{
    // Handle mouse click events here (e.g., check if buttons are clicked)
    canvas.UpdateScreen(mousePosition);
};

void UpgradeScreen::OnKeyPressed(KeyboardKey k)
{
    // Handle key press events here (e.g., check if specific keys are pressed)
    canvas.UpdateKeyboard(k);
};

void UpgradeScreen::OnCollision(GameObject2D *obj1, GameObject2D *obj2)
{
}
