#pragma once
#include <functional>
#include <utility>
#include <vector>
#include "EngineObjects/GameObject.h"

class IObjectSystem
{
protected:
    std::function<void(GameObject2D *, GameObject2D *)> onCollision;

public:
    IObjectSystem(std::function<void(GameObject2D *, GameObject2D *)> collision)
        : onCollision(std::move(collision)) {}
    virtual ~IObjectSystem() = default;
    virtual void insert(GameObject2D *obj) = 0;
    virtual void remove(GameObject2D *obj) = 0;
    virtual void update() = 0;

    virtual void DrawObjects() = 0;
    virtual void UpdateObjects(double deltaTime) = 0;
};

#define MAX_OBJECTS_SIMPLE 1000

class SimpleCollision : public IObjectSystem
{
    std::vector<GameObject2D *> objects;

public:
    using IObjectSystem::IObjectSystem;
    ~SimpleCollision() override;
    void insert(GameObject2D *obj) override;
    void remove(GameObject2D *obj) override;
    void update() override;

    void DrawObjects() override;
    void UpdateObjects(double deltaTime) override;
};