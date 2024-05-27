#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
enum class Direction {
    up,
    down,
    right,
    left,
};

class Ship {
  public:
    Ship(std::string const &filename);
    bool isOk() const;
    bool drawWrapped() const;
    sf::Sprite const &getSprite() const;
    sf::Sprite const &getWrappedSprite() const;

    void setPosition(sf::Vector2f const &pos);

    void move(Direction d, sf::Time t, sf::Vector2f const &window_size);

  private:
    int overflowedEdges(sf::Vector2f const &window_size);

    bool draw_wrapped;
    bool is_ok;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite wrapped_sprite;
};
