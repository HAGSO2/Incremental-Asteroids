#pragma once
#include "EngineObjects/Collider.h"
#include "EngineObjects/GameObject.h"
#include "EngineObjects/ObjectSystem.hpp"
#include "EngineObjects/UI.h"
#include <raylib.h>

enum GameScreen
{
  UNKNOWN = -1,
  LOGO = 0,
  TITTLE = 1,
  GAMEPLAY = 2,
  GAMEOVER = 3
};

enum OSystemType
{
  OS_NONE = 0,
  OS_SIMPLE = 1,
  OS_BY_LAYERS = 2,
  OS_DYNAMIC_AABB_TREE_2D = 3
  // TODO: Add more collision systems here
};

class Scene
{
  // TODO: Make a collision system interface and have just a pointer
  OSystemType objectType;
  IObjectSystem *objectSystem;

protected:
  GameScreen finishScreen;
  Vector2 mousePosition;
  UI canvas;
  Color backgroundColor;
  Music music;
  bool hasMusic = false;

public:
  Scene();
  Scene(Music m);
  Scene(OSystemType collisionSystem, Music m = {0}, int layers = 0, vector<uint32_t> mask = {});
  virtual ~Scene();
  virtual void InitScene();
  virtual void UpdateScreen(double deltaTime);
  virtual void DrawScreen();
  virtual void UnloadScreen();
  GameScreen FinishScreen() { return finishScreen; };
  void ChangeScene(GameScreen sc) { finishScreen = sc; }
  Music GetMusic() { return music; };

protected:
  virtual void OnMouseDown() = 0;
  virtual void OnKeyPressed(KeyboardKey) = 0;
  virtual void OnCollision(GameObject2D *obj1, GameObject2D *obj2) = 0;

  void AddGameObject(GameObject2D *obj) { objectSystem->insert(obj); };
  void EraseGameobject(GameObject2D *obj) { objectSystem->remove(obj); };

private:
  void ManageInterruptions();
};

// void AddShape2D(Scene *scene, Vector2 pos, float rot = 0, Vector2 scl =
// {1.0f, 1.0f}, Shape2D *shape, CollisionLayer layer);