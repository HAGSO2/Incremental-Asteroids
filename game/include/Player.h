#include "EngineObjects/GameObject.h"
#include <cmath>

struct Projectile{
    Vector2 position;
    Vector2 direction;
    Projectile(Vector2 pos, Vector2 dir) : position{pos}, direction{dir} {};
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

    void RotateLeft() { rotateLeft = true; }
    void RotateRight() { rotateRight = true; }
    Projectile ShootProjectile();
};