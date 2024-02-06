#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <vector>

// headers for setting precision
#include <iomanip>  
#include <sstream>  
#include "particleCanvas.hpp"
#include "inputGUI.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(1580, 720), "Input GUI and Bouncing Ball");
    sf::Clock clock;
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    InputGUI inputGUI(font, window);
    ParticleCanvas particleCanvas(window);

    // Main loop
    while (window.isOpen()) {
        //Compute the frame rate
        float time = clock.restart().asSeconds();
        float frameRate = 1.0f / (time);

        // Display FPS every 0.5 seconds
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - inputGUI.getLastFPSTime()).count();

        if (elapsed > 500) {  // Display FPS every 0.5 seconds
            inputGUI.setLastFPSTime(currentTime);
            std::cout << "Frame Rate = " << frameRate << " FPS\n" << std::endl;
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            inputGUI.handleEvent(event, particleCanvas);
        }

        window.clear();

        inputGUI.update(window);
        inputGUI.render(window, frameRate);

        particleCanvas.update();
        particleCanvas.render(window);

        window.display();

    }

    return 0;
}