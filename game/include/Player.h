#include "EngineObjects/GameObject.h"
#include <cmath>

struct Projectile
{
    Vector2 position;
    Vector2 direction;
    Projectile(Vector2 pos, Vector2 dir) : position{pos}, direction{dir} {};
    Vector2 GetPosition() { return position; };
};

class Player
{
    int health;
    int score;
    Sprite playerSprite;

    bool rotateLeft = false;
    bool rotateRight = false;

public:
    Player();
    void Update(double deltaTime);
    void Draw();

    Vector2 GetPosition() { return playerSprite.GetPosition(); };
    float GetSize() { return playerSprite.GetSize().x; }; // Assuming square sprite, return width
    void RotateLeft() { rotateLeft = true; }
    void RotateRight() { rotateRight = true; }
    void ScorePoint() { score++; }
    int GetScore() { return score; }
    int GetHealth() { return health; }
    void TakeDamage() { health -= 1; }
    Projectile* ShootProjectile();
};