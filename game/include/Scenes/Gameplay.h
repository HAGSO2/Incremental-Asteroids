#include "ProgramFlow/Scene.h"
#include "Player.h"

class Gameplay : public Scene {
    Player player;
public:
    Gameplay();
    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
};