#include "DennisBlueBall.h"

sf::Texture BlueBallTexFile;

const std::vector<RealVector2D> InAirLocations = { {25,0},{107,0},{189,0}, {271,0} };//52 x 46
const std::vector <double> InAirTimes = { 0.1,0.2,0.3,0.4 };

const std::vector<RealVector2D> EndLocations = { {25,48},{107,48},{189,48},{271,48} };
const std::vector <double> EndTimes = { 0.05,0.1,0.15,0.2 };

DennisBlueBall::DennisBlueBall() {
	IsActive = false;
	if (BlueBallTexFile.getSize() == sf::Vector2u(0, 0)) {
		BlueBallTexFile.loadFromFile("Resource/DennisBall.png");
	}
	InAirSheet.AssignTextures(BlueBallTexFile, InAirLocations, InAirTimes, 52, 46);
	InAirSheet.AssignPlayer(this);
	EndSheet.AssignTextures(BlueBallTexFile, EndLocations, EndTimes, 52, 44);
	EndSheet.AssignPlayer(this);
	EndSheet.OneTime = true;
	CurrentSheet = &InAirSheet;
	AttackHitBox = HitBox(Position, 30, 25, TYPE_ATTACK);
}

void DennisBlueBall::AssignParent(GameObject* parent) {
	Parent = parent;
	Effect_Manager = parent->Effect_Manager;
}

void DennisBlueBall::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	Position = Position + Velocity * dt;
	if (Position.get_x() < -10 || Position.get_x() > 1300) {
		GoBack();
		return;
	}
	AttackHitBox.Center = Position;
	Z_Position = Position.get_y();
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		GoBack();
		return;
	}
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	if (Velocity.get_x() < 0) {
		Direction = -1;
	}
	else if (Velocity.get_x() > 0) {
		Direction = 1;
	}
	current->setScale(sf::Vector2f((float)Direction, 1.0f));
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
	AttackHitBox.DrawBox(window);
}

void DennisBlueBall::GoBack() {
	IsActive = false;
	Position = Parent->Position;
	Velocity = { 0,0 };
	AttackHitBox.IsActive = false;
}

void DennisBlueBall::Instantiate(RealVector2D velocity) {
	Position = Parent->Position;
	InAirSheet.Time = 0;
	EndSheet.Time = 0;
	IsActive = true;
	Velocity = velocity;
	CurrentSheet = &InAirSheet;
	AttackHitBox.IsActive = true;
}

void DennisBlueBall::OnCollision(int otherID, int selfID) {
	if (HitBoxIDArray[otherID]->Type == TYPE_DAMAGE && HitBoxIDArray[otherID]->Game_Object != Parent) {
		CurrentSheet = &EndSheet;
		Velocity.SetMagnitude(0);
	}
}