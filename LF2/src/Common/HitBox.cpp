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
	if (Game_Object != nullptr) {
		circle.setPosition(sf::Vector2f(center.get_x(), Game_Object->Z_Position));
	}
	circle.setFillColor(sf::Color(0, 0, 0, 255));
	circle.setRadius(5);
	//circle.setOrigin(sf::Vector2f(3.0 / 2, 3.0 / 2));
}

HitBox::HitBox() {
}

bool HitBox::AreColliding(HitBox* other){
	if (abs(Game_Object->Z_Position - other->Game_Object->Z_Position) > COLLISION_THRESHOLD) {
		return false;
	}
	if (abs(Center.get_x() - other->Center.get_x()) <= (Width + other->Width) / 2 && abs(Center.get_y() - other->Center.get_y()) <= (Height + other->Height) / 2) {
		return true; //xyz
	}
	return false;
}

bool HitBox::JustCollided(HitBox* other) {
	if (!IsActive || !other->IsActive) {
		CanCollide[ID][other->ID] = true;
		CanCollide[other->ID][ID] = true;
		return false;
	}
	if (abs(Game_Object->Z_Position - other->Game_Object->Z_Position) > COLLISION_THRESHOLD) {
		if (!CanCollide[ID][other->ID]) {
			HitBoxIDArray[other->ID]->Game_Object->OnCollisionExit(ID, other->ID);
			HitBoxIDArray[ID]->Game_Object->OnCollisionExit(other->ID,ID);
		}
		CanCollide[ID][other->ID] = true;
		CanCollide[other->ID][ID] = true;
		return false;
	}
	if (abs(Center.get_x() - other->Center.get_x()) <= (Width + other->Width) / 2 && abs(Center.get_y() - other->Center.get_y()) <= (Height + other->Height) / 2) {
		if (!CanCollide[ID][other->ID]) {
			return false;
		}
		CanCollide[ID][other->ID] = false;
		CanCollide[other->ID][ID] = false;
		return true; //xyz
	}
	else {
		if (!CanCollide[ID][other->ID]) {
			HitBoxIDArray[other->ID]->Game_Object->OnCollisionExit(ID, other->ID);
			HitBoxIDArray[ID]->Game_Object->OnCollisionExit(other->ID, ID);
		}
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
	if (Type == HB_TYPE_ATTACK) {
		Box.setOutlineColor(sf::Color(255, 0, 0));
	}
	else if (Type == HB_TYPE_DAMAGE) {
		Box.setOutlineColor(sf::Color(0, 0, 255));
	}
	else if (Type == HB_TYPE_REBOUND) {
		Box.setOutlineColor(sf::Color(0, 255, 0));
	}
	else if (Type == HB_TYPE_ICE) {
		Box.setOutlineColor(sf::Color(0, 255, 255));
	}
	else if (Type == HB_TYPE_FIRE) {
		Box.setOutlineColor(sf::Color(255, 255, 0));
	}
	else if (Type == HB_TYPE_WALL) {
		Box.setOutlineColor(sf::Color(0, 0, 0));
	}
	else if (Type == HB_TYPE_TRIGGER) {
		Box.setOutlineColor(sf::Color(255, 255, 255));
	}
}

void HitBox::SetScale(RealVector2D scale) {
	Box.setOrigin(sf::Vector2f(-Width / 2, -Height / 2));
	Width *= scale.get_x();
	Height *= scale.get_y();
	Box.setSize(sf::Vector2f(Width, Height));
	Box.setOrigin(sf::Vector2f(Width / 2, Height / 2));
}

void HitBox::Disable(){
	if (!IsActive) return;
	IsActive = false;
	for (int i = 0; i < HitBoxIDArray.size(); i++) {
		if (i == ID) {
			continue;
		}
		if (!CanCollide[ID][i]) {
			HitBoxIDArray[i]->Game_Object->OnCollisionExit(ID,i);
			HitBoxIDArray[ID]->Game_Object->OnCollisionExit(i, ID);
		}
		CanCollide[ID][i] = true;
		CanCollide[i][ID] = true;
	}
}

void HitBox::DrawBox(sf::RenderWindow& window) {
	return;
	if (!IsActive) {
		return;
	}
	circle.setPosition(sf::Vector2f(Center.get_x(), Game_Object->Z_Position));
	Box.setPosition(sf::Vector2f(Center.get_x(), Center.get_y()));
	window.draw(Box);
	//window.draw(circle);
}

void HandleCollisions() {
	for (int i = 0; i < HitBoxIDArray.size(); i++) {
		if (!HitBoxIDArray[i]->IsActive) {
			continue;
		}
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
