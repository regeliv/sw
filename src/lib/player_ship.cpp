#include "src/lib/player_ship.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include "src/lib/projectile.h"
#include "src/lib/sprite_utils.h"
#include "src/lib/texture_manager.h"
#include "src/lib/wrapping_sprite.h"
#include <cmath>
#include <format>
#include <optional>
#include <print>
#include <vector>

Ship::Ship() {}

Ship::Ship(TextureManager &tm, std::string const &name, sf::Vector2f start_pos,
           float start_angle)
    : WrappingSprite(tm, name)
    , name{name}
    , start_pos{start_pos}
    , start_angle{start_angle}
    , alt_texture{tm.getTexture(std::format("{}-booster", name))}
    , destroyed_texture{tm.getTexture(std::format("{}-destroyed", name))} {

    reset();
}

void Ship::setPosition(sf::Vector2f const &pos, float angle) {
    sprites.front().setPosition(pos);
    sprites.front().setRotation(angle);
}

void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    WrappingSprite::draw(target, states);
}

void Ship::increaseVelocity(sf::Time t) {
    if (sprites.empty() || ship_state == ShipState::destroyed) {
        return;
    }

    ship_state = ShipState::boosting;
    float angle = getAngle();
    float secs = t.asSeconds();

    constexpr float multiplier = 2;

    velocity.x += multiplier * std::cos(angle) * secs;
    velocity.y += multiplier * std::sin(angle) * secs;
}

sf::Vector2f Ship::sunVelocityDelta(sf::Vector2f const &window_size) {
    constexpr float G = 1e3;

    sf::Vector2f sun_pos{window_size.x / 2.f, window_size.y / 2.f};
    sf::Vector2f ship_pos = sprites.front().getPosition();

    float r_squared = std::pow(sun_pos.x - ship_pos.x, 2) +
                      std::pow(sun_pos.y - ship_pos.y, 2);

    float angle = std::atan2(sun_pos.y - ship_pos.y, sun_pos.x - ship_pos.x);

    return sf::Vector2f{std::cos(angle), std::sin(angle)} * (G / r_squared);
}

std::optional<Projectile> Ship::shoot(TextureManager &tm) {
    constexpr float projectile_velocity = 40;

    if (sprites.empty() || shooting_cooldown > 0 ||
        ship_state == ShipState::destroyed) {
        return std::nullopt;
    }

    sf::Vector2f proj_coords = sprites.front().getPosition();
    float dist_from_center = sprites.front().getTextureRect().height / 2.0;

    float angle = getAngle();
    proj_coords +=
        sf::Vector2f(std::cos(angle), std::sin(angle)) * dist_from_center;

    shooting_cooldown = 1;
    return Projectile(tm,
                      {velocity.x + projectile_velocity * std::cos(angle),
                       velocity.y + projectile_velocity * std::sin(angle)},
                      proj_coords, sprites.front().getRotation());
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

    float secs = t.asSeconds();
    shooting_cooldown -= secs;

    sf::Vector2f old_pos = sprites.front().getPosition();
    sf::Vector2f pos_delta{velocity.x * secs, velocity.y * secs};

    velocity += sunVelocityDelta(window_size);

    sf::Vector2f newPos = old_pos + pos_delta;

    newPos.x = wrap(newPos.x, 0, window_size.x);
    newPos.y = wrap(newPos.y, 0, window_size.y);
    sprites.front().setPosition(newPos);

    cloneSpriteIfNecessary(window_size);
}

void Ship::rotate(RotateDirection r, sf::Time t) {
    if (sprites.empty() || ship_state == ShipState::destroyed) {
        return;
    }

    float delta = r * 90 * t.asSeconds();

    for (auto &sprite : sprites) {
        sprite.rotate(delta);
    }
}

bool Ship::hitBy(ProjectileVector const &pv) const {
    for (auto const &sprite : sprites) {
        for (auto const &projectile : pv.getProjectiles()) {
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

float Ship::getAngle() {
    // by default the angle is 0 so the sprite is pointed to the right
    // at start
    // we adjust it by subtracting 90 degrees, so that it is pointing
    // to the top
    return (sprites.front().getRotation() - 90) * (std::numbers::pi / 180);
}

void Ship::reset() {
    sprites.clear();
    sprites.emplace_back(*texture);
    centerSprite(sprites.front());

    velocity = {0, 0};
    shooting_cooldown = 0;

    setPosition(start_pos, start_angle);
}
