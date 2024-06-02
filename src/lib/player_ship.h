#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
enum class Direction {
    up,
    down,
};

enum RotateDirection {
  clockwise = 1,
  counterclockwise = -1,
};

class Ship {
  public:
    Ship(std::string const &filename);
    bool isOk() const;
    bool drawCompl() const;
    sf::Sprite const &getSprite() const;
    sf::Sprite const &getComplSprite() const;

    void setPosition(sf::Vector2f const &pos);

    void move(sf::Time t, sf::Vector2f const &window_size);
    void increaseVelocity(sf::Time t);
    void rotate(RotateDirection r, sf::Time t);

  private:
    int overflowedEdges(sf::Vector2f const &window_size);
    bool isOverflowing(sf::Vector2f const &window_size);

    sf::Vector3f sunForceParams(sf::Vector2f const &window_size);
    
    bool draw_compl;
    bool is_ok;
    
    sf::Vector2f velocity;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite compl_sprite;
};
