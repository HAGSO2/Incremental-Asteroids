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
UpgradeScreen::UpgradeScreen(vector<Upgrade> &upgrades) : Scene(UPGRADES, Music{}), upgrades(upgrades)
{
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

void UpdateScreen::Load(const json &in)
{
    // NOTE: It would be ideal to have a more generic way to load the canvas, but for now, we will do it manually.
    for (auto &obj : in["Canvas"])
    {
        float x = obj.value("x", 0.0f);
        float y = obj.value("y", 0.0f);
        float w = obj.value("width", 0.0f);
        float h = obj.value("height", 0.0f);
        if (obj.value("Type", std::string()) == "ImageButton")
        {
            string name = obj.value("Name", std::string());
            string iconPath = obj.value("iconPath", std::string());
            int cost = obj.value("cost", 0);
            switch (name)
            {
            case "Double Shot":
                // Add the button for Double Shot upgrade
                canvas.AddImageButton(x, y, w, h, iconPath.c_str(), nullptr, nullptr);
                break;
            case "Shield":
                // Add the button for Shield upgrade
                canvas.AddImageButton(x, y, w, h, iconPath.c_str(), nullptr, nullptr);
                break;
            case "Speed Boost":
                // Add the button for Speed Boost upgrade
                canvas.AddImageButton(x, y, w, h, iconPath.c_str(), nullptr, nullptr);
                break;
            }
        }
    }
}
