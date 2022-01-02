#include "HitBox.h"

#define COLLISION_THRESHOLD 25

int HitBox::nextID = 0;

std::vector <HitBox*> HitBoxIDArray;
std::vector <std::vector< bool>> CanCollide;

HitBox::HitBox(RealVector2D center, double width, double height, HitBoxType type)
:Center(center), Width(width), Height(height) {
	Type = type;
	Box.setSize(sf::Vector2f(width, height));
	Box.setFillColor(sf::Color::Transparent);
	Box.setOutlineThickness(-2);
	Box.setOutlineColor(sf::Color(255, 0, 0));
	Box.setOrigin(sf::Vector2f(width / 2, height / 2));
	circle.setPosition(sf::Vector2f(center.get_x(), center.get_y()));
	circle.setFillColor(sf::Color(0, 0, 0, 255));
	circle.setRadius(1);
	//circle.setOrigin(sf::Vector2f(3.0 / 2, 3.0 / 2));
}

HitBox::HitBox() {
}

bool HitBox::JustCollided(HitBox* other) {
	if (abs(Center.get_x() - other->Center.get_x()) <= (Width + other->Width) / 2 && abs(Center.get_y() - other->Center.get_y()) <= (Height + other->Height) / 2) {
		if (!IsActive || !other->IsActive) {
			CanCollide[ID][other->ID] = true;
			CanCollide[other->ID][ID] = true;
			return false;
		}
		if (abs(Game_Object->Z_Position - other->Game_Object->Z_Position) > COLLISION_THRESHOLD) {
			CanCollide[ID][other->ID] = true;
			CanCollide[other->ID][ID] = true;
			return false;
		}
		if (!CanCollide[ID][other->ID]) {
			return false;
		}
		CanCollide[ID][other->ID] = false;
		CanCollide[other->ID][ID] = false;
		return true; //xyz
	}
	else {
		CanCollide[ID][other->ID] = true;
		CanCollide[other->ID][ID] = true;
	}
	return false;
}
void HitBox::AssignPlayer(GameObject* gameObject) {
	Game_Object = gameObject;
}

void HitBox::RegisterID() {
	ID = nextID;
	DEBUG_TRACE("HitBox with ID = {0} Registered", ID);
	nextID++;
	HitBoxIDArray.push_back(this);
	std::vector <bool> newRow;
	for (int i = 0; i < CanCollide.size(); i++) {
		CanCollide[i].push_back(true);
		newRow.push_back(true);
	}
	newRow.push_back(false);
	CanCollide.push_back(newRow);
}

void HandleCollisions() {
	for (int i = 0; i < HitBoxIDArray.size(); i++) {
		for (int j = i+1; j < HitBoxIDArray.size(); j++) {
			if (HitBoxIDArray[i]->JustCollided(HitBoxIDArray[j])) {
				// j is ID and i is also ID
				if (HitBoxIDArray[i]->IgnoreObjectID != HitBoxIDArray[j]->Game_Object->ID) {
					HitBoxIDArray[j]->Game_Object->OnCollision(i, j);
				}
				if (HitBoxIDArray[j]->IgnoreObjectID != HitBoxIDArray[i]->Game_Object->ID) {
					HitBoxIDArray[i]->Game_Object->OnCollision(j, i);
				}
			}
		}
	}
}
