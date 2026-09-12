#include "Player.h"

void Player::CreateSprite()
{
    float alpha = 1.25f * PI;     // 120 degrees in radians for an equilateral triangle
    float radius = PLAYER_RADIUS; // Distance from the center to a vertex
    float halfBase = radius * std::cos(alpha);
    float height = radius * std::sin(alpha);
    // Vector2 p1 = {-halfBase, height}; // Left vertex
    // Vector2 p2 = {halfBase, height};  // Right vertex
    // Vector2 p3 = {0, radius};         // Apex
    Vector2 p1 = {height, -halfBase}; // Left vertex
    Vector2 p2 = {height, halfBase};  // Right vertex
    Vector2 p3 = {radius, 0};         // Apex
    // Shape2DLined(Vector2 p1, Vector2 p2, Vector2 p3, Color c, Color linec, float linel); // Constructor for TRIANGLE
    Shape2DLined *renderer = new Shape2DLined(p1, p3, p2, BLACK, WHITE, 1);
    AddShapeRenderer(renderer);
    // return SpriteFormLined(p1, p2, p3, BLACK, 270.0f, WHITE, 1);
}

Player::Player(Vector2 pos) : GameObject2D("player", pos, 90), rotateLeft(false), rotateRight(false)
{
    CreateSprite();
    AddCollider2D(C_CIRCLE);
};

Player::~Player(){
    GameObject2D::~GameObject2D();
}

void Player::UpdateObject(double deltaTime)
{
    // Update player logic here (e.g., movement, collision detection, etc.)
    if (rotateLeft)
    {
        Rotate(-115.0f * deltaTime);
        // playerSprite.Rotate(-115.0f * deltaTime); // Rotate left at 90 degrees per second
        if (!IsKeyDown(KEY_LEFT))
        {
            rotateLeft = false; // Reset the flag after rotation
        }
    }
    if (rotateRight)
    {
        Rotate(115.0f * deltaTime);
        // playerSprite.Rotate(115.0f * deltaTime); // Rotate right at 90 degrees per second
        if (!IsKeyDown(KEY_RIGHT))
        {
            rotateRight = false; // Reset the flag after rotation
        }
    }
};

// void Player::Draw()
// {
//     playerSprite.DrawObject();
// };

// Projectile *Player::ShootProjectile()
// {
//     // Create a projectile moving in the direction the player is facing
//     float angleInRadians = playerSprite.GetRotation() * (PI / 180.0f);
//     // As for raylib, the y-axis and x-axis are inverted,
//     //  so we need to negate the sin component for the direction vector.
//     Vector2 direction = {-cos(angleInRadians), -sin(angleInRadians)};
//     // return new Projectile(playerSprite.GetPosition(), direction);
//     return new Projectile(playerSprite.GetApex(), direction);
// };