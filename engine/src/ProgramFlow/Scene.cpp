#include "ProgramFlow/Scene.h"

Scene::Scene() : finishScreen{UNKNOWN}, canvas{UI()}, hasMusic{false} {};
Scene::Scene(Music m) : finishScreen{UNKNOWN}, canvas{UI()}, music{m}, hasMusic{true} {}

void Scene::InitScene()
{
    if (hasMusic)
    {
        SetMusicVolume(music, 0.8f);
        PlayMusicStream(music);
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

void Scene::UpdateScreen(double deltaTime)
{
    if (hasMusic)
    {
        UpdateMusicStream(music);
    }
    ManageInterruptions();
};