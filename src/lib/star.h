#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "texture_manager.h"

class Star {
  public:
    Star(sf::Vector2u window_size, ResourceManager &tm);

    sf::Sprite const &getSprite() const;

    void twinkle(sf::Time t);

  private:
    float min_brightness;
    float max_brightness;
    float speed;
    float time = 0.f;
    sf::Sprite sprite;
};
