#include "src/lib//projectile_vector.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <print>

void ProjectileVector::updateProjectiles(float secs, sf::Vector2f window_size,
                                         Sun const &sun) {
    std::erase_if(projectiles, [&](Projectile &p) {
        return p.lifetimeEnded() || p.inSun(sun);
    });

    for (auto &projectile : projectiles) {
        projectile.update(secs, window_size);
    }
}
void ProjectileVector::draw(sf::RenderTarget &target,
                            sf::RenderStates states) const {

    for (auto const &projectile : projectiles) {
        target.draw(projectile);
    }
}

void ProjectileVector::addProjectile(std::optional<Projectile> &&projectile) {
    if (projectile.has_value()) {
        projectiles.push_back(std::move(*projectile));
    }
}
std::vector<Projectile> const &ProjectileVector::getProjectiles() const {
    return projectiles;
}
