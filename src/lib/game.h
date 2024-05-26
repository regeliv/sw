#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "window.h"
#include "player_ship.h"

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
    sf::Texture sun_texture;

    Ship needle;
    Ship wedge;

    sf::Sprite sun;

    sf::Clock clock;
    sf::Time elapsed;
};
