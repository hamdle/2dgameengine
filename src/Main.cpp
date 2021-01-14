#include "./Game/Game.h"

int main(int argc, char* argv[]) {
    bool fullscreen = true;
    if (argc == 2) {
       fullscreen = false; 
    }

    Game game;

    game.Initialize(fullscreen);
    game.Run();
    game.Destroy();

    return 0;
}
