#pragma once
#include <SFML/Graphics.hpp>
#include "commom.h"
#include "Math/Utilities.h"

class Bandit {
public:
    RealVector2D Position;
    RealVector2D Velocity;
    float MaxSpeed = 200;
    AnimationSheet IdleSheet; //State array index 0
    AnimationSheet WalkingSheet; //State array index 1
    AnimationSheet RunningSheet; //State array index 2
    AnimationSheet JumpingSheet; //State array index 3
    AnimationSheet HittingSheet; //State array index 4
    AnimationSheet Getting_HitSheet; //State array index 5
    AnimationSheet FallingSheet; //State array index 6
    AnimationSheet* CurrentSheet; //State array index 7
    //State array stores the address of animation sheets so that new state can be assigned quickly
    AnimationSheet* StateArray[8] = { &IdleSheet, &WalkingSheet, &RunningSheet, &JumpingSheet,
                                      &HittingSheet, &Getting_HitSheet, &FallingSheet};
    int Up = 0, Down = 0, Right = 0, Left = 0;
    State CurrentState = IDLE;
    Bandit()
        :Position(RealVector2D(0, 0)), Velocity(RealVector2D(10, 10)) {
        for (int i = 0; i < 4; i++) { //Setting textures for idle sheet
            IdleSheet.Textures.push_back(sf::Texture());
            IdleSheet.Sprites.push_back(sf::Sprite());
            IdleSheet.DrawTimes.push_back((i+1)* 0.15);
            IdleSheet.Textures[i].loadFromFile("src/Resource/Bandit.png", sf::IntRect(80 * i , 0, 80, 80));
        }
        for (int i = 0; i < 4; i++) { //Setting textures for walking sheet
            WalkingSheet.Textures.push_back(sf::Texture());
            WalkingSheet.Sprites.push_back(sf::Sprite());
            WalkingSheet.DrawTimes.push_back((i + 1) * 0.15);
            WalkingSheet.Textures[i].loadFromFile("src/Resource/Bandit.png", sf::IntRect(80 * i + 320, 0, 80, 80));
        }
        IdleSheet.AssignTextures();
        WalkingSheet.AssignTextures();
        CurrentSheet = &IdleSheet;
    }

    void ChangeState(State state) {
        if (CurrentState != state) {
            CurrentSheet->Time = 0;
            CurrentState = state;
            CurrentSheet = StateArray[CurrentState];
        }
    }

    void AddForce(const double dt) {
        if (CurrentState != WALKING && CurrentState != IDLE && CurrentState != RUNNING){
            return;
        }
        if (Up + Down + Right + Left == 0) {
            Velocity.SetMagnitude(0);
            ChangeState(IDLE);
            return;
        }
        ChangeState(WALKING);
        RealVector2D Force((Right - Left) * 100, (Down - Up) * 100);
        Velocity = Velocity + Force * dt * 500;
        if (Velocity.Magnitude() > MaxSpeed) {
            Velocity.SetMagnitude(MaxSpeed);
        }
    }
    void Translate(const double dt) {
        Position = Position + Velocity * dt;
    }
    void Animate(sf::RenderWindow& window, const double dt) {
        CurrentSheet->Time += dt;
        CurrentSheet->Sprites[CurrentSheet->GetCorrectIndex()].setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
        window.draw(CurrentSheet->Sprites[CurrentSheet->GetCorrectIndex()]);
    }
};