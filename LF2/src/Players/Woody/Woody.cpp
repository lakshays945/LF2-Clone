#include "Woody.h"

sf::Texture WoodyTexFile0;
sf::Texture WoodyTexFile1;
sf::Texture WoodyTexFile2;

const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const std::vector <double> IdleTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> IdleWPNOffsets = { {4,2}, {4,2}, {4,1}, {4,1} };

const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector <RealVector2D> WalkingWPNOffsets = { {2,2}, {5,2}, {10,2}, {13,2}, {10,2}, {5,2 } };


const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80},{160,80},{240,80} };
const std::vector <double> Attack1Times = { 0.1,0.2,0.25,0.3 };

const std::vector<RealVector2D> Attack2Locations = { {320,80},{400,80},{480,80},{560,80} };
const std::vector <double> Attack2Times = { 0.1,0.2,0.25,0.3 };

const std::vector<RealVector2D> Attack3Locations = { {640,0}, {720,0}, {720,80}, {720,160},{720,240},{720,320} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };
const std::vector <RealVector2D> JumpingWPNOffsets = { {8,-3}, {-20,-23}, {8,-3} };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> RunningWPNOffsets = { {3,-17}, {-1,-17} , {3,-17}, {-3,-12} };

const std::vector<RealVector2D> JumpingAttackLocations = { {560,240},{640,240}, {640,80},{640,480},{160,480} };
const std::vector <double> JumpingAttackTimes = { 0.15,0.3,0.5,0.6,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME};
const std::vector <RealVector2D> DashWPNOffsets = { {-7,-25}, {3,2} };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit1WPNOffsets = { {0,0}, {0,0} };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,0}, {560,320} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit2WPNOffsets = { {4,-27}, {-16,-15} };


const std::vector<RealVector2D> FallingBackLocations = { {75,240},{155,240},{235,240},{395,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {0,15}, {80,15}, {160,15}, {240,15}, {320,15}, {400,15}, {480,15}, {560,15}, {640,15}, {720,15} };
const std::vector <double> SpecialAttack1Times = { 0.07,0.14,0.21,0.28,0.35,0.42,0.49,0.56,0.63,0.7 };
const std::vector <RealVector2D> SpecialAttack1WPNOffsets = { {-15,10}, {-15,10}, {-15,10}, {-15,10}, {-15,10},{-15,10}, {-15,10}, {-15,10}, {-15,10}, {-15,10} };

const std::vector<RealVector2D> SpecialAttack2Locations = { {160,100}, {240,100}, {320,100}, {400,100}, {480,100}, {560,100}, {640,85} };
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.5,0.65,0.9 };
const std::vector <RealVector2D> SpecialAttack2WPNOffsets = { {-8,-7}, {-8,-6}, {-8,-8}, {-8,-4}, {-8,-2}, {-8,-1}, {-8,0} };

const std::vector<RealVector2D> SpecialAttack3Locations = { {0,175}, {80,175}, {160,175}, {240,175}, {320,175}, {400,175}, {480,175}, {560,175},{640,175}, {720,175}, {0,255} };
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1};
const std::vector <RealVector2D> SpecialAttack3WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack4Locations = { {80,255}, {160,255}, {240,255}, {320,255}, {400,255}, {480,255}, {560,255},{640,255}, {720,255}, {720,255} };
const std::vector <double> SpecialAttack4Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0 };
const std::vector <RealVector2D> SpecialAttack4WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> BurningLocations = { {720,80}, {800,80},{473,320} }; //x,y //LOADED REVERSED
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {640,0}, {720,0} };
const std::vector<double> FreezeTimes = { 0.2,6 };

const std::vector<RealVector2D> WPNAttack1Locations = { {0,0}, {80,0}, {160,0}, {240,0} };
const std::vector<double> WPNAttack1Times = { 0.1,0.2,0.3,0.4 };
const std::vector <RealVector2D> WPNAttack1Offsets = { {-36,-7}, {-27,-25}, {30,8}, {30,12} };

const std::vector<RealVector2D> WPNAttack2Locations = { {320,0}, {400,0}, {480,0} };
const std::vector<double> WPNAttack2Times = { 0.1,0.2,0.4 };
const std::vector <RealVector2D> WPNAttack2Offsets = { {-15,-8}, {-9,-25}, {30,6} };

