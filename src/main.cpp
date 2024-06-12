#include "src/lib/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <print>
#define PROJECT_NAME "spacewar"

int main() {
    Game game{};

    if (!game.isOk()) {
        std::println(std::cerr, "Failed to load textures.");
        return 1;
    }

    while (!game.getWindow().isDone()) {
        game.handleInput();
        game.update();
        game.render();
        game.restartClock();
    }
    return 0;
}
