#pragma once

// Dependencies for the Scene class:
// - Collider.h: types and functionality related to collisions.
// - GameObject.h: definition of game objects.
// - ObjectSystem.hpp: system responsible for managing objects.
// - ISerializable.hpp: serialization interface implemented by Scene.
// - GameScreen.h: identifiers or types for game screens/scenes.
// - UI.h: graphical user interface system.
// - raylib.h: Raylib types and functionality (vectors, colors, music, input, etc.).
#include "EngineObjects/Collider.h"
#include "EngineObjects/GameObject.h"
#include "EngineObjects/ObjectSystem.hpp"
#include "ProgramFlow/ISerializable.hpp"
#include "ProgramFlow/GameScreen.h"
#include "EngineObjects/UI.h"
#include <raylib.h>

// Represents a game scene or screen.
// Acts as a base class: it gathers the common state of scenes and defines
// the operations that each specific scene must implement.
class Scene : public ISerializable
{
  // Type of object system used by this scene.
  OSystemType objectType;
  // System that manages the objects belonging to the scene.
  // It is responsible for adding, removing, and managing the objects
  // in the scene in the most optimal way possible.
  IObjectSystem *objectSystem;

protected:
  // Identifier for the screen/scene currently being executed.
  GameScreen actualScreen;
  // Scene to transition to when this one ends or a change is requested.
  GameScreen finishScreen;

  // Last known mouse position, expressed as 2D coordinates.
  Vector2 mousePosition;

  // Canvas or graphical interface context associated with this scene.
  UI canvas;

  // Color used as the background when drawing the scene.
  Color backgroundColor;
  // Music resource associated with the scene.
  Music music;
  bool hasMusic = false;

public:
  // Constructors:
  // Allow for the creation of a scene by specifying the associated screen.
  Scene(GameScreen gs);
  Scene(GameScreen gs, Music m);
  // Configurable variant: in addition to the screen and music, it allows
  // specifying the type of object/collision system, the number of layers, and a mask.
  // Default values ​​allow for the omission of music, layers, and the mask.
  Scene(GameScreen gs, OSystemType collisionSystem, Music m = {0}, int layers = 0, vector<uint32_t> mask = {});

  // Virtual destroyer: allows you to correctly destroy objects of derived classes
  // via a pointer to Scene.
  virtual ~Scene();
  // Each scene must have:

  // Scene lifecycle operations.
  // Derived classes can override these to prepare resources,
  // update logic, render, and release resources, respectively.
  virtual void InitScene();                    // Scene initialization and resource loading/preparation.
  virtual void UpdateScreen(double deltaTime); // Updating the scene state; deltaTime represents the elapsed time.
  virtual void DrawScreen();                   // Rendering the scene's visual elements.
  virtual void UnloadScreen();                 // Releasing resources used by the scene.

  // Returns the identifier of the target scene.
  GameScreen FinishScreen() { return finishScreen; };
  // Sets the scene to switch to once the current one ends.
  void ChangeScene(GameScreen sc) { finishScreen = sc; }
  // Returns the music resource associated with this scene.
  Music GetMusic() { return music; };

protected:
  // Mandatory extension points for each specific scene.
  // As these are pure virtual methods (= 0), any non-abstract derived class
  // must provide its own implementation.

  // Reaction to a mouse press/click.
  virtual void OnMouseDown() = 0;

  // Reaction to a key press; receives the detected key.
  virtual void OnKeyPressed(KeyboardKey) = 0;

  // Reaction to a collision between two game objects.
  // The pointers identify the two objects involved.
  virtual void OnCollision(GameObject2D *obj1, GameObject2D *obj2) = 0;

  // Adds an object to the scene's object system.
  // Returns the result of the insertion (e.g., whether the insertion was successful).
  bool AddGameObject(GameObject2D *obj) { return objectSystem->insert(obj); };

  // Requests the removal of an object from the system.
  // The name "save_remove" suggests that the removal might be deferred or handled
  // safely by the system itself; the specific details depend on its implementation.
  void EraseGameobject(GameObject2D *obj) { objectSystem->save_remove(obj); };

  // Updates the shape/offscreen area used by the object system.
  // The dimensions obtained from Raylib are passed. The original order is preserved
  // of the arguments: first height and then width.
  void SetOffscreenShape() { objectSystem->ChangeForm(GetScreenHeight(), GetScreenWidth()); }

  // Adds an offset to the off-screen reference system.
  void SetOffscreenOffset(float off) { objectSystem->AddOffset(off); }

private:
  // Handles input events/interrupts, such as changes in the state
  // of the keyboard or mouse. This is an internal detail of Scene.
  void ManageInterruptions();

  // Retrieves the path or filename associated with a scene identifier.
  // The specific mapping between GameScreen and paths is defined in the implementation.
  string GetScenePath(GameScreen sc);
};