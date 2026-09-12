#include "ProgramFlow/Scene.h"
#include "AssetsPath.hpp"
#include "Player.h"
#include "Projectile.h"
#include "Asteroid.h"

#define MAX_ASTEROID 70.0f
#define MAX_PROYECTILES 20

// If collisions cost NUM_ASTEROIDS x NUM_PROJECTILES, then we can have a maximum of 70 asteroids and 20 projectiles
// before the game starts to lag. This is because the collision detection algorithm checks each projectile against each asteroid,
// resulting in a total of 70 x 20 = 1400 collision checks per frame (in the worst case). If the number of asteroids or projectiles exceeds these limits,
// the game may experience performance issues due to the increased number of collision checks required.

#define ASTEROID_SPAWN_INTERVAL 2.0f
#define ASTEROID_MIN_DISTANCE 150.0f
#define PLAYER_LIVES 5

class Gameplay : public Scene
{
    struct Background
    {
        Texture2D layer_1;
        Vector2 position_1;
        Texture2D layer_2;
        Vector2 position_2;
        Vector2 size_2;
        Background() : layer_1{0}, position_1{0, 0}, layer_2{0}, position_2{0, 0}, size_2{0, 0} {}
    };
    Background background;
    Vector2 centerposition; // Center point for spawning asteroids
    Player *player;

    float asteroidSpawnTimer = 0.0f; // Timer to control asteroid spawning

    // vector<Projectile *> projectiles; // Store active projectiles
    // vector<Asteroid *> asteroids;     // Store active asteroids

    float scorenum; // Store the score text to display on the screen
    float livesnum; // Store the lives text to display on the screen

public:
    Gameplay(Music m);
    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    void OnCollision(GameObject2D *obj1, GameObject2D *obj2) override;

private:
    void CheckCollisionAndHandle();
    void CreateRandomAsteroid(float screenWidth,
                              float screenHeight,
                              float minDistance);
    // void UpdateAsteroid(Asteroid *asteroid, double deltaTime);
};