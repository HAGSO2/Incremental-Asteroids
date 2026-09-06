#pragma once
#include <vector>
#include <raylib.h>

using namespace std;
enum CollisionLayer
{
    Player = 1 << 0,
    Enemy = 1 << 1,
    PlayerProjectile = 1 << 2
};

bool CheckCollisionLayers(CollisionLayer layer1, CollisionLayer layer2) { return (layer1 & layer2) != 0; };

enum ColliderType
{
    //TODO: Line
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
    bool isColliding(Vector2 p);
    bool isColliding(Collider2D *other);
};

class Dynamic_AABB_tree
{
public:
    Dynamic_AABB_tree();
};