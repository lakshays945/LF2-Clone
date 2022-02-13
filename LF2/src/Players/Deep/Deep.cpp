#include "Deep.h"

sf::Texture DeepTexFile0;
sf::Texture DeepTexFile1;
sf::Texture DeepTexFile2;
sf::Texture DeepTexFile3;

const std::vector<RealVector2D> IdleLocations = { {0,4}, {80,4}, {160,4}, {240,4} }; //x,y
const std::vector <double> IdleTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> IdleWPNOffsets = { {0,0}, {0,0}, {0,-1}, {0,-1} };

const std::vector<RealVector2D> WalkingLocations = { {321,4}, {400,4}, {471,4}, {557,4}, {471,4}, {400,4} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector <RealVector2D> WalkingWPNOffsets = { {-2,0}, {-4,0}, {-6,0}, {-8,0}, {-6,0}, {-4,0 } };

const std::vector<RealVector2D> Attack1Locations = { {0,84},{637,84}, {82,84} };
const std::vector <double> Attack1Times = { 0.1,0.25,0.35 };

const std::vector<RealVector2D> Attack2Locations = { {174,84},{720,84} ,{247,84} };
const std::vector <double> Attack2Times = { 0.1,0.2,0.35 };

const std::vector<RealVector2D> Attack3Locations = { {560,244}, {720,164}, {640,244}, {720,244} };
const std::vector <double> Attack3Times = { 0.1,0.25,0.35,0.45 };

const std::vector<RealVector2D> JumpingLocations = { {80,484}, {160,484}, {80,484} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };
const std::vector <RealVector2D> JumpingWPNOffsets = { {-20,0}, {8,-34}, {-20,0} };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {0,160}, {80,160}, {160,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> RunningWPNOffsets = { {20,-5}, {3,11} , {20,-5}, {16,-10} };

const std::vector<RealVector2D> JumpingAttackLocations = { {320,84},{400,84}, {480,84},{160,484} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.25,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,484},{80,484} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME };
const std::vector <RealVector2D> DashWPNOffsets = { {32,-27}, {-21,-4} };

const std::vector<RealVector2D> Getting_HitLocations1 = { {80,400}, {160,400 } };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit1WPNOffsets = { {0,0}, {6,-10} };

const std::vector<RealVector2D> Getting_HitLocations2 = { {80,400}, {240,400 } };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit2WPNOffsets = { {0,0}, {-23,-10} };

const std::vector<RealVector2D> FallingBackLocations = { {75,244},{160,244},{240,244},{398,244} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {78,320},{158,320},{398,320}, {318,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = {{0,95},{160,95}, {240,95} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.3,0.4 };
const std::vector <RealVector2D> SpecialAttack1WPNOffsets = { {0,0}, {0,0}, {0,0}};

const std::vector<RealVector2D> SpecialAttack2Locations = { {0,175}, {80,175}, {160,175}, {240,175}, {320,175}, {400,175},{480,175},{560,175},{640,175},{720,175},{720,255},{640,255},{560,255},{480,255},{400,255},{320,255},{240,255},{160,255} };
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8 };
const std::vector <RealVector2D> SpecialAttack2WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack3Locations = { {-5,22}, {76,24},{166,24},{273,28}, {376,28} };
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.4,0.5};
const std::vector <RealVector2D> SpecialAttack3WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack4Locations = { {32,120}, {152,120}, {272,120}, {22,300}, {114,300},{86,203},{2,203} };
const std::vector <double> SpecialAttack4Times = { 0.1,2.5,2.57,2.62,2.67,2.72,4 };
const std::vector <RealVector2D> SpecialAttack4WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}};

const std::vector<RealVector2D> BurningLocations = { {640,484}, {720,484},{390,240} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {640,0}, {720,0} };
const std::vector<double> FreezeTimes = { 0.2,6 };

const std::vector<RealVector2D> WPNAttack1Locations = { {-5,0}, {75,0}, {155,0}, {235,0} };
const std::vector<double> WPNAttack1Times = { 0.1,0.2,0.3,0.4 };
const std::vector <RealVector2D> WPNAttack1Offsets = { {-30,-40}, {-8,-43}, {20,10}, {15,16} };

const std::vector<RealVector2D> WPNAttack2Locations = { {315,0}, {395,0}, {475,0} };
const std::vector<double> WPNAttack2Times = { 0.1,0.2,0.4 };
const std::vector <RealVector2D> WPNAttack2Offsets = { {-15,-8}, {-2,-10}, {29,0} };

