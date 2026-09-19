#include "GameObjects/Projectile.h"

Projectile::Projectile(Vector2 pos, Vector2 direction) : GameObject2D(GL_PROJECTILE, pos), direction(direction)
{
    AddShapeRenderer(new Shape2D(S_CIRCLE, PURPLE, 10));
    AddCollider2D(C_CIRCLE);
};

bool Projectile::UpdateObject(double deltaTime, Rectangle scene)
{
    float x = direction.x * PROYECTILE_SPEED * deltaTime;
    float y = direction.y * PROYECTILE_SPEED * deltaTime;
    return Move({x, y}, scene);
}