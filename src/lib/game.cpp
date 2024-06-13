#include "game.h"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <print>
#include <ranges>

Game::Game()
    : rm{"resources"}
    , window{"Spacewar!", sf::Vector2u(800, 600)}
    , sun{rm} {

    is_ok = rm.isOk();

    if (!is_ok) {
        return;
    }

    for (int _ : std::ranges::iota_view{0, 50}) {
        stars.push_back(Star(window.getWindowSize(), rm));
    }

    sf::Vector2u size = window.getWindowSize();

    sf::Vector2f center(size.x * 0.5, size.y * 0.5);
    sf::Vector2f lower_left(size.x * 0.25, size.y * 0.75);
    sf::Vector2f upper_right(size.x * 0.75, size.y * 0.25);

    needle = Ship{rm, "needle", lower_left, 45.f};
    wedge = Ship{rm, "wedge", upper_right, 225.f};

    sun.setPosition(center);

    state = GameState::Play;
    paused_text = sf::Text{"Paused", *rm.getFont("IBMPlexMono-Regular")};

    auto paused_center = paused_text.getGlobalBounds().getSize() / 2.f;
    auto local_bounds =
        paused_center + paused_text.getLocalBounds().getPosition();
    paused_text.setOrigin(local_bounds);

    paused_text.setPosition(
        {window.getViewSize().x * 0.5f, window.getViewSize().y * 0.1f});
}

Game::~Game() {}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        togglePause();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        needle.reset();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        wedge.reset();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        needle.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        needle_projectiles.addProjectile(needle.shoot(rm));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        needle.rotate(RotateDirection::counterclockwise, elapsed);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        needle.rotate(RotateDirection::clockwise, elapsed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        wedge.increaseVelocity(elapsed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        wedge_projectiles.addProjectile(wedge.shoot(rm));

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

    toggle_pause_cooldown -= elapsed.asSeconds();
    if (state == GameState::Pause) {
        return;
    }

    auto window_size = window.getViewSize();
    needle.update(elapsed, window_size);
    wedge.update(elapsed, window_size);
    needle_projectiles.updateProjectiles(elapsed.asSeconds(), window_size, sun);
    wedge_projectiles.updateProjectiles(elapsed.asSeconds(), window_size, sun);

    sun.rotate(elapsed);
    for (Star &star : stars) {
        star.twinkle(elapsed);
    }

    handleCollisions();
}

void Game::render() {
    window.beginDraw();

    if (state == GameState::Pause) {
        window.draw(paused_text);
    }

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

    auto wedge_sprites = wedge.getSprites();

    auto sun_sprite = sun.getSprite();

    if (wedge.hitBy(needle_projectiles)) {
        wedge.destroy();
    }

    if (needle.hitBy(wedge_projectiles)) {
        needle.destroy();
    }

    if (needle.inSun(sun)) {
        needle.destroy();
    }

    if (wedge.inSun(sun)) {
        wedge.destroy();
    }

    if (needle.collided(wedge)) {
        needle.destroy();
        wedge.destroy();
    }
}

sf::Time Game::getElapsed() { return elapsed; }

void Game::restartClock() { elapsed = clock.restart(); }

void Game::togglePause() {
    if (toggle_pause_cooldown > 0) {
        return;
    }

    if (state == GameState::Pause) {
        state = GameState::Play;
    } else if (state == GameState::Play) {
        state = GameState::Pause;
    }

    toggle_pause_cooldown = 0.1;
}
