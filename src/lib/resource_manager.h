#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <map>
#include <memory>

class ResourceManager {
  public:
    ResourceManager(std::string const &resource_dir);
    bool isOk();
    std::shared_ptr<sf::Texture> getTexture(std::string const &name) const;
    std::shared_ptr<sf::Font> getFont(std::string const &name) const;
    std::shared_ptr<sf::SoundBuffer> getSound(std::string const &name) const;

  private:
    bool is_ok;
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::map<std::string, std::shared_ptr<sf::Font>> fonts;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
};
