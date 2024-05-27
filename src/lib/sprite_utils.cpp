#include "sprite_utils.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

void centerSprite(sf::Sprite &sprite) {
    auto texture = sprite.getTexture();
    if (texture == NULL) {
        return;
    }

    sf::Vector2u texture_size = texture->getSize();

    sprite.setOrigin(texture_size.x * 0.5, texture_size.y * 0.5);
}

float rightEdge(sf::Sprite const &sprite) {
    return sprite.getPosition().x - sprite.getLocalBounds().width * 0.5;
}

float leftEdge(sf::Sprite const &sprite) {
    return sprite.getPosition().x + sprite.getLocalBounds().width * 0.5;
}

float topEdge(sf::Sprite const &sprite) {
    return sprite.getPosition().y - sprite.getLocalBounds().height * 0.5;
}

float bottomEdge(sf::Sprite const &sprite) {
    return sprite.getPosition().y + sprite.getLocalBounds().height * 0.5;
}

