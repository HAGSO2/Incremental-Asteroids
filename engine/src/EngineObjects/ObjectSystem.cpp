#include "EngineObjects/ObjectSystem.hpp"

#pragma region SimpleCollision

SimpleCollision::~SimpleCollision()
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
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

void SimpleCollision::DrawObjects()
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->DrawObject();
    }
}

void SimpleCollision::UpdateObjects(double deltaTime)
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->UpdateObject(deltaTime);
    }
}

#pragma endregion

#pragma region LayersCollision

LayersMaskCollision::~LayersMaskCollision()
{
    for (int i = 0; i < objects.size(); ++i)
    {
        for (int j = 0; j < objects[i].size(); ++j)
        {
            delete objects[i][j];
        }
        objects[i].clear();
    }
};

void LayersMaskCollision::insert(GameObject2D *obj)
{
    uint32_t laux = obj->layer;
    int layer = 0;
    while (laux != 0)
    {
        layer++;
        laux = laux >> 1;
    };
    obj->id = objects[layer].size();
    objects[layer].push_back(obj);
};

void LayersMaskCollision::remove(GameObject2D *obj)
{
    uint32_t idx = obj->id;
    uint32_t laux = obj->layer;
    int layer = 0;
    while (laux != 0)
    {
        layer++;
        laux = laux >> 1;
    };
    uint32_t last = (uint32_t)objects[layer].size() - 1;
    if (idx != last)
    {
        objects[layer][idx] = objects[layer][last];
        objects[layer][idx]->id = idx;
    }
    objects[layer].pop_back();
    obj->id = GameObject2D::INVALID_INDEX;
};

void LayersMaskCollision::update()
{
    for (int l1 = 0; l1 < layerCollisionMask.size(); ++l1)
    { // For each layer...
        if (layerCollisionMask[l1] == 0)
            continue;
        for (int l2 = l1 + 1; l2 < objects.size(); ++l2)
        { // Seek for each layer above...
            if (((1 << (l2 - 1)) & layerCollisionMask[l1]) != 0)
            { // if the mask is define to collide...
                for (int i = 0; i < objects[l1].size(); ++i)
                { // Check every posible collision...
                    for (int j = 0; j < objects[l2].size(); ++j)
                    {
                        if (objects[l1][i]->IsColliding(objects[l2][j]))
                        { // fire collisoin function
                            onCollision(objects[l1][i], objects[l2][j]);
                        }
                    }
                }
            }
        }
    }
}

void LayersMaskCollision::DrawObjects()
{
    // As raylib draws to the bottom the first drawed objects, order in layers are inverted.
    // This is to let starter layers that ussually have player objects grant visibility
    for (int i = objects.size() - 1; i > -1; --i)
    {
        for (int j = 0; j < objects[i].size(); j++)
        {
            objects[i][j]->DrawObject();
        }
    }
}

void LayersMaskCollision::UpdateObjects(double deltaTime)
{
    for (int i = 0; i < objects.size(); ++i)
    {
        for (int j = 0; j < objects[i].size(); ++j)
        {
            objects[i][j]->UpdateObject(deltaTime);
        }
    }
}

#pragma endregion