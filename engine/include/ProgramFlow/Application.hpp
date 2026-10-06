#pragma once
#include <string>
using namespace std;

#include "ProgramFlow/GameScreen.h"
#include "ProgramFlow/clock.h"

class Application
{
protected:
    int screenWidth = 800;
    int screenHeight = 600;
    int FPs = 60;

    string ApplicationName = "Game";
    myclock appClock = myclock();
    double lastTime = 0.0;

public:
    GameScreen currentScreen;
    GameScreen transToScreen = GameScreen(UNKNOWN);
    float transAlpha = 0.0f;
    bool onTransition = false;
    bool transFadeOut = false;
    int transFromScreen = -1;

    Application(int w, int h, int fps, string name) : screenWidth(w), screenHeight(h), FPs(fps), ApplicationName(name) {};
    void run();

protected:
    virtual void Init() {}
    virtual void Update(double deltaTime) {}
    virtual void Draw() {}
    virtual void Unload() {};
};