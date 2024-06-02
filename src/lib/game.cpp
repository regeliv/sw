#include "game.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "sprite_utils.h"
#include <ranges>

Game::Game()
    : tm{"resources"},
      window{"Spacewar!", sf::Vector2u(800, 600)},
      needle{"resources/needle.png"}, wedge{"resources/wedge.png"},
      sun{"resources/sun.png"} {
    is_ok = wedge.isOk() && needle.isOk() && sun.isOk();

    if (!tm.isOk()) {
        is_ok = false;
        return;
    }

    for (int _ : std::ranges::iota_view{0, 50}) {
        stars.push_back(Star(window.getWindowSize(), tm));
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        needle.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        needle.rotate(RotateDirection::counterclockwise, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        needle.rotate(RotateDirection::clockwise, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        wedge.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        wedge.rotate(RotateDirection::counterclockwise, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        wedge.rotate(RotateDirection::clockwise, elapsed);
    }
}

Window &Game::getWindow() { return window; }

bool Game::isOk() { return is_ok; }

void Game::update() {
    window.update();

    auto window_size = window.getViewSize();
    needle.move(elapsed, window_size);
    wedge.move(elapsed, window_size);

    handleInput();
    sun.rotate(elapsed);
    for (Star &star : stars) {
        star.twinkle(elapsed);
    }
}

void Game::render() {
    window.beginDraw();
    window.draw(sun.getSprite());
    for (Star const &star : stars) {
        window.draw(star.getSprite());
    }

    window.draw(needle.getSprite());
    if (needle.drawCompl()) {
        window.draw(needle.getComplSprite());
    }
    window.draw(wedge.getSprite());
    if (wedge.drawCompl()) {
        window.draw(wedge.getComplSprite());
    }

    window.endDraw();
}

sf::Time Game::getElapsed() { return elapsed; }

void Game::restartClock() { elapsed = clock.restart(); }
