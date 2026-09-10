#include "ProgramFlow/Scene.h"

Scene::Scene()
    : finishScreen(UNKNOWN), canvas(UI()), music({0}), hasMusic(true),
      collisionSystem(CS_SIMPLE) {};
Scene::Scene(Music m)
    : finishScreen(UNKNOWN), canvas(UI()), music(m), hasMusic(true),
      collisionSystem(CS_SIMPLE) {};
Scene::Scene(CollisionSystem collisionSystem, Music m)
    : finishScreen(UNKNOWN), canvas(UI()), music(m), hasMusic(true),
      collisionSystem(collisionSystem) {}

void Scene::InitScene()
{
  if (hasMusic)
  {
    SetMusicVolume(music, 0.8f);
    PlayMusicStream(music);
  }
  if (collisionSystem == CS_BY_LAYERS)
  {
    // TODO: Create layers and Masks
  }
  else if (collisionSystem == CS_DYNAMIC_AABB_TREE_2D)
  {
    // TODO: Create the dinamic tree;
  }
}

void Scene::AddGameObject(GameObject2D *obj){
  switch (collisionSystem)
  {
  case CS_SIMPLE:
    simpleObjects.push_back(obj);
    break;
  //TODO: Others systems
  default:
    break;
  }
}

void Scene::ManageInterruptions()
{
  if (IsMouseButtonDown(0))
  {
    mousePosition = GetMousePosition();
    OnMouseDown();
  }

  OnKeyPressed((KeyboardKey)GetKeyPressed());
};

void Scene::ManageCollisions()
{
  if (collisionSystem == CS_SIMPLE)
  {
    for (int i = 0; i < simpleObjects.size(); i++)
    {
      for (int j = 0; j < simpleObjects.size(); j++)
      {
        // TODO: simple collision system
        continue;
      }
    }
  }
  else if (collisionSystem == CS_BY_LAYERS)
  {
    // TODO: Update by layers
  }
  else if (collisionSystem == CS_DYNAMIC_AABB_TREE_2D)
  {
    // TODO: Update dinamic AABB tree
    return;
  }
}

void Scene::UpdateScreen(double deltaTime)
{
  if (hasMusic)
  {
    UpdateMusicStream(music);
  };
  ManageInterruptions();
  ManageCollisions();

  for (int i = 0; i < simpleObjects.size(); i++)
  {
    simpleObjects[i]->UpdateObject(deltaTime);
  }
};

void Scene::DrawScreen(){
  //Draw all objects of scene
  for (int i = 0; i < simpleObjects.size(); i++)
  {
    simpleObjects[i]->DrawObject();
  }

  //Draw canvas
  canvas.Draw();
}
/*
void AddShape2D(Scene *scene, Vector2 pos, float rot = 0, Vector2 scl =
{1.0f, 1.0f}, Shape2D *shape, CollisionLayer layer)
{
    GameObject2D *obj = new GameObject2D(pos, rot, scl);
    obj->AddShapeRenderer(shape);
    scene->AddGameObject(obj);
}*/