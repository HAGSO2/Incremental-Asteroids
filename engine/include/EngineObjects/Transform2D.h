#pragma once

struct Transform2D
{
    Vector2 position;
    float rotation;
    Vector2 scale;

    Transform2D(Vector2 pos = {0, 0}, float rot = 0.0f, Vector2 scl = {1, 1})
        : position(pos), rotation(rot), scale(scl) {};
    Vector2 Up()
    {
        float rad = rotation + 90 * (PI / 180.0f);
        return Vector2{static_cast<float>(cos(rad)), static_cast<float>(sin(rad))};
    };
    Vector2 Forward()
    {
        float rad = rotation * (PI / 180.0f);
        return Vector2{static_cast<float>(cos(rad)), static_cast<float>(sin(rad))};
    };
};
