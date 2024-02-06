#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "particleCanvas.hpp"

class InputGUI {
public:
    InputGUI(sf::Font& font, sf::RenderWindow& window);
    void handleEvent(sf::Event& event, ParticleCanvas& particleCanvas);
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window, float fps);
    void setLastFPSTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& time);
    const std::chrono::time_point<std::chrono::high_resolution_clock>& getLastFPSTime() const;
    int getX() const;
    int getY() const;
    int getAngle() const;
    int getVelocity() const;
    int getX1() const;
    int getX2() const;
    int getY1() const;
    int getY2() const;


private:
    sf::Text xText, yText, angleText, velocityText, titleText;
    sf::RectangleShape xInputBox, yInputBox, angleInputBox, velocityInputBox;
    sf::Text xInputText, yInputText, angleInputText, velocityInputText;
    bool isCursorVisible, isXActive, isYActive, isAngleActive, isVelocityActive;
    sf::RectangleShape cursor, submitParticleButton, submitWallButton;
    sf::Text buttonParticleText, buttonWallText;
    int x, y, angle, velocity;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastCursorToggleTime;
    sf::RenderWindow& window;
    int x1, x2, y1, y2;
    sf::Text x1Text, x2Text, y1Text, y2Text;
    sf::Text x1InputText, x2InputText, y1InputText, y2InputText;
    sf::RectangleShape x1InputBox, y1InputBox, x2InputBox, y2InputBox;
    bool isX1Active, isX2Active, isY1Active, isY2Active;
    sf::Text wallTitle;
    sf::Text frameRateText;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFPSTime;
};