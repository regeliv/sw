#include "SFML/Graphics/Texture.hpp"
#include <map>
class TextureManager {
public:
    TextureManager(std::string const& resource_dir);
    bool isOk();
    sf::Texture& getTexture(std::string const& name);
private:
    bool is_ok;
    std::map<std::string, sf::Texture> textures;
};
