#include "player_ship.h"
#include "SFML/System/Vector2.hpp"
#include "sprite_utils.h"
#include <cmath>
#include <print>

constexpr float inc = 40;

Ship::Ship(std::string const &filename) {
    is_ok = texture.loadFromFile(filename);
    if (!is_ok) {
        return;
    }

    sprite.setTexture(texture);
    centerSprite(sprite);
}

bool Ship::isOk() const { return is_ok; }

void Ship::setPosition(sf::Vector2f const &pos) { sprite.setPosition(pos); }

void Ship::move(Direction d, sf::Time t, const sf::Vector2f &window_size) {
    auto oldPos = sprite.getPosition();
    sf::Vector2f delta{};
    float secs = t.asSeconds();
    switch (d) {
    case Direction::up:
        delta.x = 0;
        delta.y = -inc * secs;
        break;
    case Direction::down:
        delta.x = 0;
        delta.y = inc * secs;
        break;
    case Direction::left:
        delta.x = -inc * secs;
        delta.y = 0;
        break;
    case Direction::right:
        delta.x = inc * secs;
        delta.y = 0;
        break;
    }

    sf::Vector2f newPos{oldPos.x + delta.x, oldPos.y + delta.y};
    if (newPos.x < 0) {
        newPos.x = window_size.x;
    } else if (newPos.x > window_size.x) {
        newPos.x = 0;
    }

    if (newPos.y < 0) {
        newPos.y = window_size.y;
    } else if (newPos.y > window_size.y) {
        newPos.y = 0;
    }

    sprite.setPosition(newPos);
}

sf::Sprite const &Ship::getSprite() const { return sprite; }


bool Ship::isOverflowing(sf::Vector2f const &window_size) {
    std::println("x: {} y: {}, w: {}, h: {}", sprite.getPosition().x,
                 sprite.getPosition().y, window_size.x, window_size.y);
    if (rightEdge(sprite) < 0) {
        std::println("right edge");
    }

    if (leftEdge(sprite) > window_size.x) {
        std::println("left edge");
    }

    if (topEdge(sprite) < 0) {
        std::println("top edge");
    }

    if (bottomEdge(sprite) > window_size.y) {
        std::println("bottom edge");
    }


    return false;
}
