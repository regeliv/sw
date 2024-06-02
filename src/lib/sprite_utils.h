#pragma once
#include "SFML/Graphics/Sprite.hpp"
void centerSprite(sf::Sprite &sprite);

float rightEdge(sf::Sprite const &sprite);

float leftEdge(sf::Sprite const &sprite);

float topEdge(sf::Sprite const &sprite);

float bottomEdge(sf::Sprite const &sprite);

float wrap(float num, float min, float max);
