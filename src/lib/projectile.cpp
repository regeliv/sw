#include "projectile.h"
#include "SFML/System/Vector2.hpp"
#include "sprite_utils.h"
#include "src/lib/texture_manager.h"

Projectile::Projectile(TextureManager &tm, sf::Vector2f velocity,
                       sf::Vector2f pos, float angle)
    : WrappingSprite(tm, "projectile"), velocity{velocity} {

    sprites.emplace_back(*texture);
    centerSprite(sprites[0]);
    sprites[0].setPosition(pos);
    sprites[0].setRotation(angle);
}

void Projectile::move(sf::Time t, sf::Vector2f const &window_size) {
    float secs = t.asSeconds();
    sf::Vector2f delta{velocity.x * secs, velocity.y * secs};

    sf::Vector2f old_pos = sprites[0].getPosition();
    sf::Vector2f new_pos{old_pos.x + delta.x, old_pos.y + delta.y};
    new_pos.x = wrap(new_pos.x, 0, window_size.x);
    new_pos.y = wrap(new_pos.y, 0, window_size.y);
    sprites[0].setPosition(new_pos);
}

bool Projectile::lifetimeEnded() {
    return lifetime <= 0;
}

void Projectile::update(sf::Time t, sf::Vector2f const &window_size) {
    move(t, window_size);
    wrapIfNecessary(window_size);

    lifetime -= t.asSeconds();
}
