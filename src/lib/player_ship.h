#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include "src/lib/projectile.h"
#include "src/lib/texture_manager.h"
#include "wrapping_sprite.h"

enum class Direction {
    up,
    down,
};

enum RotateDirection {
    clockwise = 1,
    counterclockwise = -1,
};

class Ship : public WrappingSprite {
  public:
    Ship(TextureManager &tm, std::string const &filename);

    void setPosition(sf::Vector2f const &pos);

    void update(sf::Time t, sf::Vector2f const &window_size);
    void increaseVelocity(sf::Time t);
    void rotate(RotateDirection r, sf::Time t);
    void shoot();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  private:
    std::vector<Projectile> projectiles{};

    sf::Vector3f sunForceParams(sf::Vector2f const &window_size);
    void updateProjectiles(sf::Time t, sf::Vector2f);

    sf::Vector2f velocity;

    TextureManager &tm;
};
