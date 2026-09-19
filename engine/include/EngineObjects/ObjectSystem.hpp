#pragma once
#include <functional>
#include <utility>
#include <vector>
#include "EngineObjects/GameObject.h"

using namespace std;

class IObjectSystem
{
    vector<GameObject2D *> remove_later;
protected:
    Rectangle MAX_BOX = {0, 0, 800, 600};
    function<void(GameObject2D *, GameObject2D *)> onCollision;

public:
    IObjectSystem(function<void(GameObject2D *, GameObject2D *)> collision)
        : onCollision(std::move(collision)), remove_later({}) {}
    virtual ~IObjectSystem() = default;
    virtual bool insert(GameObject2D *obj) = 0;
    virtual void remove(GameObject2D *obj) = 0;
    void save_remove(GameObject2D *obj) { remove_later.push_back(obj); }
    virtual void update();

    virtual void DrawObjects() = 0;
    virtual void UpdateObjects(double deltaTime) = 0;
    void ChangeForm(float h, float w);
    void AddOffset(float offset);
};

#define MAX_OBJECTS_SIMPLE 1000

// Can handle a maximum of 1000 objects,
// checking object by object
class SimpleCollision : public IObjectSystem
{
    vector<GameObject2D *> objects;

public:
    using IObjectSystem::IObjectSystem;
    ~SimpleCollision() override;
    bool insert(GameObject2D *obj) override;
    void remove(GameObject2D *obj) override;
    void update() override;

    void DrawObjects() override;
    void UpdateObjects(double deltaTime) override;
};

#define MAX_OBJECTS_LAYERS 500

// Can handle a maximum of 100 objects,
// checking object by layer

class LayersMaskCollision : public IObjectSystem
{
    vector<vector<GameObject2D *>> objects;
    vector<uint32_t> layerCollisionMask;

public:
    LayersMaskCollision(size_t numLayers, vector<uint32_t> masks, function<void(GameObject2D *, GameObject2D *)> collision)
        : IObjectSystem(collision), objects(numLayers), layerCollisionMask(masks) {}
    ~LayersMaskCollision() override;
    bool insert(GameObject2D *obj) override;
    void remove(GameObject2D *obj) override;
    void update() override;

    void DrawObjects() override;
    void UpdateObjects(double deltaTime) override;
};