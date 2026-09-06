#pragma once

struct Transform2D
{
    Vector2 position;
    float rotation;
    Vector2 scale;

    Transform2D(Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : position(pos), rotation(rot), scale(scl) {}
};
