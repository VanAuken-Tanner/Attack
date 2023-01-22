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


inline float g_s_left = -8.0f;
inline float g_s_right = 8.0f;
inline float g_s_bottom = -4.5f;
inline float g_s_top = 4.5f;

inline float g_s_ob_left = -16.0f;
inline float g_s_ob_right = 16.0f;
inline float g_s_ob_bottom = -9.0f;
inline float g_s_ob_top = 9.0f;
