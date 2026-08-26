#include "ProgramFlow/clock.h"

myclock::myclock() : elapsed{0} {}

double myclock::clock_update()
{
    auto now = std::chrono::steady_clock::now();

    elapsed = std::chrono::duration<double>(now - start_time).count();

    return elapsed;
}

void myclock::clock_start()
{
    start_time = std::chrono::steady_clock::now();
    elapsed = 0.0;
}

void myclock::clock_stop()
{
    start_time = std::chrono::steady_clock::time_point{};
}