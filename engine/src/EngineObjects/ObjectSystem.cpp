#include "EngineObjects/ObjectSystem.hpp"

// -----------------------------------------------------------------------------
// Common implementation of IObjectSystem
// -----------------------------------------------------------------------------

// Base class destructor.
// Frees any objects still remaining in the deferred removal queue.
// It does not iterate over active objects belonging to derived implementations here.
IObjectSystem::~IObjectSystem()
{
    for (int i = 0; i < pendingRemovals.size(); i++)
    {
        if (pendingRemovals[i] != nullptr)
            delete pendingRemovals[i];
    }
}

// Processes the queue of objects marked for removal via save_remove().
// For each object, it removes it from the concrete implementation's structure
// and then frees its memory. Finally, it clears the pending removal queue.
void IObjectSystem::update()
{
    for (int i = 0; i < pendingRemovals.size(); ++i)
    {
        remove(pendingRemovals[i]);
        delete pendingRemovals[i];
    }
    pendingRemovals.clear();
}

// Defines the rectangular region used by the system to control boundaries.
// The origin is reset to (0, 0), and the provided height and width are assigned.
void IObjectSystem::SetBounds(float h, float w)
{
    boundsRect.x = 0;
    boundsRect.y = 0;
    boundsRect.height = h;
    boundsRect.width = w;
}

// Expands the MAX_BOX region by adding a margin on each side.
// The origin shifts upward and to the left, while the height and width
// increase by twice the margin value.
void IObjectSystem::ExpandBounds(float offset)
{
    boundsRect.x -= offset;
    boundsRect.y -= offset;
    boundsRect.height += offset * 2;
    boundsRect.width += offset * 2;
}

#pragma region SimpleCollision

// -----------------------------------------------------------------------------
// SimpleCollision Implementation
// -----------------------------------------------------------------------------

// Destructor for the simple system.
// Remove the objects still stored in the vector.
// Then clean up pending objects from the base class

SimpleCollisionSystem::~SimpleCollisionSystem()
{
    UnloadObjects();
}

// Inserts an object into the single vector of objects.
// The object's identifier is set based on the position it will occupy
// in the vector, and then its pointer is stored.
bool SimpleCollisionSystem::insert(GameObject2D *obj)
{
    if (objects.size() > MAX_OBJECTS_SIMPLE)
        return false;
    obj->id = (uint32_t)objects.size();
    objects.push_back(obj);
    return true;
}

// Removes an object using its identifier as an index.
// To avoid shifting all subsequent elements, it copies the last object
// into the position of the removed object and updates the moved object's ID.
// It then shrinks the vector and marks the removed object's ID as invalid.
void SimpleCollisionSystem::remove(GameObject2D *obj)
{
    uint32_t idx = obj->id;
    uint32_t last = (uint32_t)objects.size() - 1;
    if (idx != last)
    {
        objects[idx] = objects[last];
        objects[idx]->id = idx; // update the object that was moved
    }
    objects.pop_back();
    obj->id = GameObject2D::INVALID_INDEX;
}

// Checks for collisions between all possible pairs of objects. // The index j starts at i + 1, ensuring each pair is checked only once
// and no object is compared with itself.
// If IsColliding() returns true, the pair is notified via onCollision.
// Deferred removals are processed at the end.
void SimpleCollisionSystem::update()
{
    for (size_t i = 0; i < objects.size(); ++i)
    {
        for (size_t j = i + 1; j < objects.size(); ++j)
        {
            if (i != j && objects[i]->IsColliding(objects[j]))
            {
                collisionCallback(objects[i], objects[j]);
            }
        }
    }
    IObjectSystem::update();
}

// Draws all stored objects in the order they appear in the vector.
void SimpleCollisionSystem::DrawObjects()
{
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->DrawObject();
    }
}

// Updates the objects one by one.
// Each object receives the elapsed time and the bounding region MAX_BOX.
// If UpdateObject() returns false, the object is removed from the vector.
void SimpleCollisionSystem::UpdateObjects(double deltaTime)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (!objects[i]->UpdateObject(deltaTime, boundsRect))
        {
            // The object has indicated that it is out of bounds.
            remove(objects[i]);
        }
    }
}

// Destroys all stored objects and clears the vector.
void SimpleCollisionSystem::UnloadObjects()
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
    objects.clear();
}

