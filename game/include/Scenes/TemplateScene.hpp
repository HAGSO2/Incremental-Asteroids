#include "ProgramFlow/Scene.h"

class TemplateScene : public Scene {
public:
    TemplateScene();
    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    void OnCollision() override;
};