#include "Davis.h"

sf::Texture DavisTexFile0;
sf::Texture DavisTexFile1;
sf::Texture DavisTexFile2;

const std::vector <double> IdleTimes = { 0.15,0.3,0.45,0.6 };
const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y 0.5,1,1.5,2.0,2.5,3
const std::vector <RealVector2D> IdleWPNOffsets = { {0,0}, {0,0}, {0,-1}, {0,-1} };

const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <RealVector2D> WalkingWPNOffsets = { {-1,-7}, {1,-6}, {2,-6}, {3,-12}, {2,-6}, {1,-6 } };

const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector <double> Attack1Times = { 0.07,0.14,0.21,0.28};

const std::vector<RealVector2D> Attack2Locations = { {320,80},{400,80},{480,80},{560,80} };
const std::vector <double> Attack2Times = { 0.07,0.14,0.21,0.28 };

const std::vector<RealVector2D> Attack3Locations = { {560,480}, {640,480}, {640,0}, {720,0},{720,80},{720,160},{720,240},{720,320} };
const std::vector <double> Attack3Times = { 0.07,0.14,0.21,0.28,0.35,0.42,0.49,0.56 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };
const std::vector <RealVector2D> JumpingWPNOffsets = { {10,-5}, {-15,-22}, {10,-5} };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> RunningWPNOffsets = { {12,-9}, {10,-11}, {12,-9}, {-3,11} };

const std::vector<RealVector2D> JumpingAttackLocations = { {160,480},{240,480}, { 320,480}, {400,480}, {560,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.2,0.3,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };
const std::vector <RealVector2D> DashWPNOffsets = { {0,-27}, {10,-2} };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit1WPNOffsets = { {0,0}, {0,-10} };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,0}, {560,320} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit2WPNOffsets = { {0,0}, {-23,-5} };

const std::vector<RealVector2D> FallingBackLocations = { {80,240},{160,240},{240,240},{400,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {0,15}, {80,15}, {160,15}, {240,15}, {320,15} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.6 };
const std::vector <RealVector2D> SpecialAttack1WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack2Locations = { {0,248}, {80,248}, {160,248}, {240,248}, {320,248}, {400,248}, {480,248}, {560,248} };
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.85 };
const std::vector <RealVector2D> SpecialAttack2WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack3Locations = { {240,88}, {320,88}, {400,88}, {480,88}, {560,88}, {640,88}, {720,88},{720,168}, {560,168}, {480,168}, {400,168}, {320,168} };
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2 };
const std::vector <RealVector2D> SpecialAttack3WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack4Locations = { {0,168}, {80,168}, {160,168}, {240,168} };
const std::vector <double> SpecialAttack4Times = { 0.1,2.5,2.6,3.2 };
const std::vector <RealVector2D> SpecialAttack4WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> BurningLocations = { {720,0}, {720,80}, {720,480} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {560,240}, {640,240} };
const std::vector<double> FreezeTimes = { 0.2,6 };

const std::vector<RealVector2D> WPNAttack1Locations = { {0,0}, {80,0}, {160,0}, {240,0} };
const std::vector<double> WPNAttack1Times = { 0.1,0.2,0.3,0.4 };
const std::vector <RealVector2D> WPNAttack1Offsets = { {-40,-12}, {-32,-29}, {27,6}, {27,10} };

const std::vector<RealVector2D> WPNAttack2Locations = { {320,0}, {400,0}, {480,0} };
const std::vector<double> WPNAttack2Times = { 0.1,0.2,0.4 };
const std::vector <RealVector2D> WPNAttack2Offsets = { {-15,-8}, {-9,-25}, {30,6} };

const std::vector<RealVector2D> WPNJumpAttackLocations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector<double> WPNJumpAttackTimes = { 0.1,0.2,0.3,2 };
const std::vector <RealVector2D> WPNJumpAttackOffsets = { {-40,-15}, {-36,-32}, {27,5}, {27,8} };

const std::vector<RealVector2D> WPNThrowLocations = { {320,160}, {400,160}, {480,160} };
const std::vector<double> WPNThrowTimes = { 0.1,0.2,0.5 };
const std::vector <RealVector2D> WPNThrowOffsets = { {-40,-12}, {-32,-29}, {27,9} };

const std::vector<RealVector2D> WeaponPickLocations = { {480,240} };
const std::vector<double> WeaponPickTimes = { 0.2 };
const std::vector <RealVector2D> WPNPickOffsets = { {26,25} };

