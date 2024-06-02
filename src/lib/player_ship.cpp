#include "player_ship.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include "sprite_utils.h"
#include "src/lib/projectile.h"
#include "src/lib/texture_manager.h"
#include "src/lib/wrapping_sprite.h"
#include <cmath>
#include <print>


Ship::Ship(TextureManager &tm, std::string const &name) : WrappingSprite(tm, name), tm{tm} {
    sprites.emplace_back(texture);
    centerSprite(sprites[0]);
}


void Ship::setPosition(sf::Vector2f const &pos) {
    if (sprites.size() > 0) {
        sprites[0].setPosition(pos);
    }
}


void Ship::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {
    WrappingSprite::draw(target, states);

    for (auto const &projectile : projectiles) {
        target.draw(projectile);
    }
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

void Ship::shoot() {
    if (sprites.size() < 1) {
        return;
    }

    sf::Vector2f proj_coords = sprites[0].getPosition();    
    float dist_from_center = sprites[0].getTextureRect().height / 2;
    float angle = (sprites[0].getRotation() - 90) * (std::numbers::pi / 180);

    proj_coords.x += std::cos(angle) * dist_from_center;
    proj_coords.y += std::sin(angle) * dist_from_center;

    
    projectiles.push_back(Projectile(tm, {velocity.x + 10 * std::cos(angle), velocity.y + 10 * std::sin(angle)}, proj_coords));
}

void Ship::update(sf::Time t, sf::Vector2f const &window_size) {
    if (!(sprites.size() > 0)) {
        return;
    }

    auto oldPos = sprites[0].getPosition();

    float secs = t.asSeconds();
    sf::Vector2f delta{velocity.x * secs, velocity.y * secs};

    sf::Vector3f force_params = sunForceParams(window_size);

    // TODO: Extract into method
    constexpr float G = 50000;
    velocity.x += G / force_params.x * force_params.y;
    velocity.y += G / force_params.x * force_params.z;

    sf::Vector2f newPos{oldPos.x + delta.x, oldPos.y + delta.y};
    newPos.x = wrap(newPos.x, 0, window_size.x);
    newPos.y = wrap(newPos.y, 0, window_size.y);
    sprites[0].setPosition(newPos);

    for (auto & projectile : projectiles) {
        projectile.update(t, window_size);
    }

    wrapIfNecessary(window_size);
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
