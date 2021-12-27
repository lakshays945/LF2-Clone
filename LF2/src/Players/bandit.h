#pragma once
#include "commom.h"
#include "Math/Utilities.h"
#include <iostream>
#include "Input/InputManager.h"
#include "Input/StateManager.h"
#include "HitBox.h"
#define JUMP_DURATION 0.8
#define INITIAL_JUMP_PAUSE 0.2
#define JUMP_LANDING_TIME 0.2
#define DASH_DURATION 0.4
#define DASH_LANDING_TIME 0.2

const double IdleTimes[4] = { 0.3,0.6,0.9,1.2 };
const int IdleLocations[4][2] = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const double WalkingTimes[6] = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const int WalkingLocations[6][2] = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const int Attack1Locations[5][2] = { {560,80}, {480,80}, {400,80}, {480,80}, {560,80} };
const double Attack1Times[5] = { 0.08,0.16,0.24,0.32,0.4 };
const int Attack2Locations[3][2] = { {0,80},{80,80},{160,80} };
const double Attack2Times[3] = { 0.1,0.2,0.3 };
const int Attack3Locations[3][2] = { {640,0}, {720,0}, {720,160} };
const double Attack3Times[3] = { 0.1,0.2,0.4 };
const int JumpingLocations[3][2] = { {80,480}, {160,480}, {80,480} };
const double JumpingTimes[3] = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE+JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME};
const int RunningLocations[4][2] = { {80,160}, {0,160}, {80,160}, {160,160} };
const double RunningTimes[4] = { 0.15,0.3,0.45,0.6 };
const int JumpingAttackLocations[4][2] = { {560,240},{640,240}, { 560,240}, {160,480} };
const double JumpingAttackTimes[4] = { 0.15,0.4,0.55,2 };
const int DashLocations[2][2] = { {240,480},{80,480} };
const double DashTimes[2] = { DASH_DURATION, DASH_DURATION+DASH_LANDING_TIME };


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
	AnimationSheet DashSheet;
	AnimationSheet* CurrentSheet;
	int Up = 0, Down = 0, Right = 0, Left = 0;
	int ComboStreak = 0; //the index of hitting_animation sheet
	int Direction = 1; //direction of player (1 is right , -1 is left)
	PlayerStates CurrentState = IDLE;
	StateManager State_Manager;
	InputManager Input_Manager;
	HitBox DamageHitBox;
	HitBox Attack1HitBox;
	HitBox Attack2HitBox;
	HitBox Attack3HitBox;
	HitBox JumpingAttackHitBox;
	HitBox* CurrentAttackHitBox;

	//CONSTRUCTOR
	Bandit();

	//-----------------------------------------METHODS----------------------------------------


	//does things when state is changed (isko better banana hai and also have to add things in future)
	void ChangeState(PlayerStates state, const double lastPressed, const double data = 0, const double startTime = 0);
	//Determines which functions will be called acc. to the current state
	//temporary (isko better banana hai implementation wise) 
	void Update(const double dt, sf::RenderWindow& window);
	//temporary (isko better banana hai) and many things has to be added in future
	void Attack(const double lastPressed);
	//temporary (isko better banana hai)
	void Jump(const double lastPressed);
	void JumpCalculation(const double dt, const double t);
	void Dash();
	void DashCalculations(const double dt, const double t);
	//temporary (isko better banana hai)
	void Run(const double lastPressed, int dir);
	void Stop();
	void AddForce(const double dt);
	// changes position based on velocity  nothing else
	void Translate(const double dt);
	void Animate(sf::RenderWindow& window, const double dt);


};

#undef JUMP_DURATION
#undef INITIAL_JUMP_PAUSE
#undef JUMP_LANDING_TIME
#undef DASH_DURATION
#undef DASH_LANDING_TIME
