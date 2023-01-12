#pragma once

#ifndef DEBUG_LEVEL
    #define DEBUG_LEVEL 0
#endif

enum GameState{
    Initializing,
    Running,
    Exiting
};
inline GameState g_gameState;



