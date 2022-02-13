#include "Freeze.h"

sf::Texture FreezeTexFile0;
sf::Texture FreezeTexFile1;
sf::Texture FreezeTexFile2;

const std::vector<RealVector2D> IdleLocations = { {0,0}, {80,0}, {160,0}, {240,0} }; //x,y
const std::vector <double> IdleTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> IdleWPNOffsets = { {-4,-16}, {-4,-16}, {-4,-17}, {-4,-17} };

const std::vector<RealVector2D> WalkingLocations = { {320,0}, {400,0}, {480,0}, {560,0}, {480,0}, {400,0} };//x,y
const std::vector <double> WalkingTimes = { 0.15,0.3,0.45,0.6,0.75,0.9 };
const std::vector <RealVector2D> WalkingWPNOffsets = { {-4,-16}, {-4,-17}, {-4,-16}, {-4,-17}, {-4,-16}, {-4,-17} };

const std::vector<RealVector2D> Attack1Locations = { {0,80}, {80,80} };
const std::vector <double> Attack1Times = { 0.1,0.2 };

const std::vector<RealVector2D> Attack2Locations = { {160,80},{240,80} };
const std::vector <double> Attack2Times = { 0.1,0.2 };

const std::vector<RealVector2D> Attack3Locations = { {320,80},{400,80},{480,80}, {560,80}, {640,80}, {720,80}, {720,160},{720,240} };
const std::vector <double> Attack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8 };

const std::vector<RealVector2D> JumpingLocations = { {80,480}, {160,480}, {80,480} };
const std::vector <double> JumpingTimes = { INITIAL_JUMP_PAUSE,INITIAL_JUMP_PAUSE + JUMP_DURATION,INITIAL_JUMP_PAUSE + JUMP_DURATION + JUMP_LANDING_TIME };
const std::vector <RealVector2D> JumpingWPNOffsets = { {-7,10}, {-22,-12}, {-7,10} };

const std::vector<RealVector2D> RunningLocations = { {80,160}, {160,160} , {80,160},  {0,160} };
const std::vector <double> RunningTimes = { 0.15,0.3,0.45,0.6 };
const std::vector <RealVector2D> RunningWPNOffsets = { {17,-10}, {-9,14} , {17,-10}, {16,-17} };

const std::vector<RealVector2D> JumpingAttackLocations = { {320,80},{400,80}, {480,80},{160,480} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.25,0.4,2 };

const std::vector<RealVector2D> DashLocations = { {240,480},{80,480} };
const std::vector <double> DashTimes = { DASH_DURATION, DASH_DURATION + DASH_LANDING_TIME};
const std::vector <RealVector2D> DashWPNOffsets = { {-12,-18}, {-13,10} };

const std::vector<RealVector2D> Getting_HitLocations1 = { {0,0}, {480,320} };
const std::vector <double> Getting_HitTimes1 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit1WPNOffsets = { {4,-27}, {12,-2} };

const std::vector<RealVector2D> Getting_HitLocations2 = { {0,0}, {560,320} };
const std::vector <double> Getting_HitTimes2 = { 0.05,0.6 };
const std::vector <RealVector2D> Get_Hit2WPNOffsets = { {4,-27}, {12,-2} };


const std::vector<RealVector2D> FallingBackLocations = { {75,240},{155,240},{235,240},{390,240} };
const std::vector<double> FallingBackTimes = { 0.1,0.2,0.4,2 };

const std::vector<RealVector2D> FallingFrontLocations = { {80,320},{160,320},{400,320}, {320,320} };
const std::vector<double> FallingFrontTimes = { 0.1,0.5,0.7,2 };

const std::vector<RealVector2D> SpecialAttack1Locations = { {45,12},{125,12},{205,12},{285,12},{365,12},{445,12} };
const std::vector <double> SpecialAttack1Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };
const std::vector <RealVector2D> SpecialAttack1WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0},{0,0} };

const std::vector<RealVector2D> SpecialAttack2Locations = { {640,0},{720,0},{560,80},{640,80},{720,80}};
const std::vector <double> SpecialAttack2Times = { 0.1,0.2,0.3,0.4,0.7 };
const std::vector <RealVector2D> SpecialAttack2WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack3Locations = { {45,92}, {125,92}, {205,92}, {285,92}, {365,92}, {445,92}, {525,92}, {605,92}, {685,92} };
const std::vector <double> SpecialAttack3Times = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9 };
const std::vector <RealVector2D> SpecialAttack3WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> SpecialAttack4Locations = { {45,172}, {125,172}, {205,172}, {285,172}, {365,172}, {445,172}};
const std::vector <double> SpecialAttack4Times = { 0.1,0.2,0.3,0.4,0.5,0.6 };
const std::vector <RealVector2D> SpecialAttack4WPNOffsets = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };

