#include "wrapping_sprite.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "sprite_utils.h"
#include <cmath>

WrappingSprite::WrappingSprite() {}

WrappingSprite::WrappingSprite(ResourceManager &tm,
                               std::string const &texture_name)
    : texture{tm.getTexture(texture_name)} {}

std::vector<sf::Sprite> const &WrappingSprite::getSprites() const {
    return sprites;
}

void WrappingSprite::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {
    for (auto const &sprite : sprites) {
        target.draw(sprite);
    }
}

int WrappingSprite::overflowing(sf::Vector2f const &window_size) {
    if (sprites.size() < 1) {
        return 0;
    }

    sf::Sprite &main_sprite = sprites.front();

    sf::Vector2f center = main_sprite.getPosition();
    sf::Vector2u text_rect = main_sprite.getTexture()->getSize();

    // make sure the whole sprite is in range of the circle
    float radius = hypot(text_rect.x * 0.5, text_rect.y * 0.5);

    int res = 0;
    if (center.x - radius < 0) {
        res |= Edge::left;
    } else if (center.x + radius > window_size.x) {
        res |= Edge::right;
    }

    if (center.y - radius < 0) {
        res |= Edge::top;
    } else if (center.y + radius > window_size.y) {
        res |= Edge::bottom;
    }
    return res;
}

sf::Vector2f
WrappingSprite::wrappedSpriteCoords(sf::Vector2f const &window_size,
                                    int overflowing_edges) {
    sf::Vector2f orig_coords = sprites[0].getPosition();
    float new_x = orig_coords.x;
    float new_y = orig_coords.y;

    if (overflowing_edges & Edge::left) {
        new_x = window_size.x + orig_coords.x;
    } else if (overflowing_edges & Edge::right) {
        new_x = 0 + (orig_coords.x - window_size.x);
    }

    if (overflowing_edges & Edge::top) {
        new_y = window_size.y + orig_coords.y;
    } else if (overflowing_edges & Edge::bottom) {
        new_y = 0 + (orig_coords.y - window_size.y);
    }

    return sf::Vector2f(new_x, new_y);
}

void WrappingSprite::cloneSpriteIfNecessary(sf::Vector2f const &window_size) {
    int overflowing_edges = overflowing(window_size);

    if (overflowing_edges) {
        auto wrapped_coords =
            wrappedSpriteCoords(window_size, overflowing_edges);

        if (sprites.size() < 2) {
            sprites[1].setPosition(wrapped_coords);
        } else {
            addTexture(wrapped_coords);
        }

    } else if (sprites.size() > 1) {
        sprites.pop_back();
    }
}

void WrappingSprite::addTexture(sf::Vector2f const &pos) {
    if (sprites.empty()) {
        return;
    }

    sprites.emplace_back(*sprites.front().getTexture());
    centerSprite(sprites[1]);
    sprites[1].setPosition(pos);
    sprites[1].setRotation(sprites.front().getRotation());
}
