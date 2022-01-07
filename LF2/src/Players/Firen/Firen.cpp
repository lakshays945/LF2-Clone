#include "Firen.h"

sf::Texture FirenTexFile0;
sf::Texture FirenTexFile1;

const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const std::vector <double> IdleTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };

const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80} };
const std::vector <double> Attack1Times = { 0.1,0.2};

const std::vector<RealVector2D> Attack2Locations = { {160,80},{240,80}};
const std::vector <double> Attack2Times = { 0.1,0.2 };

const std::vector<RealVector2D> Attack3Locations = { {560,80}, {640,80}, {720,80}, {720,160},{720,240},{720,320} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> JumpingAttackLocations = { {320,80},{400,80}, {480,80},{160,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.25,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };

const std::vector<RealVector2D> Getting_HitLocations = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes = { 0.05,0.6 };

const std::vector<RealVector2D> FallingBackLocations = { {0,240},{80,240},{160,240},{240,240},{315,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.3,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {0,15}, {80,15}, {160,15}, {240,15}, {320,15} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.6 };

const std::vector<RealVector2D> SpecialAttack2Locations = { {0,175}, {80,175}, {160,175}, {80,175}};
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4};

const std::vector<RealVector2D> BurningLocations = { {560,240}, {560,480}, {240,240},{315,240} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,0.7,2 };

Firen::Firen() {
	DamageHitBox = HitBox(Position, 42, 74, HB_TYPE_DAMAGE);
	DamageHitBox.AssignPlayer(this);
	DamageHitBox.RegisterID();
	DamageHitBox.SetScale(Scale);
	DamageHitBox.IsActive = true;
	AttackHitBox = HitBox(Position, 15, 15, HB_TYPE_ATTACK);
	AttackHitBox.AssignPlayer(this);
	AttackHitBox.RegisterID();
	AttackHitBox.SetScale(Scale);
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
	Getting_HitSheet.AssignPlayer(this);
	FallingBackSheet.AssignPlayer(this);
	JumpingAttackSheet.AssignPlayer(this);
	DashSheet.AssignPlayer(this);
	SpecialAttack1Sheet.AssignPlayer(this);
	SpecialAttack2Sheet.AssignPlayer(this);
	FallingBackSheet.AssignPlayer(this);
	FallingFrontSheet.AssignPlayer(this);
	BurningSheet.AssignPlayer(this);

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
	Getting_HitSheet.AssignTextures(FirenTexFile0, Getting_HitLocations, Getting_HitTimes, 80, 80);
	FallingBackSheet.AssignTextures(FirenTexFile0, FallingBackLocations, FallingBackTimes, 75, 80);
	FallingFrontSheet.AssignTextures(FirenTexFile0, FallingFrontLocations, FallingFrontTimes, 75, 80);
	BurningSheet.AssignTextures(FirenTexFile0, BurningLocations, BurningTimes, 75, 80);

	if (FirenTexFile1.getSize() == sf::Vector2u(0, 0)) {
		FirenTexFile1.loadFromFile("Resource/Firen1.png");
	};
	SpecialAttack1Sheet.AssignTextures(FirenTexFile1, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(FirenTexFile1, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);

	//Setting One Time Animations
	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet.OneTime = true;
	SpecialAttack1Sheet.OneTime = true;
	//SpecialAttack2Sheet.OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	BurningSheet.OneTime = true;

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
}


void Firen::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.4) * (t - 0.4) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate({ (float)800 * Direction,0 });
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
	if ((Input_Manager.IsKeyPressed(PlayerControl.RightKey) || Input_Manager.IsKeyPressed(PlayerControl.LeftKey) || Input_Manager.IsKeyPressed(PlayerControl.JumpKey)) && t > 0.5) {
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