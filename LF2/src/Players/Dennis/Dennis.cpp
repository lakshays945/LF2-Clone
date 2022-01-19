#include "Dennis.h"

sf::Texture DennisTexFile0;
sf::Texture DennisTexFile1;
sf::Texture DennisTexFile2;

const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const std::vector <double> IdleTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };

const std::vector<RealVector2D> Attack1Locations = { {560,80}, {480,80}, {400,80}, {480,80}, {560,80} };
const std::vector <double> Attack1Times = { 0.08,0.16,0.24,0.32,0.4 };

const std::vector<RealVector2D> Attack2Locations = { {0,80},{80,80},{160,80} };
const std::vector <double> Attack2Times = { 0.1,0.2,0.3 };

const std::vector<RealVector2D> Attack3Locations = { {640,0}, {720,0}, {720,160} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.4 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> JumpingAttackLocations = { {560,240},{640,240}, { 560,240}, {160,480} };
const std::vector <double> JumpingAttackTimes = { 0.15,0.4,0.55,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,0}, {560,320} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };

const std::vector<RealVector2D> FallingBackLocations = { {80,240},{160,240},{240,240},{400,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2};

const std::vector<RealVector2D> SpecialAttack1Locations = { {0,15}, {80,15}, {160,15}, {240,15}, {320,15} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.6 };

const std::vector<RealVector2D> SpecialAttack2Locations = { {80,335}, {160,335}, {240,335}, {320,335}, {400,335}, {480,335}, {560,335} };
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7 };

const std::vector<RealVector2D> SpecialAttack3Locations = { {0,255}, {80,255}, {160,255}, {240,255}, {320,255}, {400,255}, {480,255}, {400,255}, {320,255}, {0,335}, {640,255} };
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.4,0.55,0.6,0.75,0.8,1,1.2,1.4};

const std::vector<RealVector2D> BurningLocations = { {720,0}, {720,80},{480,480} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {560,480}, {640,480} };
const std::vector<double> FreezeTimes = { 0.2,6 };


