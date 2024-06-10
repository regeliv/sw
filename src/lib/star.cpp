#include "star.h"
#include "SFML/System/Vector2.hpp"
#include "sprite_utils.h"
#include <cmath>
#include <format>
#include <ostream>
#include <print>
#include <random>

Star::Star(sf::Vector2u window_size, ResourceManager &tm)
    : speed{2} {
    // ...
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> file_dist(1, 6);

    std::uniform_real_distribution<float> x_dist(0, window_size.x);
    std::uniform_real_distribution<float> y_dist(0, window_size.y);

    std::uniform_real_distribution<float> brightness_dist(0.1, 1);
    std::uniform_real_distribution<float> time_dist(0, 100);

    int n = file_dist(rng);

    sprite.setTexture(*tm.getTexture(std::format("star-{}", n)));

    float x, y;
    sf::Vector2f center(window_size.x * 0.5, window_size.y * 0.5);

    // make sure it doesn't overlap the sun
    do {
        x = x_dist(rng);
        y = y_dist(rng);
    } while (std::sqrt(std::pow(x - center.x, 2) + std::pow(y - center.y, 2)) <
             50);

    min_brightness = brightness_dist(rng);
    max_brightness = brightness_dist(rng);

    if (min_brightness > max_brightness) {
        std::swap(min_brightness, max_brightness);
    }

    time = time_dist(rng);

    sprite.setPosition(x, y);

    centerSprite(sprite);
}

float sineBetween(float x, float min, float max) {
    float halfRange = (max - min) * 0.5;
    return min + halfRange + std::sin(x) * halfRange;
}

void Star::twinkle(sf::Time t) {
    time += t.asSeconds();
    float brightness =
        sineBetween(time * speed, min_brightness, max_brightness);
    sprite.setColor(sf::Color(255, 255, 255, 255 * brightness));
}

sf::Sprite const &Star::getSprite() const { return sprite; }
