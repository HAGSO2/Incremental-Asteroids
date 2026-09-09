#include "EngineObjects/GameObject.h"
#include <cmath>

#define PLAYER_RADIUS 50.0f

struct Projectile
{
    Vector2 position;
    Vector2 direction;
    Projectile(Vector2 pos, Vector2 dir) : position{pos}, direction{dir} {};
    Vector2 GetPosition() { return position; };
};

class Player : public GameObject2D
{
    int health;
    int score;
    // SpriteFormLined playerSprite;

    bool rotateLeft;
    bool rotateRight;

public:
    Player(Vector2 pos, int lives);
    void CreateSprite();

    void InitializeObject() override {};
    void UpdateObject(double deltaTime) override;

    // Vector2 GetPosition() { return playerSprite.GetPosition(); };
    float GetSize() { return PLAYER_RADIUS; }; // Assuming square shape for simplicity
    void SetRotateLeft() { rotateLeft = true; }
    void SetRotateRight() { rotateRight = true; }
    void ScorePoint() { score++; }
    int GetScore() { return score; }
    int GetHealth() { return health; }
    void TakeDamage() { health -= 1; }
    // Projectile *ShootProjectile();
};