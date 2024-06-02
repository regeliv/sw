#include "player_ship.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include "sprite_utils.h"
#include <cmath>
#include <print>

constexpr float inc = 40;

Ship::Ship(std::string const &filename) {
    is_ok = texture.loadFromFile(filename);
    if (!is_ok) {
        return;
    }

    sprites.emplace_back(texture);
    centerSprite(sprites[0]);

    // sprite.setTexture(texture);
    // compl_sprite.setTexture(texture);
    // draw_compl = false;
    // centerSprite(sprite);
    // centerSprite(compl_sprite);
}

bool Ship::isOk() const { return is_ok; }

void Ship::setPosition(sf::Vector2f const &pos) {
    if (sprites.size() > 0) {
        sprites[0].setPosition(pos);
    }
}

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

void Ship::increaseVelocity(sf::Time t) {
    if (!(sprites.size() > 0)) {
        return;
    }

    // by default the angle is 0 so the sprite is pointed to the right
    // at start
    // we adjust it by subtracting 90 degrees, so that it is pointing
    // to the top
    float angle = (sprites[0].getRotation() - 90) * (std::numbers::pi / 180);
    float secs = t.asSeconds();

    constexpr int incr = 2;

    velocity.x += incr * std::cos(angle) * secs;
    velocity.y += incr * std::sin(angle) * secs;
}

sf::Vector3f Ship::sunForceParams(sf::Vector2f const &window_size) {
    sf::Vector2f sun_pos{window_size.x / 2, window_size.y / 2};
    sf::Vector2f ship_pos = sprites[0].getPosition();

    float dist = hypot(sun_pos.x - ship_pos.x, sun_pos.y - ship_pos.y);

    float hypot = dist * dist;
    float cosine = (sun_pos.x - ship_pos.x) / hypot;
    float sine = (sun_pos.y - ship_pos.y) / hypot;

    return sf::Vector3f{hypot, cosine, sine};
}

void Ship::move(sf::Time t, sf::Vector2f const &window_size) {
    if (!(sprites.size() > 0)) {
        return;
    }
    auto oldPos = sprites[0].getPosition();

    // float angle = (sprites[0].getRotation() - 90) * (std::numbers::pi / 180);
    sf::Vector2f delta{};
    float secs = t.asSeconds();

    delta.x = velocity.x * secs; // inc * secs * std::cos(angle);
    delta.y = velocity.y * secs; // inc * secs * std::sin(angle);

    sf::Vector3f force_params = sunForceParams(window_size);

    constexpr float G = 50000;
    velocity.x += G / force_params.x * force_params.y;
    velocity.y += G / force_params.x * force_params.z;

    sf::Vector2f newPos{oldPos.x + delta.x, oldPos.y + delta.y};
    newPos.x = wrap(newPos.x, 0, window_size.x);
    newPos.y = wrap(newPos.y, 0, window_size.y);
    sprites[0].setPosition(newPos);

    wrapIfNecessary(window_size);

    // // int overflowed_edges = overflowedEdges(window_size);
    // draw_compl = static_cast<bool>(overflowed_edges);
    // if (!draw_compl) {
    //     return;
    // }

    // compl_sprite.setPosition(
    //     coordsOfWrappedShip(newPos, window_size, overflowed_edges));
}

void Ship::rotate(RotateDirection r, sf::Time t) {
    if (!(sprites.size() > 0)) {
        return;
    }

    sprites[0].rotate(r * 90 * t.asSeconds());

    if (sprites.size() > 1) {
        sprites[1].setRotation(sprites[0].getRotation());
    }
}

// int Ship::overflowedEdges(sf::Vector2f const &window_size) {
//     sf::Vector2f center = sprite.getPosition();
//     sf::Vector2u text_rect = sprite.getTexture()->getSize();
//     // make sure the whole sprite is in range of the circle
//     float radius = hypot(text_rect.x * 0.5, text_rect.y * 0.5);

//     int res = 0;
//     if (center.x - radius < 0) {
//         res |= Edge::left;
//     } else if (center.x + radius > window_size.x) {
//         res |= Edge::right;
//     }

//     if (center.y - radius < 0) {
//         res |= Edge::top;
//     } else if (center.y + radius > window_size.y) {
//         res |= Edge::bottom;
//     }
//     return res;
// }
