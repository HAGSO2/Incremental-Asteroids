#include "Player.h"

Player::Player() : health{100}, score{0}, playerSprite{Vector2{400, 300}, Vector2{50, 50}, RED, TRIANGLE} {};

void Player::Update()
{
    // Update player logic here (e.g., movement, collision detection, etc.)
};

void Player::Draw()
{
    playerSprite.DrawObject();
};