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

class GameObject
{
public:
    GameObject();
    virtual void DrawObject() = 0;
};

class GameObject2D
{
    string tag;
    Transform2D *transform;
    Renderer *renderer;
    Collider2D *collider;

public:
    static constexpr uint32_t INVALID_INDEX = 0xFFFFFFFF;
    uint32_t id;
    GameObject2D(string tag = "", Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : transform(new Transform2D(pos, rot, scl)), renderer(nullptr), collider(nullptr), tag(tag), id(0) {}
    virtual ~GameObject2D();
    Transform2D *GetTransform() { return transform; }
    Vector2 GetPosition() { return transform->position; }
    float GetRotation() { return transform->rotation; }
    Vector2 GetScale() { return transform->scale; }
    Vector2 GetUp() { return transform->Up(); }
    Vector2 GetForward() { return transform->Forward(); }
    string GetTag() { return tag; }
    void SetId(uint32_t i) { id = i; }
    uint32_t GetId() { return id; }

    void SetPosition(Vector2 pos)
    {
        transform->position = pos;
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
    }
    void Move(Vector2 dist)
    {
        Vector2 lastpos = transform->position;
        transform->position = {lastpos.x + dist.x, lastpos.y + dist.y};
        if (renderer != nullptr)
            renderer->UpdateObject(transform);
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

    // ¿Objetos o Agentes?
    virtual void InitializeObject() = 0;
    void DrawObject()
    {
        if (renderer != nullptr)
        {
            renderer->DrawObject(transform);
        }
    }
    virtual void UpdateObject(double deltaTime) = 0;
    void UnloadObject()
    {
        if (renderer != nullptr)
        {
            renderer->UnloadObject();
        }
    }

    void AddShapeRenderer(Shape2D *r)
    {
        renderer = r;
        renderer->UpdateObject(transform);
    }
    //TODO: Change the vector to a static array
    void AddCollider2D(ColliderType type, vector<Vector2 *> otherPoints = {});

    bool IsColliding(GameObject2D *other);
};