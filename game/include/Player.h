#include "EngineObjects/GameObject.h"

class Player
{
    int health;
    int score;
    Sprite playerSprite;
public:
    Player();
    void Update();
    void Draw();
};