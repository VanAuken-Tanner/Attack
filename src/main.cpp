#include <iostream>

#include "Game.h"

//TODO
// implement object destruction
// obj & texture vertex - realize
// Implement Texture Manager
// Standardize scenes with camera and layer array
// implement better vbo packing
// Goblin coords not floats?


int main(int argc, char const *argv[])
{
    Game game;

    game.Init();
    game.Run();
    game.Close();

    return 0;
}
