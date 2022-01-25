#include "Firen.h"

sf::Texture FirenTexFile0;
sf::Texture FirenTexFile1;
sf::Texture FirenTexFile2;

const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const std::vector <double> IdleTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> IdleWPNOffsets = { {4,6}, {4,6}, {4,5}, {4,5} };

const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector <RealVector2D> WalkingWPNOffsets = { {8,6}, {4,6}, {2,6}, {1,6}, {2,6}, {4,6 } };

const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80} };
const std::vector <double> Attack1Times = { 0.1,0.2};

const std::vector<RealVector2D> Attack2Locations = { {160,80},{240,80} };
const std::vector <double> Attack2Times = { 0.1,0.2 };

const std::vector<RealVector2D> Attack3Locations = { {560,80}, {640,80}, {720,80}, {720,160},{720,240},{720,320} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };
const std::vector <RealVector2D> JumpingWPNOffsets = { {-15,0}, {-23,-22}, {-15,0} };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {160,160} , {80,160}, {0,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> RunningWPNOffsets = { {13,-8}, {-13,6} , {13,-8}, {14,-17} };

const std::vector<RealVector2D> JumpingAttackLocations = { {320,80},{400,80}, {480,80},{160,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.25,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };
const std::vector <RealVector2D> DashWPNOffsets = { {-7,-23}, {-22,3} };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit1WPNOffsets = { {0,0}, {8,-7} };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,0}, {560,320} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit2WPNOffsets = { {0,0}, {-5,-25} };

const std::vector<RealVector2D> FallingBackLocations = { {75,240},{155,240},{235,240},{390,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {0,15}, {80,15}, {160,15}, {240,15}, {320,15} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.6 };
const std::vector <RealVector2D> SpecialAttack1WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack2Locations = { {0,175}, {80,175}, {160,175}, {80,175}};
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4};
const std::vector <RealVector2D> SpecialAttack2WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack3Locations = { {400,255}, {480,255}, {560,255}, {640,255}, {720,255}, {720,335}, {640,335} };
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.5,0.9,0.95,1 };
const std::vector <RealVector2D> SpecialAttack3WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack4Locations = { {0,255}, {80,255}, {160,255}, {240,255},{320,255}, {320,255} };
const std::vector <double> SpecialAttack4Times = {0.1,0.2,0.3,0.4,0.5,1 };
const std::vector <RealVector2D> SpecialAttack4WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0} };

const std::vector<RealVector2D> BurningLocations = { {635,240}, {635,480},{390,240} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {640,0}, {720,0} };
const std::vector<double> FreezeTimes = { 0.2,6 };

const std::vector<RealVector2D> WPNAttack1Locations = { {-5,-5}, {75,-5}, {155,-5}, {235,-5} };
const std::vector<double> WPNAttack1Times = { 0.1,0.2,0.3,0.4 };
const std::vector <RealVector2D> WPNAttack1Offsets = { {-34,-8}, {-2,-43}, {38,10}, {36,12} };

const std::vector<RealVector2D> WPNAttack2Locations = { {320,0}, {400,0}, {480,0} };
const std::vector<double> WPNAttack2Times = { 0.1,0.2,0.4 };
const std::vector <RealVector2D> WPNAttack2Offsets = { {-15,-8}, {-9,-25}, {34,2} };

const std::vector<RealVector2D> WPNJumpAttackLocations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector<double> WPNJumpAttackTimes = { 0.1,0.2,0.3,2 };
const std::vector <RealVector2D> WPNJumpAttackOffsets = { {-33,-20}, {-6,-54}, {32,4}, {32,9} };

const std::vector<RealVector2D> WPNThrowLocations = { {320,160}, {400,160}, {480,160} };
const std::vector<double> WPNThrowTimes = { 0.1,0.2,0.5 };
const std::vector <RealVector2D> WPNThrowOffsets = { {-34,-8}, {-2,-43}, {38,10}, {36,12} };

const std::vector<RealVector2D> WeaponPickLocations = { {480,240} };
const std::vector<double> WeaponPickTimes = { 0.2 };
const std::vector <RealVector2D> WPNPickOffsets = { {26,25} };

