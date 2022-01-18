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
		WallHitBox = HitBox(Position,85, 135,HB_TYPE_WALL);
		AttackHitBox = HitBox(Position, 70, 135, HB_TYPE_ICE);
	}
	else if (index == 2) {
		InitialSheet.AssignTextures(IceBergTexFile, InitialLocations2, InitialTimes2, 108, 108);
		WallHitBox = HitBox(Position, 60, 135, HB_TYPE_WALL);
		AttackHitBox = HitBox(Position, 37, 135, HB_TYPE_ICE);
	}
	else {
		InitialSheet.AssignTextures(IceBergTexFile, InitialLocations3, InitialTimes3, 108, 108);
		WallHitBox = HitBox(Position, 50, 135, HB_TYPE_WALL);
		AttackHitBox = HitBox(Position, 46, 135, HB_TYPE_ICE);
	}
}

void IceBerg::Instantiate(RealVector2D position) {
	IsActive = true;
	CurrentSheet = &InitialSheet;
	Position = position;
	Z_Position = Position.get_y() + 20;
	InitialSheet.Time = 0;
	EndSheet.Time = 0;
	Direction = Parent->Direction;
	AttackHitBox.IsActive = true;
	WallHitBox.IsActive = true;
	AttackHitBox.Center = Position;
	WallHitBox.Center = Position;
	TotalTime = 0;
	if (Index == 3) {
		WallHitBox.Center = Position + RealVector2D(-Direction * 10, 0);
		AttackHitBox.Center = Position + RealVector2D(-Direction * 13, 0);
	}
	else if (Index == 2) {
		WallHitBox.Center = Position + RealVector2D(-Direction * 4, 0);
	}
	else {
		WallHitBox.Center = Position + RealVector2D(-Direction * 10, 0);
		AttackHitBox.Center = Position + RealVector2D(-Direction * 4, 0);
	}
}

void IceBerg::GoBack() {
	AttackHitBox.Disable();
	WallHitBox.Disable();
	IsActive = false;
	Position = Parent->Position;
}

void IceBerg::AssignParent(GameObject* parent) {
	Parent = parent;
	AttackHitBox.IgnoreObjectID = Parent->ID;
}

void IceBerg::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if (TotalTime > 0.3) {
		AttackHitBox.Center = Parent->Position;
		AttackHitBox.Disable();
	}
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
	AttackHitBox.DrawBox(window);
	WallHitBox.DrawBox(window);
}

void IceBerg::OnCollision(int otherID, int selfID) {
	HitBoxType otherType = HitBoxIDArray[otherID]->Type;
	if (HitBoxIDArray[selfID]->Type == HB_TYPE_WALL) {
		CanCollide[otherID][selfID] = true;
		CanCollide[selfID][otherID] = true;
	}
	if (HitBoxIDArray[selfID]->Type == HB_TYPE_ICE && otherType == HB_TYPE_DAMAGE && HitBoxIDArray[otherID]->Game_Object != Parent) {
		GameObject* goCollided = HitBoxIDArray[otherID]->Game_Object;
		if (goCollided->GO_Type == GO_Character) {
			if (Z_Position > goCollided->Z_Position) {
				goCollided->Position = goCollided->Position + RealVector2D(0, -26);
			}
			else {
				goCollided->Position = goCollided->Position + RealVector2D(0, 26);
			}
			goCollided->Z_Position = goCollided->Position.get_y();
			HitBoxIDArray[otherID]->Center = goCollided->Position;
		}
		return;
	}
	if ((otherType == HB_TYPE_FIRE || otherType == HB_TYPE_ATTACK || otherType == HB_TYPE_ICE) && HitBoxIDArray[otherID]->Game_Object != this) {
		if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character && abs(HitBoxIDArray[otherID]->Game_Object->Z_Position - Z_Position) > 23) {
			return;
		}
		GoBack();
	}
}
