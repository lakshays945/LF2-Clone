#include "IceBerg.h"

sf::Texture IceBergTexFile;

const std::vector<RealVector2D> InitialLocations1 = { {0,0},{110,0},{220,0}, {330,0}, {440,0}, {550,0} }; //108 x 108
const std::vector <double> InitialTimes1 = { 0.05,0.1,0.15,0.2,0.25,6 };

const std::vector<RealVector2D> InitialLocations2 = { {0,110},{110,110},{220,110}, {330,110},{440,110}, {550,110} }; //108 x 108
const std::vector <double> InitialTimes2 = { 0.05,0.1,0.15,0.2,0.25,6 };

const std::vector<RealVector2D> InitialLocations3 = { {0,220},{110,220},{220,220}, {330,220},{440,220}, {550,220} }; //108 x 108
const std::vector <double> InitialTimes3 = { 0.05,0.1,0.15,0.2,0.25,6 };

const std::vector<RealVector2D> EndLocations1 = { {0,83},{82,83},{164,83},{246,83} };
const std::vector <double> EndTimes1 = { 0.05,0.1,0.15,0.2 };

IceBerg::IceBerg() {
	IsActive = false;
	if (IceBergTexFile.getSize() == sf::Vector2u(0, 0)) {
		IceBergTexFile.loadFromFile("Resource/FreezeIceBerg.png");
	}
	InitialSheet.OneTime = true;
	EndSheet.OneTime = true;
	CurrentSheet = &InitialSheet;
}

void IceBerg::SetIceTextures(int index) {
	Index = index;
	if (index == 1) {
		InitialSheet.AssignTextures(IceBergTexFile, InitialLocations1, InitialTimes1, 108, 108);
	}
	else if (index == 2) {
		InitialSheet.AssignTextures(IceBergTexFile, InitialLocations2, InitialTimes2, 108, 108);
	}
	else {
		InitialSheet.AssignTextures(IceBergTexFile, InitialLocations3, InitialTimes3, 108, 108);
	}
}

void IceBerg::Instantiate(RealVector2D position) {
	IsActive = true;
	CurrentSheet = &InitialSheet;
	Position = position;
	Z_Position = Position.get_y();
	InitialSheet.Time = 0;
	EndSheet.Time = 0;
	Direction = Parent->Direction;
	TotalTime = 0;
	if (Index == 3) {
		Wall->Direction = Direction;
		Wall->Instantiate(position-RealVector2D(15*Direction,0));
		Wall->WallHitBox.SetSize(50, 135);
		Wall->AttackHitBox.SetSize(50, 135);
		Wall->AttackHitBox.Center = Position - RealVector2D(20*Direction,0);
		Wall->ActiveBergs[2] = 1;
	}
	else if (Index == 2) {
		Wall->Instantiate(position - RealVector2D(25 * Direction, 0));
		Wall->ActiveBergs[1] = 1;
		Wall->WallHitBox.SetSize(110, 135);
		Wall->AttackHitBox.Center = Position;
		Wall->AttackHitBox.SetSize(80, 135);
	}
	else {
		DEBUG_INFO("SPAWNED");
		Wall->ActiveBergs[0] = 1;
		if (Wall->ActiveBergs[2]) {
			Wall->Instantiate(position - RealVector2D(50 * Direction, 0));
			Wall->WallHitBox.SetSize(170, 135);
		}
		else if(!Wall->ActiveBergs[1] && !Wall->ActiveBergs[2]) {
			Wall->Instantiate(position - RealVector2D(10 * Direction, 0));
			Wall->WallHitBox.SetSize(90, 135);
		}
		else {
			Wall->Instantiate(position - RealVector2D(30 * Direction, 0));
			Wall->WallHitBox.SetSize(140, 135);
		}
		Wall->AttackHitBox.Center = Position;
		Wall->AttackHitBox.SetSize(80, 135);
		Wall->IsSetActive = true;
	}
}

void IceBerg::GoBack() {
	if (Index == 1) {
		DEBUG_INFO("Destroyed");
	}
	IsActive = false;
	Position = Parent->Position;
	Wall->ReduceSize(Index);
}

void IceBerg::AssignParent(GameObject* parent) {
	Parent = parent;
}

void IceBerg::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			GoBack();
			return;
		}
	}
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	current->setScale(Scale.get_x() * Direction, Scale.get_y());
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
}

