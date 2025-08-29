#include "engine/Game.hpp"

int main(int argc, char* argv[]) {
    Game* game = new Game();
    game->run();
    delete game;
    return 0;
}
