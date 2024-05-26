#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"
#include <SFML/Graphics.hpp>
#include <print>
#include <src/lib/foo.h>
#define PROJECT_NAME "spacewar"

constexpr int width = 800;
constexpr int height = 600;

auto main(int argc, char **argv) -> int{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SMFL works!");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture needle_texture;
    if (!needle_texture.loadFromFile("../resources/needle.png")) {
        return 1;
    }

    sf::Texture wedge_texture;
    if (!wedge_texture.loadFromFile("../resources/wedge.png")) {
        return 1;
    }

    sf::Texture sun_texture;
    if (!sun_texture.loadFromFile("../resources/sun.png")) {
        return 1;
    }
    

    sf::Sprite needle_sprite;
    needle_sprite.setTexture(needle_texture);
    needle_sprite.setPosition(sf::Vector2f(width / 4., 3 * height / 4.));
    // TODO: set origin

    sf::Sprite wedge_sprite;
    wedge_sprite.setTexture(wedge_texture);
    wedge_sprite.setPosition(sf::Vector2f(3 * width / 4., height / 4.));
    // TODO: set origin

    sf::Sprite sun_sprite;
    sun_sprite.setTexture(sun_texture);
    sun_sprite.setPosition(sf::Vector2f(width / 2., height / 2.));
    sun_sprite.setOrigin(sf::Vector2f(25.f, 25.f));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(needle_sprite);
        window.draw(wedge_sprite);
        window.draw(sun_sprite);
        window.display();
    }

    return 0;
}
