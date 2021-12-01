#pragma once
#include <SFML/Graphics.hpp>
#include "Math/Utilities.h"
sf::Texture Loader;
class Bandit {
public:
    RealVector2D Position;
    RealVector2D Velocity;
    float MaxSpeed = 200;
    sf::Sprite IdleSprite[4];
    sf::Sprite CurrentSprite;
    int Up = 0, Down = 0, Right = 0, Left = 0;
    float MaxTime = 4, Time = 0;
    Bandit()
        :Position(RealVector2D(0, 0)), Velocity(RealVector2D(10, 10)) {
        for (int i = 0; i < 3; i++) {
            Loader.loadFromFile("src/Resource/Bandit.png", sf::IntRect(80 * i + 320, 0, 80, 80));
            IdleSprite[i].setTexture(Loader);
        }
        CurrentSprite = IdleSprite[1];
    }
    void AddForce(const double dt) {
        if (Up + Down + Right + Left == 0) {
            Velocity.SetMagnitude(0);
            return;
        }
        RealVector2D Force((Right - Left) * 100, (Down - Up) * 100);
        Velocity = Velocity + Force * dt * 500;
        if (Velocity.Magnitude() > MaxSpeed) {
            Velocity.SetMagnitude(MaxSpeed);
        }
    }
    void Translate(const double dt) {
        Position = Position + Velocity * dt;
    }
    void Animate(sf::RenderWindow& window) {
        CurrentSprite.setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
        window.draw(CurrentSprite);
    }
};