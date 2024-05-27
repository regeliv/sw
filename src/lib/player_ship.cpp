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
    wrapped_sprite.setTexture(texture);
    centerSprite(sprite);
    centerSprite(wrapped_sprite);
}

bool Ship::isOk() const { return is_ok; }
bool Ship::drawWrapped() const { return draw_wrapped; }
sf::Sprite const &Ship::getSprite() const { return sprite; }
sf::Sprite const &Ship::getWrappedSprite() const { return wrapped_sprite; }

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
    newPos.x = wrap(newPos.x, 0, window_size.x);
    newPos.y = wrap(newPos.y, 0, window_size.y);
    sprite.setPosition(newPos);

    int overflowed_edges = overflowedEdges(window_size);
    draw_wrapped = static_cast<bool>(overflowed_edges);
    if (!draw_wrapped) {
        return;
    }

    wrapped_sprite.setPosition(coordsOfWrappedShip(newPos, window_size, overflowed_edges));
}


int Ship::overflowedEdges(sf::Vector2f const &window_size) {
    int res = 0;
    if (leftEdge(sprite) < 0) {
        res |= Edge::left;
    } else if (rightEdge(sprite) > window_size.x) {
        res |= Edge::right;
    }

    if (topEdge(sprite) < 0) {
        res |= Edge::top;
    } else if (bottomEdge(sprite) > window_size.y) {
        res |= Edge::bottom;
    }
    return res;
}
