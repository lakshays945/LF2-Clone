#include "ChaseBall.h"

sf::Texture ChaseBallTexFile;

const std::vector<RealVector2D> InitialLocations = { {0,0} };
const std::vector<double> InitialTimes = { 0.2 };

const std::vector <RealVector2D> ChaseModeLocations = { {90,0},{171,0} };
const std::vector <double> ChaseModeTimes = { 0.2,0.4 };

const std::vector <RealVector2D> EndLocations = { {25,85},{105,85}, {185,85}, {265,85} };
const std::vector <double> EndTimes = { 0.05,0.1,0.15,0.2 };

const std::vector <RealVector2D> FastModeLocations = {{254,0}};
const std::vector <double> FastModeTimes = {1};

ChaseBall::ChaseBall() {
	IsActive = false;
	if (ChaseBallTexFile.getSize() == sf::Vector2u(0, 0)) {
		ChaseBallTexFile.loadFromFile("Resource/ChaseBall.png");
	}
	InitialSheet.AssignTextures(ChaseBallTexFile, InitialLocations, InitialTimes, 75, 75);
	InAirSheet.AssignTextures(ChaseBallTexFile, ChaseModeLocations, ChaseModeTimes, 65, 75);
	FastSheet.AssignTextures(ChaseBallTexFile, FastModeLocations, FastModeTimes, 66, 80);
	EndSheet.AssignTextures(ChaseBallTexFile, EndLocations, EndTimes, 55, 80);
	CurrentSheet = &InitialSheet;
	AttackHitBox = HitBox(Position, 40, 40, HB_TYPE_ATTACK);
	ReboundHitBox = HitBox(Position, 40, 40, HB_TYPE_REBOUND);
	AttackHitBox.KnockOutPower = 300;
	MaxStrength = 300;
	CurrentStrength = MaxStrength;
}

bool ChaseBall::SetTarget() {
	TotalTime = 0;
	Target = nullptr;
	int index = -1;
	double minDist = INT16_MAX;
	for (int i = 0; i < CharacterIDArray.size(); i++) {
		if (CharacterIDArray[i]->IsActive && minDist > Parent->Position.DistanceFrom(CharacterIDArray[i]->Position) && CharacterIDArray[i]->ID != Parent->ID) {
			minDist = Parent->Position.DistanceFrom(CharacterIDArray[i]->Position);
			index = i;
		}
	}
	if (index == -1) {
		DEBUG_WARNING("No Target");
		return false;
	}
	Target = CharacterIDArray[index];
	MeanY = (Target->Position.get_y() + Position.get_y()) / 2;
	BeforeMean = true;
	InitialY = Target->Position.get_y();
	Rebounded = false;
	return true;
}

void ChaseBall::CalculateVelocity(const double dt) {
	if (Target == nullptr) {
		DEBUG_WARNING("No Target for Dennis-ChaseBall");
		return;
	}
	if (TotalTime > 3.2 || Rebounded) {
		Velocity.SetMagnitude(600);
		return;
	}
	int mul;
	if (Target->Position.get_x() > Position.get_x()) {
		if (Velocity.get_x() > 0) {
			mul = 0;
		}
		else {
			mul = -1;
		}
	}
	else {
		if (Velocity.get_x() > 0) {
			mul = 1;
		}
		else {
			mul = 0;
		}
	}
	if (BeforeMean) {
		RealVector2D Acc =  RealVector2D(mul*400/(-log(abs(MeanY)+1)), MeanY - Position.get_y());
		Velocity = Velocity + Acc * 5 * dt;
		if (abs(Position.get_y()-InitialY) <= 10 && TotalTime > 0.7) {
			Velocity.Set({ Velocity.get_x(),0 });
			BeforeMean = false;
		}
	}
	else {
		Velocity = Velocity + (Target->Position-Position)*5*dt;
		if (Velocity.Magnitude() > 600) {
			Velocity.SetMagnitude(600);
		}
	}
}

void ChaseBall::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if (CurrentSheet != &EndSheet) {
		CalculateVelocity(dt);
	}
	Position = Position + Velocity * dt;
	if (Position.get_x() < -150 || Position.get_x() > 1350 || Position.get_y() < -150 || Position.get_y() > 950) {
		GoBack();
		return;
	}
	AttackHitBox.Center = Position;
	ReboundHitBox.Center = Position + RealVector2D(Direction * 15, 0);
	Z_Position = Position.get_y();
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			CurrentSheet = &InAirSheet;
			CorrectIndex = 0;
		}
		else {
			GoBack();
			return;
		}
	}

	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	if (Velocity.get_x() < 0) {
		Direction = -1;
	}
	else if (Velocity.get_x() > 0) {
		Direction = 1;
	}
	current->setScale(Scale.get_x() * Direction, Scale.get_y());
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
	AttackHitBox.DrawBox(window);
	ReboundHitBox.DrawBox(window);
}

void ChaseBall::OnCollision(int otherID, int selfID) {
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (other->Game_Object->ID != self->IgnoreObjectID && other->Game_Object->ID != self->Game_Object->ID) {

		if ((other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && self->Type == HB_TYPE_ATTACK) {
			if (other->Type == HB_TYPE_WALL) {
				AttackHitBox.IsActive = false;
			}
			CurrentSheet = &EndSheet;
			Velocity.SetMagnitude(0);
		}
		else if (other->Game_Object->GO_Type == GO_Projectile && (other->Type == HB_TYPE_ATTACK || other->Type == HB_TYPE_FIRE || other->Type == HB_TYPE_ICE) && self->Type == HB_TYPE_ATTACK) {
			ProjectileBall* ball = (ProjectileBall*)other->Game_Object;
			CurrentStrength -= ball->MaxStrength;
			if (CurrentStrength <= 0) {
				CurrentSheet = &EndSheet;
				Velocity.SetMagnitude(0);
			}
		}
		else if (other->Type == HB_TYPE_ATTACK && self->Type == HB_TYPE_REBOUND && HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character) {
			ReboundHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			AttackHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			Rebounded = true;
			Rebound();
		}
	}
}

