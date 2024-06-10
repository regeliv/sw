#include "sun.h"
#include "sprite_utils.h"
#include "src/lib/texture_manager.h"

Sun::Sun(ResourceManager &tm) {
    sprite.setTexture(*tm.getTexture("sun"));
    centerSprite(sprite);
}

bool Sun::isOk() { return is_ok; }

void Sun::rotate(sf::Time t) { sprite.rotate(t.asSeconds() * (360 / 60.)); }
sf::Sprite const &Sun::getSprite() const { return sprite; }

void Sun::setPosition(sf::Vector2f const &pos) { sprite.setPosition(pos); }
