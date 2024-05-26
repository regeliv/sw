#include "game.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "sprite_utils.h"

Game::Game()
    : window{"Spacewar!", sf::Vector2u(800, 600)}
    , needle{"resources/needle.png"}
    , wedge{"resources/wedge.png"}
{
    if (!wedge.isOk() || !needle.isOk()) {
        is_ok = false;
        return;
    }

    if (!sun_texture.loadFromFile("resources/sun.png")) {
        is_ok = false;
        return;
    }

    is_ok = true;

    sun.setTexture(sun_texture);

    sf::Vector2u size = window.getWindowSize();

    sf::Vector2f center(size.x * 0.5, size.y * 0.5);
    sf::Vector2f lower_left(size.x * 0.25, size.y * 0.75);
    sf::Vector2f upper_right(size.x * 0.75, size.y * 0.25);

    sun.setPosition(center);
    centerSprite(sun);

    needle.setPosition(lower_left);
    wedge.setPosition(upper_right);
}

Game::~Game() {}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        needle.move(Direction::up, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        needle.move(Direction::down, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        needle.move(Direction::left, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        needle.move(Direction::right, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        wedge.move(Direction::up, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        wedge.move(Direction::down, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        wedge.move(Direction::left, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        wedge.move(Direction::right, elapsed);
    }
}

Window &Game::getWindow() { return window; }

bool Game::isOk() { return is_ok; }

void Game::update() {
    window.update();
    handleInput();
}

void Game::render() {
    window.beginDraw();
    window.draw(sun);
    window.draw(needle.getSprite());
    window.draw(wedge.getSprite());
    window.endDraw();
}

sf::Time Game::getElapsed() { return elapsed; }

void Game::restartClock() { elapsed = clock.restart(); }
