#include "FirenFireBall.h"

sf::Texture FirenFireBallTexFile;

const std::vector<RealVector2D> InitialLocations = { {10,15},{92,15},{172,15}, {255,15} };//76 x 54
const std::vector <double> InitialTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> EndLocations = { {24,177},{101,174},{188,173},{278,174} }; //64 x 64
const std::vector <double> EndTimes = { 0.05,0.1,0.15,0.2 };


FirenFireBall::FirenFireBall() {
	IsActive = false;
	if (FirenFireBallTexFile.getSize() == sf::Vector2u(0, 0)) {
		FirenFireBallTexFile.loadFromFile("Resource/FirenFireBall.png");
	}
	InitialSheet.AssignTextures(FirenFireBallTexFile, InitialLocations, InitialTimes, 68, 54);
	InAirSheet.AssignTextures(FirenFireBallTexFile, InitialLocations, InitialTimes, 68, 54);
	EndSheet.AssignTextures(FirenFireBallTexFile, EndLocations, EndTimes, 64, 64);
	FastSheet.AssignTextures(FirenFireBallTexFile, InitialLocations, InitialTimes, 76, 54);
	AttackHitBox = HitBox(Position, 60, 25, HB_TYPE_FIRE);
	ReboundHitBox = HitBox(Position, 70, 25, HB_TYPE_REBOUND);
	AttackHitBox.KnockOutPower = 300;
	InitialSheet.OneTime = true;
	EndSheet.OneTime = true;
	MaxStrength = 150;
	AttackHitBox.Damage = 45;
	CurrentStrength = MaxStrength;
}

void FirenFireBall::Animate(sf::RenderWindow& window, const double dt) {
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

void FirenFireBall::OnCollision(int otherID, int selfID) {
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (other->Game_Object->ID != self->IgnoreObjectID && other->Game_Object->ID != self->Game_Object->ID) {
		if ((other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && self->Type == HB_TYPE_FIRE) {
			if (other->Type == HB_TYPE_WALL) {
				AttackHitBox.Disable();
			}
			CurrentSheet = &EndSheet;
			AttackHitBox.IgnoreObjectID = -1;
			Velocity.SetMagnitude(0);
		}
		else if (other->Game_Object->GO_Type == GO_Projectile && (other->Type == HB_TYPE_ATTACK || other->Type == HB_TYPE_FIRE || other->Type == HB_TYPE_ICE) && self->Type == HB_TYPE_FIRE) {
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
	}
}

void FirenFireBall::OnCollisionExit(int otherID, int selfID)
{
}
