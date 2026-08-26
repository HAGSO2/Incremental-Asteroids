#pragma once
#include <string>
using namespace std;

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
    void run();

protected:
    virtual void Init() {}
    virtual void Update(double deltaTime) {}
    virtual void Draw() {}
    virtual void Unload() {};
};