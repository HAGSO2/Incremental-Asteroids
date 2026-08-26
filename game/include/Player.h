#include "EngineObjects/GameObject.h"

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
};