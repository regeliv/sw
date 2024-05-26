#include "sun.h"
#include "sprite_utils.h"

Sun::Sun(std::string const &filename) {
    is_ok = texture.loadFromFile(filename);
    if (!is_ok) {
        return;
    }

    sprite.setTexture(texture);
    centerSprite(sprite);
}

bool Sun::isOk() {
    return is_ok;
}

void Sun::rotate(sf::Time t) {
    sprite.rotate(t.asSeconds() * (360  / 60.));

}
sf::Sprite const& Sun::getSprite() const {
    return sprite;
}

void Sun::setPosition(sf::Vector2f const& pos) {
    sprite.setPosition(pos);
}
