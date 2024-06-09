#pragma once
#include "player_ship.h"
#include "src/lib/projectile.h"
#include "src/lib/projectile_vector.h"
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
    void handleCollisions();
    
    TextureManager tm;
    Window window;
    bool is_ok;

    Ship needle;
    Ship wedge;
    ProjectileVector needle_projectiles;
    ProjectileVector wedge_projectiles;
    
    Sun sun;
    std::vector<Star> stars;

    sf::Clock clock;
    sf::Time elapsed;
};
