#include "game.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <print>
#include <ranges>

Game::Game()
    : tm{"resources"}, window{"Spacewar!", sf::Vector2u(800, 600)},
      needle{tm, "needle"}, wedge{tm, "wedge"}, sun{"resources/sun.png"} {

    is_ok = true;

    if (!tm.isOk() || !sun.isOk()) {
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
    needle.setPosition(lower_left, 45.f);
    wedge.setPosition(upper_right, 225.f);
}

Game::~Game() {}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        needle.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        needle.shoot();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        needle.rotate(RotateDirection::counterclockwise, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        needle.rotate(RotateDirection::clockwise, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        wedge.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        wedge.shoot();

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
    needle.update(elapsed, window_size);
    wedge.update(elapsed, window_size);

    sun.rotate(elapsed);
    for (Star &star : stars) {
        star.twinkle(elapsed);
    }

    handleCollisions();
}

void Game::render() {
    window.beginDraw();
    window.draw(sun.getSprite());

    for (Star const &star : stars) {
        window.draw(star.getSprite());
    }

    window.draw(needle);
    window.draw(wedge);

    window.endDraw();
}

void Game::handleCollisions() {
    auto needle_sprites = needle.getSprites();
    auto needle_projectiles = needle.getProjectiles();

    auto wedge_sprites = wedge.getSprites();
    auto wedge_projectiles = wedge.getProjectiles();

    auto sun_sprite = sun.getSprite();

    if (wedge.hitBy(needle)) {
        std::println("Wedge hit by needle!");
    }

    if (needle.hitBy(wedge)) {
        std::println("Needle hit by wedge!");
    }

    if (needle.inSun(sun)) {
        std::println("Needle in sun");
    }

    if (wedge.inSun(sun)) {
        std::println("Wedge in sun");
    }

    if (needle.collided(wedge)) {
        std::println("Collided!");
    }

}

sf::Time Game::getElapsed() { return elapsed; }

void Game::restartClock() { elapsed = clock.restart(); }
