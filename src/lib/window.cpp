#include "window.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"

Window::Window(std::string title, sf::Vector2u size)
    : window_size{std::move(size)}, window_title{std::move(title)}
    , is_fullscreen{false}
    , is_done{false} 
{
    create();
    window.setFramerateLimit(120);
}

void Window::create() {
    auto style = is_fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    window.create(sf::VideoMode{window_size.x, window_size.y}, window_title,
                  style);

}

void Window::destroy() { window.close(); }

Window::~Window() { destroy(); }

void Window::toggleFullscreen() {
    is_fullscreen = !is_fullscreen;
    destroy();
    create();
}

void Window::update() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            is_done = true;
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::F5) {
                toggleFullscreen();
            }
            break;
        default:
            break;
        }
    }
}

void Window::beginDraw() {
    window.clear();
}

void Window::endDraw() {
    window.display();
}

void Window::draw(sf::Drawable const& drawable) {
    window.draw(drawable);
}

bool Window::isFullscreen() const {
    return is_fullscreen;
}

bool Window::isDone() const {
    return is_done;
}

sf::Vector2u Window::getWindowSize() const {
    return window.getSize();
}
