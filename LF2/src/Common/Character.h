#pragma once
#include "AnimationSheet.h"
#include "Math/Utilities.h"
#include "Input/InputManager.h"
#include "Input/StateManager.h"
#include "HitBox.h"
#include <vector>
#include "GameObject/GameObject.h"

#define JUMP_DURATION 0.8
#define INITIAL_JUMP_PAUSE 0.2
#define JUMP_LANDING_TIME 0.2
#define DASH_DURATION 0.4
#define DASH_LANDING_TIME 0.2
#define DEFAULT_RUN_VELOCITY 300
#define DEFAULT_JUMP_VELOCITY -600
#define DEFAULT_DASH_VELOCITY_X 600
#define DEFAULT_DASH_VELOCITY_Y -400
#define DEFAULT_FORCE_SCALE 500*100
#define COMBO_THRESHOLD 0.4
#define MAX_LAST_TIME 20
#define JUMP_GRAVITY_FACTOR -(DEFAULT_JUMP_VELOCITY*2)/(DEFAULT_GRAVITY_CONSTANT*JUMP_DURATION)
#define DASH_GRAVITY_SCALE -(DEFAULT_DASH_VELOCITY_Y*2)/(DEFAULT_GRAVITY_CONSTANT*DASH_DURATION)
#define FALL_DURATION 0.7
#define FALL_VELOCITY_Y 300
#define FALL_VELOCITY_X 200
#define FALL_GRAVITY_SCALE -(FALL_VELOCITY_Y*2)/(DEFAULT_GRAVITY_CONSTANT*FALL_DURATION)


class Character: public GameObject  {
protected:
	static int nextCharacterID;
public:
	int CharacterID;
	RealVector2D LastPosition;
	float MaxSpeed = 200;
	int JumpSpeedY = -600;
	int DashSpeedX = 600;
	int RunSpeed = 300;
	double JumpGravityFactor;
	double TimeSinceLastState = 0;
	bool JustStateChanged = false;
	AnimationSheet IdleSheet;
	AnimationSheet WalkingSheet;
	AnimationSheet RunningSheet;
	AnimationSheet JumpingSheet;
	AnimationSheet HittingSheet[3];
	AnimationSheet Getting_HitSheet;
	AnimationSheet FallingBackSheet;
	AnimationSheet FallingFrontSheet;
	AnimationSheet JumpingAttackSheet;
	AnimationSheet DashSheet;
	AnimationSheet SpecialAttack1Sheet;
	AnimationSheet SpecialAttack2Sheet;
	AnimationSheet* CurrentSheet;
	int Up = 0, Down = 0, Right = 0, Left = 0;
	int ComboStreak = 0; //the index of hitting_animation sheet
	PlayerStates CurrentState = IDLE;
	StateManager State_Manager;
	InputManager Input_Manager;
	HitBox DamageHitBox;
	HitBox AttackHitBox;

	//CONSTRUCTOR
	Character();

	//-----------------------------------------METHODS----------------------------------------

	void RegisterCharacter();
	void ChangeState(PlayerStates state, const double lastPressed, const double data = 0, const double startTime = 0);
	void Update(const double dt, sf::RenderWindow& window);
	void Attack(const double lastPressed);
	void Jump(const double lastPressed);
	void JumpCalculation(const double dt, const double t);
	void Dash();
	void DashCalculations(const double dt, const double t);
	void Run(const double lastPressed, int dir);
	void Stop();
	void AddForce(const double dt);
	void Translate(const double dt);
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void FallBack(int SpeedX);
	void FallFront(int SpeedX);
	void FallBackCalculations(const double dt, const double t);
	void FallFrontCalculations(const double dt, const double t);

	//-----------------------------------PLAYER-SPECIFIC-METHODS----------------------------------------

	virtual void SpecialAttack1Calculations(const double dt, const double t) = 0;
	virtual void SpecialAttack2Calculations(const double dt, const double t) = 0;
};

extern std::vector <Character*> CharacterIDArray;

/*#undef JUMP_DURATION
#undef INITIAL_JUMP_PAUSE
#undef JUMP_LANDING_TIME
#undef DASH_DURATION
#undef DASH_LANDING_TIME*/
