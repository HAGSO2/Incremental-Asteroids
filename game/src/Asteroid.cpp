#include <raylib.h>
#include <raymath.h>
#include "Asteroid.h"

Asteroid::Asteroid(float s, Vector2 center, Vector2 initpos, Vector2 scale) : GameObject2D("asteroid", initpos, 0, scale), speed(s), centerposition(center)
{
    AddShapeRenderer(new Shape2DLined(S_CIRCLE, BLACK, scale.x, WHITE, 1));
    AddCollider2D(C_CIRCLE);
};

void Asteroid::UpdateObject(double deltaTime)
{
    Vector2 direction = Vector2Subtract(centerposition, GetPosition());

    direction = Vector2Normalize(direction);

    direction.x = direction.x * speed * deltaTime;
    direction.y = direction.y * speed * deltaTime;

    Move(direction);
}