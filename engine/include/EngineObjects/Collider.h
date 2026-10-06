#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Collider2D
{
public:
    virtual ~Collider2D() = default;
    virtual bool isColliding(Vector2 p) = 0;
    virtual bool isColliding(Vector2 p1, Vector2 p2) = 0;
    virtual bool isColliding(Collider2D *other) = 0;
};

enum ColliderType
{
    // TODO: Line
    C_RECTANGLE = 0,
    C_CIRCLE = 1,
    C_CUSTOM = 2
};

class ShapeCollider : public Collider2D
{
    ColliderType form;
    vector<Vector2 *> points;

public:
    ShapeCollider(ColliderType form, vector<Vector2 *> points) : form(form), points(points) {};
    ~ShapeCollider();
    bool isColliding(Vector2 p) override;
    bool isColliding(Vector2 p1, Vector2 p2) override;
    bool isColliding(Collider2D *other) override;
};

// struct Collider2D
// {
//     ColliderType form;
//     // As for RECTANGLE and CIRCLE points are:
//     // points[0] == transform.(Vector2 position)
//     // points[1] == transform.(Vector2 scale)
//     vector<Vector2 *> points;

// public:
//     Collider2D(ColliderType form, vector<Vector2 *> points) : form(form), points(points) {};
//     ~Collider2D();
//     bool isColliding(Vector2 p);
//     bool isColliding(Collider2D *other);
// };