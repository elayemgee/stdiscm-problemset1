#include "InputGUI.hpp"
#include "particleCanvas.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

InputGUI::InputGUI(sf::Font& font, sf::RenderWindow& window) : window(window) {
    // Implementation of the constructor
    frameRateText.setFont(font);
    frameRateText.setCharacterSize(30);
    frameRateText.setFillColor(sf::Color::Yellow);
    frameRateText.setPosition(140, 0);

    titleText.setFont(font);
    titleText.setString("Particle");
    titleText.setCharacterSize(30);
    titleText.setFillColor(sf::Color::White);

    xText.setFont(font);
    yText.setFont(font);
    angleText.setFont(font);
    velocityText.setFont(font);

    xText.setString("Enter x:");
    yText.setString("Enter y:");
    angleText.setString("Enter angle:");
    velocityText.setString("Enter velocity:");

    xText.setCharacterSize(16);
    yText.setCharacterSize(16);
    angleText.setCharacterSize(16);
    velocityText.setCharacterSize(16);

    xText.setPosition(10, 50);
    yText.setPosition(10, 90);
    angleText.setPosition(10, 130);
    velocityText.setPosition(10, 170);

    xInputBox.setSize(sf::Vector2f(100, 20));
    yInputBox.setSize(sf::Vector2f(100, 20));
    angleInputBox.setSize(sf::Vector2f(100, 20));
    velocityInputBox.setSize(sf::Vector2f(100, 20));

    xInputBox.setPosition(120, 50);
    yInputBox.setPosition(120, 90);
    angleInputBox.setPosition(120, 130);
    velocityInputBox.setPosition(120, 170);

    xInputText.setFont(font);
    yInputText.setFont(font);
    angleInputText.setFont(font);
    velocityInputText.setFont(font);

    xInputText.setCharacterSize(16);
    yInputText.setCharacterSize(16);
    angleInputText.setCharacterSize(16);
    velocityInputText.setCharacterSize(16);

    xInputText.setPosition(130, 50);
    yInputText.setPosition(130, 90);
    angleInputText.setPosition(130, 130);
    velocityInputText.setPosition(130, 170);

    cursor.setSize(sf::Vector2f(1, 16));
    cursor.setFillColor(sf::Color::Black);

    submitParticleButton.setSize(sf::Vector2f(100, 20));
    submitParticleButton.setPosition(120, 210);
    submitParticleButton.setFillColor(sf::Color::Blue);
    buttonParticleText.setFont(font);
    buttonParticleText.setFillColor(sf::Color::White);
    buttonParticleText.setString("Submit");
    buttonParticleText.setCharacterSize(16);
    buttonParticleText.setPosition(140, 210);

    x = 0;
    y = 0;
    angle = 0;
    velocity = 0;

    isXActive = false;
    isYActive = false;
    isAngleActive = false;
    isVelocityActive = false;

    isCursorVisible = true;
    lastCursorToggleTime = std::chrono::high_resolution_clock::now();

    // Title text for "Wall"
    wallTitle.setFont(font);
    wallTitle.setString("Wall");
    wallTitle.setCharacterSize(30);
    wallTitle.setPosition(10, 220);
    wallTitle.setFillColor(sf::Color::White);
    wallTitle.move(0, 30);

    // Wall Inputs
    x1Text.setFont(font);
    x2Text.setFont(font);
    y1Text.setFont(font);
    y2Text.setFont(font);

    x1Text.setString("Enter x1:");
    x2Text.setString("Enter x2:");
    y1Text.setString("Enter y1:");
    y2Text.setString("Enter y2:");

    x1Text.setCharacterSize(16);
    x2Text.setCharacterSize(16);
    y1Text.setCharacterSize(16);
    y2Text.setCharacterSize(16);

    x1Text.setPosition(10, 300);
    x2Text.setPosition(10, 340);
    y1Text.setPosition(10, 380);
    y2Text.setPosition(10, 420);


    // Wall Input Boxes
    x1InputBox.setSize(sf::Vector2f(100, 20));
    x2InputBox.setSize(sf::Vector2f(100, 20));
    y1InputBox.setSize(sf::Vector2f(100, 20));
    y2InputBox.setSize(sf::Vector2f(100, 20));

    x1InputBox.setPosition(120, 300);
    x2InputBox.setPosition(120, 340);
    y1InputBox.setPosition(120, 380);
    y2InputBox.setPosition(120, 420);

    //Wall Input Text
    x1InputText.setFont(font);
    x2InputText.setFont(font);
    y1InputText.setFont(font);
    y2InputText.setFont(font);

    x1InputText.setCharacterSize(16);
    x2InputText.setCharacterSize(16);
    y1InputText.setCharacterSize(16);
    y2InputText.setCharacterSize(16);

    x1InputText.setPosition(130, 300);
    x2InputText.setPosition(130, 340);
    y1InputText.setPosition(130, 380);
    y2InputText.setPosition(130, 420);

    //Wall Submit
    submitWallButton.setSize(sf::Vector2f(100, 20));
    submitWallButton.setPosition(120, 460);
    submitWallButton.setFillColor(sf::Color::Blue);
    buttonWallText.setFont(font);
    buttonWallText.setFillColor(sf::Color::White);
    buttonWallText.setString("Submit");
    buttonWallText.setCharacterSize(16);
    buttonWallText.setPosition(140, 460);

    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;

    isX1Active = false;
    isX2Active = false;
    isY1Active = false;
    isY2Active = false;
}

