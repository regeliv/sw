#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
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

    void move(Direction d, sf::Time t);
    void setPosition(sf::Vector2f pos);
    sf::Sprite const &getSprite() const;

  private:
    bool is_ok;
    sf::Texture texture;
    sf::Sprite sprite;
};
