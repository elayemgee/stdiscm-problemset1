#include "particle.hpp"

Particle::Particle(float size) {
    // Implementation of the constructor
    shape.setSize(sf::Vector2f(size, size));
    shape.setFillColor(sf::Color::Green);
}

void Particle::update(sf::RenderWindow& window) {
    // Implementation of the update function
    position += velocity;

    // Bounce off the walls
    if (position.x < 300 || position.x >  window.getSize().x - shape.getSize().x) {
        velocity.x = -velocity.x;
    }

    if (position.y < 0 || position.y >  window.getSize().y - shape.getSize().y) {
        velocity.y = -velocity.y;
    }

    shape.setPosition(position);
}

void Particle::render(sf::RenderWindow& window) {
    // Implementation of the render function
    window.draw(shape);
}