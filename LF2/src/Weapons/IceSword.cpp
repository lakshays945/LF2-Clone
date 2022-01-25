#include "IceSword.h"

sf::Texture IceSowrdTexFile;

const std::vector<RealVector2D> IdleLocations1 = { {296,147} };
const std::vector<double> IdleTimes1 = { 1 };

const std::vector<RealVector2D> IdleLocations2 = { {296,147} };
const std::vector<double> IdleTimes2 = { 1 };

const std::vector<RealVector2D> IdleLocations3 = { {296,147} };
const std::vector<double> IdleTimes3 = { 1 };

const std::vector<RealVector2D> IdleLocations4 = { {393,98} };
const std::vector<double> IdleTimes4 = { 1 };

const std::vector<RealVector2D> WalkingLocations1 = { {295,142}, {295,142}, {246,142}, {197,142}, {246,142}, {295,142} };//x,y
const std::vector <double> WalkingTimes1 = { 0.15,0.3,0.45,0.6,0.75,0.9 };

const std::vector<RealVector2D> WalkingLocations2 = { {296,147} };//x,y
const std::vector <double> WalkingTimes2 = { 1 };

const std::vector<RealVector2D> WalkingLocations3 = { {296,147} };//x,y
const std::vector <double> WalkingTimes3 = { 1 };

const std::vector<RealVector2D> WalkingLocations4 = { {393,98} };//x,y
const std::vector <double> WalkingTimes4 = { 1 };

const std::vector<RealVector2D> AttackLocations1 = { {295,98},{393,98}, {344,147}, {344,147} };
const std::vector <double> AttackTimes1 = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> AttackLocations2 = { {246,98},{295,98}, {344,147}, {344,147} };
const std::vector <double> AttackTimes2 = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> JumpingLocations = { {197,147}, {393,98}, {197,147} };
const std::vector <double> JumpingTimes = { 0.2,1.0,1.2 };

const std::vector<RealVector2D> RunningLocations1 = { {246,145}, {393,101}, {246,145}, {442,145} };
const std::vector <double> RunningTimes1 = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> RunningLocations2 = { {248,142}, {444,146}, {248,142},  {395,98} };
const std::vector <double> RunningTimes2 = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> RunningLocations3 = { {197,147} };
const std::vector <double> RunningTimes3 = { 1 };

const std::vector<RealVector2D> RunningLocations4 = { {246,142}, {442,142}, {246,142},  {393,98} };
const std::vector <double> RunningTimes4 = { 0.15,0.3,0.45,0.6 };

const std::vector<RealVector2D> JumpingAttackLocations = { {295,98},{344,98}, {393,147},{393,147} };
const std::vector <double> JumpingAttackTimes = { 0.1,0.2,0.3,2 };

const std::vector<RealVector2D> Getting_HitLocations1 = { {197,147} };
const std::vector <double> Getting_HitTimes1 = { 1 };

const std::vector<RealVector2D> Getting_HitLocations2 = { {393,98} };
const std::vector <double> Getting_HitTimes2 = { 1 };

const std::vector<RealVector2D> SpecialAttackLocations = { {99,98} };
const std::vector <double> SpecialAttackTimes = { 1 };


const std::vector<RealVector2D> InAirLocations = { {442,0}, {197,49}, {246,49}, {295,49}, {344,49}, {393,49}, {442,49}, {0,0}, {49,0}, {98,0}, {147,0}, {196,0}, {245,0}, {294,0}, {343,0}, {392,0} }; //x,y
const std::vector <double> InAirTimes = { 0.02,0.04,0.06,0.08,0.1,0.12,0.14,0.16,0.18,0.2,0.22,0.24,0.26,0.28,0.3,0.32 };

const std::vector<RealVector2D> OnFloorLocations = { {293,0} }; //x,y
const std::vector <double> OnFloorTimes = { 1 };

const std::vector<RealVector2D> DashLocations = { {197,147} };
const std::vector<double> DashTimes = { {1} };

const std::vector<RealVector2D> WobbleLocations = { {393,49},{295,49} };
const std::vector<double> WobbleTimes = { 0.15,0.3 };

