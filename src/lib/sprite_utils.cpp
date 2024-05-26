#include "sprite_utils.h"
#include "SFML/Graphics/Texture.hpp"

void centerSprite(sf::Sprite &sprite) {
    auto texture = sprite.getTexture();
    if (texture == NULL) {
        return;
    }

    sf::Vector2u texture_size = texture->getSize();

    sprite.setOrigin(texture_size.x * 0.5, texture_size.y * 0.5);
}
