#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"
#include "src/lib/projectile.h"
#include "src/lib/sun.h"
#include "src/lib/texture_manager.h"
#include "src/lib/wrapping_sprite.h"

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

    std::vector<Projectile> const& getProjectiles() const;

    void setPosition(sf::Vector2f const &pos, float angle);

    void update(sf::Time t, sf::Vector2f const &window_size);
    void increaseVelocity(sf::Time t);
    void rotate(RotateDirection r, sf::Time t);
    void shoot();

    void destroyFromSun();
    void destroy();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    bool hitBy(Ship const& ship) const;
    bool inSun(Sun const& sun) const;
    bool collided(Ship const& ship) const;

  private:
    std::vector<Projectile> projectiles{};

    sf::Vector3f sunForceParams(sf::Vector2f const &window_size);
    void updateProjectiles(sf::Time t, sf::Vector2f);
    float cooldown = 0; 

    sf::Vector2f velocity;

    std::shared_ptr<sf::Texture> alt_texture;
    bool is_boosting;

    TextureManager &tm;

};
