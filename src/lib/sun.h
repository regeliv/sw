#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "src/lib/texture_manager.h"
#include <string>

class Sun {
  public:
    Sun(ResourceManager &tm);

    void rotate(sf::Time t);
    void setPosition(sf::Vector2f const &pos);

    bool isOk();
    sf::Sprite const &getSprite() const;

  private:
    bool is_ok;
    sf::Texture texture;
    sf::Sprite sprite;
};
