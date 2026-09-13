#include "EngineObjects/ObjectSystem.hpp"

SimpleCollision::~SimpleCollision(){
    for(int i = 0; i < objects.size(); i++) {delete objects[i];}
    objects.clear();
}

void SimpleCollision::insert(GameObject2D *obj)
{
    obj->id = (uint32_t)objects.size();
    objects.push_back(obj);
}

void SimpleCollision::remove(GameObject2D *obj)
{
    uint32_t idx = obj->id;
    uint32_t last = (uint32_t)objects.size() - 1;
    if (idx != last)
    {
        objects[idx] = objects[last];
        objects[idx]->id = idx; // actualizar al que movimos
    }
    objects.pop_back();
    obj->id = GameObject2D::INVALID_INDEX;
}

void SimpleCollision::update()
{
    for (size_t i = 0; i < objects.size(); ++i)
    {
        for (size_t j = i + 1; j < objects.size(); ++j)
        {
            if (i != j && objects[i]->IsColliding(objects[j]))
            {
                onCollision(objects[i], objects[j]);
            }
        }
    }
}

void SimpleCollision::DrawObjects(){
    for(int i = 0; i < objects.size(); i++){objects[i]->DrawObject();}
}

void SimpleCollision::UpdateObjects(double deltaTime){
    for(int i = 0; i < objects.size(); i++){objects[i]->UpdateObject(deltaTime);}
}