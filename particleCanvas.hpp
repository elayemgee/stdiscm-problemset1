#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "particle.hpp"

class ParticleCanvas {
public:
    ParticleCanvas(sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);
    void addParticle(sf::Vector2f position, sf::Vector2f velocity);

private:
    std::vector<Particle> particles;
    sf::RenderWindow& window;
};