#pragma once
#include "SFML/Graphics/Text.hpp"
#include "player_ship.h"
#include "src/lib/projectile_vector.h"
#include "star.h"
#include "sun.h"
#include "window.h"
#include <vector>

enum class GameState {
    Play,
    Pause,
};

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
    void togglePause();

    GameState state;

    ResourceManager rm;
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
    sf::Text paused_text;

    float toggle_pause_cooldown = 0.0;
};
