#pragma once

#ifndef LOG_LEVEL_INIT
    #define LOG_LEVEL_INIT 0
#endif


enum GameState{
    Initializing,
    Running,
    Exiting
};
inline GameState g_gameState;



