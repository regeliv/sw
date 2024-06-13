#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "src/lib/projectile.h"
#include "src/lib/projectile_vector.h"
#include "src/lib/sun.h"
#include "src/lib/texture_manager.h"
#include "src/lib/wrapping_sprite.h"

enum RotateDirection {
    clockwise = 1,
    counterclockwise = -1,
};

enum class ShipState {
    alive,
    boosting,
    destroyed,
};

class Ship : public WrappingSprite {
  public:
    Ship();
    Ship(ResourceManager &tm, std::string const &name, sf::Vector2f start_pos,
         float start_angle);

    void setPosition(sf::Vector2f const &pos, float angle);

    void update(sf::Time t, sf::Vector2f const &window_size);
    void increaseVelocity(sf::Time t);
    void rotate(RotateDirection r, sf::Time t);
    std::optional<Projectile> shoot(ResourceManager &tm);

    void destroy();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    bool hitBy(ProjectileVector const &pv) const;
    bool inSun(Sun const &sun) const;
    bool collided(Ship const &ship) const;

    void reset();

  private:
    std::string name;
    ShipState ship_state{ShipState::alive};

    sf::Vector2f start_pos;
    float start_angle;
    float respawn_cooldown;
    float shooting_cooldown = 0;

    sf::Vector2f velocity;
    sf::Sound shot;
    sf::Sound explosion;

    std::shared_ptr<sf::Texture> alt_texture;
    std::vector<std::shared_ptr<sf::Texture>> destroyed_textures;

    sf::Vector2f sunVelocityDelta(sf::Vector2f const &window_size);

    void updateTextures(sf::Texture const &t);

    float getAngle();
};
