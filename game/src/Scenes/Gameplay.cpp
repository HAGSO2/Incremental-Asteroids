#include <raylib.h>
#include <raymath.h>
#include "Scenes/Gameplay.h"

#pragma region To other scenes

#pragma endregion

// Constructor
Gameplay::Gameplay() : Scene()
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = GRAY;
    player = Player();
    centerposition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
};

void Gameplay::InitScene() {
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
};

void Gameplay::UpdateScreen(double deltaTime)
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen(deltaTime);
    player.Update(deltaTime); // Update player logic

    for (int i = 0; i < projectiles.size(); ++i)
    {
        // Update projectile position based on its direction
        projectiles[i].position.x += projectiles[i].direction.x * 300 * deltaTime; // Move at 300 units per second
        projectiles[i].position.y += projectiles[i].direction.y * 300 * deltaTime;

        // Optionally, remove projectiles that go off-screen
        if (projectiles[i].position.x < 0 || projectiles[i].position.x > GetScreenWidth() ||
            projectiles[i].position.y < 0 || projectiles[i].position.y > GetScreenHeight())
        {
            projectiles.erase(projectiles.begin() + i);
            --i; // Adjust index after removal
        }
    }
    asteroidSpawnTimer += deltaTime;
    if (asteroidSpawnTimer >= asteroidSpawnInterval && asteroids.size() < MAX_ASTEROID)
    {
        asteroids.push_back(
            CreateRandomAsteroid(
                GetScreenWidth(),
                GetScreenHeight(),
                asteroidMinDistance));
        asteroidSpawnTimer = 0.0f; // Reset the timer
        TraceLog(LOG_INFO, "Asteroid spawned. Total asteroids: %d", asteroids.size());
    }
    CheckCollisionAndHandle(); // Check for collisions between projectiles and asteroids

    for (int i = 0; i < asteroids.size(); ++i)
    {
        UpdateAsteroid(asteroids[i], deltaTime, 80.0f); // Move asteroids towards the center at a speed of 100 units per second    
    }
};

void Gameplay::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    // Draw buttons and other UI elements
    canvas.Draw();
    // Draw Gameplay elements (e.g., player, enemies, etc.)
    for (int i = 0; i < projectiles.size(); ++i)
    {
        DrawCircleV(projectiles[i].position, 5, YELLOW); // Draw each projectile as a small circle
    }

    for (int i = 0; i < asteroids.size(); ++i)
    {
        DrawCircleV(asteroids[i].position, asteroids[i].radius, DARKGRAY); // Draw each asteroid as a circle
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

    if (k == KEY_LEFT)
    {
        player.RotateLeft();
    }
    else if (k == KEY_RIGHT)
    {
        player.RotateRight();
    }
    else if (k == KEY_SPACE)
    {
        if (projectiles.size() >= MAX_PROYECTILES)
        {
            TraceLog(LOG_WARNING, "Maximum number of projectiles reached. Cannot shoot more.");
            return; // Exit early if the maximum number of projectiles is reached
        }
        // Shoot a projectile
        Projectile newProjectile = player.ShootProjectile();
        projectiles.push_back(newProjectile);
    }
};

Asteroid Gameplay::CreateRandomAsteroid(float screenWidth,
                              float screenHeight,
                              float minDistance)
{
    Vector2 position;

    // Generar hasta encontrar una posición suficientemente
    // alejada del centro.
    do
    {
        position = {
            static_cast<float>(rand() % static_cast<int>(screenWidth)),
            static_cast<float>(rand() % static_cast<int>(screenHeight))};
    } while (Vector2Distance(position, centerposition) < minDistance);

    float radius = 10.0f + static_cast<float>(rand() % 21);

    return Asteroid{position, radius};
}

void Gameplay::CheckCollisionAndHandle()
{
    // Check for collisions between projectiles and asteroids
    for (int i = 0; i < projectiles.size(); ++i)
    {
        for (int j = 0; j < asteroids.size(); ++j)
        {
            float distance = Vector2Distance(projectiles[i].position, asteroids[j].position);
            if (distance < asteroids[j].radius)
            {
                // Collision detected, remove both projectile and asteroid
                projectiles.erase(projectiles.begin() + i);
                asteroids.erase(asteroids.begin() + j);
                --i;   // Adjust index after removal
                break; // Exit the inner loop since the projectile is removed
            }
        }
    }
}

void Gameplay::UpdateAsteroid(Asteroid& asteroid, double deltaTime, float speed)
{

    // Dirección desde el asteroide hacia el centro
    Vector2 direction = Vector2Subtract(centerposition, asteroid.position);

    // Normalizar para que la velocidad sea constante
    direction = Vector2Normalize(direction);

    // Mover usando deltaTime
    asteroid.position.x += direction.x * speed * deltaTime;
    asteroid.position.y += direction.y * speed * deltaTime;
}