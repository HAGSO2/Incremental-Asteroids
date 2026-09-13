#include "ProgramFlow/Scene.h"

Scene::Scene()
    : finishScreen(UNKNOWN), canvas(UI()), music({0}), hasMusic(true),
      objectType(OS_NONE), objectSystem(nullptr) {}
Scene::Scene(Music m)
    : finishScreen(UNKNOWN), canvas(UI()), music(m), hasMusic(true),
      objectType(OS_NONE), objectSystem(nullptr) {}
Scene::Scene(OSystemType collisionSystem, Music m)
    : finishScreen(UNKNOWN), canvas(UI()), music(m), hasMusic(true),
      objectType(collisionSystem)
{
  switch (objectType)
  {
  case OS_SIMPLE:
    objectSystem = new SimpleCollision(
        [this](GameObject2D *obj1, GameObject2D *obj2)
        {
          OnCollision(obj1, obj2);
        });
    break;

  default:
    break;
  }
}

Scene::~Scene()
{
  delete objectSystem;
}

void Scene::InitScene()
{
  if (hasMusic)
  {
    SetMusicVolume(music, 0.8f);
    PlayMusicStream(music);
  }
  // Each time a scene is loaded it is created a new object system
  //  as every time the scene is unloaded, the sistem is deleted
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

void Scene::UpdateScreen(double deltaTime)
{
  if (hasMusic)
  {
    UpdateMusicStream(music);
  };
  ManageInterruptions();
  if (objectSystem != nullptr)
  {
    objectSystem->UpdateObjects(deltaTime);
    objectSystem->update();
  }
};

void Scene::DrawScreen()
{
  // Draw all objects of scene
  if (objectSystem != nullptr)
  {
    objectSystem->DrawObjects();
  }

  // Draw canvas
  canvas.Draw();
}

void Scene::UnloadScreen()
{
  delete objectSystem;
}