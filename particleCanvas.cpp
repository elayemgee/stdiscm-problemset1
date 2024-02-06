#include "particleCanvas.hpp"

ParticleCanvas::ParticleCanvas(sf::RenderWindow& window) : window(window) {
    // Implementation of the constructor
}

void ParticleCanvas::update() {
    // Implementation of the update function
    for (auto& particle : particles) {
        particle.update(window);
    }
}

void ParticleCanvas::render(sf::RenderWindow& window) {
    // Implementation of the render function
    for (auto& particle : particles) {
        particle.render(window);
    }
}

void ParticleCanvas::addParticle(sf::Vector2f position, sf::Vector2f velocity) {
    // Implementation of the addParticle function
    Particle newParticle;
    newParticle.position = position;
    newParticle.velocity = velocity;
    particles.push_back(newParticle);
}