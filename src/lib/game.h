#include "window.h"
#include "player_ship.h"
#include "sun.h"

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

    Ship needle;
    Ship wedge;
    Sun sun;


    sf::Clock clock;
    sf::Time elapsed;
};
