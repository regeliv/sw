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
    compl_sprite.setTexture(texture);
    draw_compl = false;
    centerSprite(sprite);
    centerSprite(compl_sprite);
}

bool Ship::isOk() const { return is_ok; }
bool Ship::drawCompl() const { return draw_compl; }
sf::Sprite const &Ship::getSprite() const { return sprite; }
sf::Sprite const &Ship::getComplSprite() const { return compl_sprite; }

void Ship::setPosition(sf::Vector2f const &pos) { sprite.setPosition(pos); }

enum Edge {
    left = 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4,
};

float wrap(float num, float min, float max) {
    return (num < 0 ? max : min) + std::fmod(num - min, max - min);
}

sf::Vector2f coordsOfWrappedShip(sf::Vector2f const &pos,
                                 sf::Vector2f const &window_size,
                                 int overflowed_edges) {

    float wrapped_x = pos.x;
    float wrapped_y = pos.y;

    if (overflowed_edges & Edge::left) {
        wrapped_x = window_size.x + pos.x;
    } else if (overflowed_edges & Edge::right) {
        wrapped_x = 0 + (pos.x - window_size.x);
    }

    if (overflowed_edges & Edge::top) {
        wrapped_y = window_size.y + pos.y;
    } else if (overflowed_edges & Edge::bottom) {
        wrapped_y = 0 + (pos.y - window_size.y);
    }

    return sf::Vector2f(wrapped_x, wrapped_y);
}

void Ship::move(Direction d, sf::Time t, const sf::Vector2f &window_size) {
    auto oldPos = sprite.getPosition();
    // by default the angle is 0 so the sprite is pointed to the right
    // at start
    // we adjust it by subtracting 90 degrees, so that it is pointing
    // to the top
    float angle = (sprite.getRotation() - 90) * (std::numbers::pi / 180);
    sf::Vector2f delta{};
    float secs = t.asSeconds();
    switch (d) {
    case Direction::up:
        delta.x = inc * secs * std::cos(angle);
        delta.y = inc * secs * std::sin(angle);
        break;
    case Direction::down:
        // delta.x = -inc * secs * std::cos(angle);
        // delta.y = -inc * secs * std::sin(angle);
        break;
    }

    sf::Vector2f newPos{oldPos.x + delta.x, oldPos.y + delta.y};
    newPos.x = wrap(newPos.x, 0, window_size.x);
    newPos.y = wrap(newPos.y, 0, window_size.y);
    sprite.setPosition(newPos);

    int overflowed_edges = overflowedEdges(window_size);
    draw_compl = static_cast<bool>(overflowed_edges);
    if (!draw_compl) {
        return;
    }

    compl_sprite.setPosition(
        coordsOfWrappedShip(newPos, window_size, overflowed_edges));
}

void Ship::rotate(RotateDirection r, sf::Time t) {
    sprite.rotate(r * 90 * t.asSeconds());
    compl_sprite.rotate(r * 90 * t.asSeconds());
}

int Ship::overflowedEdges(sf::Vector2f const &window_size) {
    sf::Vector2f center = sprite.getPosition();
    sf::Vector2u text_rect = sprite.getTexture()->getSize();
    // make sure the whole sprite is in range of the circle
    float radius = hypot(text_rect.x * 0.5, text_rect.y * 0.5);

    int res = 0;
    if (center.x - radius < 0) {
        res |= Edge::left;
    } else if (center.x + radius > window_size.x) {
        res |= Edge::right;
    }

    if (center.y - radius < 0) {
        res |= Edge::top;
    } else if (center.y + radius > window_size.y) {
        res |= Edge::bottom;
    }
    return res;
}
