#include "texture_manager.h"
#include <filesystem>
#include <print>

ResourceManager::ResourceManager(std::string const &resource_dir) {
    is_ok = true;
    for (const auto &entry :
         std::filesystem::recursive_directory_iterator(resource_dir)) {

        auto path = entry.path();
        auto extension = path.extension().string();

        if ((extension != ".png" && extension != ".otf") ||
            entry.is_directory()) {
            continue;
        }

        auto name = path.stem().string();
        auto file = path.relative_path().string();

        if (extension == ".png") {
            textures[name] = std::make_shared<sf::Texture>();
            is_ok = textures[name]->loadFromFile(file);
        } else if (extension == ".otf") {
            fonts[name] = std::make_shared<sf::Font>();
            is_ok = fonts[name]->loadFromFile(file);
        }

        if (!is_ok) {
            std::println("Failed to load {}", path.string());
            return;
        }
    }
}

std::shared_ptr<sf::Texture>
ResourceManager::getTexture(std::string const &name) const {
    return textures.at(name);
}

std::shared_ptr<sf::Font>
ResourceManager::getFont(std::string const &name) const {
    return fonts.at(name);
}

bool ResourceManager::isOk() { return is_ok; }
