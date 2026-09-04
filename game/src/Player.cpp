#include "Player.h"

SpriteFormLined Player::CreateSprite()
{
    Vector2 center = {400, 300};  // Center position of the triangle
    float alpha = 1.25f * PI;     // 120 degrees in radians for an equilateral triangle
    float radius = PLAYER_RADIUS; // Distance from the center to a vertex
    float halfBase = radius * std::cos(alpha);
    float height = radius * std::sin(alpha);
    Vector2 p1 = {center.x - halfBase, center.y + height}; // Left vertex
    Vector2 p2 = {center.x + halfBase, center.y + height}; // Right vertex
    Vector2 p3 = {center.x, center.y + radius};            // Apex
    return SpriteFormLined(p1, p2, p3, BLACK, 270.0f, WHITE, 1);
}

Player::Player(int lives) : health(lives), score(0), rotateLeft(false), rotateRight(false), playerSprite(CreateSprite()) {};

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

Projectile *Player::ShootProjectile()
{
    // Create a projectile moving in the direction the player is facing
    float angleInRadians = playerSprite.GetRotation() * (PI / 180.0f);
    // As for raylib, the y-axis and x-axis are inverted,
    //  so we need to negate the sin component for the direction vector.
    Vector2 direction = {-cos(angleInRadians), -sin(angleInRadians)};
    // return new Projectile(playerSprite.GetPosition(), direction);
    return new Projectile(playerSprite.GetApex(), direction);
};