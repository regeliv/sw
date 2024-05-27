#include "player_ship.h"
#include "star.h"
#include "sun.h"
#include "window.h"
#include <vector>

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
    TextureManager tm;
    Window window;
    bool is_ok;

    Ship needle;
    Ship wedge;
    Sun sun;
    std::vector<Star> stars;

    sf::Clock clock;
    sf::Time elapsed;
};
