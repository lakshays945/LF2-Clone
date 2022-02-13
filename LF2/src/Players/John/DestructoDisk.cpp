#include "DestructoDisk.h"

sf::Texture DiskTexFile;

const std::vector<RealVector2D> Initialocations = { {0,21},{91,21},{273,21}}; //89 x 19
const std::vector <double> InitialTimes = { 0.1,0.2,0.3};

const std::vector<RealVector2D> InAirLocations = { {0,0},{91,0},{182,0}, {273,0} };
const std::vector <double> InAirTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> EndLocations = { {182,42},{273,42}};
const std::vector <double> EndTimes = { 0.1,0.2 };

DestructoDisk::DestructoDisk(){
	IsActive = false;
	if (DiskTexFile.getSize() == sf::Vector2u(0, 0)) {
		DiskTexFile.loadFromFile("Resource/DestructoDisk.png");
	}
	InitialSheet.AssignTextures(DiskTexFile, Initialocations, InitialTimes, 89, 19);
	InAirSheet.AssignTextures(DiskTexFile, InAirLocations, InAirTimes, 89, 19);
	EndSheet.AssignTextures(DiskTexFile, EndLocations, EndTimes, 89, 19);
	AttackHitBox = HitBox(Position, 60, 25, HB_TYPE_ATTACK);
	ReboundHitBox = HitBox(Position, 1, 1, HB_TYPE_REBOUND);
	AttackHitBox.KnockOutPower = 200;
	MaxStrength = 400;
	AttackHitBox.Damage = 70;
	CurrentStrength = MaxStrength;
}

void DestructoDisk::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if (CurrentSheet != &EndSheet) {
		CalculateVelocity(dt);
	}
	if (TotalTime > 0.8) {
		CalculateVelocity(dt);
		Position = Position + Velocity * dt;
	}
	else if (TotalTime > 0.3) {
		Position = Position + Velocity * dt;
	}
	if (Position.get_x() < -150 || Position.get_x() > 1350 || Position.get_y() < -150 || Position.get_y() > 950) {
		GoBack();
		return;
	}
	AttackHitBox.Center = Position;
	ReboundHitBox.Center = Position + RealVector2D(Direction * 15, 0);
	Z_Position = Position.get_y() + 20;
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

bool DestructoDisk::SetTarget(){
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
	Collided = false;
	return true;
}

void DestructoDisk::OnCollision(int otherID, int selfID){
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (other->Game_Object->ID != self->IgnoreObjectID && other->Game_Object->ID != self->Game_Object->ID) {

		if ((other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && self->Type == HB_TYPE_ATTACK) {
			if (other->Type == HB_TYPE_WALL) {
				Velocity.SetMagnitude(0);
				return;
			}
			Collided = true;
		}
		else if (other->Game_Object->GO_Type == GO_Projectile && (other->Type == HB_TYPE_ATTACK || other->Type == HB_TYPE_FIRE || other->Type == HB_TYPE_ICE) && self->Type == HB_TYPE_ATTACK) {
			ProjectileBall* ball = (ProjectileBall*)other->Game_Object;
			if (ball->AttackHitBox.IgnoreObjectID == AttackHitBox.IgnoreObjectID) {
				return;
			}
			CurrentStrength -= ball->MaxStrength;
			if (CurrentStrength <= 0) {
				CurrentSheet = &EndSheet;
				Velocity.SetMagnitude(0);
			}
		}
		/*else if (other->Type == HB_TYPE_ATTACK && self->Type == HB_TYPE_REBOUND && HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character) {
			ReboundHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			AttackHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			Rebound();
		}*/
	}
}

void DestructoDisk::OnCollisionExit(int otherID, int selfID)
{
}

void DestructoDisk::CalculateVelocity(const double dt){
	if (Target == nullptr) {
		DEBUG_WARNING("No Target for DestructoDisk");
		return;
	}
	RealVector2D acc = RealVector2D(1600,600);
	if (TotalTime > 2.2 || Rebounded || Collided) {
		if (Velocity.get_x() < 0) {
			acc = RealVector2D(-1600, 600);
		}
		if (Velocity.get_y() > 0) {
			acc = RealVector2D(0,-600);
		}
		Velocity = Velocity + acc * dt;
		if (Velocity.Magnitude() > 500) {
			Velocity.SetMagnitude(500);
		}
		return;
	}
	acc = Target->Position - Position - Velocity*0.2;
	acc.SetMagnitude(400);
	Velocity = Velocity + acc * dt;
	if (Velocity.Magnitude() > 400) {
		Velocity.SetMagnitude(400);
	}
}
