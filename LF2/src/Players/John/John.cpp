#include "John.h"

sf::Texture JohnTexFile0;
sf::Texture JohnTexFile1;
sf::Texture JohnTexFile2;

const std::vector<RealVector2D> IdleLocations = { {0,5}, {80,5}, {160,5}, {240,5} }; //x,y
const std::vector <double> IdleTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> IdleWPNOffsets = { {4,1}, {4,1}, {4,0}, {4,0} };

const std::vector<RealVector2D> WalkingLocations = { {320,5}, {400,5}, {480,5}, {560,5}, {480,5}, {400,5} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector <RealVector2D> WalkingWPNOffsets = { {10,2}, {6,2}, {4,2}, {3,2}, {4,2}, {6,2 } };

const std::vector<RealVector2D> Attack1Locations = { {0,85}, {80,85} };
const std::vector <double> Attack1Times = { 0.15,0.3 };

const std::vector<RealVector2D> Attack2Locations = { {160,85},{240,85} };
const std::vector <double> Attack2Times = { 0.15,0.3 };

const std::vector<RealVector2D> Attack3Locations = { {560,245},{720,165},{640,245}, {720,245} };
const std::vector <double> Attack3Times = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };
const std::vector <RealVector2D> JumpingWPNOffsets = { {-5,0}, {-23,-22}, {-5,0} };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> RunningWPNOffsets = { {30,-5}, {3,11} , {30,-5}, {19,-17} };

const std::vector<RealVector2D> JumpingAttackLocations = { {320,80},{400,80}, {480,80},{160,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.25,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };
const std::vector <RealVector2D> DashWPNOffsets = { {-7,-20}, {-7,-2} };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,5}, {480,325} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit1WPNOffsets = { {0,0}, {-30,-30} };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,5}, {560,325} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit2WPNOffsets = { {0,0}, {-38,-15} };


const std::vector<RealVector2D> FallingBackLocations = { {75,240},{155,240},{235,240},{390,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {635,271},{495,271},{560,31},{345,271} };
const std::vector <double> SpecialAttack1Times = { 0.3,0.4,0.5,0.6 };
const std::vector <RealVector2D> SpecialAttack1WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack2Locations = { {0,187}, {80,187}, {160,187}, {240,187},{320,187}, {403,187}, {483,187}, {563,187},{643,187}, {720,187} };
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0};
const std::vector <RealVector2D> SpecialAttack2WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack3Locations = { {320,107}, {400,107}, {480,107}, {560,107}, {640,107}, {720,107}};
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };
const std::vector <RealVector2D> SpecialAttack3WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack4Locations = { {0,27}, {80,27}, {160,27}, {240,27}, {320,27}, {400,27} };
const std::vector <double> SpecialAttack4Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };
const std::vector <RealVector2D> SpecialAttack4WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };


const std::vector<RealVector2D> BurningLocations = { {720,80}, {720,480},{390,240} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {640,5}, {720,5} };
const std::vector<double> FreezeTimes = { 0.2,6 };

const std::vector<RealVector2D> WPNAttack1Locations = { {-6,-3}, {80,0}, {160,0}, {240,0} };
const std::vector<double> WPNAttack1Times = { 0.1,0.2,0.3,0.4 };
const std::vector <RealVector2D> WPNAttack1Offsets = { {-25,-7}, {-23,-44}, {22,3}, {27,10} };

const std::vector<RealVector2D> WPNAttack2Locations = { {320,0}, {400,0}, {480,0} };
const std::vector<double> WPNAttack2Times = { 0.1,0.2,0.4 };
const std::vector <RealVector2D> WPNAttack2Offsets = { {-15,-8}, {-9,-25}, {27,6} };

const std::vector<RealVector2D> WPNJumpAttackLocations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector<double> WPNJumpAttackTimes = { 0.1,0.2,0.3,2 };
const std::vector <RealVector2D> WPNJumpAttackOffsets = { {-35,-40}, {-16,-52}, {17,9}, {17,13} };

const std::vector<RealVector2D> WPNThrowLocations = { {320,160}, {400,160}, {480,160} };
const std::vector<double> WPNThrowTimes = { 0.1,0.2,0.5 };
const std::vector <RealVector2D> WPNThrowOffsets = { {-45,-14}, {0,-44}, {22,3} };

const std::vector<RealVector2D> WeaponPickLocations = { {480,240} };
const std::vector<double> WeaponPickTimes = { 0.2 };
const std::vector <RealVector2D> WPNPickOffsets = { {26,25} };

const std::vector<RealVector2D> GuardLocations = { {480,405} };
const std::vector<double> GuardTimes = { 0.8 };
const std::vector<RealVector2D> WPNGuardOffsets = { {10,-10} };

