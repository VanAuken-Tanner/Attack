#include <iostream>

#include "Game.h"

//TODO

// Major Reafactoring
// implement object destruction
// obj & texture vertex - realize
// Implement Texture Manager
// Standardize scenes with camera and layer array
// implement better vbo packing
// 
// Goblin coords not floats?
// move rng class


int main(int argc, char const *argv[])
{
    Game game;

    game.Init();
    game.Run();
    game.Close();

    return 0;
}
