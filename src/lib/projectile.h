#pragma once
#include "SFML/System/Vector2.hpp"
#include "src/lib/sun.h"
#include "src/lib/wrapping_sprite.h"

class Projectile : public WrappingSprite {
  public:
    bool lifetimeEnded();
    bool inSun(Sun const &sun);

    Projectile(ResourceManager &tm, sf::Vector2f velocity, sf::Vector2f pos,
               float angle);
    void update(float secs, sf::Vector2f const &window_size);

  private:
    sf::Vector2f velocity;
    float lifetime = 5;

    void move(float secs, sf::Vector2f const &window_size);
};
