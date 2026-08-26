#pragma once

#include <chrono>

class myclock
{
    std::chrono::steady_clock::time_point start_time;
    double elapsed;

public:
    myclock();

    // Starts the provided clock. Resets elapsed time.
    void clock_start();

    // Updates the provided clock. Should be called just before checking elapsed time.
    // Has no effect on non-started clocks.
    double clock_update();

    // Stops the provided clock. Does not reset elapsed time.
    void clock_stop();
};