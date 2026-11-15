#include "Scenes/ChangeToScenes.h"
#include "ProgramFlow/Scene.h"

void ToGameplay(void *ptr)
{
    Scene *sc = (Scene *)ptr;
    sc->ChangeScene(GAMEPLAY);
    TraceLog(LOG_DEBUG, "Transitioning to Gameplay scene...");
}
