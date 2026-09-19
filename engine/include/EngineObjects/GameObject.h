#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <cmath>
#include <stdint.h>
#include <algorithm>

#include "EngineObjects/Collider.h"
#include "EngineObjects/Renderer.h"
#include "EngineObjects/Transform2D.h"

using namespace std;

#define MAX_OBJECT_DISTANCE_X 300
#define MAX_OBJECT_DISTANCE_Y 300

class GameObject
{
public:
    GameObject();
    virtual void DrawObject() = 0;
};

class GameObject2D
{
    Transform2D *transform;
    Renderer *renderer;
    Collider2D *collider;

public:
    inline static constexpr uint32_t INVALID_INDEX = 0xFFFFFFFF;
    uint32_t id;
    uint32_t layer;
    // Layers are defined on custom objects
    GameObject2D(Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : transform(new Transform2D(pos, rot, scl)), renderer(nullptr), collider(nullptr), id(0), layer(0) {}
    GameObject2D(uint32_t l = 0, Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : transform(new Transform2D(pos, rot, scl)), renderer(nullptr), collider(nullptr), id(0), layer(l) {}
    virtual ~GameObject2D();

#pragma region Transform Methods
    Transform2D *GetTransform() { return transform; }
    Vector2 GetPosition() { return transform->position; }
    float GetRotation() { return transform->rotation; }
    Vector2 GetScale() { return transform->scale; }
    Vector2 GetUp() { return transform->Up(); }
    Vector2 GetForward() { return transform->Forward(); }
    void SetId(uint32_t i) { id = i; }
    uint32_t GetId() { return id; }

    void SetPosition(Vector2 pos)
    {
        transform->position = pos;
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
    }
    bool Move(Vector2 dist, Rectangle scene)
    {
        Vector2 lastpos = transform->position;
        transform->position = {lastpos.x + dist.x, lastpos.y + dist.y};
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
        return CheckCollisionPointRec(transform->position, scene);
    }
    void SetRotation(float rot)
    {
        transform->rotation = rot;
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
    }
    void Rotate(float angle)
    {
        transform->rotation += angle;
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
    }
    void SetScale(Vector2 scl)
    {
        transform->scale = scl;
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
    }
#pragma endregion
#pragma region Loop Methods
    // ¿Objetos o Agentes?
    virtual void InitializeObject() = 0;
    void DrawObject()
    {
        if (renderer != nullptr)
        {
            renderer->DrawObject(transform);
        }
    }
    // Returns if the objects has been moved
    virtual bool UpdateObject(double deltaTime, Rectangle scene) = 0;
    void UnloadObject()
    {
        if (renderer != nullptr)
        {
            renderer->UnloadObject();
        }
    }
#pragma endregion
#pragma region Components Methods
    void AddShapeRenderer(Shape2D *r)
    {
        renderer = r;
        renderer->UpdateObject(transform);
    }
    // TODO: Change the vector to a static array
    void AddCollider2D(ColliderType type, vector<Vector2 *> otherPoints = {});

    bool IsColliding(GameObject2D *other);
#pragma endregion
};