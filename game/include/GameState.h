#pragma once

#include "Misc/Upgrade.h"

// Global variables
struct GameState
{
    vector<Upgrade> upgrades;
    int money;
    GameState() : upgrades(vector<Upgrade>()), money(0) {};
};