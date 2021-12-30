#include "HitBox.h"
//#include "bandit.h"

#define COLLISION_THRESHOLD 25

int HitBox::nextID = 0;
std::vector <HitBox*> IDArray;
std::vector <std::vector< bool>> CanCollide;

HitBox::HitBox(RealVector2D center, double width, double height)
:Center(center), Width(width), Height(height) {
	ID = ++nextID;
	IDArray.push_back(this);
	std::vector <bool> newRow;
	for (int i = 0; i < CanCollide.size(); i++) {
		CanCollide[i].push_back(true);
		newRow.push_back(true);
	}
	newRow.push_back(false);
	CanCollide.push_back(newRow);
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
	ID = ++nextID;
	IDArray.push_back(this);
	std::vector <bool> newRow;
	for (int i = 0; i < CanCollide.size(); i++) {
		CanCollide[i].push_back(true);
		newRow.push_back(true);
	}
	newRow.push_back(false);
	CanCollide.push_back(newRow);
}

bool HitBox::IsColliding(HitBox* other) {

	if (!IsActive || !other->IsActive) {
		CanCollide[ID][other->ID] = true;
		CanCollide[other->ID][ID] = true;
		return false;
	}
	if (abs(Game_Object->Position.get_y() - other->Game_Object->Position.get_y()) > COLLISION_THRESHOLD) {
		CanCollide[ID][other->ID] = true;
		CanCollide[other->ID][ID] = true;
		return false;
	}
	if (!CanCollide[ID][other->ID]) {
		return false;
	}
	if (abs(Center.get_x() - other->Center.get_x()) <= (Width + other->Width) / 2 && abs(Center.get_y() - other->Center.get_y()) <= (Height + other->Height) / 2) {
		CanCollide[ID][other->ID] = false;
		CanCollide[other->ID][ID] = false;
		return true;
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