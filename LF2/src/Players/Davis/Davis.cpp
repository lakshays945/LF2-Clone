#include "Davis.h"

sf::Texture DavisTexFile0;
sf::Texture DavisTexFile1;
sf::Texture DavisTexFile2;

const std::vector <double> IdleTimes = { 0.3,0.6,0.9,1.2 };
const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y

const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y

const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector <double> Attack1Times = { 0.1,0.2,0.3,0.4};

const std::vector<RealVector2D> Attack2Locations = { {320,80},{400,80},{480,80},{560,80} };
const std::vector <double> Attack2Times = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> Attack3Locations = { {560,480}, {640,480}, {640,0}, {720,0},{720,80},{720,160},{720,240},{720,320} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> JumpingAttackLocations = { {160,480},{240,480}, { 320,480}, {400,480}, {480,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.2,0.3,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };

const std::vector<RealVector2D> Getting_HitLocations = { {480,320} };
const std::vector <double> Getting_HitTimes = { 0.3 };

const std::vector<RealVector2D> FallingBackLocations = { {0,240},{80,240},{160,240},{240,240},{320,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.3,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {0,15}, {80,15}, {160,15}, {240,15}, {320,15} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.6 };

const std::vector<RealVector2D> SpecialAttack2Locations = { {0,248}, {80,248}, {160,248}, {240,248}, {320,248}, {400,248}, {480,248}, {560,248} };
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.85 };


Davis::Davis() {
	//HitBox Assignments
	DamageHitBox = HitBox(Position, 42, 74, HB_TYPE_DAMAGE);
	DamageHitBox.AssignPlayer(this);
	DamageHitBox.RegisterID();
	DamageHitBox.IsActive = true;
	AttackHitBox = HitBox(Position, 15, 15, HB_TYPE_ATTACK);
	AttackHitBox.AssignPlayer(this);
	AttackHitBox.RegisterID();

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
	FallingBackSheet.AssignPlayer(this);
	FallingFrontSheet.AssignPlayer(this);
	SpecialAttack1Sheet.AssignPlayer(this);
	SpecialAttack2Sheet.AssignPlayer(this);

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
	Getting_HitSheet.AssignTextures(DavisTexFile0, Getting_HitLocations, Getting_HitTimes, 80, 80);
	FallingBackSheet.AssignTextures(DavisTexFile0, FallingBackLocations, FallingBackTimes, 80, 80);
	FallingFrontSheet.AssignTextures(DavisTexFile0, FallingFrontLocations, FallingFrontTimes, 80, 80);


	if (DavisTexFile1.getSize() == sf::Vector2u(0, 0)) {
		DavisTexFile1.loadFromFile("Resource/Davis1.png");
	}
	JumpingAttackSheet.AssignTextures(DavisTexFile1, JumpingAttackLocations, JumpingAttackTimes, 80, 80);

	if (DavisTexFile2.getSize() == sf::Vector2u(0, 0)) {
		DavisTexFile2.loadFromFile("Resource/Davis2.png");
	}

	SpecialAttack1Sheet.AssignTextures(DavisTexFile2, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(DavisTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);

	//Setting One Time Animations
	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet.OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	SpecialAttack1Sheet.OneTime = true;
	SpecialAttack2Sheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(3, { 5,10 }, 47, 29,200);
	JumpingAttackSheet.AssignHitbox(4, { 5,10 }, 47, 29,200);
	HittingSheet[0].AssignHitbox(1, { 9,0 }, 26, 39);
	HittingSheet[1].AssignHitbox(1, { 10,0 }, 33, 27);
	HittingSheet[2].AssignHitbox(2,{ 10,2 }, 25, 49,1);
	HittingSheet[2].AssignHitbox(6, { 12,0 }, 25, 73,200);
	SpecialAttack2Sheet.AssignHitbox(1, { 3,3 }, 33, 75,120);
	SpecialAttack2Sheet.AssignHitbox(3, { 3,0 }, 28, 72, 300);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Davis Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Davis Registered with ID = {0}", CharacterID);

	for (int i = 0; i < 10; i++) {
		BallArray.push_back(DavisBlueBall());
		BallArray[i].AssignParent(this);
	}
	for (int i = 0; i < 10; i++) {
		BallArray[i].RegisterGameObject(GO_Projectile);
		BallArray[i].AttackHitBox.AssignPlayer(&BallArray[i]);
		BallArray[i].AttackHitBox.RegisterID();
		BallArray[i].AttackHitBox.IgnoreObjectID = ID;
		BallArray[i].ReboundHitBox.AssignPlayer(&BallArray[i]);
		BallArray[i].ReboundHitBox.RegisterID();
		BallArray[i].ReboundHitBox.IgnoreObjectID = ID;
	}

	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
}

void Davis::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.3) * (t - 0.3) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate({ (float)400 * Direction,0 });
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
	Velocity = Velocity + GravityVector * dt * 1.27;
	Translate(dt);
}