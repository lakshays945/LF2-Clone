#include "FirenGroundFire.h"
#include "Firen.h"
sf::Texture GroundFireTexFile;


const std::vector<RealVector2D> InitialLocations = { {108, 150}, {72,150}, {36,150}, {0,150},{108, 100}, {72,100}, {36,100}, {0,100} }; //34 x 48
const std::vector<double> InitialTimes = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4 };

const std::vector<RealVector2D> BurnLocations = { {0,0}, {36,0}, {72,0}, {108,0},{0,50}, {36,50}, {72,50}, {108,50} }; //34 x 48
const std::vector<double> BurnTimes = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4 };

const std::vector<RealVector2D> EndLocations = { {0,100}, {36,100}, {72,100}, {108, 100}, {0,150}, {36,150}, {72,150}, {108, 150} }; //34 x 48
const std::vector<double> EndTimes = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8 };

FirenGroundFire::FirenGroundFire() {
	IsActive = false;
	if (GroundFireTexFile.getSize() == sf::Vector2u(0, 0)) {
		GroundFireTexFile.loadFromFile("Resource/FirenGroundFire.png");
	}
	InitialSheet.AssignTextures(GroundFireTexFile, InitialLocations, InitialTimes, 32, 48);
	InitialSheet.AssignPlayer(this);
	BurnSheet.AssignTextures(GroundFireTexFile, BurnLocations, BurnTimes, 32, 48);
	BurnSheet.AssignPlayer(this);
	EndSheet.AssignTextures(GroundFireTexFile, EndLocations, EndTimes, 32, 48);
	EndSheet.AssignPlayer(this);
	InitialSheet.OneTime = true;
	EndSheet.OneTime = true;
}

void FirenGroundFire::AssignParent(GameObject* parent) {
	Parent = parent;
	Scale = Scale * parent->Scale;
	Effect_Manager = parent->Effect_Manager;
}

void FirenGroundFire::SetScale(RealVector2D scale) {
	Scale = scale;
	InitialSheet.SetScale(Scale);
	BurnSheet.SetScale(Scale);
	EndSheet.SetScale(Scale);
}

void FirenGroundFire::Instantiate(RealVector2D position) {
	if (Parent->Scale != Scale) {
		SetScale(Parent->Scale);
	}
	Direction = Parent->Direction;
	TotalTime = 0;
	IsActive = true;
	Position = position;
	Z_Position = Position.get_y();
	InitialSheet.Time = 0;
	BurnSheet.Time = 0;
	EndSheet.Time = 0;
	CurrentSheet = &InitialSheet;
}

void FirenGroundFire::Animate(sf::RenderWindow &window, const double dt) {
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if ((MaxTime < TotalTime) && CurrentSheet != &EndSheet) {
		CurrentSheet = &EndSheet;
	}
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			CurrentSheet = &BurnSheet;
			CorrectIndex = 0;
		}
		else {
			GoBack();
			return;
		}
	}
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	current->setScale(Scale.get_x() * Direction, Scale.get_y());
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
	//AttackHitBox.DrawBox(window);
}

void FirenGroundFire::GoBack() {
	IsActive = false;
	Position = Parent->Position;
}

void FirenGroundFire::OnCollision(int otherID, int selfID) {

}

GroundFireHitBox::GroundFireHitBox() {
	IsActive = false;
	AttackHitBox = HitBox(Position, 25, 25, HB_TYPE_FIRE);
	AttackHitBox.KnockOutPower = 200;
}

void GroundFireHitBox::AssignParent(Firen* parent) {
	Parent = parent;
	AttackHitBox.IgnoreObjectID = Parent->ID;
	ParentSpeed = Parent->FireRunSpeed;
	SpawnRate = Parent->FireRunSpawnRate;
}

void GroundFireHitBox::Instantiate(RealVector2D position) {
	TotalTime = 0;
	IsActive = true;
	Position = position;
	Z_Position = Position.get_y();
	AttackHitBox.IsActive = true;
	AttackHitBox.SetSize(30, 30);
	Velocity = Parent->Velocity*(0.5);
	Direction = Parent->Direction;
	Stopped = false;
	Extinguished = 0;
	Spawned = 0;
}

void GroundFireHitBox::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	if (!Stopped) {
		Position = Position + Velocity * dt;
	}
	TotalTime += dt;
	if (TotalTime > MaxTime+0.8 + SpawnRate * Extinguished) {
		Extinguished++;
		Position = Position + RealVector2D((Direction * ParentSpeed * SpawnRate) / 2.0, 0);
		if (Stopped) {
			AttackHitBox.SetSize(ParentSpeed * SpawnRate * (Spawned - Extinguished), 10);
		}
	}
	AttackHitBox.Center = Position;
	if (TotalTime > Spawned * SpawnRate && !Stopped) {
		Spawned++;
		AttackHitBox.SetSize(Parent->FireRunSpeed * Parent->FireRunSpawnRate * (Spawned-Extinguished), 10);
	}
	if (Spawned == Extinguished && Stopped) {
		AttackHitBox.IsActive = false;
		IsActive = false;
	}
	if (Parent->CurrentState != SPECIALATTACK2) {
		Stopped = true;
	}
	AttackHitBox.DrawBox(window);
}

void GroundFireHitBox::OnCollision(int otherID, int selfID) {

}