#include "ProgramFlow/Scene.h"
#include "AssetsPath.hpp"
#include "Scenes/Gameplay_definitions.h"
#include "Player.h"
#include "Projectile.h"
#include "Asteroid.h"

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
    ~Gameplay() = default; //NOTE: player is deleted on unload screen
    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    void OnCollision(GameObject2D *obj1, GameObject2D *obj2) override;

private:
    void CreateRandomAsteroid(float screenWidth,
                              float screenHeight,
                              float minDistance);
};