#pragma once
#include "SFML/System/Vector2.hpp"
#include "src/lib/texture_manager.h"
#include "wrapping_sprite.h"

class Projectile : public WrappingSprite {
  private:
    sf::Vector2f velocity;
    float lifetime = 5;
    void move(float secs, sf::Vector2f const& window_size);

  public:
    bool lifetimeEnded();
    Projectile(TextureManager &tm, sf::Vector2f velocity, sf::Vector2f pos, float angle);
    void update(float secs, sf::Vector2f const& window_size);
};