const std::vector<RealVector2D> WPNJumpAttackLocations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector<double> WPNJumpAttackTimes = { 0.1,0.2,0.3,2 };
const std::vector <RealVector2D> WPNJumpAttackOffsets = { {-38,-10}, {-31,-27}, {27,9}, {27,13} };

const std::vector<RealVector2D> WPNThrowLocations = { {320,160}, {400,160}, {480,160} };
const std::vector<double> WPNThrowTimes = { 0.1,0.2,0.5 };
const std::vector <RealVector2D> WPNThrowOffsets = { {-36,-7}, {-27,-25}, {30,8}};

const std::vector<RealVector2D> WeaponPickLocations = { {480,240} };
const std::vector<double> WeaponPickTimes = { 0.2 };
const std::vector <RealVector2D> WPNPickOffsets = { {26,21} };

const std::vector<RealVector2D> GuardLocations = { {480,400} };
const std::vector<double> GuardTimes = { 0.8 };
const std::vector<RealVector2D> WPNGuardOffsets = { {26,-13} };

Woody::Woody() {
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
	if (WoodyTexFile0.getSize() == sf::Vector2u(0, 0)) {
		WoodyTexFile0.loadFromFile("Resource/Woody.png");
	}
	IdleSheet.AssignTextures(WoodyTexFile0, IdleLocations, IdleTimes, 70, 80);
	WalkingSheet.AssignTextures(WoodyTexFile0, WalkingLocations, WalkingTimes, 70, 80);
	HittingSheet[0].AssignTextures(WoodyTexFile0, Attack1Locations, Attack1Times, 80, 80);
	HittingSheet[1].AssignTextures(WoodyTexFile0, Attack2Locations, Attack2Times, 80, 80);
	HittingSheet[2].AssignTextures(WoodyTexFile0, Attack3Locations, Attack3Times, 80, 80);
	JumpingSheet.AssignTextures(WoodyTexFile0, JumpingLocations, JumpingTimes, 70, 80);
	RunningSheet.AssignTextures(WoodyTexFile0, RunningLocations, RunningTimes, 70, 80);
	JumpingAttackSheet.AssignTextures(WoodyTexFile0, JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	DashSheet.AssignTextures(WoodyTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet[0].AssignTextures(WoodyTexFile0, Getting_HitLocations1, Getting_HitTimes1, 80, 80);
	Getting_HitSheet[1].AssignTextures(WoodyTexFile0, Getting_HitLocations2, Getting_HitTimes2, 80, 80);
	FallingBackSheet.AssignTextures(WoodyTexFile0, FallingBackLocations, FallingBackTimes, -80, 80);
	FallingFrontSheet.AssignTextures(WoodyTexFile0, FallingFrontLocations, FallingFrontTimes, 80, 80);
	WeaponPickSheet.AssignTextures(WoodyTexFile0, WeaponPickLocations, WeaponPickTimes, 80, 80);
	GuardSheet.AssignTextures(WoodyTexFile0, GuardLocations, GuardTimes, 80, 80);


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
	SpecialAttack4Sheet.AssignWPNOffsets(SpecialAttack4WPNOffsets);
	WeaponPickSheet.AssignWPNOffsets(WPNPickOffsets);
	GuardSheet.AssignWPNOffsets(WPNGuardOffsets);

	if (WoodyTexFile1.getSize() == sf::Vector2u(0, 0)) {
		WoodyTexFile1.loadFromFile("Resource/Woody1.png");
	};
	BurningSheet.AssignTextures(WoodyTexFile1, BurningLocations, BurningTimes, -75, 80);
	FreezedSheet.AssignTextures(WoodyTexFile1, FreezeLocations, FreezeTimes, 80, 80);
	WPNAttackSheet[0].AssignTextures(WoodyTexFile1, WPNAttack1Locations, WPNAttack1Times, 80, 80);
	WPNAttackSheet[1].AssignTextures(WoodyTexFile1, WPNAttack2Locations, WPNAttack2Times, 80, 80);
	WPNJumpAttackSheet.AssignTextures(WoodyTexFile1, WPNJumpAttackLocations, WPNJumpAttackTimes, 80, 80);
	WPNThrowSheet.AssignTextures(WoodyTexFile1, WPNThrowLocations, WPNThrowTimes, 80, 80);

	if (WoodyTexFile2.getSize() == sf::Vector2u(0, 0)) {
		WoodyTexFile2.loadFromFile("Resource/Woody2.png");
	};
	SpecialAttack1Sheet.AssignTextures(WoodyTexFile2, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(WoodyTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);
	SpecialAttack3Sheet.AssignTextures(WoodyTexFile2, SpecialAttack3Locations, SpecialAttack3Times, 80, 80);
	SpecialAttack4Sheet.AssignTextures(WoodyTexFile2, SpecialAttack4Locations, SpecialAttack4Times, 80, 80);

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
	JumpingAttackSheet.AssignHitbox(1, { 8,15 }, 40, 31, 200,300,70);
	HittingSheet[0].AssignHitbox(1, { 14,9 }, 36, 55,-10,300,20);
	HittingSheet[1].AssignHitbox(1, { 17,9 }, 37, 53,20);
	HittingSheet[2].AssignHitbox(1, { 9,5 }, 40, 65, 150, 350,70);
	SpecialAttack2Sheet.AssignHitbox(3, { 8,5 }, 40, 70, 750, 250,80);
	SpecialAttack2Sheet.AssignHitbox(4, { 8,5 }, 40, 70, 650, 250,80);
	SpecialAttack2Sheet.AssignHitbox(5, { 8,5 }, 40, 70, 550, 250,80);
	SpecialAttack2Sheet.AssignHitbox(6, { 8,5 }, 40, 70, 500, 250,80);
	SpecialAttack3Sheet.AssignHitbox(2, { 0,6 }, 63, 65,-300,25);
	SpecialAttack3Sheet.AssignHitbox(5, { 0,6 }, 63, 65,-300,25);
	SpecialAttack3Sheet.AssignHitbox(8, { 0,6 }, 63, 65,100,300,25);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Firen Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Firen Registered with ID = {0}", CharacterID);
	WeaponHolderType = 2;

	for (int i = 0; i < 10; i++) {
		BallArray.push_back(WoodyBall());
	}
	for (int i = 0; i < 10; i++) {
		BallArray[i].AssignParent(this);
		BallArray[i].RegisterGameObject(GO_Projectile);
		BallArray[i].AttackHitBox.RegisterID();
		BallArray[i].ReboundHitBox.RegisterID();
	}
	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
	SpecialAttackMP[0] = 25;
	SpecialAttackMP[1] = 40;
	SpecialAttackMP[2] = 10;
	SpecialAttackMP[3] = 10;
}

void Woody::SpecialAttack1Calculations(const double dt, const double t){
	if ((t - dt - 0.56) * (t - 0.56) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position + RealVector2D(Direction * 30, 0), RealVector2D(400 * Direction, -50));
				return;
			}
		}
	}
	else if ((t - dt - 0.35) * (t - 0.35) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position + RealVector2D(Direction * 30, 0), RealVector2D(400 * Direction, 50));
				return;
			}
		}
	}
}

