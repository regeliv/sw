#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "window.h"
class Game {
  public:
    Game();
    ~Game();

    void handleInput();
    void update();
    void render();
    Window &getWindow();

    sf::Time getElapsed();
    void restartClock();

    bool isOk();

  private:
    Window window;
    bool is_ok;
    sf::Texture needle_texture;
    sf::Texture wedge_texture;
    sf::Texture sun_texture;

    sf::Sprite needle;
    sf::Sprite wedge;
    sf::Sprite sun;

    sf::Clock clock;
    sf::Time elapsed;
};