Firen::Firen() {
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

	//Sprite and Texture Loadindg{
	if (FirenTexFile0.getSize() == sf::Vector2u(0, 0)) {
		FirenTexFile0.loadFromFile("Resource/Firen.png");
	}
	IdleSheet.AssignTextures(FirenTexFile0, IdleLocations, IdleTimes, 70, 80);
	WalkingSheet.AssignTextures(FirenTexFile0, WalkingLocations, WalkingTimes, 70, 80);
	HittingSheet[0].AssignTextures(FirenTexFile0, Attack1Locations, Attack1Times, 70, 80);
	HittingSheet[1].AssignTextures(FirenTexFile0, Attack2Locations, Attack2Times, 70, 80);
	HittingSheet[2].AssignTextures(FirenTexFile0, Attack3Locations, Attack3Times, 70, 80);
	JumpingSheet.AssignTextures(FirenTexFile0, JumpingLocations, JumpingTimes, 70, 80);
	RunningSheet.AssignTextures(FirenTexFile0, RunningLocations, RunningTimes, 70, 80);
	JumpingAttackSheet.AssignTextures(FirenTexFile0, JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	DashSheet.AssignTextures(FirenTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet[0].AssignTextures(FirenTexFile0, Getting_HitLocations1, Getting_HitTimes1, 80, 80);
	Getting_HitSheet[1].AssignTextures(FirenTexFile0, Getting_HitLocations2, Getting_HitTimes2, 80, 80);
	FallingBackSheet.AssignTextures(FirenTexFile0, FallingBackLocations, FallingBackTimes, -75, 80);
	FallingFrontSheet.AssignTextures(FirenTexFile0, FallingFrontLocations, FallingFrontTimes, 75, 80);
	BurningSheet.AssignTextures(FirenTexFile0, BurningLocations, BurningTimes, -75, 80);
	FreezedSheet.AssignTextures(FirenTexFile0, FreezeLocations, FreezeTimes, 80, 80);
	WeaponPickSheet.AssignTextures(FirenTexFile0, WeaponPickLocations, WeaponPickTimes, 75, 75);

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

	if (FirenTexFile1.getSize() == sf::Vector2u(0, 0)) {
		FirenTexFile1.loadFromFile("Resource/Firen1.png");
	};
	SpecialAttack1Sheet.AssignTextures(FirenTexFile1, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(FirenTexFile1, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);
	SpecialAttack3Sheet.AssignTextures(FirenTexFile1, SpecialAttack3Locations, SpecialAttack3Times, 80, 80);
	SpecialAttack4Sheet.AssignTextures(FirenTexFile1, SpecialAttack4Locations, SpecialAttack4Times, 80, 80);

	if (FirenTexFile2.getSize() == sf::Vector2u(0, 0)) {
		FirenTexFile2.loadFromFile("Resource/Firen2.png");
	};
	WPNAttackSheet[0].AssignTextures(FirenTexFile2, WPNAttack1Locations, WPNAttack1Times, 80, 80);
	WPNAttackSheet[1].AssignTextures(FirenTexFile2, WPNAttack2Locations, WPNAttack2Times, 80, 80);
	WPNJumpAttackSheet.AssignTextures(FirenTexFile2, WPNJumpAttackLocations, WPNJumpAttackTimes, 80, 80);
	WPNThrowSheet.AssignTextures(FirenTexFile2, WPNThrowLocations, WPNThrowTimes, 80, 80);

	//Setting One Time Animations
	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet[0].OneTime = true;
	Getting_HitSheet[1].OneTime = true;
	SpecialAttack1Sheet.OneTime = true;
	SpecialAttack3Sheet.OneTime = true;
	//SpecialAttack2Sheet.OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	BurningSheet.OneTime = true;
	WPNAttackSheet[0].OneTime = true;
	WPNAttackSheet[1].OneTime = true;
	WPNThrowSheet.OneTime = true;
	WeaponPickSheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(2, { 8,15 }, 40, 31,200);
	HittingSheet[0].AssignHitbox(1, { 10,17 }, 22, 44);
	HittingSheet[1].AssignHitbox(1, { 15,1 }, 15, 50);
	HittingSheet[2].AssignHitbox(1, { 10,21 }, 41, 34);
	HittingSheet[2].AssignHitbox(4, { 6,14 }, 44, 55,200);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
	WeaponHolderType = 1;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Firen Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Firen Registered with ID = {0}", CharacterID);

	for (int i = 0; i < 10; i++) {
		BallArray.push_back(FirenFireBall());
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
		FlameThrowArray.push_back(FlameThrow());
	}
	for (int i = 0; i < 10; i++) {
		FlameThrowArray[i].AssignParent(this);
		FlameThrowArray[i].RegisterGameObject(GO_Projectile);
		FlameThrowArray[i].AttackHitBox.RegisterID();
		FlameThrowArray[i].AttackHitBox.IgnoreObjectID = ID;
		FlameThrowArray[i].ReboundHitBox.RegisterID();
		FlameThrowArray[i].ReboundHitBox.IgnoreObjectID = ID;

	}

	for (int i = 0; i < 8; i++) {
		FireHitBoxArray.push_back(GroundFireHitBox());
	}
	for (int i = 0; i < 8; i++) {
		FireHitBoxArray[i].AssignParent(this);
		FireHitBoxArray[i].RegisterGameObject(GO_Null);
		FireHitBoxArray[i].AttackHitBox.AssignPlayer(&FireHitBoxArray[i]);
		FireHitBoxArray[i].AttackHitBox.RegisterID();
	}
	for (int i = 0; i < 30; i++) {
		GroundFireArray.push_back(FirenGroundFire());
	}
	for (int i = 0; i < 30; i++) {
		GroundFireArray[i].AssignParent(this);
		GroundFireArray[i].RegisterGameObject(GO_Weapon);
	}
	Firen_ExplosionBoxRD.RegisterGameObject(GO_Null);
	Firen_ExplosionBoxRD.ExplosionHitBox.RegisterID();
	Firen_ExplosionBoxRD.AssignParent(this);
	Firen_ExplosionBoxRD.ExplosionHitBox.AssignPlayer(&Firen_ExplosionBoxRD);
	Firen_ExplosionBoxRD.AssignOffset({43,30});
	Firen_ExplosionBoxLD.RegisterGameObject(GO_Null);
	Firen_ExplosionBoxLD.ExplosionHitBox.RegisterID();
	Firen_ExplosionBoxLD.AssignParent(this);
	Firen_ExplosionBoxLD.ExplosionHitBox.AssignPlayer(&Firen_ExplosionBoxLD);
	Firen_ExplosionBoxLD.AssignOffset({ -43,30 });
	Firen_ExplosionBoxRU.RegisterGameObject(GO_Null);
	Firen_ExplosionBoxRU.ExplosionHitBox.RegisterID();
	Firen_ExplosionBoxRU.AssignParent(this);
	Firen_ExplosionBoxRU.ExplosionHitBox.AssignPlayer(&Firen_ExplosionBoxRU);
	Firen_ExplosionBoxRU.AssignOffset({ 43,-12 });
	Firen_ExplosionBoxLU.RegisterGameObject(GO_Null);
	Firen_ExplosionBoxLU.ExplosionHitBox.RegisterID();
	Firen_ExplosionBoxLU.AssignParent(this);
	Firen_ExplosionBoxLU.ExplosionHitBox.AssignPlayer(&Firen_ExplosionBoxLU);
	Firen_ExplosionBoxLU.AssignOffset({ -43,-12 });
	Firen_ExplosionAnimation.RegisterGameObject(GO_Null);
	Firen_ExplosionAnimation.AssignParent(this);
	
}


void Firen::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.4) * (t - 0.4) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position,RealVector2D(800 * Direction, 0));
				return;
			}
		}
	}
}