void Woody::SpecialAttack2Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		Stop();
		Z_Velocity = 0;
	}
	if ((t - dt - 0.3) * (t - 0.3) <= 0) {
		Velocity = RealVector2D(Direction * 600, -600);
	}
	if (Z_Position > Position.get_y() && t > 0.3) {
		Velocity = Velocity + RealVector2D(0, 2550)*dt;
	}
	if(t > 0.8) {
		DEBUG_INFO("Resetted");
		Position = RealVector2D(Position.get_x(), Z_Position);
		Stop();
		State_Manager.ForceStateChange(IDLE);
		return;
	}
	Translate(dt);
}

void Woody::SpecialAttack3Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		Velocity = RealVector2D(Direction * 200, 0);
	}
	Translate(dt);
}

void Woody::SpecialAttack4Calculations(const double dt, const double t){
	if ((t - dt - 0.4) * (t - 0.4) <= 0) {
		Stop();
		double minDist = 10000;
		RealVector2D minPos = Position;
		for (int i = 0; i < CharacterIDArray.size(); i++) {
			if (i == CharacterID) {
				continue;
			}
			if (minDist > Position.DistanceFrom(RealVector2D(CharacterIDArray[i]->Position.get_x(),CharacterIDArray[i]->Z_Position))) {
				minDist = Position.DistanceFrom(RealVector2D(CharacterIDArray[i]->Position.get_x(), CharacterIDArray[i]->Z_Position));
				minPos = CharacterIDArray[i]->Position;
			}
		}
		if (Direction > 0) {
			minPos = minPos + RealVector2D(-100, 0);
		}
		else {
			minPos = minPos + RealVector2D(100, 0);
		}
		TargetPosition = minPos;
		Position = TargetPosition;
		Z_Position = Position.get_y();
	}
}