John::John() {
	Name = "John";
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
	SpecialAttack4Sheet.AssignPlayer(this);
	FallingBackSheet.AssignPlayer(this);
	FallingFrontSheet.AssignPlayer(this);
	BurningSheet.AssignPlayer(this);
	FreezedSheet.AssignPlayer(this);
	WPNAttackSheet[0].AssignPlayer(this);
	WPNAttackSheet[1].AssignPlayer(this);
	WPNJumpAttackSheet.AssignPlayer(this);
	WPNThrowSheet.AssignPlayer(this);
	WeaponPickSheet.AssignPlayer(this);
	GuardSheet.AssignPlayer(this);

	//Sprite and Texture Loadindg{
	if (JohnTexFile0.getSize() == sf::Vector2u(0, 0)) {
		JohnTexFile0.loadFromFile("Resource/John.png");
	}
	IdleSheet.AssignTextures(JohnTexFile0, IdleLocations, IdleTimes, 70, 80);
	WalkingSheet.AssignTextures(JohnTexFile0, WalkingLocations, WalkingTimes, 70, 80);
	HittingSheet[0].AssignTextures(JohnTexFile0, Attack1Locations, Attack1Times, 70, 80);
	HittingSheet[1].AssignTextures(JohnTexFile0, Attack2Locations, Attack2Times, 70, 80);
	HittingSheet[2].AssignTextures(JohnTexFile0, Attack3Locations, Attack3Times, 70, 80);
	JumpingSheet.AssignTextures(JohnTexFile0, JumpingLocations, JumpingTimes, 70, 80);
	RunningSheet.AssignTextures(JohnTexFile0, RunningLocations, RunningTimes, 70, 80);
	JumpingAttackSheet.AssignTextures(JohnTexFile0, JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	DashSheet.AssignTextures(JohnTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet[0].AssignTextures(JohnTexFile0, Getting_HitLocations1, Getting_HitTimes1, 80, 80);
	Getting_HitSheet[1].AssignTextures(JohnTexFile0, Getting_HitLocations2, Getting_HitTimes2, 80, 80);
	FallingBackSheet.AssignTextures(JohnTexFile0, FallingBackLocations, FallingBackTimes, -75, 80);
	FallingFrontSheet.AssignTextures(JohnTexFile0, FallingFrontLocations, FallingFrontTimes, 75, 80);
	BurningSheet.AssignTextures(JohnTexFile0, BurningLocations, BurningTimes, -75, 80);
	FreezedSheet.AssignTextures(JohnTexFile0, FreezeLocations, FreezeTimes, 80, 80);
	WeaponPickSheet.AssignTextures(JohnTexFile0, WeaponPickLocations, WeaponPickTimes, 80, 80);
	GuardSheet.AssignTextures(JohnTexFile0, GuardLocations, GuardTimes, 80, 80);

	IdleSheet.AssignWPNOffsets(IdleWPNOffsets);
	WalkingSheet.AssignWPNOffsets(WalkingWPNOffsets);
	JumpingSheet.AssignWPNOffsets(JumpingWPNOffsets);
	RunningSheet.AssignWPNOffsets(RunningWPNOffsets);
	DashSheet.AssignWPNOffsets(DashWPNOffsets);
	WPNAttackSheet[0].AssignWPNOffsets(WPNAttack1Offsets);
	WPNAttackSheet[1].AssignWPNOffsets(WPNAttack2Offsets);
	WPNJumpAttackSheet.AssignWPNOffsets(WPNJumpAttackOffsets);
	WPNThrowSheet.AssignWPNOffsets(WPNThrowOffsets);
	Getting_HitSheet[0].AssignWPNOffsets(Get_Hit1WPNOffsets);
	Getting_HitSheet[1].AssignWPNOffsets(Get_Hit2WPNOffsets);
	SpecialAttack1Sheet.AssignWPNOffsets(SpecialAttack1WPNOffsets);
	SpecialAttack2Sheet.AssignWPNOffsets(SpecialAttack2WPNOffsets);
	SpecialAttack3Sheet.AssignWPNOffsets(SpecialAttack3WPNOffsets);
	WeaponPickSheet.AssignWPNOffsets(WPNPickOffsets);
	//SpecialAttack4Sheet.AssignWPNOffsets(SpecialAttack4WPNOffsets);
	GuardSheet.AssignWPNOffsets(WPNGuardOffsets);

	if (JohnTexFile1.getSize() == sf::Vector2u(0, 0)) {
		JohnTexFile1.loadFromFile("Resource/John1.png");
	};

	WPNAttackSheet[0].AssignTextures(JohnTexFile1, WPNAttack1Locations, WPNAttack1Times, 80, 80);
	WPNAttackSheet[1].AssignTextures(JohnTexFile1, WPNAttack2Locations, WPNAttack2Times, 80, 80);
	WPNJumpAttackSheet.AssignTextures(JohnTexFile1, WPNJumpAttackLocations, WPNJumpAttackTimes, 80, 80);
	WPNThrowSheet.AssignTextures(JohnTexFile1, WPNThrowLocations, WPNThrowTimes, 80, 80);

	if (JohnTexFile2.getSize() == sf::Vector2u(0, 0)) {
		JohnTexFile2.loadFromFile("Resource/John2.png");
	}
	SpecialAttack1Sheet.AssignTextures(JohnTexFile2, SpecialAttack1Locations, SpecialAttack1Times, 130, 80);
	SpecialAttack2Sheet.AssignTextures(JohnTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);
	SpecialAttack3Sheet.AssignTextures(JohnTexFile2, SpecialAttack3Locations, SpecialAttack3Times, 80, 80);
	SpecialAttack4Sheet.AssignTextures(JohnTexFile2, SpecialAttack4Locations, SpecialAttack4Times, 80, 80);

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
	SpecialAttack3Sheet.OneTime = true;
	SpecialAttack4Sheet.OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	BurningSheet.OneTime = true;
	WPNAttackSheet[0].OneTime = true;
	WPNAttackSheet[1].OneTime = true;
	WPNThrowSheet.OneTime = true;
	WeaponPickSheet.OneTime = true;
	GuardSheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(1, { 11,11 }, 41, 32, 200,200,45);
	HittingSheet[0].AssignHitbox(1, { 10,19 }, 56, 41,-10,300,20);
	HittingSheet[1].AssignHitbox(1, { 9,18 }, 50, 45,-10,300,20);
	HittingSheet[2].AssignHitbox(2, { 16,6 }, 46, 65, 200,50);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject John Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character John Registered with ID = {0}", CharacterID);

	for (int i = 0; i < 10; i++) {
		BallArray.push_back(JohnBlueBall());
	}
	for (int i = 0; i < 10; i++) {
		BallArray[i].AssignParent(this);
		BallArray[i].RegisterGameObject(GO_Projectile);
		BallArray[i].AttackHitBox.RegisterID();
		BallArray[i].ReboundHitBox.RegisterID();
	}
	for (int i = 0; i < 10; i++) {
		ShieldArray.push_back(JohnShield());
	}
	for (int i = 0; i < 10; i++) {
		ShieldArray[i].AssignParent(this);
		ShieldArray[i].RegisterGameObject(GO_Null);
		ShieldArray[i].AttackHitBox.AssignPlayer(&ShieldArray[i]);
		ShieldArray[i].AttackHitBox.RegisterID();
	}
	for (int i = 0; i < 10; i++) {
		DiskArray.push_back(DestructoDisk());
	}
	for (int i = 0; i < 10; i++) {
		DiskArray[i].AssignParent(this);
		DiskArray[i].RegisterGameObject(GO_Projectile);
		DiskArray[i].AttackHitBox.RegisterID();
		DiskArray[i].ReboundHitBox.RegisterID();
	}
	for (int i = 0; i < 10; i++) {
		SparkleArray.push_back(Sparkle());
	}
	for (int i = 0; i < 5; i++) {
		SparkleArray[i].AssignParent(this);
		SparkleArray[i].RegisterGameObject(GO_Projectile);
	}
	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
	WeaponHolderType = 1;
	SpecialAttackMP[0] = 15;
	SpecialAttackMP[1] = 50;
	SpecialAttackMP[2] = 20;
	SpecialAttackMP[3] = 0;
}

void John::SpecialAttack1Calculations(const double dt, const double t){
	if (t > 0.45 && t < 0.5) {
		Velocity = RealVector2D(200 * Direction, 0);
		Translate(-dt);
	}
	if ((t - dt - 0.4) * (t - 0.4) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position + RealVector2D(Direction*30,0),RealVector2D(400 * Direction, 0));
				return;
			}
		}
	}
}