void Firen::SpecialAttack2Calculations(const double dt, const double t) {
	if (t-dt <= 0) {
		FireSpawned = 0;
		Velocity = RealVector2D(FireRunSpeed * Direction, 0);
		for (int i = 0; i < FireHitBoxArray.size(); i++) {
			if (!FireHitBoxArray[i].IsActive) {
				FireHitBoxArray[i].Instantiate(Position + RealVector2D(0, 5));
				break;
			}
		}
	}
	Translate(dt);
	if ((Input_Manager.IsKeyPressed(PlayerControl.RightKey) || Input_Manager.IsKeyPressed(PlayerControl.LeftKey) || Input_Manager.IsKeyPressed(PlayerControl.JumpKey)) && t > 1) {
		State_Manager.ForceStateChange(IDLE, 0);
	}
	if (t > FireSpawned*FireRunSpawnRate) {
		for (int i = 0; i < GroundFireArray.size()-1; i++) {
			if (!GroundFireArray[i].IsActive) {
				GroundFireArray[i].Instantiate(Position+RealVector2D(0, 10));
				//GroundFireArray[i + 1].Instantiate(Position + RealVector2D(0, 5));
				FireSpawned++;
				return;
			}
		}
	}
}

void Firen::SpecialAttack3Calculations(const double dt, const double t){
	if ((t-dt-0.6)*(t-0.6) <= 0) {
		Firen_ExplosionBoxRD.Instantiate(Position);
		Firen_ExplosionBoxLD.Instantiate(Position);
		Firen_ExplosionBoxRU.Instantiate(Position);
		Firen_ExplosionBoxLU.Instantiate(Position);
		Firen_ExplosionAnimation.Instantiate(Position);
	}
}

void Firen::SpecialAttack4Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		FireSpawned = 0;
		for (int i = 0; i < FlameThrowArray.size(); i++) {
			if (!FlameThrowArray[i].IsActive) {
				FlameThrowArray[i].Instantiate(Position + RealVector2D(Direction * 30, -30), RealVector2D(Direction * 30, 0));
				FlameThrowArray[i].Direction = Direction;
				FlameThrowArray[i].TotalTime = 0;
				FlameThrowArray[i].Z_Position = Z_Position;
				FlameThrowArray[i].ReboundHitBox.IsActive = false;
				FireSpawned++;
				break;
			}
		}
	}
	if (t > 0.5 && (Input_Manager.IsKeyPressed(PlayerControl.LeftKey) || Input_Manager.IsKeyPressed(PlayerControl.RightKey))) {
		State_Manager.ForceStateChange(IDLE);
	}
	if (CurrentSheet->Time > 0.5) {
		CurrentSheet->Time = 0.31;
	}
	if (t > FireSpawned * 0.25 + (-2.0+rand()%3)/10.0) {
		for (int i = 0; i < FlameThrowArray.size() - 1; i++) {
			if (!FlameThrowArray[i].IsActive) {
				FlameThrowArray[i].Instantiate(Position + RealVector2D(Direction * 30, -15 + (-10 + rand()%10)), RealVector2D(Direction * (40 + rand()%10), 0));
				FlameThrowArray[i].Direction = Direction;
				FlameThrowArray[i].TotalTime = 0;
				FlameThrowArray[i].Z_Position = Z_Position;
				FlameThrowArray[i].ReboundHitBox.IsActive = false;
				FireSpawned++;
				break;
			}
		}
	}
}
