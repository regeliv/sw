#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include "src/lib/player_ship.h"
#include "src/lib/sprite_utils.h"
#include "src/lib/projectile.h"
#include "src/lib/texture_manager.h"
#include "src/lib/wrapping_sprite.h"
#include <cmath>
#include <format>
#include <print>
#include <vector>

Ship::Ship(TextureManager &tm, std::string const &name)
    : WrappingSprite(tm, name), name{name}, tm{tm} {
    sprites.emplace_back(*texture);
    alt_texture = tm.getTexture(std::format("{}-booster", name));
    destroyed_texture = tm.getTexture(std::format("{}-destroyed", name));
    centerSprite(sprites[0]);
}

void Ship::setPosition(sf::Vector2f const &pos, float angle) {
    if (!sprites.empty()) {
        sprites.front().setPosition(pos);
        sprites.front().setRotation(angle);
    }
}

void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    WrappingSprite::draw(target, states);

    for (auto const &projectile : projectiles) {
        target.draw(projectile);
    }
}

std::vector<Projectile> const &Ship::getProjectiles() const {
    return projectiles;
}

void Ship::increaseVelocity(sf::Time t) {
    if (sprites.empty() || ship_state == ShipState::destroyed) {
        return;
    }

    ship_state = ShipState::boosting;

    // by default the angle is 0 so the sprite is pointed to the right
    // at start
    // we adjust it by subtracting 90 degrees, so that it is pointing
    // to the top
    // TODO: Refactor
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
    if (sprites.empty() || cooldown > 0 || ship_state == ShipState::destroyed) {
        return;
    }

    sf::Vector2f proj_coords = sprites[0].getPosition();
    float dist_from_center = sprites[0].getTextureRect().height / 2.0;
    float angle = (sprites[0].getRotation() - 90) * (std::numbers::pi / 180);

    proj_coords.x += std::cos(angle) * dist_from_center;
    proj_coords.y += std::sin(angle) * dist_from_center;

    projectiles.push_back(Projectile(
        tm,
        {velocity.x + 40 * std::cos(angle), velocity.y + 40 * std::sin(angle)},
        proj_coords, sprites[0].getRotation()));
    cooldown = 1;
}

void Ship::updateProjectiles(sf::Time t, sf::Vector2f window_size) {
    std::erase_if(projectiles,
                  [&](Projectile &p) { return p.lifetimeEnded(); });

    for (auto &projectile : projectiles) {
        projectile.update(t, window_size);
    }

    cooldown -= t.asSeconds();
}

void Ship::updateTextures(sf::Texture const &t) {
    for (auto &sprite : sprites) {
        sprite.setTexture(t);
    }
}

void Ship::update(sf::Time t, sf::Vector2f const &window_size) {
    if (sprites.empty()) {
        return;
    }

    switch (ship_state) {
    case ShipState::alive:
        updateTextures(*texture);
        break;
    case ShipState::boosting:
        updateTextures(*alt_texture);
        ship_state = ShipState::alive;
        break;
    case ShipState::destroyed:
        updateTextures(*destroyed_texture);
        break;
    default:
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

    updateProjectiles(t, window_size);

    wrapIfNecessary(window_size);
}

void Ship::rotate(RotateDirection r, sf::Time t) {
    if (sprites.empty() || ship_state == ShipState::destroyed) {
        return;
    }

    float delta = r * 90 * t.asSeconds();

    for (auto & sprite : sprites) {
        sprite.rotate(delta);
    }
}

bool Ship::hitBy(Ship const &ship) const {
    auto &projectiles = ship.getProjectiles();

    for (auto const &sprite : sprites) {
        for (auto const &projectile : projectiles) {
            for (auto const &projectile_sprite : projectile.getSprites()) {
                if (projectile_sprite.getGlobalBounds().intersects(
                        sprite.getGlobalBounds())) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Ship::inSun(Sun const &sun) const {
    for (auto const &sprite : sprites) {
        if (sprite.getGlobalBounds().intersects(
                sun.getSprite().getGlobalBounds())) {
            return true;
        }
    }

    return false;
}

bool Ship::collided(Ship const &ship) const {
    for (auto const &sprite : sprites) {
        for (auto const &other_sprite : ship.getSprites()) {
            if (sprite.getGlobalBounds().intersects(
                    other_sprite.getGlobalBounds())) {
                return true;
            }
        }
    }

    return false;
}

void Ship::destroy() { ship_state = ShipState::destroyed; }

void Ship::destroyBySun() { std::println("Destroying ship {} by Sun!", name); }
