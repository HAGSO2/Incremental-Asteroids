#include "ProgramFlow/Scene.h"
#include "Player.h"

#define MAX_ASTEROID 70.0f
#define MAX_PROYECTILES 20

// If collisions cost NUM_ASTEROIDS x NUM_PROJECTILES, then we can have a maximum of 70 asteroids and 20 projectiles
// before the game starts to lag. This is because the collision detection algorithm checks each projectile against each asteroid,
// resulting in a total of 70 x 20 = 1400 collision checks per frame (in the worst case). If the number of asteroids or projectiles exceeds these limits,
// the game may experience performance issues due to the increased number of collision checks required.

struct Asteroid
{
    Vector2 position;
    float radius;
    Asteroid(Vector2 pos, float r) : position{pos}, radius{r} {};
};

class Gameplay : public Scene
{
    Vector2 centerposition; // Center point for spawning asteroids
    Player player;
    vector<Projectile> projectiles;           // Store active projectiles
    float asteroidSpawnTimer = 0.0f;          // Timer to control asteroid spawning
    float asteroidSpawnInterval = 2.0f;       // Spawn an asteroid every 2 seconds
    const float asteroidMinDistance = 150.0f; // Minimum distance from the center

    vector<Asteroid> asteroids; // Store active asteroids

public:
    Gameplay();
    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;

private:
    void CheckCollisionAndHandle();
    Asteroid CreateRandomAsteroid(float screenWidth,
                                  float screenHeight,
                                  float minDistance);
    void UpdateAsteroid(Asteroid &asteroid, double deltaTime, float speed);
};