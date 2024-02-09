#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <iostream>

#define SIZE 8

class Wall {
public:
    Wall(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2), shape(sf::Lines, 2) {
        shape[0].position = sf::Vector2f(x1, y1);
        shape[0].color = sf::Color::Green;
        shape[1].position = sf::Vector2f(x2, y2);
        shape[1].color = sf::Color::Green;
    }

    sf::VertexArray shape;

private:
    float x1;
    float y1;
    float x2;
    float y2;
};

class Particle {
public:
    Particle(float x, float y, float speed, float angle) : speed(speed) {
        shape.setSize(sf::Vector2f(SIZE, SIZE));
        shape.setFillColor(sf::Color::Magenta);
        shape.setPosition(x, y);
        setAngleVelocity(angle);
    }

    void setAngleVelocity(float angleDegrees) {
        float angleRadians = angleDegrees * 3.14159 / 180;
        velocity.x = speed * std::cos(angleRadians);
        velocity.y = speed * std::sin(angleRadians);
    }

    sf::RectangleShape shape;
    sf::Vector2f velocity;

private:
    float speed;
};

void handleCollision(Particle& particle, const sf::Vector2u& windowSize, bool is_collide) {
    sf::FloatRect bounds = particle.shape.getGlobalBounds();

    if (bounds.left < 0 || bounds.left + bounds.width > windowSize.x) {
        particle.velocity.x = -particle.velocity.x;
    }

    if (bounds.top < 0 || bounds.top + bounds.height > windowSize.y) {
        particle.velocity.y = -particle.velocity.y;
    }

    if (is_collide) {
        particle.velocity = -particle.velocity;
    }
}

sf::Vector2f calculateRelativePos(const Particle& particle) {
    sf::FloatRect bounds = particle.shape.getGlobalBounds();

    float relative_x;
    float relative_y;

    if (particle.velocity.x > 0) {
        relative_x = bounds.left + bounds.width;
    }
    else {
        relative_x = bounds.left;
    }

    if (particle.velocity.y > 0) {
        relative_y = bounds.top + bounds.height;
    }
    else {
        relative_y = bounds.top;
    }

    return sf::Vector2f(relative_x, relative_y);
}


sf::Vector2f calculateCollisionOffset(const Particle& particle, const Wall& wall) {
    sf::Vector2f particlePosition = calculateRelativePos(particle);
    sf::Vector2f projection = particlePosition + particle.velocity;
    sf::Vector2f p0 = wall.shape[0].position;
    sf::Vector2f p1 = wall.shape[1].position;

    float determinant = (p1.x - p0.x) * (projection.y - particlePosition.y) - (p1.y - p0.y) * (projection.x - particlePosition.x);
    float numerator1 = (p1.x - p0.x) * (p0.y - particlePosition.y) - (p1.y - p0.y) * (p0.x - particlePosition.x);
    float numerator2 = (projection.x - particlePosition.x) * (p0.y - particlePosition.y) - (projection.y - particlePosition.y) * (p0.x - particlePosition.x);

    if (determinant == 0) {
        return particle.velocity;
    }

    float alpha = numerator1 / determinant;
    float beta = numerator2 / determinant;

    if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1) {
        float intersectionX = particlePosition.x + alpha * (projection.x - particlePosition.x);
        float intersectionY = particlePosition.y + alpha * (projection.y - particlePosition.y);

        return sf::Vector2f(intersectionX, intersectionY) - particlePosition;
    }

    return particle.velocity;
}


