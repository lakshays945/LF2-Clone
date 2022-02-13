#include "DavisBlueBall.h"

sf::Texture DavisBlueBallTexFile;

const std::vector<RealVector2D> InitialLocations = { {25,0},{107,0},{189,0}, {271,0} };//52 x 46
const std::vector <double> InitialTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> FastModeLocations = { {7,96},{86,96} };//73 x 42
const std::vector <double> FastModeTimes = { 0.15,0.3 };

const std::vector<RealVector2D> EndLocations = { {25,48},{107,48},{189,48},{271,48} };
const std::vector <double> EndTimes = { 0.05,0.1,0.15,0.2 };

DavisBlueBall::DavisBlueBall() {
	IsActive = false;
	if (DavisBlueBallTexFile.getSize() == sf::Vector2u(0, 0)) {
		DavisBlueBallTexFile.loadFromFile("Resource/DavisBlueBall.png");
	}
	InitialSheet.AssignTextures(DavisBlueBallTexFile, InitialLocations, InitialTimes, 52, 46);
	InAirSheet.AssignTextures(DavisBlueBallTexFile, InitialLocations, InitialTimes, 52, 46);
	EndSheet.AssignTextures(DavisBlueBallTexFile, EndLocations, EndTimes, 52, 44);
	FastSheet.AssignTextures(DavisBlueBallTexFile, FastModeLocations, FastModeTimes,73,42);
	AttackHitBox = HitBox(Position, 60, 25, HB_TYPE_ATTACK);
	ReboundHitBox = HitBox(Position, 70, 25, HB_TYPE_REBOUND);
	MaxStrength = 150;
	AttackHitBox.Damage = 30;
	CurrentStrength = MaxStrength;
}

void DavisBlueBall::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	Position = Position + Velocity * dt;
	if (Position.get_x() < -10 || Position.get_x() > 1300) {
		GoBack();
		return;
	}
	AttackHitBox.Center = Position;
	ReboundHitBox.Center = Position + RealVector2D(Direction * 10, 0);
	Z_Position = Position.get_y();
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			CurrentSheet = &FastSheet;
			Velocity =RealVector2D(Velocity.get_x() * 1.2,Velocity.get_y());
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

void DavisBlueBall::OnCollisionExit(int otherID, int selfID)
{
}

void DavisBlueBall::OnCollision(int otherID, int selfID) {
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (other->Game_Object->ID != self->IgnoreObjectID && other->Game_Object->ID != self->Game_Object->ID) {
		if ((other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && self->Type == HB_TYPE_ATTACK) {
			if (other->Type == HB_TYPE_WALL) {
				AttackHitBox.Disable();
				ReboundHitBox.Disable();
			}
			CurrentSheet = &EndSheet;
			Velocity.SetMagnitude(0);
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
		else if (other->Type == HB_TYPE_ATTACK && self->Type == HB_TYPE_REBOUND && (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character || (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Weapon))) {
			ReboundHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			AttackHitBox.IgnoreObjectID = HitBoxIDArray[otherID]->Game_Object->ID;
			Rebound();
		}
	}
}