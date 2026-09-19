#include "ProgramFlow/Scene.h"

// enum TemplateLayers
// {
//     TL_NONE = 0,
//     TL_PLAYER = 1 << 0,
//     TL_ASTEROID = 1 << 1,
//     TL_PROJECTILE = 1 << 2

// };

// vector<uint32_t> mask = {GL_ASTEROID, GL_PROJECTILE, 0};

class TemplateScene : public Scene
{
public:
    TemplateScene();
    ~TemplateScene() = default;
    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    void OnCollision(GameObject2D *obj1, GameObject2D *obj2) override;
};