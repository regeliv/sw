#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "src/lib/projectile.h"

class ProjectileVector : public sf::Drawable {
  private:
    std::vector<Projectile> projectiles;

  public:
    void updateProjectiles(float secs, sf::Vector2f window_size);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void addProjectile(std::optional<Projectile>&& projectile);

    std::vector<Projectile> const& getProjectiles() const;
};
