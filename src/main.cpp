#include "main.h"

#include "game/entity.hpp"

int main(int argc, char **argv) {

    Game game("Pong", 800, 600);

    game.init();
    game.run();

    return EXIT_SUCCESS;
}