#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "src/lib/texture_manager.h"
#include <memory>
#include <vector>

enum Edge {
    left = 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4,
};

class WrappingSprite : public sf::Drawable {
  public:
    WrappingSprite(TextureManager &tm, std::string const& texture_filename);

    void cloneSpriteIfNecessary(sf::Vector2f const& window_size);
    std::vector<sf::Sprite> const& getSprites() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;    

  protected:
    int overflowing(sf::Vector2f const& window_size);
    sf::Vector2f wrappedSpriteCoords(sf::Vector2f const& window_size, int overflowing_edges);
    void addTexture(sf::Vector2f const& pos);
    std::vector<sf::Sprite> sprites;
    std::shared_ptr<sf::Texture> texture;
};
