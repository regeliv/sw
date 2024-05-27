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

    void move(Direction d, sf::Time t, sf::Vector2f const &window_size);
    void setPosition(sf::Vector2f const &pos);
    sf::Sprite const &getSprite() const;

  private:
    bool isOverflowing(sf::Vector2f const &window_size);
    bool is_ok;
    sf::Texture texture;
    sf::Sprite sprite;
};
