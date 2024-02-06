#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
    sf::RectangleShape shape;
    sf::Vector2f position, velocity;

    Particle(float size = 40.0f);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
};
