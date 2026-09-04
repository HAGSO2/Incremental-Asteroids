#include "ProgramFlow/Scene.h"
#include "AssetsPath.hpp"
#include "Player.h"

#define MAX_ASTEROID 70.0f
#define MAX_PROYECTILES 20

// If collisions cost NUM_ASTEROIDS x NUM_PROJECTILES, then we can have a maximum of 70 asteroids and 20 projectiles
// before the game starts to lag. This is because the collision detection algorithm checks each projectile against each asteroid,
// resulting in a total of 70 x 20 = 1400 collision checks per frame (in the worst case). If the number of asteroids or projectiles exceeds these limits,
// the game may experience performance issues due to the increased number of collision checks required.

#define ASTEROID_SPAWN_INTERVAL 2.0f
#define ASTEROID_MIN_DISTANCE 150.0f
#define PLAYER_LIVES 5

struct Asteroid
{
    Vector2 position;
    float radius;
    int speed;
    Asteroid(Vector2 pos, float r, int s) : position{pos}, radius{r}, speed{s} {};
};

class Gameplay : public Scene
{
    struct Background
    {
        Texture2D texture;
        Vector2 position;
    };
    Background background;
    Vector2 centerposition; // Center point for spawning asteroids
    Player player;

    float asteroidSpawnTimer = 0.0f; // Timer to control asteroid spawning

    vector<Projectile *> projectiles; // Store active projectiles
    vector<Asteroid *> asteroids;     // Store active asteroids

    float scorenum; // Store the score text to display on the screen
    float livesnum; // Store the lives text to display on the screen

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
    Asteroid *CreateRandomAsteroid(float screenWidth,
                                   float screenHeight,
                                   float minDistance);
    void UpdateAsteroid(Asteroid *asteroid, double deltaTime);
};