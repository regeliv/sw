#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "src/lib/texture_manager.h"
#include "wrapping_sprite.h"

class Projectile : public WrappingSprite {
  private:
    sf::Vector2f velocity;
    float lifetime = 5;
    void move(sf::Time t, sf::Vector2f const& window_size);

  public:
    bool lifetimeEnded();
    Projectile(TextureManager &tm, sf::Vector2f velocity, sf::Vector2f pos);
    void update(sf::Time t, sf::Vector2f const& window_size);
};