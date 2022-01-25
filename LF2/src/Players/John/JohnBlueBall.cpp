#include "JohnBlueBall.h"

sf::Texture JohnBallTexFile;

const std::vector<RealVector2D> InAirLocations = { {0,0},{83,0},{165,0}, {247,0} };//52 x 46
const std::vector <double> InAirTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> EndLocations = { {328,84},{410,84},{492,84},{574,84} };
const std::vector <double> EndTimes = { 0.05,0.1,0.15,0.2 };

JohnBlueBall::JohnBlueBall() {
	IsActive = false;
	if (JohnBallTexFile.getSize() == sf::Vector2u(0, 0)) {
		JohnBallTexFile.loadFromFile("Resource/JohnBall.png");
	}
	InitialSheet.AssignTextures(JohnBallTexFile, InAirLocations, InAirTimes, 80, 80);
	InAirSheet.AssignTextures(JohnBallTexFile, InAirLocations, InAirTimes, 80, 80);
	FastSheet.AssignTextures(JohnBallTexFile, InAirLocations, InAirTimes, 80, 80);
	EndSheet.AssignTextures(JohnBallTexFile, EndLocations, EndTimes, 80, 75);
	AttackHitBox = HitBox(Position, 30, 25, HB_TYPE_ATTACK);
	ReboundHitBox = HitBox(Position, 45, 25, HB_TYPE_REBOUND);
	MaxStrength = 150;
	CurrentStrength = MaxStrength;
}

void JohnBlueBall::Animate(sf::RenderWindow& window, const double dt){
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
	Z_Position = Position.get_y() + 1;
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

void JohnBlueBall::OnCollision(int otherID, int selfID){
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (other->Game_Object->ID != self->IgnoreObjectID && other->Game_Object->ID != self->Game_Object->ID) {
		if ((other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && self->Type == HB_TYPE_ATTACK) {
			if (other->Type == HB_TYPE_WALL) {
				AttackHitBox.Disable();
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

void JohnBlueBall::OnCollisionExit(int otherID, int selfID)
{
}
