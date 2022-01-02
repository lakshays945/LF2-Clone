#include "Davis.h"

sf::Texture DavisTexFile0;
sf::Texture DavisTexFile1;

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

const std::vector<RealVector2D> JumpingAttackLocations = { {560,240},{640,240}, { 560,240}, {160,480} };
const std::vector <double> JumpingAttackTimes = { 0.15,0.4,0.55,2 };


const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };

const std::vector<RealVector2D> Getting_HitLocations = { {480,320} };
const std::vector <double> Getting_HitTimes = { 0.3 };


Davis::Davis() {
	//HitBox Assignments
	DamageHitBox = HitBox(Position, 42, 74, TYPE_DAMAGE);
	DamageHitBox.AssignPlayer(this);
	DamageHitBox.RegisterID();
	AttackHitBox = HitBox(Position, 15, 15, TYPE_ATTACK);
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
	FallingSheet.AssignPlayer(this);
	JumpingAttackSheet.AssignPlayer(this);
	DashSheet.AssignPlayer(this);

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
	JumpingAttackSheet.AssignTextures(DavisTexFile0, JumpingAttackLocations, JumpingAttackTimes, 80, 80);
	DashSheet.AssignTextures(DavisTexFile0, DashLocations, DashTimes, 80, 80);
	Getting_HitSheet.AssignTextures(DavisTexFile0, Getting_HitLocations, Getting_HitTimes, 80, 80);

	//Setting One Time Animations
	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(1, { 32,2 }, 15, 15);
	HittingSheet[0].AssignHitbox(2, { 17,14 }, 40, 38);
	HittingSheet[1].AssignHitbox(1, { 19,13 }, 46, 52);
	HittingSheet[2].AssignHitbox(6, { 14,14 }, 50, 50);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	RegisterGameObject();
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Davis Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Davis Registered with ID = {0}", CharacterID);
	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
}

void Davis::SpecialAttack1Calculations(const double dt, const double t) {

}
void Davis::SpecialAttack2Calculations(const double dt, const double t) {

}