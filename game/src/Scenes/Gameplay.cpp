#include "Scenes/Gameplay.h"
#include <raylib.h>
#include <raymath.h>

#pragma region To other scenes

#pragma endregion

#pragma region Scene Methods

// Constructor
Gameplay::Gameplay(Music m)
  : Scene(OS_BY_LAYERS, m, NUMBER_LAYERS, {0, GL_ASTEROID, GL_PROJECTILE, GL_WALL}), scorenum(0.0f),
      livesnum(PLAYER_LIVES) /*, player(PLAYER_LIVES)*/
{
  // Initialize UI canvas and add buttons
  canvas = UI();
  canvas.AddPlainText(10, 10, 100, 30, 20, "Score: ", scorenum);
  canvas.AddPlainText(10, 50, 100, 30, 20, "Lives: ", livesnum);
  backgroundColor = GRAY;
  background = Background();
  float h = GetScreenHeight();
  float w = GetScreenWidth();
  centerposition = {w / 2.0f, h / 2.0f};
  player = new Player(centerposition);
  AddGameObject(player);
  //TODO: Add Walls at the end of the screen
  Vector2 zero = {};
  Vector2 hizq = {GetScreenHeight(), 0};
  // GameObject2D
};

void Gameplay::InitScene()
{
  Scene::InitScene(); // Call base class InitScene to handle common
                      // initialization tasks
  // Initialize scene elements here (e.g., load textures, set up UI, etc.)
  Image bck1 = LoadImage(BACKGROUND_1);
  Image bck2 = LoadImage(BACKGROUND_2);
  background.layer_1 = LoadTextureFromImage(bck1);
  background.layer_2 = LoadTextureFromImage(bck2);
  background.size_2 = {(float)bck2.width, (float)bck2.height};
  UnloadImage(bck1);
  UnloadImage(bck2);
};

void Gameplay::UpdateScreen(double deltaTime)
{
  // Update base scene logic (e.g., handle input, update UI, etc.)
  Scene::UpdateScreen(deltaTime);
  
  // Update asteroids and spawn new ones if needed
  asteroidSpawnTimer += deltaTime;
  if (asteroidSpawnTimer >= ASTEROID_SPAWN_INTERVAL)
  {
    CreateRandomAsteroid(GetScreenWidth(), GetScreenHeight(), ASTEROID_MIN_DISTANCE);
    asteroidSpawnTimer = 0.0f; // Reset the timer
  }
};

void Gameplay::DrawScreen()
{
  // Draw the title screen elements here (e.g., background, title text, buttons,
  // etc.) Background DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
  // backgroundColor);
  DrawTexture(background.layer_1, 0, 0, WHITE);
  DrawTexture(background.layer_2, 0, 0, Fade(WHITE, 0.3f));
  DrawTexture(background.layer_2, background.size_2.x, 0, Fade(WHITE, 0.3f));
  DrawTexture(background.layer_2, 0, background.size_2.y, Fade(WHITE, 0.3f));
  DrawTexture(background.layer_2, background.size_2.x, background.size_2.y,
              Fade(WHITE, 0.3f));
  // Draw IU and gameobjects;
  Scene::DrawScreen();

};

void Gameplay::UnloadScreen()
{
  Scene::UnloadScreen();
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
    player->SetRotateLeft();
  }
  else if (k == KEY_RIGHT)
  {
    player->SetRotateRight();
  }
  else if (k == KEY_SPACE)
  {
    // TODO: Handle number of Projectiles
    //  if (projectiles.size() >= MAX_PROjECTILES)
    //  {
    //    TraceLog(LOG_WARNING,
    //             "Maximum number of projectiles reached. Cannot shoot more.");
    //    return; // Exit early if the maximum number of projectiles is reached
    //  }
    //  Shoot a projectile
    Vector2 forw = player->GetForward();
    Vector2 apex = Vector2{forw.x * 50 + centerposition.x, forw.y * 50 + centerposition.y};
    TraceLog(LOG_ALL, "Projectile created");
    // DrawCircleV(apex, PLAYER_RADIUS / 3, YELLOW);

    AddGameObject(new Projectile(apex, forw));
    // Projectile *newProjectile = player.ShootProjectile();
    // projectiles.push_back(newProjectile);
  }
};

void Gameplay::OnCollision(GameObject2D *obj1, GameObject2D *obj2)
{
  if ((obj1->layer == GL_PLAYER && obj2->layer == GL_PROJECTILE) ||
      (obj2->layer == GL_PLAYER && obj1->layer == GL_PROJECTILE))
    return;
  TraceLog(LOG_ALL, "Is valid collision");
  Asteroid *asteroid = nullptr;
  GameObject2D *other = nullptr;
  if (obj1->layer == GL_ASTEROID && obj2->layer != GL_ASTEROID)
  {
    asteroid = (Asteroid *)obj1;
    other = obj2;
  }
  else if (obj2->layer == GL_ASTEROID && obj1->layer != GL_ASTEROID)
  {
    asteroid = (Asteroid *)obj2;
    other = obj1;
  }
  else
    return;
  
  EraseGameobject(asteroid);
  
  
  if (other->layer == GL_PLAYER)
    livesnum--;
  else
  {
    scorenum += 5;
    EraseGameobject(other);
  }
}

#pragma endregion

void Gameplay::CreateRandomAsteroid(float screenWidth, float screenHeight,
                                    float minDistance)
{
  Vector2 position;

  // Generar hasta encontrar una posición suficientemente
  // alejada del centro.
  do
  {
    position = {static_cast<float>(rand() % static_cast<int>(screenWidth)),
                static_cast<float>(rand() % static_cast<int>(screenHeight))};
  } while (Vector2Distance(position, centerposition) < minDistance);

  float radius = 10.0f + static_cast<float>(rand() % 21);
  int speed = 50 + rand() % 5;

  AddGameObject(new Asteroid(speed, centerposition, position, {radius, radius}));
  // return new Asteroid(position, radius, speed);
}