const std::vector<RealVector2D> BurningLocations = { {635,240}, {635,480},{390,240} }; //x,y
const std::vector <double> BurningTimes = { 0.25,0.5,2 };

const std::vector<RealVector2D> FreezeLocations = { {640,0}, {720,0} };
const std::vector<double> FreezeTimes = { 0.2,6 };

const std::vector<RealVector2D> WPNAttack1Locations = { {0,0}, {80,0}, {160,0}, {240,0} };
const std::vector<double> WPNAttack1Times = { 0.1,0.2,0.3,0.4 };
const std::vector <RealVector2D> WPNAttack1Offsets = { {-34,-8}, {-6,-39}, {35,10}, {33,14} };

const std::vector<RealVector2D> WPNAttack2Locations = { {320,0}, {400,0}, {480,0} };
const std::vector<double> WPNAttack2Times = { 0.1,0.2,0.4 };
const std::vector <RealVector2D> WPNAttack2Offsets = { {-15,-8}, {-9,-25}, {30,6} };

const std::vector<RealVector2D> WPNJumpAttackLocations = { {0,80}, {80,80}, {160,80}, {160,80} };
const std::vector<double> WPNJumpAttackTimes = { 0.1,0.2,0.3,2 };
const std::vector <RealVector2D> WPNJumpAttackOffsets = {  {-33,-20}, {-6,-54}, {20,11}, {22,11} };

const std::vector<RealVector2D> WPNThrowLocations = { {320,160}, {400,160}, {480,160} };
const std::vector<double> WPNThrowTimes = { 0.1,0.2,0.5 };
const std::vector <RealVector2D> WPNThrowOffsets = { {-34,-8}, {-6,-39}, {35,10} };

const std::vector<RealVector2D> WeaponPickLocations = { {480,240} };
const std::vector<double> WeaponPickTimes = { 0.2 };
const std::vector <RealVector2D> WPNPickOffsets = { {20,30} };

const std::vector<RealVector2D> GuardLocations = { {480,400} };
const std::vector<double> GuardTimes = { 0.8 };
const std::vector<RealVector2D> WPNGuardOffsets = { {-5,-15} };

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
	WeaponPickSheet.AssignTextures(FreezeTexFile0, WeaponPickLocations, WeaponPickTimes, 75, 75);
	GuardSheet.AssignTextures(FreezeTexFile0, GuardLocations, GuardTimes, 80, 80);

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
	SpecialAttack4Sheet.AssignWPNOffsets(SpecialAttack4WPNOffsets);
	GuardSheet.AssignWPNOffsets(WPNGuardOffsets);

	if (FreezeTexFile1.getSize() == sf::Vector2u(0, 0)) {
		FreezeTexFile1.loadFromFile("Resource/Freeze1.png");
	};
	SpecialAttack1Sheet.AssignTextures(FreezeTexFile1, SpecialAttack1Locations, SpecialAttack1Times, 80, 80);
	SpecialAttack3Sheet.AssignTextures(FreezeTexFile1, SpecialAttack3Locations, SpecialAttack3Times, 80, 80);
	SpecialAttack4Sheet.AssignTextures(FreezeTexFile1, SpecialAttack4Locations, SpecialAttack4Times, 80, 80);

	if (FreezeTexFile2.getSize() == sf::Vector2u(0, 0)) {
		FreezeTexFile2.loadFromFile("Resource/Freeze2.png");
	}
	SpecialAttack2Sheet.AssignTextures(FreezeTexFile2, SpecialAttack2Locations, SpecialAttack2Times, 80, 80);
	WPNAttackSheet[0].AssignTextures(FreezeTexFile2, WPNAttack1Locations, WPNAttack1Times, 80, 75);
	WPNAttackSheet[1].AssignTextures(FreezeTexFile2, WPNAttack2Locations, WPNAttack2Times, 80, 80);
	WPNJumpAttackSheet.AssignTextures(FreezeTexFile2, WPNJumpAttackLocations, WPNJumpAttackTimes, 80, 75);
	WPNThrowSheet.AssignTextures(FreezeTexFile2, WPNThrowLocations, WPNThrowTimes, 80, 80);

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
	JumpingAttackSheet.AssignHitbox(2, { 8,15 }, 40, 31, 200,200,35);
	HittingSheet[0].AssignHitbox(1, { 24,17 }, 22, 45,-10,300,20);
	HittingSheet[1].AssignHitbox(1, { 11,19 }, 32, 42,-10,300,20);
	HittingSheet[2].AssignHitbox(1, { 10,3 }, 36, 46,-10,300,20);
	HittingSheet[2].AssignHitbox(5, { 10,16 }, 42, 54, 200,300,65);

	//Initialising CurrentSheet
	CurrentSheet = &IdleSheet;

	RegisterGameObject(GO_Character);
	RegisterCharacter();
	DEBUG_SUCCESS("GameObject Freeze Registered with ID = {0}", ID);
	DEBUG_SUCCESS("Character Freeze Registered with ID = {0}", CharacterID);
	WeaponHolderType = 3;

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
		BergArray1.push_back(IceBerg());
		BergArray2.push_back(IceBerg());
		BergArray3.push_back(IceBerg());
	}
	for (int i = 0; i < 10; i++) {
		BergArray1[i].SetIceTextures(1);
		BergArray1[i].AssignParent(this);
		BergArray1[i].RegisterGameObject(GO_Null);
		BergArray1[i].WallHitBox.RegisterID();
		BergArray1[i].WallHitBox.AssignPlayer(&BergArray1[i]);
		BergArray1[i].AttackHitBox.RegisterID();
		BergArray1[i].AttackHitBox.AssignPlayer(&BergArray1[i]);

		BergArray2[i].SetIceTextures(2);
		BergArray2[i].AssignParent(this);
		BergArray2[i].RegisterGameObject(GO_Null);
		BergArray2[i].WallHitBox.RegisterID();
		BergArray2[i].WallHitBox.AssignPlayer(&BergArray2[i]);
		BergArray2[i].AttackHitBox.RegisterID();
		BergArray2[i].AttackHitBox.AssignPlayer(&BergArray2[i]);

		
		BergArray3[i].SetIceTextures(3);
		BergArray3[i].AssignParent(this);
		BergArray3[i].RegisterGameObject(GO_Null);
		BergArray3[i].WallHitBox.RegisterID();
		BergArray3[i].WallHitBox.AssignPlayer(&BergArray3[i]);
		BergArray3[i].AttackHitBox.RegisterID();
		BergArray3[i].AttackHitBox.AssignPlayer(&BergArray3[i]);
	}
	Freeze_Tornado.RegisterGameObject(GO_Null);
	Freeze_Tornado.AssignParent(this);
	Freeze_Tornado.AttackHitBox.AssignPlayer(&Freeze_Tornado);
	Freeze_Tornado.AttackHitBox.RegisterID();
	Freeze_Tornado.ForceFieldBox.AssignPlayer(&Freeze_Tornado);
	Freeze_Tornado.ForceFieldBox.RegisterID();

	//Variable Assignment
	MaxSpeed = 200;
	RunSpeed = 500;
	JumpSpeedY = -600;
	DashSpeedX = 600;
	JumpGravityFactor = -(JumpSpeedY * 2) / (DEFAULT_GRAVITY_CONSTANT * JUMP_DURATION);
	SpecialAttackMP[0] = 20;
	SpecialAttackMP[1] = 30;
	SpecialAttackMP[2] = 60;
	SpecialAttackMP[3] = 30;
}

