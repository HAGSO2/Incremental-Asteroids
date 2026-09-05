#pragma once
#include <raylib.h>
enum CollisionLayer{
    Player = 1 << 0,
    Enemy = 1 << 1,
    PlayerProjectile = 1 << 2
};

bool CheckCollisionLayers(CollisionLayer layer1, CollisionLayer layer2){return (layer1 & layer2) != 0;};

// class Collider2D{
//     CollisionLayer layer;
//     CollisionLayer mask;
//     Rectangle bounds;
//     Circle circleBounds;
// public:
//     Collider2D(CollisionLayer l, CollisionLayer m) : layer(l), mask(m) {};
// };

