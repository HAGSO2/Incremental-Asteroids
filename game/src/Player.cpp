#include "Player.h"

Player::Player() : health{5}, score{0}, playerSprite{Vector2{400, 300}, Vector2{50, 50}, RED, TRIANGLE} {};

void Player::Update(double deltaTime)
{
    // Update player logic here (e.g., movement, collision detection, etc.)
    if (rotateLeft)
    {
        playerSprite.Rotate(-115.0f * deltaTime); // Rotate left at 90 degrees per second
        if (!IsKeyDown(KEY_LEFT))
        {
            rotateLeft = false; // Reset the flag after rotation
        }
    }
    if (rotateRight)
    {
        playerSprite.Rotate(115.0f * deltaTime); // Rotate right at 90 degrees per second
        if (!IsKeyDown(KEY_RIGHT))
        {
            rotateRight = false; // Reset the flag after rotation
        }
    }
};

void Player::Draw()
{
    playerSprite.DrawObject();
};

Projectile* Player::ShootProjectile()
{
    // Create a projectile moving in the direction the player is facing
    float angleInRadians = playerSprite.GetRotation() * (PI / 180.0f);
    Vector2 direction = {cos(angleInRadians), sin(angleInRadians)};
    return new Projectile(playerSprite.GetPosition(), direction);
};