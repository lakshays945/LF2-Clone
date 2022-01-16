#include "Freeze.h"

sf::Texture FreezeTexFile0;
sf::Texture FreezeTexFile1;
sf::Texture FreezeTexFile2;

const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const std::vector <double> IdleTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };

const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80} };
const std::vector <double> Attack1Times = { 0.1,0.2 };

const std::vector<RealVector2D> Attack2Locations = { {160,80},{240,80} };
const std::vector <double> Attack2Times = { 0.1,0.2 };

const std::vector<RealVector2D> Attack3Locations = { {320,80},{400,80},{480,80}, {560,80}, {640,80}, {720,80}, {720,160},{720,240} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> JumpingAttackLocations = { {320,80},{400,80}, {480,80},{160,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.25,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,0}, {560,320} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };


const std::vector<RealVector2D> FallingBackLocations = { {75,240},{155,240},{235,240},{315,240},{390,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.3,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {45,12},{125,12},{205,12},{285,12},{365,12},{445,12} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };

const std::vector<RealVector2D> SpecialAttack2Locations = { {640,0},{720,0},{560,80},{640,80},{720,80}};
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.7 };

const std::vector<RealVector2D> BurningLocations = { {635,240}, {635,480}, {315,240},{390,240} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,0.7,2 };

const std::vector<RealVector2D> FreezeLocations = { {640,0}, {720,0} };
const std::vector<double> FreezeTimes = { 0.2,4.5 };

Freeze::Freeze() {
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
	FallingBackSheet.AssignPlayer(this);
	FallingFrontSheet.AssignPlayer(this);
	BurningSheet.AssignPlayer(this);
	FreezedSheet.AssignPlayer(this);

	//Sprite and Texture Loadindg{
	if (FreezeTexFile0.getSize() == sf::Vector2u(0, 0)) {
		FreezeTexFile0.loadFromFile("Resource/Freeze.png");
	}
	IdleSheet.AssignTextures(FreezeTexFile0, IdleLocations, IdleTimes, 70, 80);
	WalkingSheet.AssignTextures(FreezeTexFile0, WalkingLocations, WalkingTimes, 70, 80);
	HittingSheet[0].AssignTextures(FreezeTexFile0, Attack1Locations, Attack1Times, 70, 80);
	HittingSheet[1].AssignTextures(FreezeTexFile0, Attack2Locations, Attack2Times, 70, 80);
	HittingSheet[2].AssignTextures(FreezeTexFile0, Attack3Locations, Attack3Times, 70, 80);
	JumpingSheet.AssignTextures(FreezeTexFile0, JumpingLocations, JumpingTimes, 70, 80);
	RunningSheet.AssignTextures(FreezeTexFile0, RunningLocations, RunningTimes, 70, 80);
	JumpingAttackSheet.AssignTextures(FreezeTexFile0, JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	DashSheet.AssignTextures(FreezeTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet[0].AssignTextures(FreezeTexFile0, Getting_HitLocations1, Getting_HitTimes1, 80, 80);
	Getting_HitSheet[1].AssignTextures(FreezeTexFile0, Getting_HitLocations2, Getting_HitTimes2, 80, 80);
	FallingBackSheet.AssignTextures(FreezeTexFile0, FallingBackLocations, FallingBackTimes, -75, 80);
	FallingFrontSheet.AssignTextures(FreezeTexFile0, FallingFrontLocations, FallingFrontTimes, 75, 80);
	BurningSheet.AssignTextures(FreezeTexFile0, BurningLocations, BurningTimes, -75, 80);
	FreezedSheet.AssignTextures(FreezeTexFile0, FreezeLocations, FreezeTimes, 80, 80);

	if (FreezeTexFile1.getSize() == sf::Vector2u(0, 0)) {
		FreezeTexFile1.loadFromFile("Resource/Freeze1.png");
	};
	SpecialAttack1Sheet.AssignTextures(FreezeTexFile1, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);

	if (FreezeTexFile2.getSize() == sf::Vector2u(0, 0)) {
		FreezeTexFile2.loadFromFile("Resource/Freeze2.png");
	}
	SpecialAttack2Sheet.AssignTextures(FreezeTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);

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

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(2, { 8,15 }, 40, 31, 200);
	HittingSheet[0].AssignHitbox(1, { 24,17 }, 22, 45);
	HittingSheet[1].AssignHitbox(1, { 11,19 }, 32, 42);
	HittingSheet[2].AssignHitbox(1, { 10,3 }, 36, 46);
	HittingSheet[2].AssignHitbox(5, { 10,16 }, 42, 54, 200);

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
	DEBUG_SUCCESS("GameObject Freeze Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Freeze Registered with ID = {0}", CharacterID);

	for (int i = 0; i < 10; i++) {
		BallArray.push_back(FreezeBall());
	}
	for (int i = 0; i < 10; i++) {
		BallArray[i].AssignParent(this);
		BallArray[i].RegisterGameObject(GO_Projectile);
		BallArray[i].AttackHitBox.RegisterID();
		BallArray[i].AttackHitBox.IgnoreObjectID = ID;
		BallArray[i].ReboundHitBox.RegisterID();
		BallArray[i].ReboundHitBox.IgnoreObjectID = ID;

	}

	for (int i = 0; i < 10; i++) {
		WallArray.push_back(IceBergWall());
	}

	for (int i = 0; i < 10; i++) {
		WallArray[i].AssignParent(this);
		WallArray[i].RegisterGameObject(GO_Null);
		WallArray[i].WallHitBox.RegisterID();
		WallArray[i].WallHitBox.AssignPlayer(&WallArray[i]);
		WallArray[i].AttackHitBox.RegisterID();
		WallArray[i].AttackHitBox.AssignPlayer(&WallArray[i]);
	}

	for (int i = 0; i < 10; i++) {
		BergArray1.push_back(IceBerg());
		BergArray2.push_back(IceBerg());
		BergArray3.push_back(IceBerg());
	}
	for (int i = 0; i < 10; i++) {
		BergArray1[i].SetIceTextures(1);
		BergArray1[i].AssignParent(this);
		BergArray1[i].AssignWall(&WallArray[i]);
		BergArray1[i].RegisterGameObject(GO_Null);

		BergArray2[i].SetIceTextures(2);
		BergArray2[i].AssignParent(this);
		BergArray2[i].AssignWall(&WallArray[i]);
		BergArray2[i].RegisterGameObject(GO_Null);
		
		BergArray3[i].SetIceTextures(3);
		BergArray3[i].AssignParent(this);
		BergArray3[i].AssignWall(&WallArray[i]);
		BergArray3[i].RegisterGameObject(GO_Null);
	}

}

void Freeze::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.3) * (t - 0.3) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate({ (float)400 * Direction,0 });
				return;
			}
		}
	}
}
void Freeze::SpecialAttack2Calculations(const double dt, const double t) {
	if ((t - dt - 0.4) * (t - 0.4) <= 0) {
		for (int i = 0; i < BergArray1.size(); i++) {
			if (!BergArray3[i].IsActive && !WallArray[i].IsSetActive) {
				IceBergIndex = i;
				BergArray3[IceBergIndex].Instantiate(Position + RealVector2D(Direction * 60, -20));
				return;
			}
		}
	}
	else if ((t - dt - 0.55) * (t - 0.55) <= 0) {
		BergArray2[IceBergIndex].Instantiate(Position + RealVector2D(Direction * 100, -20));
	}
	else if ((t - dt - 0.69) * (t - 0.69) <= 0) {
		BergArray1[IceBergIndex].Instantiate(Position + RealVector2D(Direction * 160, -20));
	}
}

void Freeze::SpecialAttack3Calculations(const double dt, const double t)
{
}