#pragma endregion

#pragma region LayersCollision
// -----------------------------------------------------------------------------
// Implementation of LayeredCollisionSystem
// -----------------------------------------------------------------------------

// Destructor for the layer-based system.
// The intent is to release pending objects, destroy objects
// stored within the layers, and clear the collision mask.
// Note: The explicit call to the base destructor should be reviewed for the same
// reason mentioned in SimpleCollision: the base class is destroyed automatically.
LayeredCollisionSystem::~LayeredCollisionSystem()
{
    UnloadObjects();
    layerCollisionMask.clear();
};

// Inserts an object into the layer corresponding to its 'layer' value.
// The loop shifts the mask to the right and counts the shifts;
// this counter is used as the layer index.
// The ID assigned to the object is its position within that layer's vector.
bool LayeredCollisionSystem::insert(GameObject2D *obj)
{
    uint32_t laux = obj->layer;
    int layer = 0;
    while (laux != 0)
    {
        layer++;
        laux = laux >> 1;
    };
    if (objects[layer].size() > MAX_OBJECTS_LAYERS)
        return false;
    obj->id = objects[layer].size();
    objects[layer].push_back(obj);
    return true;
};

// Removes an object from the layer calculated based on obj->layer.
// It uses the object's ID as an index; if the object is not the last one,
// it moves the last element to that position and updates its ID.
// Finally, it removes the last position and marks the removed ID as invalid.
void LayeredCollisionSystem::remove(GameObject2D *obj)
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

// Checks for collisions between layers based on the configured mask.
// Iterates through layers l1 and l2, comparing their objects only if the
// corresponding bit in layerCollisionMask[l1] is set.
// For each enabled pair of layers, it compares all objects from both layers.
// If a collision is detected, it executes the onCollision callback.
// Once finished, it processes the deferred removal queue from the base class.
void LayeredCollisionSystem::update()
{
    for (int l1 = 0; l1 < objects.size() - 1; ++l1)
    { // For each layer...
        if (layerCollisionMask[l1] == 0)
            continue;
        for (int l2 = l1 + 1; l2 < objects.size(); ++l2)
        { // Look at subsequent layers...
            if ((layerCollisionMask[l1] & (1 << (l2 - 1))) != 0)
            { // If the mask indicates that collisions should be checked...
                for (int i = 0; i < objects[l1].size(); ++i)
                { // Check potential pairs of objects...
                    for (int j = 0; j < objects[l2].size(); ++j)
                    {
                        if (objects[l1][i]->IsColliding(objects[l2][j]))
                        { // Notify of the collision...
                            collisionCallback(objects[l1][i], objects[l2][j]);
                        }
                    }
                }
            }
        }
    }
    IObjectSystem::update();
}

// Draws the objects, starting from the last layer and ending with the first.
// This reverse order is used because, according to the original comment,
// Raylib's drawing order causes elements drawn later to appear
// on top of those drawn earlier.
void LayeredCollisionSystem::DrawObjects()
{
    // The layer order is reversed to control which objects remain visible on top.
    for (int i = objects.size() - 1; i > -1; --i)
    {
        for (int j = 0; j < objects[i].size(); j++)
        {
            objects[i][j]->DrawObject();
        }
    }
}

// Updates all objects, iterating first through the layers and then
// through the objects within each layer. Each object receives deltaTime and MAX_BOX.
// If UpdateObject() returns false, the object is removed from its layer.
void LayeredCollisionSystem::UpdateObjects(double deltaTime)
{
    for (int i = 0; i < objects.size(); ++i)
    {
        for (int j = 0; j < objects[i].size(); ++j)
        {
            if (!objects[i][j]->UpdateObject(deltaTime, boundsRect))
            {
                // The object has indicated that it is out of bounds.
                remove(objects[i][j]);
            }
        }
    }
}

// Destroys all objects across all layers.
// It first iterates through and clears each inner vector, and finally
// removes the outer layer structure itself.
void LayeredCollisionSystem::UnloadObjects()
{
    for (int i = 0; i < objects.size(); ++i)
    {
        for (int j = 0; j < objects[i].size(); ++j)
        {
            delete objects[i][j];
        }
        objects[i].clear();
    }
    objects.clear();
}

#pragma endregion