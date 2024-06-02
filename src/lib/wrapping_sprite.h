#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include <optional>
#include <vector>

enum Edge {
    left = 1,
    right = 1 << 2,
    top = 1 << 3,
    bottom = 1 << 4,
};

class WrappingSprite {
  public:
    void wrapIfNecessary(sf::Vector2f const& window_size);

  private:
    int overflowing(sf::Vector2f const& window_size);
    sf::Vector2f wrappedSpriteCoords(sf::Vector2f const& window_size, int overflowing_edges);
    void addTexture(sf::Vector2f const& pos);
    std::vector<sf::Sprite> sprites;
    sf::Texture texture;
};