IceSword::IceSword(){

	if (IceSowrdTexFile.getSize() == sf::Vector2u(0, 0)) {
		IceSowrdTexFile.loadFromFile("Resource/IceSwN.png");
	};
	OnFloorSheet.AssignPlayer(this);
	IdleSheet[0].AssignPlayer(this);
	IdleSheet[1].AssignPlayer(this);
	IdleSheet[2].AssignPlayer(this);
	IdleSheet[3].AssignPlayer(this);
	WalkingSheet[0].AssignPlayer(this);
	WalkingSheet[1].AssignPlayer(this);
	WalkingSheet[2].AssignPlayer(this);
	WalkingSheet[3].AssignPlayer(this);
	RunningSheet[0].AssignPlayer(this);
	RunningSheet[1].AssignPlayer(this);
	RunningSheet[2].AssignPlayer(this);
	RunningSheet[3].AssignPlayer(this);
	JumpingSheet.AssignPlayer(this);
	DashSheet.AssignPlayer(this);
	HittingSheet[0].AssignPlayer(this);
	HittingSheet[1].AssignPlayer(this);
	JumpAttackSheet.AssignPlayer(this);
	InAirSheet.AssignPlayer(this);
	GettingHitSheet[0].AssignPlayer(this);
	GettingHitSheet[1].AssignPlayer(this);
	SpecialAttackSheet.AssignPlayer(this);
	WobbleSheet.AssignPlayer(this);

	OnFloorSheet.AssignTextures(IceSowrdTexFile, OnFloorLocations, OnFloorTimes, -47, 47);
	IdleSheet[0].AssignTextures(IceSowrdTexFile, IdleLocations1, IdleTimes1, 47, 47);
	IdleSheet[1].AssignTextures(IceSowrdTexFile, IdleLocations2, IdleTimes2, 47, 47);
	IdleSheet[2].AssignTextures(IceSowrdTexFile, IdleLocations3, IdleTimes3, 47, 47);
	IdleSheet[3].AssignTextures(IceSowrdTexFile, IdleLocations4, IdleTimes4, 47, 47);
	WalkingSheet[0].AssignTextures(IceSowrdTexFile, WalkingLocations1, WalkingTimes1, 47, 47);
	WalkingSheet[1].AssignTextures(IceSowrdTexFile, WalkingLocations2, WalkingTimes2, 47, 47);
	WalkingSheet[2].AssignTextures(IceSowrdTexFile, WalkingLocations3, WalkingTimes3, 47, 47);
	WalkingSheet[3].AssignTextures(IceSowrdTexFile, WalkingLocations4, WalkingTimes4, 47, 47);
	RunningSheet[0].AssignTextures(IceSowrdTexFile, RunningLocations1, RunningTimes1, 47, 47);
	RunningSheet[1].AssignTextures(IceSowrdTexFile, RunningLocations2, RunningTimes2, 47, 47);
	RunningSheet[2].AssignTextures(IceSowrdTexFile, RunningLocations3, RunningTimes3, 47, 47);
	RunningSheet[3].AssignTextures(IceSowrdTexFile, RunningLocations4, RunningTimes4, 47, 47);
	JumpingSheet.AssignTextures(IceSowrdTexFile, JumpingLocations, JumpingTimes, 47, 47);
	DashSheet.AssignTextures(IceSowrdTexFile, DashLocations, DashTimes, 47, 47);
	HittingSheet[0].AssignTextures(IceSowrdTexFile, AttackLocations1, AttackTimes1, 47, 47);
	HittingSheet[1].AssignTextures(IceSowrdTexFile, AttackLocations2, AttackTimes2, 47, 47);
	JumpAttackSheet.AssignTextures(IceSowrdTexFile, JumpingAttackLocations, JumpingAttackTimes, 47, 47);
	InAirSheet.AssignTextures(IceSowrdTexFile, InAirLocations, InAirTimes, 47, 47);
	GettingHitSheet[0].AssignTextures(IceSowrdTexFile, Getting_HitLocations1, Getting_HitTimes1, 47, 47);
	GettingHitSheet[1].AssignTextures(IceSowrdTexFile, Getting_HitLocations2, Getting_HitTimes2, 47, 47);
	SpecialAttackSheet.AssignTextures(IceSowrdTexFile, SpecialAttackLocations, SpecialAttackTimes, 47, 47);
	WobbleSheet.AssignTextures(IceSowrdTexFile, WobbleLocations, WobbleTimes, 47, 47);

	AttackHitBox.Type = HB_TYPE_ICE;
	HittingSheet[0].AssignHitbox(2, { 5.0f,0.f }, 40, 25);
	HittingSheet[1].AssignHitbox(2, { 5.0f,0.f }, 40, 25);
	JumpAttackSheet.AssignHitbox(2, { 5.0f,0.f }, 40, 25);
}
