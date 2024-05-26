#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <string>
class Window {
  public:
    Window(std::string title, sf::Vector2u size = sf::Vector2u(640, 480));
    ~Window();

    bool isFullscreen() const;
    bool isDone() const;
    sf::Vector2u getWindowSize() const;

    void toggleFullscreen();

    void update();

    void beginDraw();
    void draw(sf::Drawable const &drawable);
    void endDraw();


  private:
    void create();
    void destroy();

    sf::RenderWindow window;
    sf::Vector2u window_size;
    std::string window_title;
    bool is_fullscreen;
    bool is_done = true;
};
