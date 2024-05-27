#include "game.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "sprite_utils.h"

Game::Game()
    : window{"Spacewar!", sf::Vector2u(800, 600)}
    , needle{"resources/needle.png"}
    , wedge{"resources/wedge.png"}
    , sun{"resources/sun.png"}
{
    is_ok = wedge.isOk() && needle.isOk() && sun.isOk();
    if (!is_ok) {
        return;
    }

    sf::Vector2u size = window.getWindowSize();

    sf::Vector2f center(size.x * 0.5, size.y * 0.5);
    sf::Vector2f lower_left(size.x * 0.25, size.y * 0.75);
    sf::Vector2f upper_right(size.x * 0.75, size.y * 0.25);


    sun.setPosition(center);
    needle.setPosition(lower_left);
    wedge.setPosition(upper_right);
}

Game::~Game() {}

void Game::handleInput() {
    auto window_size = window.getViewSize();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        needle.move(Direction::up, elapsed, window_size);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        needle.move(Direction::down, elapsed, window_size);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        needle.move(Direction::left, elapsed, window_size);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        needle.move(Direction::right, elapsed, window_size);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        wedge.move(Direction::up, elapsed, window_size);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        wedge.move(Direction::down, elapsed, window_size);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        wedge.move(Direction::left, elapsed, window_size);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        wedge.move(Direction::right, elapsed, window_size);
    }
}

Window &Game::getWindow() { return window; }

bool Game::isOk() { return is_ok; }

void Game::update() {
    window.update();
    handleInput();
    sun.rotate(elapsed);
}

void Game::render() {
    window.beginDraw();
    window.draw(sun.getSprite());
    window.draw(needle.getSprite());
    window.draw(wedge.getSprite());
    window.endDraw();
}

sf::Time Game::getElapsed() { return elapsed; }

void Game::restartClock() { elapsed = clock.restart(); }
