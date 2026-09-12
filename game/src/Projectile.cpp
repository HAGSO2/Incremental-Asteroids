#include "Projectile.h"

Projectile::Projectile(Vector2 pos, Vector2 direction) : GameObject2D("projectile", pos), direction(direction)
{
    AddShapeRenderer(new Shape2D(S_CIRCLE, PURPLE, 10));
    AddCollider2D(C_CIRCLE);
};

void Projectile::UpdateObject(double deltaTime)
{
    float x = direction.x * PROYECTILE_SPEED * deltaTime;
    float y = direction.y * PROYECTILE_SPEED * deltaTime;
    Move({x, y});
}