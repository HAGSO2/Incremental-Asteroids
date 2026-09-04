#include <raylib.h>
#include <raymath.h>
#include "Scenes/Gameplay.h"

#pragma region To other scenes

#pragma endregion

// Constructor
Gameplay::Gameplay() : Scene(), scorenum(0.0f), livesnum(PLAYER_LIVES), player(PLAYER_LIVES)
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    canvas.AddPlainText(10, 10, 100, 30, 20, "Score: ", scorenum);
    canvas.AddPlainText(10, 50, 100, 30, 20, "Lives: ", livesnum);
    backgroundColor = GRAY;
    background = Background();
    centerposition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
};

void Gameplay::InitScene()
{
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
    Image bck1 = LoadImage(BACKGROUND_1);
    Image bck2 = LoadImage(BACKGROUND_2);
    background.layer_1 = LoadTextureFromImage(bck1);
    background.layer_2 = LoadTextureFromImage(bck2);
    background.size_2 = { (float)bck2.width, (float)bck2.height };
    UnloadImage(bck1);
    UnloadImage(bck2);
};

void Gameplay::UpdateScreen(double deltaTime)
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen(deltaTime);
    if (player.GetHealth() <= 0)
    {
        ChangeScene(GameScreen::GAMEOVER);
    };

    // Update gameplay-specific logic here (e.g., player movement, enemy behavior, etc.)
    player.Update(deltaTime); // Update player logic

    // Update projectiles
    for (int i = 0; i < projectiles.size(); ++i)
    {
        // Update projectile position based on its direction
        projectiles[i]->position.x += projectiles[i]->direction.x * 300 * deltaTime; // Move at 300 units per second
        projectiles[i]->position.y += projectiles[i]->direction.y * 300 * deltaTime;

        // Optionally, remove projectiles that go off-screen
        if (projectiles[i]->position.x < 0 || projectiles[i]->position.x > GetScreenWidth() ||
            projectiles[i]->position.y < 0 || projectiles[i]->position.y > GetScreenHeight())
        {
            delete projectiles[i];
            projectiles.erase(projectiles.begin() + i);
            --i; // Adjust index after removal
        }
    }

    // Update asteroids and spawn new ones if needed
    asteroidSpawnTimer += deltaTime;
    if (asteroidSpawnTimer >= ASTEROID_SPAWN_INTERVAL && asteroids.size() < MAX_ASTEROID)
    {
        asteroids.push_back(
            CreateRandomAsteroid(
                GetScreenWidth(),
                GetScreenHeight(),
                ASTEROID_MIN_DISTANCE));
        asteroidSpawnTimer = 0.0f; // Reset the timer
    }
    CheckCollisionAndHandle(); // Check for collisions between projectiles and asteroids

    for (int i = 0; i < asteroids.size(); ++i)
    {
        UpdateAsteroid(asteroids[i], deltaTime); // Move asteroids towards the center at a speed of 100 units per second
    }
};

void Gameplay::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    // DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    DrawTexture(background.layer_1, 0, 0, WHITE);
    DrawTexture(background.layer_2, 0, 0, Fade(WHITE, 0.3f));
    DrawTexture(background.layer_2, background.size_2.x, 0, Fade(WHITE, 0.3f));
    DrawTexture(background.layer_2, 0, background.size_2.y, Fade(WHITE, 0.3f));
    DrawTexture(background.layer_2, background.size_2.x, background.size_2.y, Fade(WHITE, 0.3f));
    //   Draw buttons and other UI elements
    canvas.Draw();
    // Draw Gameplay elements (e.g., player, enemies, etc.)
    for (int i = 0; i < projectiles.size(); ++i)
    {
        DrawCircleV(projectiles[i]->position, 5, DARKPURPLE); // Draw each projectile as a small circle
    }

    for (int i = 0; i < asteroids.size(); ++i)
    {
        DrawCircleV(asteroids[i]->position, asteroids[i]->radius, BLACK);                                 // Draw each asteroid as a circle
        DrawCircleLines(asteroids[i]->position.x, asteroids[i]->position.y, asteroids[i]->radius, WHITE); // Draw each asteroid as a circle
    }

    player.Draw();
};

void Gameplay::UnloadScreen()
{
    // Unload scene resources here (e.g., textures, sounds, etc.)
    UnloadTexture(background.layer_1);
    UnloadTexture(background.layer_2);
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
        Projectile *newProjectile = player.ShootProjectile();
        projectiles.push_back(newProjectile);
    }
};

Asteroid *Gameplay::CreateRandomAsteroid(float screenWidth,
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
    int speed = 50 + rand() % 5;

    return new Asteroid(position, radius, speed);
}

void Gameplay::CheckCollisionAndHandle()
{
    // Check for collisions between projectiles and asteroids
    for (int i = 0; i < asteroids.size(); ++i)
    {
        float playerDistance = Vector2Distance(player.GetPosition(), asteroids[i]->position);
        if (playerDistance < (player.GetSize() / 2 + asteroids[i]->radius))
        {
            // Collision detected between player and asteroid
            player.TakeDamage(); // Reduce player's health
            livesnum -= 1;
            delete asteroids[i]; // Free the memory allocated for the asteroid
            asteroids.erase(asteroids.begin() + i);
            --i;      // Adjust index after removal
            continue; // Skip to the next asteroid since this one is removed
        }
        for (int j = 0; j < projectiles.size(); ++j)
        {
            float distance = Vector2Distance(projectiles[j]->position, asteroids[i]->position);
            if (distance < asteroids[i]->radius)
            {
                // Collision detected, remove both projectile and asteroid
                delete projectiles[j]; // Free the memory allocated for the projectile
                projectiles.erase(projectiles.begin() + j);
                delete asteroids[i]; // Free the memory allocated for the asteroid
                asteroids.erase(asteroids.begin() + i);
                player.ScorePoint(); // Increase player's score
                scorenum += 1.0f;    // Increase score
                --j;                 // Adjust index after removal
                break;               // Exit the inner loop since the projectile is removed
            }
        }
    }
}

void Gameplay::UpdateAsteroid(Asteroid *asteroid, double deltaTime)
{

    // Dirección desde el asteroide hacia el centro
    Vector2 direction = Vector2Subtract(centerposition, asteroid->position);

    // Normalizar para que la velocidad sea constante
    direction = Vector2Normalize(direction);

    // Mover usando deltaTime
    asteroid->position.x += direction.x * asteroid->speed * deltaTime;
    asteroid->position.y += direction.y * asteroid->speed * deltaTime;
}