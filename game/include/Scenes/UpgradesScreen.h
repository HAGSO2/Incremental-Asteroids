#include "ProgramFlow/Scene.h"

class UpgradeScreen : public Scene
{
public:
    UpgradeScreen();
    ~UpgradeScreen() = default;

    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    void OnCollision(GameObject2D *obj1, GameObject2D *obj2) override;
};