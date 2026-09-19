#include "Scenes/Gameplay.h"
#include <raylib.h>
#include <raymath.h>

#pragma region To other scenes

#pragma endregion

#pragma region Scene Methods

// Constructor
Gameplay::Gameplay(Music m)
    : Scene(OS_BY_LAYERS, m, NUMBER_LAYERS, {0, GL_ASTEROID, GL_PROJECTILE, 0}), scorenum(0.0f),
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
};

void Gameplay::InitScene()
{
  Scene::InitScene(); // Call base class InitScene to handle common
                      // initialization tasks
  // Initialize scene elements here (e.g., load textures, set up UI, etc.)
  // Load background images
  Image bck1 = LoadImage(BACKGROUND_1);
  Image bck2 = LoadImage(BACKGROUND_2);
  // Set background structure
  background.layer_1 = LoadTextureFromImage(bck1);
  background.layer_2 = LoadTextureFromImage(bck2);
  background.size_2 = {(float)bck2.width, (float)bck2.height};
  UnloadImage(bck1);
  UnloadImage(bck2);

  // Set screen limits, 20 units out of visible screen
  SetOffscreenShape();
  SetOffscreenOffset(20);
};

void Gameplay::UpdateScreen(double deltaTime)
{
  // Update base scene logic (e.g., handle input, update UI, etc.)
  Scene::UpdateScreen(deltaTime);

  // Defeat condition
  if (livesnum < 0)
    finishScreen = GAMEOVER;

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
    Vector2 forw = player->GetForward();
    Vector2 apex = Vector2{forw.x * 50 + centerposition.x, forw.y * 50 + centerposition.y};
    // DrawCircleV(apex, PLAYER_RADIUS / 3, YELLOW);
    Projectile *posiblePro = new Projectile(apex, forw);
    if (!AddGameObject(posiblePro))
      delete posiblePro;
  }
};

void Gameplay::OnCollision(GameObject2D *obj1, GameObject2D *obj2)
{
  // Handle all collisions:

  // Non important collisions
  if ((obj1->layer == GL_PLAYER && obj2->layer == GL_PROJECTILE) ||
      (obj2->layer == GL_PLAYER && obj1->layer == GL_PROJECTILE))
    return;

  // Set wich pointer is the asteroid
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

  // Erase asteroid and handle reward or punishment
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

  // Generate until find a enough far position
  // from the center.
  do
  {
    position = {static_cast<float>(rand() % static_cast<int>(screenWidth)),
                static_cast<float>(rand() % static_cast<int>(screenHeight))};
  } while (Vector2Distance(position, centerposition) < minDistance);

  float radius = 10.0f + static_cast<float>(rand() % 21);
  int speed = 50 + rand() % 5;

  // Add the object if posible
  Asteroid *posibleAst = new Asteroid(speed, centerposition, position, {radius, radius});
  if (!AddGameObject(posibleAst))
    delete posibleAst;
}