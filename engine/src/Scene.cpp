#include "ProgramFlow/Scene.h"

Scene::Scene() :finishScreen{ UNKNOWN }, canvas{UI()} {};

void Scene::ManageInterruptions(){
    if(IsMouseButtonDown(0)){
        mousePosition = GetMousePosition();
        OnMouseDown();
    }

    OnKeyPressed((KeyboardKey)GetKeyPressed());
};

void Scene::UpdateScreen(){
    ManageInterruptions();
};