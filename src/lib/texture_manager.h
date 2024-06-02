#pragma once
#include "SFML/Graphics/Texture.hpp"
#include <map>
#include <memory>
class TextureManager {
public:
    TextureManager(std::string const& resource_dir);
    bool isOk();
    std::shared_ptr<sf::Texture> getTexture(std::string const& name);
private:
    bool is_ok;
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
};