Dennis::Dennis() {
	//Manager Assignments
	State_Manager.AssignPlayer(this);
	Input_Manager.AssignPlayer(this);

	//AnimationSheet Assignments
	IdleSheet.AssignPlayer(this);
	WalkingSheet.AssignPlayer(this);
	RunningSheet.AssignPlayer(this);
	JumpingSheet.AssignPlayer(this);
	HittingSheet[0].AssignPlayer(this);
	HittingSheet[1].AssignPlayer(this);
	HittingSheet[2].AssignPlayer(this);
	Getting_HitSheet[0].AssignPlayer(this);
	Getting_HitSheet[1].AssignPlayer(this);
	FallingBackSheet.AssignPlayer(this);
	JumpingAttackSheet.AssignPlayer(this);
	DashSheet.AssignPlayer(this);
	SpecialAttack1Sheet.AssignPlayer(this);
	SpecialAttack2Sheet.AssignPlayer(this);
	SpecialAttack3Sheet.AssignPlayer(this);
	FallingBackSheet.AssignPlayer(this);
	FallingFrontSheet.AssignPlayer(this);
	BurningSheet.AssignPlayer(this);
	FreezedSheet.AssignPlayer(this);


	//Sprite and Texture Loadindg{
	if (DennisTexFile0.getSize() == sf::Vector2u(0, 0)) {
		DennisTexFile0.loadFromFile("Resource/Dennis.png");
	}
	IdleSheet.AssignTextures(DennisTexFile0, IdleLocations, IdleTimes, 80, 80);
	WalkingSheet.AssignTextures(DennisTexFile0, WalkingLocations, WalkingTimes, 80, 80);
	HittingSheet[0].AssignTextures(DennisTexFile0, Attack1Locations, Attack1Times, 80, 80);
	HittingSheet[1].AssignTextures(DennisTexFile0, Attack2Locations, Attack2Times, 80, 80);
	HittingSheet[2].AssignTextures(DennisTexFile0, Attack3Locations, Attack3Times, 80, 80);
	JumpingSheet.AssignTextures(DennisTexFile0, JumpingLocations, JumpingTimes, 80, 80);
	RunningSheet.AssignTextures(DennisTexFile0, RunningLocations, RunningTimes, 80, 80);
	JumpingAttackSheet.AssignTextures(DennisTexFile0,JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	DashSheet.AssignTextures(DennisTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet[0].AssignTextures(DennisTexFile0, Getting_HitLocations1, Getting_HitTimes1, 80, 80);
	Getting_HitSheet[1].AssignTextures(DennisTexFile0, Getting_HitLocations2, Getting_HitTimes2, 80, 80);
	FallingBackSheet.AssignTextures(DennisTexFile0, FallingBackLocations, FallingBackTimes, -80, 80);
	FallingFrontSheet.AssignTextures(DennisTexFile0, FallingFrontLocations, FallingFrontTimes, 80, 80);
	FreezedSheet.AssignTextures(DennisTexFile0, FreezeLocations, FreezeTimes, 80, 80);

	if (DennisTexFile1.getSize() == sf::Vector2u(0, 0)) {
		DennisTexFile1.loadFromFile("Resource/Dennis1.png");
	};
	SpecialAttack1Sheet.AssignTextures(DennisTexFile1, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(DennisTexFile1, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);
	SpecialAttack3Sheet.AssignTextures(DennisTexFile1, SpecialAttack3Locations,SpecialAttack3Times, 80, 80);

	if (DennisTexFile2.getSize() == sf::Vector2u(0, 0)) {
		DennisTexFile2.loadFromFile("Resource/Dennis2.png");
	};
	BurningSheet.AssignTextures(DennisTexFile2, BurningLocations, BurningTimes, -80, 80);

	//Setting One Time Animations
	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet[0].OneTime = true;
	Getting_HitSheet[1].OneTime = true;
	SpecialAttack1Sheet.OneTime = true;
	SpecialAttack2Sheet.OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	BurningSheet.OneTime = true;
	SpecialAttack3Sheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(1, { 20,12 }, 40, 26,200);
	HittingSheet[0].AssignHitbox(2, { 17,14 }, 40, 38);
	HittingSheet[1].AssignHitbox(1, { 19,13 }, 46, 52);
	HittingSheet[2].AssignHitbox(2, { 14,14 }, 50, 50,200);
	SpecialAttack3Sheet.AssignHitbox(2, { 20,9 }, 60, 37,-350);
	SpecialAttack3Sheet.AssignHitbox(4, { -14.0f,15.0f }, 41, 38,-350);
	SpecialAttack3Sheet.AssignHitbox(6, { 20,12 }, 60, 32,-350);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Dennis Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Dennis Registered with ID = {0}", CharacterID);
	//Gviving Dennis his 10 Blue Balls :)
	for (int i = 0; i < 10; i++) {
		BallArray.push_back(DennisBlueBall());
	}
	for (int i = 0; i < 10; i++) {
		BallArray[i].AssignParent(this);
		BallArray[i].RegisterGameObject(GO_Projectile);
		BallArray[i].AttackHitBox.RegisterID();
		BallArray[i].AttackHitBox.IgnoreObjectID = ID;
		BallArray[i].ReboundHitBox.RegisterID();
		BallArray[i].ReboundHitBox.IgnoreObjectID = ID;

	}
	for (int i = 0; i < 15; i++) {
		ChaseBallArray.push_back(ChaseBall());
	}
	for (int i = 0; i < 15; i++) {
		ChaseBallArray[i].AssignParent(this);
		ChaseBallArray[i].RegisterGameObject(GO_Projectile);
		ChaseBallArray[i].AttackHitBox.RegisterID();
		ChaseBallArray[i].ReboundHitBox.RegisterID();
	}
	Helicopter_Kick.RegisterGameObject(GO_Null);
	Helicopter_Kick.RegisterHitBox.RegisterID();
	Helicopter_Kick.RegisterHitBox.AssignPlayer(&Helicopter_Kick);
	Helicopter_Kick.ProjectileReboundHitBox.RegisterID();
	Helicopter_Kick.ProjectileReboundHitBox.AssignPlayer(&Helicopter_Kick);
	Helicopter_Kick.AssignParent(this);
}

void Dennis::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.4) * (t - 0.4) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position, RealVector2D(400 * Direction, 0));
				return;
			}
		}
	}
}
void Dennis::SpecialAttack2Calculations(const double dt, const double t) {
	if ((t - dt - 0.4) * (t - 0.4) < 0) {
		for (int i = 0; i < ChaseBallArray.size(); i++) {
			if (!ChaseBallArray[i].IsActive) {
				ChaseBallArray[i].Instantiate(Position,RealVector2D(400*Direction,0));
				ChaseBallArray[i].SetTarget();
				return;
			}
		}
	}
}

void Dennis::SpecialAttack3Calculations(const double dt, const double t){
	if ((Input_Manager.IsKeyPressed(PlayerControl.LeftKey) || Input_Manager.IsKeyPressed(PlayerControl.RightKey)) && t > 0.8) {
		if (CurrentSheet->Time < 1) {
			CurrentSheet->Time = 1.1;
			Stop();
			Position = RealVector2D(Position.get_x(), Z_Position);
		}
		
	}
	if (CurrentSheet->Time > 0.9 && CurrentSheet->Time < 1.0) {
		CurrentSheet->Time = 0.35;
	}
	else if (t - dt <= 0) {
		Velocity = RealVector2D(0, -50);
	}
	else if ((t - dt - 0.3) * (t - 0.3) < 0) {
		Helicopter_Kick.Instantiate(Position);
		Velocity = RealVector2D(250 * Direction, 0);
	}
	Translate(dt);
}

