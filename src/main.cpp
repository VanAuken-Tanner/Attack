#include <iostream>

#include "Game.h"

//TODO
//Fix debugger using log level global
//Fix object position updating

int main(int argc, char const *argv[])
{
    Game game;

    game.Init();
    game.Run();
    game.Close();

    return 0;
}
