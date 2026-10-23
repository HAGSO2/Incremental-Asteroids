#include "ProgramFlow/Scene.h"
#include "Misc/Upgrade.h"

using namespace std;

class UpgradeScreen : public Scene
{
    vector<Upgrade> upgrades;
public:
    UpgradeScreen(vector<Upgrade> upgrades) : Scene(Music{}), upgrades(upgrades) {};
    ~UpgradeScreen() = default;

    void InitScene() override;
    void UpdateScreen(double deltaTime) override;
    void DrawScreen() override;
    void UnloadScreen() override;
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    void OnCollision(GameObject2D *obj1, GameObject2D *obj2) override;
};