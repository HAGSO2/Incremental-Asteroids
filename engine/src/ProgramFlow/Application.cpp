#include "ProgramFlow/Application.hpp"
#include <raylib.h>

void Application::run()
{
    // Main application loop code here
    Init();
    appClock.clock_start();
    lastTime = appClock.clock_update();

    while (!WindowShouldClose())
    {
        double currentTime = appClock.clock_update();
        double deltaTime = currentTime - lastTime;
        Update(deltaTime);
        lastTime = currentTime;

        Draw();
    }

    Unload();

    CloseWindow();
}