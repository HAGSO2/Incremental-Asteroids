#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "EngineObjects/Renderer.h"
#include "EngineObjects/Collider.h"

using namespace std;

struct Transform2D
{
    Vector2 position;
    float rotation;
    Vector2 scale;

    Transform2D(Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : position(pos), rotation(rot), scale(scl) {}
};

class GameObject
{
public:
    GameObject();
    virtual void DrawObject() = 0;
};

class GameObject2D
{
    Transform2D* transform;
    Renderer *renderer;
    Collider2D *collider;

public:
    GameObject2D(Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : transform(new Transform2D(pos, rot, scl))/*, renderer(nullptr)*/, collider(nullptr) {}
    Transform2D* GetTransform() { return transform; }
    Vector2 GetPosition() { return transform->position; }
    float GetRotation() { return transform->rotation; }
    Vector2 GetScale()   { return transform->scale; }

    void SetPosition(Vector2 pos) { transform->position = pos; renderer->UpdateObject(transform); }
    void SetRotation(float rot) { transform->rotation = rot; renderer->UpdateObject(transform); }
    void SetScale(Vector2 scl) { transform->scale = scl; renderer->UpdateObject(transform); }


    void DrawObject() {renderer->DrawObject(transform);}
    void UnloadObject() { renderer->UnloadObject(); }
    // ¿Objetos o Agentes?
    /*
        virtual void InitializeObject() = 0;
        virtual void DrawObject() = 0;
        virtual void UpdateObject(float deltaTime) = 0;
        virtual void UnloadObject() = 0;
        */
    void AddShapeRenderer(Shape2D *r) { renderer = r; }
    void AddCollider2D(ColliderType type, vector<Vector2*> *otherPoints = nullptr);
};