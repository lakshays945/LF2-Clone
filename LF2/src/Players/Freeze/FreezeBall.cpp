#include "FreezeBall.h"

sf::Texture FreezeBallTexFile;

const std::vector<RealVector2D> InAirLocations = { {0,0},{84,0},{166,0}, {248,0} };//80 x 81
const std::vector <double> InAirTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> EndLocations = { {0,83},{82,83},{164,83},{246,83} };
const std::vector <double> EndTimes = { 0.05,0.1,0.15,0.2 };

FreezeBall::FreezeBall() {
	if (FreezeBallTexFile.getSize() == sf::Vector2u(0, 0)) {
		FreezeBallTexFile.loadFromFile("Resource/FreezeBall.png");
	}
	InitialSheet.AssignTextures(FreezeBallTexFile, InAirLocations, InAirTimes, 75, 81);
	InAirSheet.AssignTextures(FreezeBallTexFile, InAirLocations, InAirTimes, 75, 81);
	FastSheet.AssignTextures(FreezeBallTexFile, InAirLocations, InAirTimes, 75, 81);
	EndSheet.AssignTextures(FreezeBallTexFile, EndLocations, EndTimes, 75, 81);
	AttackHitBox = HitBox(Position, 30, 25, HB_TYPE_ICE);
	ReboundHitBox = HitBox(Position, 45, 25, HB_TYPE_REBOUND);
	MaxStrength = 150;
	CurrentStrength = MaxStrength;
	AttackHitBox.Damage = 40;
}

void FreezeBall::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	Position = Position + Velocity * dt;
	if (Position.get_x() < -10 || Position.get_x() > 1300) {
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

void FreezeBall::OnCollision(int otherID, int selfID) {
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (other->Game_Object->ID != self->IgnoreObjectID && other->Game_Object->ID != self->Game_Object->ID) {
		if ((other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && self->Type == HB_TYPE_ICE) {
			if (other->Type == HB_TYPE_WALL) {
				AttackHitBox.Disable();
			}
			CurrentSheet = &EndSheet;
			Velocity.SetMagnitude(0);
		}
		else if (other->Game_Object->GO_Type == GO_Projectile && (other->Type == HB_TYPE_ATTACK || other->Type == HB_TYPE_FIRE || other->Type == HB_TYPE_ICE) && self->Type == HB_TYPE_ICE) {
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
		else if (other->Type == HB_TYPE_ATTACK && self->Type == HB_TYPE_REBOUND && (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character || (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Weapon))) {
			ReboundHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			AttackHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			Rebound();
		}
	}
}

void FreezeBall::OnCollisionExit(int otherID, int selfID)
{
}