void John::SpecialAttack2Calculations(const double dt, const double t){
	if ((t - dt - 0.97) * (t - 0.97) <= 0) {
		Position = Position + RealVector2D(-Direction * 20, 0);
		State_Manager.ForceStateChange(IDLE);
	}
	else if ((t - dt - 0.5) * (t - 0.5) <= 0) {
		for (int i = 0; i < ShieldArray.size(); i++) {
			if (!ShieldArray[i].IsActive) {
				ShieldArray[i].Instantiate(Position + RealVector2D(Direction * 30, 0));
				return;
			}
		}
	}
}

void John::SpecialAttack3Calculations(const double dt, const double t){
	if ((t - dt - 0.3) * (t - 0.3) < 0) {
		for (int i = 0; i < DiskArray.size(); i++) {
			if (!DiskArray[i].IsActive) {
				DiskArray[i].Instantiate(Position + RealVector2D(0, -40), RealVector2D(500 * Direction, 0));
				DiskArray[i].SetTarget();
				return;
			}
		}
	}
}

void John::SpecialAttack4Calculations(const double dt, const double t){
	if ((t - dt - 0.55) * (t - 0.55) < 0) {
		HealthPoints = std::min(600, HealthPoints + 200);
	}
	if ((t - dt) * t <= 0) {
		for (int i = 0; i < SparkleArray.size(); i++) {
			if (!SparkleArray[i].IsActive) {
				SparkleArray[i].Instantiate(Position);
				return;
			}
		}
	}
}