void Freeze::SpecialAttack1Calculations(const double dt, const double t) {
	if ((t - dt - 0.3) * (t - 0.3) < 0) {
		for (int i = 0; i < BallArray.size(); i++) {
			if (!BallArray[i].IsActive) {
				BallArray[i].Instantiate(Position,RealVector2D(400 * Direction, 0));
				return;
			}
		}
	}
}
void Freeze::SpecialAttack2Calculations(const double dt, const double t) {
	if ((t - dt - 0.4) * (t - 0.4) <= 0) {
		for (int i = 0; i < BergArray1.size(); i++) {
			if (!BergArray3[i].IsActive) {
				IceBergIndex = i;
				BergArray3[IceBergIndex].Instantiate(Position + RealVector2D(Direction * 60, -20));
				return;
			}
		}
	}
	else if ((t - dt - 0.55) * (t - 0.55) <= 0) {
		BergArray2[IceBergIndex].Instantiate(Position + RealVector2D(Direction * 110, -20));
	}
	else if ((t - dt - 0.69) * (t - 0.69) <= 0) {
		BergArray1[IceBergIndex].Instantiate(Position + RealVector2D(Direction * 185, -20));
	}
}

void Freeze::SpecialAttack3Calculations(const double dt, const double t){
	if (Freeze_Tornado.IsActive) {
		State_Manager.ForceStateChange(IDLE);
		return;
	}
	if ((t - dt - 0.4) * (t - 0.4) <= 0) {
		Freeze_Tornado.GoBack();
		Freeze_Tornado.Instantiate(Position);
	}
}

void Freeze::SpecialAttack4Calculations(const double dt, const double t){
	if (t - dt <= 0) {
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Throw(RealVector2D(-25+rand()%50, -25 + rand() % 50), false);
		}
	}
	if (t > 0.55) {
		CurrentWeapon = new IceSword;
		CurrentWeapon->Position = Position;
		CurrentWeapon->PickUpHitBox.Disable();
		CurrentWeapon->AttackHitBox.IgnoreObjectID = ID;
		State_Manager.ForceStateChange(IDLE);
	}
}
