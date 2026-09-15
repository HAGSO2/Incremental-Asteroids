#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

// #define LAYERS_NUMBER 3

// enum GameplayLayers
// {
//     CL_NONE = 0,
//     CL_PLAYER = 1 << 0,
//     CL_ENEMY = 1 << 1,
//     CL_PROJECTILE = 1 << 2
// };

enum ColliderType
{
    // TODO: Line
    C_RECTANGLE = 0,
    C_CIRCLE = 1,
    C_CUSTOM = 2
};

struct Collider2D
{
    ColliderType form;
    // As for RECTANGLE and CIRCLE points are:
    // points[0] == transform.(Vector2 position)
    // points[1] == transform.(Vector2 scale)
    vector<Vector2 *> points;

public:
    Collider2D(ColliderType form, vector<Vector2 *> points) : form(form), points(points) {};
    ~Collider2D();
    bool isColliding(Vector2 p);
    bool isColliding(Collider2D *other);
};