void updateParticles(std::vector<Particle>& particles, const std::vector<Wall>& walls) {
    for (auto& particle : particles) {
        sf::Vector2f newVelocity = particle.velocity;
        bool collideWithWall = false;

        for (const auto& wall : walls) {
            sf::Vector2f collisionOffset = calculateCollisionOffset(particle, wall);
            if (collisionOffset != newVelocity) {
                newVelocity = collisionOffset;
                collideWithWall = true;
                break;
            }
        }

        particle.shape.move(newVelocity);
        handleCollision(particle, { 1280, 720 }, collideWithWall);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bouncing Particles GUI");
    ImGui::SFML::Init(window);
    window.setFramerateLimit(60);

    std::vector<Particle> particles;
    std::vector<Wall> walls;

    sf::Clock deltaClock;
    sf::Clock frameClock;  // Clock to measure frame time
    sf::Clock fpsClock;    // Clock to track FPS update interval
    int frameCount = 0;
    int fps = 0;

    float px = 0.f;
    float py = 0.f;
    float angle = 0.f;
    float velocity = 0.f;

    float wx1 = 0.f;
    float wy1 = 0.f;
    float wx2 = 0.f;
    float wy2 = 0.f;

    //Case 1
    float startx = 0.f;
    float endx = 0.f;
    float starty = 0.f;
    float endy = 0.f;
    float constantAngle1 = 0.f;
    float constantVel1 = 0.f;
    int n1 = 0;

    //Case 2
    float startTheta = 0.f;
    float endTheta = 0.f;
    float x0 = 0.f;
    float y0 = 0.f;
    float constantVel2 = 0.f;
    int n2 = 0;

    //Case 3
    float startVelocity = 0.f;
    float endVelocity = 0.f;
    float cAngle = 0.f;
    float xStart = 0.f;
    float yStart = 0.f;
    int n3 = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, sf::seconds(1.0f / 60.0f)); // Limit ImGui update to 60 FPS

        // Compute the frame rate
        float frameRate = 1.0f / frameClock.restart().asSeconds();

        // Display FPS every 0.5 seconds
        if (fpsClock.getElapsedTime().asSeconds() >= 0.5) {
            fps = frameCount / fpsClock.restart().asSeconds();
            frameCount = 0;
            std::cout << "Frame Rate = " << fps << " FPS\n" << std::endl;
        }

        ImGui::Begin("Menu");
        ImGui::SetWindowFontScale(1.3f);
        ImGui::Text("FPS: %d", fps);
        ImGui::NewLine();
        ImGui::StyleColorsLight();

        ImGui::Columns(2, "Menu", false);

        ImGui::Text("Particle");
        ImGui::InputFloat("x", &px);
        ImGui::InputFloat("y", &py);
        ImGui::InputFloat("Angle", &angle);
        ImGui::InputFloat("Velocity", &velocity);
        if (ImGui::Button("Add Particle")) {
            Particle particle(px, py, velocity, angle);
            particles.push_back(particle);
        }

        ImGui::NextColumn();
        ImGui::Text("Wall");
        ImGui::InputFloat("x1", &wx1);
        ImGui::InputFloat("y1", &wy1);

        ImGui::InputFloat("x2", &wx2);
        ImGui::InputFloat("y2", &wy2);

        if (ImGui::Button("Add Wall")) {
            Wall wall(wx1, wy1, wx2, wy2);
            walls.push_back(wall);
        }

        // Case 1
        ImGui::NextColumn();

        // Inputs for the new row
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::Text("1. Add particles by batch:");
        ImGui::InputInt("1_# Particles", &n1);

        ImGui::NewLine();
        ImGui::InputFloat("1_x0", &startx);
        ImGui::InputFloat("1_x1", &endx);
        ImGui::InputFloat("cAngle", &constantAngle1);

        ImGui::NextColumn();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::InputFloat("1_y0", &starty);
        ImGui::InputFloat("1_y1", &endy);
        ImGui::InputFloat("cVelocity", &constantVel1);
        if (ImGui::Button("1_Add_Particles")) {
            float deltaX = (endx - startx) / n1;
            float deltaY = (endy - starty) / n1;
            float currentX = startx;
            float currentY = starty;
            for (int i = 0; i < n1; ++i) {
                Particle particle(currentX, currentY, constantVel1, constantAngle1);
                particles.push_back(particle);
                currentX += deltaX;
                currentY += deltaY;
            }
        }


        // Case 2
        ImGui::NextColumn();
        // Inputs for the new row
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::Text("2. Add particles by batch:");
        ImGui::InputInt("2_# of Particles", &n2);
        ImGui::NewLine();

        ImGui::InputFloat(":x0", &x0);
        ImGui::InputFloat("theta0", &startTheta);
        ImGui::InputFloat("2_Velocity", &constantVel2);

        ImGui::NextColumn();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::InputFloat(":y0", &y0);
        ImGui::InputFloat("theta1", &endTheta);
        if (ImGui::Button("Fan Out")) {
            float deltaTheta = (endTheta - startTheta) / n2;
            float currentTheta = startTheta;
            for (int i = 0; i < n2; ++i) {
                // Calculate particle position based on current angle (theta)
                float x = x0 + cos(currentTheta);
                float y = y0 + sin(currentTheta);
                Particle particle(x, y, constantVel2, currentTheta);
                particles.push_back(particle);
                currentTheta += deltaTheta;
            }
        }


        // Case 3
        ImGui::NextColumn();
        // Inputs for the new row
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::Text("3. Add particles by batch:");
        ImGui::InputInt("3_# of Particles", &n3);
        ImGui::NewLine();
        ImGui::InputFloat("-x0", &xStart);
        ImGui::InputFloat("velocity0", &startVelocity);
        ImGui::InputFloat(":angle", &cAngle);

        ImGui::NextColumn();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();


        ImGui::InputFloat("-y0", &yStart);
        ImGui::InputFloat("velocity1", &endVelocity);
        if (ImGui::Button("3_Add_Particles")) {
            // Calculate the velocity difference
            float velocityDifference = endVelocity - startVelocity;

            // Calculate the uniform increment in velocity for each particle
            float velocityIncrement = velocityDifference / (n3 - 1);

            // Add particles with uniformly distributed velocities
            float currentVelocity = startVelocity;
            for (int i = 0; i < n3; ++i) {
                // Add particle with current velocity
                Particle particle(xStart, yStart, currentVelocity, cAngle);
                particles.push_back(particle);

                // Increment velocity for next particle
                currentVelocity += velocityIncrement;
            }
        }


        ImGui::End();


        updateParticles(particles, walls);

        ++frameCount;
        window.clear();

        //invert y-axis
        window.setView(sf::View(sf::FloatRect(0.f, 720.f, 1280.f, -720.f)));

        for (const auto& particle : particles) {
            window.draw(particle.shape);
        }

        for (const auto& wall : walls) {
            window.draw(wall.shape);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
