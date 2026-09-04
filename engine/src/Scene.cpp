#include "ProgramFlow/Scene.h"

Scene::Scene() : finishScreen{UNKNOWN}, canvas{UI()} {};

void Scene::InitScene()
{
    // SetMusicVolume(music, 1.0f);
    // PlayMusicStream(music);
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
    // if (music.ctxType != 0)
    // {
    //     UpdateMusicStream(music);
    // }
    ManageInterruptions();
};