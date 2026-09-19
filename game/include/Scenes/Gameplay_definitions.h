#pragma once

#define PROYECTILE_SPEED 300
#define PLAYER_RADIUS 50.0f

#define MAX_ASTEROID 70.0f
#define MAX_PROYECTILES 20

// If collisions cost NUM_ASTEROIDS x NUM_PROJECTILES, then we can have a maximum of 70 asteroids and 20 projectiles
// before the game starts to lag. This is because the collision detection algorithm checks each projectile against each asteroid,
// resulting in a total of 70 x 20 = 1400 collision checks per frame (in the worst case). If the number of asteroids or projectiles exceeds these limits,
// the game may experience performance issues due to the increased number of collision checks required.

#define ASTEROID_SPAWN_INTERVAL 2.0f
#define ASTEROID_MIN_DISTANCE 150.0f
#define PLAYER_LIVES 5

#define NUMBER_LAYERS 4

enum GameplayLayers
{
    GL_NONE = 0,
    GL_PLAYER = 1 << 0,    //[1]
    GL_ASTEROID = 1 << 1,  //[2]
    GL_PROJECTILE = 1 << 2 //[3]
};