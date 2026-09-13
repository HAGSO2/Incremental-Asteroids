#pragma once
#include "EngineObjects/GameObject.h"

#define ASTEROID_TAG "asteroid"

class Asteroid : public GameObject2D
{
    float speed;
    Vector2 centerposition;

public:
    Asteroid(float s, Vector2 center, Vector2 initpos, Vector2 scale);
    ~Asteroid() = default;
    void InitializeObject() override {};
    void UpdateObject(double deltaTime) override;
};