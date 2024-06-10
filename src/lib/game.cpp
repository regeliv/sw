#include "game.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <print>
#include <ranges>

Game::Game()
    : tm{"resources"}, window{"Spacewar!", sf::Vector2u(800, 600)},
      needle{tm, "needle"}, wedge{tm, "wedge"}, sun{tm} {

    is_ok = tm.isOk();

    if (!is_ok) {
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        needle.destroy();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        needle.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        needle_projectiles.addProjectile(needle.shoot(tm));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        needle.rotate(RotateDirection::counterclockwise, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        needle.rotate(RotateDirection::clockwise, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        wedge.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        wedge_projectiles.addProjectile(wedge.shoot(tm));

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
    needle_projectiles.updateProjectiles(elapsed.asSeconds(), window_size);
    wedge_projectiles.updateProjectiles(elapsed.asSeconds(), window_size);


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
    window.draw(needle_projectiles);
    window.draw(wedge_projectiles);

    window.endDraw();
}

void Game::handleCollisions() {
    auto needle_sprites = needle.getSprites();
    // auto needle_projectiles = needle.getProjectiles();

    auto wedge_sprites = wedge.getSprites();
    // auto wedge_projectiles = wedge.getProjectiles();

    auto sun_sprite = sun.getSprite();

    if (wedge.hitBy(needle_projectiles)) {
        wedge.destroy();
    }

    if (needle.hitBy(wedge_projectiles)) {
        needle.destroy();
    }

    if (needle.inSun(sun)) {
        needle.destroyBySun();
    }

    if (wedge.inSun(sun)) {
        wedge.destroyBySun();
    }

    if (needle.collided(wedge)) {
        needle.destroy();
        wedge.destroy();
    }

}

sf::Time Game::getElapsed() { return elapsed; }

void Game::restartClock() { elapsed = clock.restart(); }