void IceBerg::OnCollision(int otherID, int selfID) {
}

void IceBerg::AssignWall(IceBergWall* wall) {
	Wall = wall;
	Wall->IceBergArray[Index-1] = this;
}

IceBergWall::IceBergWall() {
	IsActive = false;
	WallHitBox.IsActive = false;
	AttackHitBox.IsActive = false;
	WallHitBox = HitBox(Position, 100, 100, HB_TYPE_WALL);
	AttackHitBox = HitBox(Position, 30, 30, HB_TYPE_ICE);
}

void IceBergWall::GoBack() {
	IsSetActive = false;
	IsActive = false;
	WallHitBox.IsActive = false;
	AttackHitBox.IsActive = false;
	Position = Parent->Position;
}

void IceBergWall::Instantiate(RealVector2D position) {
	TotalTime = 0;
	
	IsActive = true;
	WallHitBox.IsActive = true;
	AttackHitBox.IsActive = true;
	Position = position;
	Z_Position = Position.get_y() + 20.0;
	WallHitBox.Center = Position;
	AttackHitBox.Center = Position;
	AttackHitBox.SetSize(50, 135);
	WallHitBox.SetSize(50, 135);
}

void IceBergWall::ReduceSize(int index) {
	index--;
	ActiveBergs[index] = false;
	if (index == 2) {
		if (ActiveBergs[0] && ActiveBergs[1]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(20 * Direction, 0);
			DEBUG_INFO("HERE");
			WallHitBox.SetSize(135, 135);
		}
		else if (!ActiveBergs[0] && ActiveBergs[1]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(18 * Direction, 0);
			WallHitBox.SetSize(87, 135);
		}
		else {
			GoBack();
		}
	}
	else if (index == 1) {
		if (ActiveBergs[2]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(-30 * Direction, 0);
			WallHitBox.SetSize(50, 135);
		}
		else if (ActiveBergs[0]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(25 * Direction, 0);
			WallHitBox.SetSize(90, 135);
		}
		else {
			GoBack();
		}
	}
	else {
		if (ActiveBergs[2] && ActiveBergs[1]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(-35 * Direction, 0);
			WallHitBox.SetSize(110, 135);
		}
		else if (ActiveBergs[1] && !ActiveBergs[2]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(-30 * Direction, 0);
			WallHitBox.SetSize(66, 135);
		}
		else if (!ActiveBergs[1] && ActiveBergs[2]) {
			WallHitBox.Center = WallHitBox.Center + RealVector2D(-60 * Direction, 0);
			WallHitBox.SetSize(66, 135);
		}
		else {
			GoBack();
		}
	}
}

void IceBergWall::AssignParent(GameObject* parent) {
	Parent = parent;
	AttackHitBox.IgnoreObjectID = Parent->ID;
}

void IceBergWall::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if (TotalTime > 0.3) {
		AttackHitBox.Center = Parent->Position;
		AttackHitBox.IsActive = false;
	}
	if (!IceBergArray[0] && !IceBergArray[1] && !IceBergArray[2]) {
		GoBack();
	}
	WallHitBox.DrawBox(window);
	AttackHitBox.DrawBox(window);
}

void IceBergWall::OnCollision(int otherID, int selfID) {
	HitBoxType otherType = HitBoxIDArray[otherID]->Type;
	if (HitBoxIDArray[selfID]->Type == HB_TYPE_WALL) {
		CanCollide[otherID][selfID] = true;
		CanCollide[selfID][otherID] = true;
	}
	if ((otherType == HB_TYPE_FIRE || otherType == HB_TYPE_ATTACK || otherType == HB_TYPE_ICE) && HitBoxIDArray[otherID]->Game_Object != this) {
		if (HitBoxIDArray[selfID]->Type == HB_TYPE_ICE) {
			return;
		}
		if (HitBoxIDArray[otherID]->Game_Object->Direction*Direction == -1) {
			for (int i = 0; i < 3; i++) {
				if (IceBergArray[i]->IsActive) {
					IceBergArray[i]->GoBack();
					break;
				}
			}
		}
		else {
			for (int i = 2; i >= 0; i--) {
				DEBUG_INFO("other ID = {}", otherID);
				DEBUG_INFO("self ID = {}", selfID);
				if (IceBergArray[i]->IsActive) {
					IceBergArray[i]->GoBack();
					break;
				}
			}
		}
	}
}