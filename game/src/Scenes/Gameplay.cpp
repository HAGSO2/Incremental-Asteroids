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
    player.Update(deltaTime); // Update player logic

    for (int i = 0; i < projectiles.size(); ++i) {
        // Update projectile position based on its direction
        projectiles[i].position.x += projectiles[i].direction.x * 300 * deltaTime; // Move at 300 units per second
        projectiles[i].position.y += projectiles[i].direction.y * 300 * deltaTime;

        // Optionally, remove projectiles that go off-screen
        if (projectiles[i].position.x < 0 || projectiles[i].position.x > GetScreenWidth() ||
            projectiles[i].position.y < 0 || projectiles[i].position.y > GetScreenHeight()) {
            projectiles.erase(projectiles.begin() + i);
            --i; // Adjust index after removal
        }
    }
};

void Gameplay::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    // Draw buttons and other UI elements
    canvas.Draw();
    //Draw Gameplay elements (e.g., player, enemies, etc.)
    for(int i = 0; i < projectiles.size(); ++i) {
        DrawCircleV(projectiles[i].position, 5, YELLOW); // Draw each projectile as a small circle
    }

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

    if (k == KEY_LEFT) {
        player.RotateLeft();
    } else if (k == KEY_RIGHT) {
        player.RotateRight();
    }
    else if (k == KEY_SPACE) {
        // Shoot a projectile
        Projectile newProjectile = player.ShootProjectile();
        projectiles.push_back(newProjectile);
    }
};
