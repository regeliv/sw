#include "game.h"
#include "SFML/System/Vector2.hpp"

Game::Game()
    : window{"Spacewar!", sf::Vector2u(800, 600)}
{
    if (!needle_texture.loadFromFile("resources/needle.png")) {
        is_ok = false;
        return;
    }
    if (!wedge_texture.loadFromFile("resources/wedge.png")) {
        is_ok = false;
        return;
    }
    if (!sun_texture.loadFromFile("resources/sun.png")) {
        is_ok = false;
        return;
    }
    is_ok = true;

    needle.setTexture(needle_texture);
    wedge.setTexture(wedge_texture);
    sun.setTexture(sun_texture);
}

Game::~Game() {}

void Game::handleInput(){}

Window& Game::getWindow() {
    return window;
}

bool Game::isOk() {
    return is_ok;
}

void Game::update() {
    window.update();
}

void Game::render() {
    window.beginDraw();
    window.draw(sun);
    window.draw(needle);
    window.draw(wedge);
    window.endDraw();
}
    
