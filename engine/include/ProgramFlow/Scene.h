#pragma once
#include <raylib.h>
#include "EngineObjects/UI.h"
#include "EngineObjects/GameObject.h"
#include "EngineObjects/CollisionLayers.h"

enum GameScreen
{
	UNKNOWN = -1,
	LOGO = 0,
	TITTLE = 1,
	GAMEPLAY = 2,
	GAMEOVER = 3
};

enum CollisionSystem
{
	BY_LAYERS = 0,
	DYNAMIC_AABB_TREE_2D = 1
	// TODO: Add more collision systems here
};

#define GameplayButtonText "Play!"

class Scene
{
	CollisionSystem collisionSystem = BY_LAYERS;
	// Get the game objects and their collision layers
	// And set the collision mask for each layer
	vector<pair<vector<GameObject2D *>, CollisionLayer>> gameObjects;

protected:
	GameScreen finishScreen;
	Vector2 mousePosition;
	UI canvas;
	Color backgroundColor;
	Music music;
	bool hasMusic = false;

public:
	Scene(CollisionSystem collisionSystem = BY_LAYERS);
	Scene(CollisionSystem collisionSystem = BY_LAYERS, Music m);
	virtual void InitScene();
	virtual void UpdateScreen(double deltaTime);
	
	virtual void DrawScreen() = 0;
	virtual void UnloadScreen() = 0;
	GameScreen FinishScreen() { return finishScreen; };

	virtual void OnMouseDown() = 0;
	virtual void OnKeyPressed(KeyboardKey) = 0;
	virtual void OnCollision(GameObject2D *obj1, GameObject2D *obj2) = 0;

	void ChangeScene(GameScreen sc) { finishScreen = sc; }
	Music GetMusic() { return music; };
	void AddGameObject(GameObject2D *obj, CollisionLayer layer) { gameObjects[layer].first.push_back(obj); }

private:
	void ManageInterruptions();
	void ManageCollisions();
};

void AddShape2D(Scene *scene, Vector2 pos, float rot = 0, Vector2 scl = {1.0f, 1.0f}, Shape2D *shape, CollisionLayer layer);