#include "ProgramFlow/Scene.h"

Scene::Scene(CollisionSystem collisionSystem = SIMPLE) : finishScreen{UNKNOWN}, canvas{UI()}, hasMusic{false}, collisionSystem{collisionSystem} {};
Scene::Scene(CollisionSystem collisionSystem = SIMPLE, Music m) : finishScreen{UNKNOWN}, canvas{UI()}, music{m}, hasMusic{true}, collisionSystem{collisionSystem} {}

void Scene::InitScene()
{
    if (hasMusic)
    {
        SetMusicVolume(music, 0.8f);
        PlayMusicStream(music);
    }
    if (collisionSystem == BY_LAYERS)
    {
        //TODO: Create layers and Masks
    }
    else if (collisionSystem == DYNAMIC_AABB_TREE_2D)
    {
        //TODO: Create the dinamic tree;
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

void Scene::ManageCollisions(){
    if (collisionSystem == BY_LAYERS){
        //TODO: Update by layers
    }
    else if (collisionSystem == DYNAMIC_AABB_TREE_2D){
        //TODO: Update dinamic AABB tree
        return;
    }
}

void Scene::UpdateScreen(double deltaTime)
{
    if (hasMusic)
    {
        UpdateMusicStream(music);
    }
    ManageInterruptions();
    ManageCollisions();
};

void AddShape2D(Scene *scene, Vector2 pos, float rot = 0, Vector2 scl = {1.0f, 1.0f}, Shape2D *shape, CollisionLayer layer)
{
    GameObject2D *obj = new GameObject2D(pos, rot, scl);
    obj->AddShapeRenderer(shape);
    scene->AddGameObject(obj);
}