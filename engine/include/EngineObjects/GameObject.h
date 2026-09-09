#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <cmath>
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
    Transform2D *transform;
    Renderer *renderer;
    Collider2D *collider;

public:
    GameObject2D(Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : transform(new Transform2D(pos, rot, scl)) /*, renderer(nullptr)*/, collider(nullptr) {}
    Transform2D *GetTransform() { return transform; }
    Vector2 GetPosition() { return transform->position; }
    float GetRotation() { return transform->rotation; }
    Vector2 GetScale() { return transform->scale; }

    void SetPosition(Vector2 pos)
    {
        transform->position = pos;
        renderer->UpdateObject(transform);
    }
    void Move(Vector2 dist)
    {
        Vector2 lastpos = transform->position;
        transform->position = {lastpos.x + dist.x, lastpos.y + dist.y};
        renderer->UpdateObject(transform);
    }
    void SetRotation(float rot)
    {
        transform->rotation = rot;
        renderer->UpdateObject(transform);
    }
    void Rotate(float angle)
    {
        transform->rotation += angle;
        renderer->UpdateObject(transform);
    }
    void SetScale(Vector2 scl)
    {
        transform->scale = scl;
        renderer->UpdateObject(transform);
    }

    // ¿Objetos o Agentes?
    virtual void InitializeObject() = 0;
    void DrawObject() { renderer->DrawObject(transform); }
    virtual void UpdateObject(double deltaTime) = 0;
    void UnloadObject() { renderer->UnloadObject(); }

    void AddShapeRenderer(Shape2D *r) { renderer = r; }
    void AddCollider2D(ColliderType type, vector<Vector2 *> *otherPoints = nullptr);

    void DestroyObject();
};