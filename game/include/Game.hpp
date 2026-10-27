#include "ProgramFlow/Application.hpp"

#include "Scenes/Logo.h"
#include "Scenes/Tittle.h"
#include "Scenes/Gameplay.h"
#include "Scenes/UpgradesScreen.h"
#include "Scenes/GameOver.h"

#include "Misc/Upgrade.h"

#define NUMBER_OF_SCENES 5

class Game : public Application
{
    /********************
     * GLOBAL VARIABLES *
     ********************/
    Font font = {0};
    // Music music = {};
    Sound logo_music = {};
    Music tittle_music = {};
    Music gameplay_music = {};
    vector<Upgrade> upgrades;

    Scene *gameScenes[NUMBER_OF_SCENES] = {0};

    // TODO: Load each scene from its own file. 
    // As it is serializable, it should be possible to load each scene from a JSON file, including its objects and properties. 
    // This would allow for more flexibility and easier modifications without recompiling the code.
    void LoadResources();
    void UnLoadResources();
    void LoadUpgrades();
    void InitStarters();
    void UpdateDrawFrame();
    // TODO: Take this to the Application class, maybe with some methods to manage it?
    void TransitionToScreen(GameScreen screen);
    void UpdateTransition(void);
    void DrawTransition(void);

public:
    Game(int w, int h, int fps, string name) : Application(w, h, fps, name) {};
    void Init() override;
    void Update(double deltaTime) override;
    void Draw() override;
    void Unload() override;
};