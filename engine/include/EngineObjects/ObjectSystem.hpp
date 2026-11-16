#pragma once
#include <functional>
#include <utility>
#include <vector>
#include "EngineObjects/GameObject.h"

using namespace std;

// Identifies the object management and collision detection strategy to be used
// by the engine. This value can be used to select which implementation to instantiate.
enum ObjectSystemType
{
    OS_NONE = 0,                // Do not use an object/collision system.
    OS_SIMPLE = 1,              // Simple system that compares objects against one another.
    OS_BY_LAYERS = 2,           // System that organizes objects into layers.
    OS_DYNAMIC_AABB_TREE_2D = 3 // Identifier reserved for a 2D dynamic AABB tree.
    // TODO: Add more collision systems here
};

// Base interface for systems that manage 2D objects in a scene.
// Defines the common operations that the various strategies must provide:
// inserting and removing objects, updating them, drawing them, and releasing their resources.
class IObjectSystem
{
    // Objects whose removal has been requested, but which will actually
    // be removed during the next call to update().
    // This queue allows for deferring removal until a controlled point in the cycle.
    vector<GameObject2D *> pendingRemovals;

protected:
    // Rectangle that defines the region considered by the system.
    // It is used as a boundary when updating objects.
    // Initially, it represents an 800 x 600 region starting from the origin.
    Rectangle boundsRect = {0, 0, 800, 600};

    // Function that executes when the system detects a collision.
    // It receives the two objects involved. The scene or the system's owner
    // provides this function when constructing the system.
    function<void(GameObject2D *, GameObject2D *)> collisionCallback;

public:
    // Initializes the system with the function that will notify of collisions.
    // std::move transfers the received function object to the onCollision attribute.
    IObjectSystem(function<void(GameObject2D *, GameObject2D *)> collision)
        : collisionCallback(std::move(collision)), pendingRemovals({}) {}

    // Virtual destructor to allow destruction of derived implementations
    // via a pointer to IObjectSystem.
    virtual ~IObjectSystem();

    // Inserts an object into the implementation's storage structure.
    // Returns true if the insertion was successful, and false if it is not supported.
    virtual bool insert(GameObject2D *obj) = 0;

    // Removes an object from the storage structure.
    // Each implementation must know how to locate and remove it.
    virtual void remove(GameObject2D *obj) = 0;

    // Requests the deferred removal of an object.
    // The object is added to the remove_later queue and will be removed during update().
    // This function does not remove the object immediately.
    void QueueRemoval(GameObject2D *obj) { pendingRemovals.push_back(obj); }

    // Processes the queue of pending deletions.
    // A derived implementation may override update() to also perform
    // its own tasks, such as checking for collisions.
    virtual void update();

    // Initialices the system
    virtual void Init() = 0;

    // Draws all objects managed by the system.
    virtual void DrawObjects() = 0;

    // Updates the logic and state of all objects.
    // deltaTime represents the time elapsed since the previous update.
    virtual void UpdateObjects(double deltaTime) = 0;

    // Releases objects managed by the system.
    // The contract specifies that implementations must dispose of all their objects.
    virtual void UnloadObjects() = 0;

    // Sets the bounding rectangle based on its height and width.
    void SetBounds(float h, float w);

    // Expand the bounding rectangle by adding a margin around its four sides.
    void ExpandBounds(float offset);
};

// Limit on the number of objects supported by the SimpleCollision system.
#define MAX_OBJECTS_SIMPLE 1000

// A simple implementation of an object and collision system.
// It stores all objects in a single vector and checks for collisions
// by comparing each object against those that follow it.
// The computational cost of collision detection grows approximately quadratically
// with the number of objects.
class SimpleCollisionSystem : public IObjectSystem
{
    // A single list of objects managed by this implementation.
    // Each element is a pointer to a GameObject2D.
    vector<GameObject2D *> objects;

public:
    // Inherits constructors from IObjectSystem.
    using IObjectSystem::IObjectSystem;

    // Releases resources specific to this implementation.
    ~SimpleCollisionSystem() override;

    // Adds an object to the vector and assigns it an identifier based on its position.
    bool insert(GameObject2D *obj) override;

    // Removes an object from the vector. To avoid shifting all subsequent elements,
    // it moves the last object into the removed object's position and updates its identifier.
    void remove(GameObject2D *obj) override;

    // Checks for collisions between pairs of objects and processes deferred removals
    // inherited from IObjectSystem.
    void update() override;

    // Initialices the system
    void Init() override { objects = vector<GameObject2D *>(); };

    // Iterates through the vector and draws each object.
    void DrawObjects() override;

    // Updates all objects using deltaTime and the MAX_BOX rectangle.
    // If an object indicates that it should no longer remain within the region,
    // its removal from the system is requested.
    void UpdateObjects(double deltaTime) override;

    // Removes all stored objects and clears the vector.
    void UnloadObjects() override;
};

// Limit on the number of objects allowed per layer in the LayersMaskCollision system.
#define MAX_OBJECTS_LAYERS 500

// Implementation that organizes objects into groups or layers.
// The primary structure is a vector of vectors:
// each inner vector contains the objects belonging to a specific layer.
// The collision mask determines which pairs of layers should be checked.
class LayeredCollisionSystem : public IObjectSystem
{
    size_t numLayers;
    // Storage by layer:
    // objects[layer] contains pointers to the objects in that layer.
    vector<vector<GameObject2D *>> objects;

    // A bitmask that defines collision relationships between layers.
    // Each bit position enables or disables collision checks with another layer.
    // The exact interpretation of these bits is defined within update() and
    // the implementation that constructs and provides these masks.
    vector<uint32_t> layerCollisionMask;

public:
    // Constructs the system, specifying:
    // - numLayers: the number of layers in the storage structure.
    // - masks: the configuration defining which layers should check for collisions with one another.
    // - collision: a callback to be executed when a collision is detected.
    LayeredCollisionSystem(size_t numLayers, vector<uint32_t> masks, function<void(GameObject2D *, GameObject2D *)> collision)
        : IObjectSystem(collision), numLayers(numLayers), layerCollisionMask(masks) {}

    // Releases the objects and data specific to the layer-based system.
    ~LayeredCollisionSystem() override;

    // Inserts an object into the vector corresponding to its layer.
    // The object's identifier represents its position within that layer.
    bool insert(GameObject2D *obj) override;

    // Removes an object from its layer, replacing it with the last element
    // in that layer's vector (if the object is not already in the last position).
    void remove(GameObject2D *obj) override; // Checks for collisions only between pairs of layers enabled
    // by layerCollisionMask. Then, processes deferred removals.
    void update() override;

    void Init() override { objects = vector<vector<GameObject2D *>>(numLayers); }

    // Draws the objects by iterating through the layers in reverse order.
    void DrawObjects() override;

    // Updates the objects in all layers using deltaTime and MAX_BOX.
    // Objects that move outside the region are removed from the system.
    void UpdateObjects(double deltaTime) override;

    // Removes objects from all layers and clears the data structures.
    void UnloadObjects() override;
};