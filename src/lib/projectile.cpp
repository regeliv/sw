#include "projectile.h"
#include "SFML/System/Vector2.hpp"
#include "sprite_utils.h"
#include "src/lib/texture_manager.h"
#include <print>

Projectile::Projectile(TextureManager &tm, sf::Vector2f velocity,
                       sf::Vector2f pos, float angle)
    : WrappingSprite(tm, "projectile"), velocity{velocity} {

    sprites.emplace_back(*texture);
    centerSprite(sprites.front());

    sprites.front().setPosition(pos);
    sprites.front().setRotation(angle);
}

void Projectile::move(float secs, sf::Vector2f const &window_size) {
    sf::Vector2f pos_delta = velocity * secs;

    sf::Vector2f old_pos = sprites.front().getPosition();
    sf::Vector2f new_pos = old_pos + pos_delta;

    new_pos.x = wrap(new_pos.x, 0, window_size.x);
    new_pos.y = wrap(new_pos.y, 0, window_size.y);

    sprites.front().setPosition(new_pos);
}

bool Projectile::lifetimeEnded() {
    return lifetime <= 0;
}

void Projectile::update(float secs, sf::Vector2f const &window_size) {
    move(secs, window_size);
    cloneSpriteIfNecessary(window_size);

    lifetime -= secs;
}
