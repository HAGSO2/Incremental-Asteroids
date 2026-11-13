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

void BuyUpgrade(void *ptr)
{
    pair<UpgradeScreen *, int> *upgradePair = (pair<UpgradeScreen *, int> *)ptr;
    // Just change the finishScreen to the Gameplay
    (upgradePair->first)->AddUpgrade(upgradePair->second);
};

#pragma endregion

// Constructor
UpgradeScreen::UpgradeScreen(vector<Upgrade> &upgrades) : Scene(UPGRADES, Music{}), upgrades(upgrades)
{
    backgroundColor = PURPLE;
    LoadFromFile();
};

void UpgradeScreen::InitScene()
{
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
    Scene::InitScene();
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

void UpgradeScreen::OnCollision(GameObject2D *obj1, GameObject2D *obj2) {
};

void UpgradeScreen::Load(const json &in)
{
    // NOTE: It would be ideal to have a more generic way to load the canvas, but for now, we will do it manually.
    for (auto &obj : in["Canvas"])
    {
        float x = obj.value("x", 0.0f);
        float y = obj.value("y", 0.0f);
        float w = obj.value("width", 0.0f);
        float h = obj.value("height", 0.0f);
        int id = obj.value("id", 0);
        if (obj.value("Type", std::string()) == "ImageButton")
        {
            pair<UpgradeScreen *, int> *upgradePair = new pair<UpgradeScreen *, int>(this, id);
            canvas.AddImageButton(x, y, w, h, upgrades[id].iconPath.c_str(), BuyUpgrade, upgradePair);
        }
    }
}

void UpgradeScreen::AddUpgrade(int id)
{
    TraceLog(LOG_DEBUG, "Attempting to add upgrade with ID: %d", id);
    TraceLog(LOG_DEBUG, "Upgrade %s added.\n", upgrades[id].name.c_str());
    // switch (id)
    // {
    // case 0:
    //     break;
    // case 1:
    //     break;
    // case 2:
    //     break;
    // case 3:
    //     break;
    // case 4:
    //     break;
    // case 5:
    //     break;
    // case 6:
    //     break;
    // case 7:
    //     break;
    // default:
    //     TraceLog(LOG_DEBUG, "Unknown upgrade id: %d", id);
    //     break;
    // }
}
