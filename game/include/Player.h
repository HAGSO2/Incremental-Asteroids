#include "EngineObjects/GameObject.h"
#include "Scenes/Gameplay_definitions.h"
#include <cmath>

class Player : public GameObject2D
{
    // SpriteFormLined playerSprite;

    bool rotateLeft;
    bool rotateRight;

public:
    Player(Vector2 pos);
    ~Player() = default;
    void CreateSprite();

    void InitializeObject() override {};
    void UpdateObject(double deltaTime) override;

    // Vector2 GetPosition() { return playerSprite.GetPosition(); };
    float GetSize() { return PLAYER_RADIUS; }; // Assuming square shape for simplicity
    void SetRotateLeft() { rotateLeft = true; }
    void SetRotateRight() { rotateRight = true; }
    // void ScorePoint() { score++; }
    // int GetScore() { return score; }
    // int GetHealth() { return health; }
    // void TakeDamage() { health -= 1; }
    // Projectile *ShootProjectile();
};