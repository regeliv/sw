#include "player_ship.h"
#include "SFML/System/Vector2.hpp"
#include "sprite_utils.h"

constexpr float inc = 10;

Ship::Ship(std::string const &filename) {
    is_ok = texture.loadFromFile(filename);
    if (!is_ok) {
        return;
    }

    sprite.setTexture(texture);
    centerSprite(sprite);
}

bool Ship::isOk() const {
    return is_ok;
}

void Ship::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Ship::move(Direction d, sf::Time t) {
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

    sprite.setPosition(oldPos.x + delta.x, oldPos.y + delta.y);
}

sf::Sprite const &Ship::getSprite() const {
    return sprite;
}
