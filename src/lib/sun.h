#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include <string>

class Sun {
  public:
    Sun(std::string const &filename);

    void rotate(sf::Time t);
    void setPosition(sf::Vector2f const& pos);

    bool isOk();
    sf::Sprite const& getSprite() const;
   

  private:
    bool is_ok;
    sf::Texture texture;
    sf::Sprite sprite;

};
