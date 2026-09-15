#pragma once
#include "EngineObjects/GameObject.h"
#include "Scenes/Gameplay_definitions.h"

class Projectile : public GameObject2D
{
    Vector2 direction;

public:
    Projectile(Vector2 pos, Vector2 direction);
    ~Projectile() = default;
    void InitializeObject() override {};
    void UpdateObject(double deltaTime) override;
};