const std::vector<RealVector2D> GuardLocations = { {480,400} };
const std::vector<double> GuardTimes = {0.8};
const std::vector<RealVector2D> WPNGuardOffsets = { {15,-11} };

Davis::Davis() {
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
	FallingBackSheet.AssignPlayer(this);
	FallingFrontSheet.AssignPlayer(this);
	SpecialAttack1Sheet.AssignPlayer(this);
	SpecialAttack2Sheet.AssignPlayer(this);
	SpecialAttack3Sheet.AssignPlayer(this);
	SpecialAttack4Sheet.AssignPlayer(this);
	BurningSheet.AssignPlayer(this);
	FreezedSheet.AssignPlayer(this);
	WPNAttackSheet[0].AssignPlayer(this);
	WPNAttackSheet[1].AssignPlayer(this);
	WPNJumpAttackSheet.AssignPlayer(this);
	WPNThrowSheet.AssignPlayer(this);
	WeaponPickSheet.AssignPlayer(this);
	GuardSheet.AssignPlayer(this);

	//Sprite and Texture Loadindg
	if (DavisTexFile0.getSize() == sf::Vector2u(0, 0)) {
		DavisTexFile0.loadFromFile("Resource/Davis.png");
	}
	IdleSheet.AssignTextures(DavisTexFile0, IdleLocations, IdleTimes,80,80);
	WalkingSheet.AssignTextures(DavisTexFile0, WalkingLocations, WalkingTimes, 80, 80);
	HittingSheet[0].AssignTextures(DavisTexFile0, Attack1Locations, Attack1Times, 80, 80);
	HittingSheet[1].AssignTextures(DavisTexFile0, Attack2Locations, Attack2Times, 80, 80);
	HittingSheet[2].AssignTextures(DavisTexFile0, Attack3Locations, Attack3Times, 80, 80);
	JumpingSheet.AssignTextures(DavisTexFile0, JumpingLocations, JumpingTimes, 80, 80);
	RunningSheet.AssignTextures(DavisTexFile0, RunningLocations, RunningTimes, 80, 80);
	DashSheet.AssignTextures(DavisTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet[0].AssignTextures(DavisTexFile0, Getting_HitLocations1, Getting_HitTimes1, 80, 80);
	Getting_HitSheet[1].AssignTextures(DavisTexFile0, Getting_HitLocations2, Getting_HitTimes2, 80, 80);
	FallingBackSheet.AssignTextures(DavisTexFile0, FallingBackLocations, FallingBackTimes, -80, 80);
	FallingFrontSheet.AssignTextures(DavisTexFile0, FallingFrontLocations, FallingFrontTimes, 80, 80);
	FreezedSheet.AssignTextures(DavisTexFile0, FreezeLocations, FreezeTimes, 80, 80);
	WeaponPickSheet.AssignTextures(DavisTexFile0, WeaponPickLocations, WeaponPickTimes, 80, 80);
	GuardSheet.AssignTextures(DavisTexFile0, GuardLocations, GuardTimes, 80, 80);

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

	if (DavisTexFile1.getSize() == sf::Vector2u(0, 0)) {
		DavisTexFile1.loadFromFile("Resource/Davis1.png");
	}
	JumpingAttackSheet.AssignTextures(DavisTexFile1, JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	BurningSheet.AssignTextures(DavisTexFile1, BurningLocations, BurningTimes, -80, 70);
	WPNAttackSheet[0].AssignTextures(DavisTexFile1, WPNAttack1Locations, WPNAttack1Times, 80, 80);
	WPNAttackSheet[1].AssignTextures(DavisTexFile1, WPNAttack2Locations, WPNAttack2Times, 80, 80);
	WPNJumpAttackSheet.AssignTextures(DavisTexFile1, WPNJumpAttackLocations, WPNJumpAttackTimes, 80, 80);
	WPNThrowSheet.AssignTextures(DavisTexFile1, WPNThrowLocations, WPNThrowTimes, 80, 80);

	if (DavisTexFile2.getSize() == sf::Vector2u(0, 0)) {
		DavisTexFile2.loadFromFile("Resource/Davis2.png");
	}

	SpecialAttack1Sheet.AssignTextures(DavisTexFile2, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(DavisTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);
	SpecialAttack3Sheet.AssignTextures(DavisTexFile2, SpecialAttack3Locations, SpecialAttack3Times, 80, 80);
	SpecialAttack4Sheet.AssignTextures(DavisTexFile2, SpecialAttack4Locations, SpecialAttack4Times, 80, 75);

	//Setting One Time Animations
	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet[0].OneTime = true;
	Getting_HitSheet[1].OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	SpecialAttack1Sheet.OneTime = true;
	SpecialAttack2Sheet.OneTime = true;
	SpecialAttack3Sheet.OneTime = true;
	SpecialAttack4Sheet.OneTime = true;
	BurningSheet.OneTime = true;
	WPNAttackSheet[0].OneTime = true;
	WPNAttackSheet[1].OneTime = true;
	WPNThrowSheet.OneTime = true;
	WeaponPickSheet.OneTime = true;
	GuardSheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(3, { 5,10 }, 47, 29,200,200,60);
	HittingSheet[0].AssignHitbox(1, { 9,0 }, 26, 39,-10,300,20);
	HittingSheet[1].AssignHitbox(1, { 10,0 }, 33, 27,-10,300,20);
	HittingSheet[2].AssignHitbox(2,{ 10,2 }, 25, 49,1,300,20);
	HittingSheet[2].AssignHitbox(6, { 12,0 }, 25, 73,200,300,80);
	SpecialAttack2Sheet.AssignHitbox(1, { 3,3 }, 50, 75,120,300,60);
	SpecialAttack2Sheet.AssignHitbox(3, { 3,0 }, 40, 72, 300,300,80);
	SpecialAttack3Sheet.AssignHitbox(1, { 15,16 }, 27, 43, -120,300,14);
	SpecialAttack3Sheet.AssignHitbox(3, { 8,17 }, 30, 43, -120,300,18);
	SpecialAttack3Sheet.AssignHitbox(6, { 17,8 }, 51, 51, -150,300,14);
	SpecialAttack3Sheet.AssignHitbox(10, { 11,9 }, 30, 55, 200, 600,26);
	SpecialAttack4Sheet.AssignHitbox(2, { 1,16 }, 20, 40, 150,100,40);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Davis Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Davis Registered with ID = {0}", CharacterID);

	for (int i = 0; i < 10; i++) {
		BallArray.push_back(DavisBlueBall());
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
	SpecialAttackMP[0] = 8;
	SpecialAttackMP[1] = 45;
	SpecialAttackMP[2] = 15;
	SpecialAttackMP[3] = 5;
}

void Davis::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.3) * (t - 0.3) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position,RealVector2D(400 * Direction, 0));
				return;
			}
		}
	}
}
void Davis::SpecialAttack2Calculations(const double dt, const double t) {
	if ((t - dt) * t <= 0) {
		Velocity = RealVector2D(150 * Direction, -500);
		LastPosition = RealVector2D(Position.get_x() + Velocity.get_x()*0.8,Position.get_y());
	}
	if (t > 0.8) {
		Stop();
		Position = LastPosition;
		return;
	}
	if (!WallIDs.empty()) {
		DEBUG_INFO("HERE");
		if(!WallIDs.empty()) {
			int WallID = WallIDs.front();
			WallIDs.pop();
			if ((Position.get_x() > HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() < 0) || (Position.get_x() < HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() > 0)) {
				Velocity = RealVector2D(0, Velocity.get_y());
				LastPosition = RealVector2D(Position.get_x(), LastPosition.get_y());
			}
		}
	}
	Velocity = Velocity + GravityVector * dt * 1.27;
	Translate(dt);
}

void Davis::SpecialAttack3Calculations(const double dt, const double t) {
	if (t - dt <= 0) {
		Velocity = RealVector2D(Direction * 100, 0);
	}
	if (t > 1) {
		Velocity = RealVector2D(0, 0);
	}
	Translate(dt);
}

void Davis::SpecialAttack4Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		Velocity = RealVector2D(Direction * 200, 2*JumpSpeedY/3);
	}
	if (t > 0.1 && Input_Manager.IsKeyPressed(PlayerControl.AttackKey)) {
		CurrentSheet->Time = 2.51;
	}
	if (Z_Position >= Position.get_y() || t < 0.2) {
		Velocity = Velocity + GravityVector * (dt * 2*JumpGravityFactor/3);
	}
	else {
		Position = RealVector2D(Position.get_x(), Z_Position);
		Stop();
		State_Manager.ForceStateChange(IDLE);
		return;
	}
	Translate(dt);
}
