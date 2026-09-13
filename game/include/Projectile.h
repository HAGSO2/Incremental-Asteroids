#pragma once
#include "EngineObjects/GameObject.h"

#define PROYECTILE_SPEED 300
#define PROJECTILE_TAG "projectile"

class Projectile : public GameObject2D
{
    Vector2 direction;

public:
    Projectile(Vector2 pos, Vector2 direction);
    ~Projectile() = default;
    void InitializeObject() override {};
    void UpdateObject(double deltaTime) override;
};