const std::vector<RealVector2D> WPNJumpAttackLocations = { {0,80}, {80,80}, {160,80}, {240,80} };
const std::vector<double> WPNJumpAttackTimes = { 0.1,0.2,0.3,2 };
const std::vector <RealVector2D> WPNJumpAttackOffsets = { {-37,-39}, {-21,-47}, {18,7}, {13,15} };

const std::vector<RealVector2D> WPNThrowLocations = { {320,160}, {400,160}, {480,160} };
const std::vector<double> WPNThrowTimes = { 0.1,0.2,0.5 };
const std::vector <RealVector2D> WPNThrowOffsets = { {-30,-40}, {-8,-43}, {20,10}, {15,16} };

const std::vector<RealVector2D> WeaponPickLocations = { {480,240} };
const std::vector<double> WeaponPickTimes = { 0.2 };
const std::vector <RealVector2D> WPNPickOffsets = { {0,25} };

const std::vector<RealVector2D> GuardLocations = { {480,400} };
const std::vector<double> GuardTimes = { 0.8 };
const std::vector<RealVector2D> WPNGuardOffsets = { {0,-15} };

Deep::Deep() {
	//Manager Assignments
	State_Manager.AssignPlayer(this);
	Input_Manager.AssignPlayer(this);
	DamageHitBox.SetSize(48, 74);
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
	if (DeepTexFile0.getSize() == sf::Vector2u(0, 0)) {
		DeepTexFile0.loadFromFile("Resource/Deep.png");
	}
	IdleSheet.AssignTextures(DeepTexFile0, IdleLocations, IdleTimes, 75, 80);
	WalkingSheet.AssignTextures(DeepTexFile0, WalkingLocations, WalkingTimes, 70, 80);
	HittingSheet[0].AssignTextures(DeepTexFile0, Attack1Locations, Attack1Times, 85, 80);
	HittingSheet[1].AssignTextures(DeepTexFile0, Attack2Locations, Attack2Times, 73, 80);
	HittingSheet[2].AssignTextures(DeepTexFile0, Attack3Locations, Attack3Times, 75, 80);
	JumpingSheet.AssignTextures(DeepTexFile0, JumpingLocations, JumpingTimes, 75, 80);
	RunningSheet.AssignTextures(DeepTexFile0, RunningLocations, RunningTimes, 75, 80);
	JumpingAttackSheet.AssignTextures(DeepTexFile0, JumpingAttackLocations, JumpingAttackTimes, 75, 80);
	DashSheet.AssignTextures(DeepTexFile0, DashLocations, DashTimes, 75, 80);
	FallingBackSheet.AssignTextures(DeepTexFile0, FallingBackLocations, FallingBackTimes, -80, 80);
	FallingFrontSheet.AssignTextures(DeepTexFile0, FallingFrontLocations, FallingFrontTimes, 80, 80);
	BurningSheet.AssignTextures(DeepTexFile0, BurningLocations, BurningTimes, -80, 80);
	FreezedSheet.AssignTextures(DeepTexFile0, FreezeLocations, FreezeTimes, 80, 80);
	FreezedSheet.AssignTextures(DeepTexFile0, FreezeLocations, FreezeTimes, 80, 80);
	WeaponPickSheet.AssignTextures(DeepTexFile0, WeaponPickLocations, WeaponPickTimes, 75, 80);
	GuardSheet.AssignTextures(DeepTexFile0, GuardLocations, GuardTimes, 80, 80);


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

	if (DeepTexFile1.getSize() == sf::Vector2u(0, 0)) {
		DeepTexFile1.loadFromFile("Resource/Deep1.png");
	};
	Getting_HitSheet[0].AssignTextures(DeepTexFile1, Getting_HitLocations1, Getting_HitTimes1, 75, 80);
	Getting_HitSheet[1].AssignTextures(DeepTexFile1, Getting_HitLocations2, Getting_HitTimes2, 75, 80);
	WPNAttackSheet[0].AssignTextures(DeepTexFile1, WPNAttack1Locations, WPNAttack1Times, 80, 80);
	WPNAttackSheet[1].AssignTextures(DeepTexFile1, WPNAttack2Locations, WPNAttack2Times, 80, 80);
	WPNJumpAttackSheet.AssignTextures(DeepTexFile1, WPNJumpAttackLocations, WPNJumpAttackTimes, 80, 80);
	WPNThrowSheet.AssignTextures(DeepTexFile1, WPNThrowLocations, WPNThrowTimes, 80, 80);

	if (DeepTexFile2.getSize() == sf::Vector2u(0, 0)) {
		DeepTexFile2.loadFromFile("Resource/Deep2.png");
	};
	SpecialAttack1Sheet.AssignTextures(DeepTexFile2, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack2Sheet.AssignTextures(DeepTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);


	if (DeepTexFile3.getSize() == sf::Vector2u(0, 0)) {
		DeepTexFile3.loadFromFile("Resource/Deep3.png");
	};
	SpecialAttack3Sheet.AssignTextures(DeepTexFile3, SpecialAttack3Locations, SpecialAttack3Times, 105, 80);
	SpecialAttack4Sheet.AssignTextures(DeepTexFile3, SpecialAttack4Locations, SpecialAttack4Times, 110, 80);

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
	SpecialAttack4Sheet.OneTime = true;
	SpecialAttack2Sheet.OneTime = true;
	FallingBackSheet.OneTime = true;
	FallingFrontSheet.OneTime = true;
	BurningSheet.OneTime = true;
	WPNAttackSheet[0].OneTime = true;
	WPNAttackSheet[1].OneTime = true;
	WPNThrowSheet.OneTime = true;
	WeaponPickSheet.OneTime = true;
	GuardSheet.OneTime = true;

	//Assigning HitBoxes to Sheets
	JumpingAttackSheet.AssignHitbox(1, { 14,11 }, 47, 46, 200,300, 60);
	HittingSheet[0].AssignHitbox(2, { 25,20 }, 49, 44,-10,300, 35);
	HittingSheet[1].AssignHitbox(1, { 15,15 }, 42, 48,-10,300, 35);
	HittingSheet[2].AssignHitbox(1, { 15,7 }, 49, 66,20,100, 70);
	SpecialAttack2Sheet.AssignHitbox(2, { 12,14 }, 53, 46,180, 200,54);
	SpecialAttack2Sheet.AssignHitbox(6, { 10,7 }, 63, 61, 180, 200,42);
	SpecialAttack2Sheet.AssignHitbox(10, { 7,12 }, 50, 47, 180, 250,42);
	SpecialAttack2Sheet.AssignHitbox(14, { 10,13 }, 63, 49, 400, 300,48);
	SpecialAttack3Sheet.AssignHitbox(1, { 15,0 }, 50, 60, 100, 600,60);
	SpecialAttack3Sheet.AssignHitbox(3, { -25,0 }, 40, 60, 50, 150,30);
	SpecialAttack4Sheet.AssignHitbox(4, { 30,0 }, 50, 60,50, 150,40);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
	WeaponPosOffsets[WALKING] = { -10,0 };
	WeaponHolderType = 1;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Deep Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Deep Registered with ID = {0}", CharacterID);

	for (int i = 0; i < 10; i++) {
		SlashArray.push_back(DeepSlash());
	}
	for (int i = 0; i < 10; i++) {
		SlashArray[i].AssignParent(this);
		SlashArray[i].RegisterGameObject(GO_Projectile);
		SlashArray[i].AttackHitBox.RegisterID();
		SlashArray[i].ReboundHitBox.RegisterID();
	}

}

void Deep::SpecialAttack1Calculations(const double dt, const double t){
	if ((t - dt - 0.1) * (t - 0.1) < 0) {
		for (int i = 0; i < SlashArray.size(); i++) {
			if (!SlashArray[i].IsActive) {
				SlashArray[i].TotalTime = 0;
				SlashArray[i].Instantiate(Position + RealVector2D(Direction * 30, 0), RealVector2D(400 * Direction, 0));
				return;
			}
		}
	}
}

void Deep::SpecialAttack2Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		Velocity = RealVector2D(Direction * 180, 0);
	}
	Translate(dt);
}

void Deep::SpecialAttack3Calculations(const double dt, const double t){
	if ((t - dt - 0.48) * (t - 0.48) <= 0) {
		Position = Position + RealVector2D(Direction * 5, 0);
		DamageHitBox.Center = Position;
	}
}

void Deep::SpecialAttack4Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		Velocity = RealVector2D(Direction * 200, 2*JumpSpeedY/3);
	}
	if (t > 0.1 && Input_Manager.IsKeyPressed(PlayerControl.AttackKey)) {
		CurrentSheet->Time = 2.53;
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