void InputGUI::handleEvent(sf::Event& event, ParticleCanvas& particleCanvas) {
    // Implementation of the handleEvent function
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (xInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = true;
            isYActive = false;
            isAngleActive = false;
            isVelocityActive = false;
            isX1Active = false;
            isX2Active = false;
            isY1Active = false;
            isY2Active = false;
        }
        else if (yInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = true;
            isAngleActive = false;
            isVelocityActive = false;
            isX1Active = false;
            isX2Active = false;
            isY1Active = false;
            isY2Active = false;
        }
        else if (angleInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = false;
            isAngleActive = true;
            isVelocityActive = false;
            isX1Active = false;
            isX2Active = false;
            isY1Active = false;
            isY2Active = false;
        }
        else if (velocityInputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = false;
            isAngleActive = false;
            isVelocityActive = true;
            isX1Active = false;
            isX2Active = false;
            isY1Active = false;
            isY2Active = false;
        }
        else if (x1InputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = false;
            isAngleActive = false;
            isVelocityActive = false;
            isX1Active = true;
            isX2Active = false;
            isY1Active = false;
            isY2Active = false;
        }
        else if (x2InputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = false;
            isAngleActive = false;
            isVelocityActive = false;
            isX1Active = false;
            isX2Active = true;
            isY1Active = false;
            isY2Active = false;
        }
        else if (y1InputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = false;
            isAngleActive = false;
            isVelocityActive = false;
            isX1Active = false;
            isX2Active = false;
            isY1Active = true;
            isY2Active = false;
        }
        else if (y2InputBox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            isXActive = false;
            isYActive = false;
            isAngleActive = false;
            isVelocityActive = false;
            isX1Active = false;
            isX2Active = false;
            isY1Active = false;
            isY2Active = true;
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (isXActive && event.text.unicode == 8) {  // Backspace
            std::string currentString = xInputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                xInputText.setString(currentString);
            }
        }
        else if (isYActive && event.text.unicode == 8) {
            std::string currentString = yInputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                yInputText.setString(currentString);
            }
        }
        else if (isAngleActive && event.text.unicode == 8) {
            std::string currentString = angleInputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                angleInputText.setString(currentString);
            }
        }
        else if (isVelocityActive && event.text.unicode == 8) {
            std::string currentString = velocityInputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                velocityInputText.setString(currentString);
            }
        }
        else if (isX1Active && event.text.unicode == 8) {
            std::string currentString = x1InputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                x1InputText.setString(currentString);
            }
        }
        else if (isX2Active && event.text.unicode == 8) {
            std::string currentString = x2InputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                x2InputText.setString(currentString);
            }
        }
        else if (isY1Active && event.text.unicode == 8) {
            std::string currentString = y1InputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                y1InputText.setString(currentString);
            }
        }
        else if (isY2Active && event.text.unicode == 8) {
            std::string currentString = y2InputText.getString();
            if (!currentString.empty()) {
                currentString.pop_back();
                y2InputText.setString(currentString);
            }
        }

        else if (isXActive && event.text.unicode >= 32 && event.text.unicode < 127) {
            xInputText.setString(xInputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isYActive && event.text.unicode >= 32 && event.text.unicode < 127) {
            yInputText.setString(yInputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isAngleActive && event.text.unicode >= 32 && event.text.unicode < 127) {
            angleInputText.setString(angleInputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isVelocityActive && event.text.unicode >= 32 && event.text.unicode < 127) {
            velocityInputText.setString(velocityInputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isX1Active && event.text.unicode >= 32 && event.text.unicode < 127) {
            x1InputText.setString(x1InputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isX2Active && event.text.unicode >= 32 && event.text.unicode < 127) {
            x2InputText.setString(x2InputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isY1Active && event.text.unicode >= 32 && event.text.unicode < 127) {
            y1InputText.setString(y1InputText.getString() + static_cast<char>(event.text.unicode));
        }
        else if (isY2Active && event.text.unicode >= 32 && event.text.unicode < 127) {
            y2InputText.setString(y2InputText.getString() + static_cast<char>(event.text.unicode));
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonParticleBounds = submitParticleButton.getGlobalBounds();
        sf::FloatRect buttonWallBounds = submitWallButton.getGlobalBounds();
        if (buttonParticleBounds.contains(mousePos.x, mousePos.y)) {
            if (!xInputText.getString().isEmpty() && !yInputText.getString().isEmpty() &&
                !angleInputText.getString().isEmpty() && !velocityInputText.getString().isEmpty()) {
                x = std::stoi(xInputText.getString().toAnsiString());
                y = std::stoi(yInputText.getString().toAnsiString());
                angle = std::stoi(angleInputText.getString().toAnsiString());
                velocity = std::stoi(velocityInputText.getString().toAnsiString());

                std::cout << "x: " << x << "\n";
                std::cout << "y: " << y << "\n";
                std::cout << "angle: " << angle << "\n";
                std::cout << "velocity: " << velocity << "\n";

                particleCanvas.update();
                //particleCanvas.displayParticleAt(x, y, angle, velocity);
                particleCanvas.addParticle(sf::Vector2f(x + 300, y), sf::Vector2f(velocity * std::cos(angle), velocity * std::sin(angle)));

            }
        }
        if (buttonWallBounds.contains(mousePos.x, mousePos.y)) {
            if (!x1InputText.getString().isEmpty() && !x2InputText.getString().isEmpty() &&
                !y1InputText.getString().isEmpty() && !y2InputText.getString().isEmpty()) {
                x1 = std::stoi(x1InputText.getString().toAnsiString());
                x2 = std::stoi(x2InputText.getString().toAnsiString());
                y1 = std::stoi(y1InputText.getString().toAnsiString());
                y2 = std::stoi(y2InputText.getString().toAnsiString());

                std::cout << "x1: " << x1 << "\n";
                std::cout << "x2: " << x2 << "\n";
                std::cout << "y1: " << y1 << "\n";
                std::cout << "y2: " << y2 << "\n";
            }
        }
    }
}

void InputGUI::update(sf::RenderWindow& window) {
    // Implementation of the update function
    // Handle cursor visibility
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCursorToggleTime).count();

    if (elapsed > 500) {  // Toggle cursor every 500 milliseconds
        isCursorVisible = !isCursorVisible;
        lastCursorToggleTime = currentTime;
    }

    // Set the text color of the active input box to black and the inactive ones to gray
    xInputText.setFillColor(isXActive ? sf::Color::Black : sf::Color::Black);
    yInputText.setFillColor(isYActive ? sf::Color::Black : sf::Color::Black);
    angleInputText.setFillColor(isAngleActive ? sf::Color::Black : sf::Color::Black);
    velocityInputText.setFillColor(isVelocityActive ? sf::Color::Black : sf::Color::Black);

    x1InputText.setFillColor(isX1Active ? sf::Color::Black : sf::Color::Black);
    x2InputText.setFillColor(isX2Active ? sf::Color::Black : sf::Color::Black);
    y1InputText.setFillColor(isY1Active ? sf::Color::Black : sf::Color::Black);
    y2InputText.setFillColor(isY2Active ? sf::Color::Black : sf::Color::Black);
}

void InputGUI::render(sf::RenderWindow& window, float fps) {
    // Implementation of the render function
    // Draw dividing line...
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(300, 0)),
        sf::Vertex(sf::Vector2f(300, 720))
    };
    window.draw(line, 2, sf::Lines);

    std::stringstream fpsStringStream;
    fpsStringStream << std::fixed << std::setprecision(2) << fps;

    frameRateText.setString("FPS: " + fpsStringStream.str());
    // Draw GUI elements...
    window.draw(frameRateText);
    window.draw(titleText);
    window.draw(xText);
    window.draw(yText);
    window.draw(angleText);
    window.draw(velocityText);

    window.draw(xInputBox);
    window.draw(yInputBox);
    window.draw(angleInputBox);
    window.draw(velocityInputBox);

    window.draw(xInputText);
    window.draw(yInputText);
    window.draw(angleInputText);
    window.draw(velocityInputText);

    //Wall
    window.draw(wallTitle);
    window.draw(x1Text);
    window.draw(x2Text);
    window.draw(y1Text);
    window.draw(y2Text);

    window.draw(x1InputBox);
    window.draw(x2InputBox);
    window.draw(y1InputBox);
    window.draw(y2InputBox);

    window.draw(x1InputText);
    window.draw(x2InputText);
    window.draw(y1InputText);
    window.draw(y2InputText);

    // Draw the cursor if the input box is active and the cursor is visible
    if (isXActive && isCursorVisible) {
        cursor.setPosition(xInputText.findCharacterPos(xInputText.getString().getSize()).x, 50);
        window.draw(cursor);
    }
    else if (isYActive && isCursorVisible) {
        cursor.setPosition(yInputText.findCharacterPos(yInputText.getString().getSize()).x, 90);
        window.draw(cursor);
    }
    else if (isAngleActive && isCursorVisible) {
        cursor.setPosition(angleInputText.findCharacterPos(angleInputText.getString().getSize()).x, 130);
        window.draw(cursor);
    }
    else if (isVelocityActive && isCursorVisible) {
        cursor.setPosition(velocityInputText.findCharacterPos(velocityInputText.getString().getSize()).x, 170);
        window.draw(cursor);
    }
    else if (isX1Active && isCursorVisible) {
        cursor.setPosition(x1InputText.findCharacterPos(x1InputText.getString().getSize()).x, 300);
        window.draw(cursor);
    }
    else if (isX2Active && isCursorVisible) {
        cursor.setPosition(x2InputText.findCharacterPos(x2InputText.getString().getSize()).x, 340);
        window.draw(cursor);
    }
    else if (isY1Active && isCursorVisible) {
        cursor.setPosition(y1InputText.findCharacterPos(y1InputText.getString().getSize()).x, 380);
        window.draw(cursor);
    }
    else if (isY2Active && isCursorVisible) {
        cursor.setPosition(y2InputText.findCharacterPos(y2InputText.getString().getSize()).x, 420);
        window.draw(cursor);
    }

    // Draw Submit button...
    window.draw(submitParticleButton);
    window.draw(buttonParticleText);

    window.draw(submitWallButton);
    window.draw(buttonWallText);
}

void InputGUI::setLastFPSTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& time) {
    // Implementation of the setLastFPSTime function
    lastFPSTime = time;

}

const std::chrono::time_point<std::chrono::high_resolution_clock>& InputGUI::getLastFPSTime() const {
    // Implementation of the getLastFPSTime function
    return lastFPSTime;
}

int InputGUI::getX() const {
    // Implementation of the getX function
    return x;
}

int InputGUI::getY() const {
    // Implementation of the getY function
    return y;
}

int InputGUI::getAngle() const {
    // Implementation of the getAngle function
    return angle;
}

int InputGUI::getVelocity() const {
    // Implementation of the getVelocity function
    return velocity;
}

int InputGUI::getX1() const {
    // Implementation of the getX1 function
    return x1;
}

int InputGUI::getX2() const {
    // Implementation of the getX2 function
    return x2;
}

int InputGUI::getY1() const {
    // Implementation of the getY1 function
    return y1;
}

int InputGUI::getY2() const {
    // Implementation of the getY2 function
    return y2;
}