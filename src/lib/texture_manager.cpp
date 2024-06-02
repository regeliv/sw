#include "texture_manager.h"
#include <filesystem>
#include <print>

TextureManager::TextureManager(std::string const &resource_dir) {
    is_ok = true;
    for (const auto &entry :
         std::filesystem::directory_iterator(resource_dir)) {
        if (entry.path().extension().string() == ".png" &&
            !entry.is_directory()) {

            auto name = entry.path().stem().string();
            auto file = entry.path().relative_path().string();

            textures[name] = sf::Texture();
            is_ok = textures[name].loadFromFile(file);
            if (!is_ok) {
                std::println("Failed to load {}", entry.path().string());
                return;
            }
        }
    }
}

sf::Texture& TextureManager::getTexture(std::string const& name) {
    return textures[name];
}

bool TextureManager::isOk() {
    return is_ok;
}
