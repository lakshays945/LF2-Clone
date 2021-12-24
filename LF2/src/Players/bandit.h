#pragma once
#include "commom.h"
#include "../Math/Utilities.h"

const double IdleTimes[4] = { 0.3,0.6,0.9,1.2 };
const int IdleLoactions[4][2] = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const double WalkingTimes[6] = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const int WalkingLoactions[6][2] = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const int Attack1Loactions[5][2] = { {560,80}, {480,80}, {400,80}, {480,80}, {560,80} };
const double Attack1Times[5] = { 0.08,0.16,0.24,0.32,0.4 };
const int Attack2Loactions[3][2] = { {0,80},{80,80},{160,80} };
const double Attack2Times[3] = { 0.1,0.2,0.3 };
const int Attack3Loactions[3][2] = { {640,0}, {720,0}, {720,160} };
const double Attack3Times[3] = { 0.1,0.2,0.4 };
const int JumpingLoactions[3][2] = { {80,480}, {160,480}, {80,480} };
const double JumpingTimes[3] = {0.15,0.85,1.0};
const int RunningLocations[4][2] = { {80,160}, {0,160}, {80,160}, {160,160} };
const double RunningTimes[4] = { 0.15,0.3,0.45,0.6 };
const int JumpingAttackLocations[3][2] = { {560,240},{640,240}, { 560,240} };
const double JumpingAttackTimes[3] = { 0.15,0.4,0.55 };
const int CrouchLocations[1][2] = { {0,480} };
const double CrouchTimes[1] = { 0.1 };
class Bandit {
public:
    RealVector2D Position;
    RealVector2D LastPosition;
    RealVector2D Velocity;
    float MaxSpeed = 200;
    double TimeSinceLastState = 0;
    bool JustStateChanged = false;
    AnimationSheet IdleSheet; 
    AnimationSheet WalkingSheet; 
    AnimationSheet RunningSheet;
    AnimationSheet JumpingSheet; 
    AnimationSheet HittingSheet[3]; 
    AnimationSheet Getting_HitSheet; 
    AnimationSheet FallingSheet; 
    AnimationSheet JumpingAttackSheet;
    AnimationSheet* CurrentSheet;
    int Up = 0, Down = 0, Right = 0, Left = 0;
    int ComboStreak = 0; //the index of hitting_animation sheet
    int Direction = 1; //direction of player (1 is right , -1 is left)
    State CurrentState = IDLE;
    StateManager State_Manager;
    InputManager Input_Manager;
    Bandit() //Constructor (Mainly assigning images to animationSheet is done)
        :Position(RealVector2D(100, 100)), Velocity(RealVector2D(10, 10)) {
        State_Manager.AssignPlayer(this);
        Input_Manager.AssignPlayer(this);
        IdleSheet.AssignPlayer(this);
        WalkingSheet.AssignPlayer(this);
        RunningSheet.AssignPlayer(this);
        JumpingSheet.AssignPlayer(this);
        HittingSheet[0].AssignPlayer(this);
        HittingSheet[1].AssignPlayer(this);
        HittingSheet[2].AssignPlayer(this);
        Getting_HitSheet.AssignPlayer(this);
        FallingSheet.AssignPlayer(this);
        JumpingAttackSheet.AssignPlayer(this);
        for (int i = 0; i < 4; i++) { //Setting textures for idle sheet
            IdleSheet.Textures.push_back(sf::Texture());
            IdleSheet.Sprites.push_back(sf::Sprite());
            IdleSheet.DrawTimes.push_back(IdleTimes[i]);
            IdleSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(IdleLoactions[i][0], IdleLoactions[i][1], 80, 80));
        }
        for (int i = 0; i < 6; i++) { //Setting textures for walking sheet
            WalkingSheet.Textures.push_back(sf::Texture());
            WalkingSheet.Sprites.push_back(sf::Sprite());
            WalkingSheet.DrawTimes.push_back(WalkingTimes[i]);
            WalkingSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(WalkingLoactions[i][0], WalkingLoactions[i][1], 80, 80));
        }
        for (int i = 0; i < 5; i++) {
            HittingSheet[0].Textures.push_back(sf::Texture());
            HittingSheet[0].Sprites.push_back(sf::Sprite());
            HittingSheet[0].DrawTimes.push_back(Attack1Times[i]);
            HittingSheet[0].Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(Attack1Loactions[i][0], Attack1Loactions[i][1], 80, 80));
        }
        for (int i = 0; i < 3; i++) {
            HittingSheet[1].Textures.push_back(sf::Texture());
            HittingSheet[1].Sprites.push_back(sf::Sprite());
            HittingSheet[1].DrawTimes.push_back(Attack2Times[i]);
            HittingSheet[1].Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(Attack2Loactions[i][0], Attack2Loactions[i][1], 80, 80));
        }
        for (int i = 0; i < 3; i++) {
            HittingSheet[2].Textures.push_back(sf::Texture());
            HittingSheet[2].Sprites.push_back(sf::Sprite());
            HittingSheet[2].DrawTimes.push_back(Attack3Times[i]);
            HittingSheet[2].Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(Attack3Loactions[i][0], Attack3Loactions[i][1], 80, 80));
        }
        for (int i = 0; i < 3; i++) {
            JumpingSheet.Textures.push_back(sf::Texture());
            JumpingSheet.Sprites.push_back(sf::Sprite());
            JumpingSheet.DrawTimes.push_back(JumpingTimes[i]);
            JumpingSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(JumpingLoactions[i][0], JumpingLoactions[i][1], 80, 80));
        }
        for (int i = 0; i < 4; i++) {
            RunningSheet.Textures.push_back(sf::Texture());
            RunningSheet.Sprites.push_back(sf::Sprite());
            RunningSheet.DrawTimes.push_back(RunningTimes[i]);
            RunningSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(RunningLocations[i][0], RunningLocations[i][1], 80, 80));
        }
        for (int i = 0; i < 3; i++) {
            JumpingAttackSheet.Textures.push_back(sf::Texture());
            JumpingAttackSheet.Sprites.push_back(sf::Sprite());
            JumpingAttackSheet.DrawTimes.push_back(JumpingAttackTimes[i]);
            JumpingAttackSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(JumpingAttackLocations[i][0], JumpingAttackLocations[i][1], 80, 80));
        }
        IdleSheet.AssignTextures();
        WalkingSheet.AssignTextures();
        HittingSheet[0].AssignTextures();
        JumpingSheet.AssignTextures();
        RunningSheet.AssignTextures();
        JumpingAttackSheet.AssignTextures();
        JumpingSheet.OneTime = true;
        JumpingAttackSheet.OneTime = true;
        HittingSheet[0].OneTime = true;
        HittingSheet[1].AssignTextures();
        HittingSheet[1].OneTime = true;
        HittingSheet[2].AssignTextures();
        HittingSheet[2].OneTime = true;
        CurrentSheet = &IdleSheet;
    }

    //does things when state is changed (isko better banana hai and also have to add things in future)
    void ChangeState(State state,const double lastPressed, const int data=0) {
        CurrentSheet->Time = 0; //resetting the sheet currently being used (as it will be changed soon)
        CurrentState = state;
        TimeSinceLastState = 0;
        switch (state) {
        case IDLE:
            CurrentSheet = &IdleSheet;
            break;
        case WALKING:
            CurrentSheet = &WalkingSheet;
            break;
        case RUNNING:
            Run(lastPressed,data);
            CurrentSheet = &RunningSheet;
            break;
        case JUMPING:
            LastPosition = Position + RealVector2D(Velocity.get_x(),Velocity.get_y());
            Jump(lastPressed);
            CurrentSheet = &JumpingSheet;
            break;
        case HITTING:
            Attack(lastPressed);
            CurrentSheet = &HittingSheet[ComboStreak];
            break;
        case GETTING_HIT:
            CurrentSheet = &Getting_HitSheet;
            break;
        case FALLING:
            CurrentSheet = &FallingSheet;
            break;
        case JUMPINGATTACK:
            CurrentSheet = &JumpingAttackSheet;
            break;
        default:
            break;
        }
    }

    //Determines which functions will be called acc. to the current state
    void Update(const double dt,sf::RenderWindow &window) { //temporary (isko better banana hai implementation wise) 
        Input_Manager.Update(dt);
        if (TimeSinceLastState < 20) {
            TimeSinceLastState += dt;
        }
        switch (CurrentState) {
        case IDLE:
            AddForce(dt);
            Translate(dt);
            break;
        case WALKING:
            AddForce(dt);
            Translate(dt);
            break;
        case RUNNING:
            Translate(dt);
            break;
        case JUMPING:
            Velocity = Velocity + Gravity*dt;
            Translate(dt);
            if (TimeSinceLastState >= 1) {
                Position.Set(LastPosition);
                ///State_Manager.ForceStateChange(IDLE);
            }
            break;
        case HITTING:
            break;
        case GETTING_HIT:
            
            break;
        case FALLING:
            
            break;
        case JUMPINGATTACK:
            Velocity = Velocity + Gravity * dt * (1/0.55);
            Translate(dt);
            break;
        default:
            break;
        }
        Animate(window, dt); //after determining position and other stuff then animate() will be called
    }

    void Attack(const double lastPressed) { //temporary (isko better banana hai) and many things has to be added in future
        Velocity.SetMagnitude(0);
        Up = 0; Down = 0; Left = 0; Down = 0;
        if (lastPressed < 0.4) {
            ComboStreak++;
        }
        else {
            ComboStreak = 0;
        }
        if (ComboStreak > 2)
            ComboStreak = 0;
    }

    void Jump(const double lastPressed) { //temporary (isko better banana hai)
        Velocity = RealVector2D(Velocity.get_x(), -500 + Velocity.get_y());
    }

    void JumpCalculation(const double dt, const double t) {
        
    }

    void Run(const double lastPressed, int dir) { //temporary (isko better banana hai)
        Velocity = RealVector2D(300*dir, 0);
    }

    void AddForce(const double dt) { //for movement based upon inputs
        Up = Input_Manager.IsKeyPressed(sf::Keyboard::W);
        Down = Input_Manager.IsKeyPressed(sf::Keyboard::S);
        Right = Input_Manager.IsKeyPressed(sf::Keyboard::D);
        Left = Input_Manager.IsKeyPressed(sf::Keyboard::A);
        if ((Up + Down + Right + Left == 0) || (Up - Down == 0 && Right - Left == 0)) {
            Velocity.SetMagnitude(0);
            State_Manager.ForceStateChange(IDLE);
            return;
        }
        State_Manager.ForceStateChange(WALKING);
        RealVector2D Force((Right - Left) * 100, (Down - Up) * 100);
        Velocity = Velocity + Force * dt * 500;
        if (Velocity.Magnitude() > MaxSpeed) {
            Velocity.SetMagnitude(MaxSpeed);
        }
    }

    void Translate(const double dt) {// changes position based on velocity  nothing else
        Position = Position + Velocity * dt;
    }
    void Animate(sf::RenderWindow& window, const double dt) { //give it an animation sheet (not as a parameter) and window and it will animate
        CurrentSheet->Time += dt;
        sf::Sprite* current = &CurrentSheet->Sprites[CurrentSheet->GetCorrectIndex()];
        if (Velocity.get_x() < 0) {
            Direction = -1;
        }
        else if(Velocity.get_x() > 0) {
            Direction = 1;
        }
        current->setScale(sf::Vector2f(Direction, 1));
        current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
        window.draw(*current);
    }
};