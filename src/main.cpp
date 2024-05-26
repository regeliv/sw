#include <SFML/Graphics.hpp>
#include <iostream>
#include <print>
#include "src/lib/game.h"
#define PROJECT_NAME "spacewar"

int main(int argc, char **argv) {
    Game game{};

    if (!game.isOk()) {
        std::println(std::cerr, "Failed to load textures.");
        return 1;
    }

    while (!game.getWindow().isDone()) {
        game.handleInput();
        game.update();
        game.render();
    }
    return 0;
}
