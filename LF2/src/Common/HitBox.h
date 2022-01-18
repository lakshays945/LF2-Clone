#pragma once
#include "Math/Utilities.h"
#include <math.h>
#include "SFML/Graphics.hpp"
#include <vector>
#include "GameObject/GameObject.h"

enum HitBoxType {
	HB_TYPE_DAMAGE = 0, HB_TYPE_ATTACK = 1, HB_TYPE_REBOUND = 2, HB_TYPE_FIRE = 3, HB_TYPE_ICE = 4, HB_TYPE_WALL = 5, HB_TYPE_TRIGGER = 6,
};

class HitBox {
	sf::RectangleShape Box;
	sf::CircleShape circle;
	double TimeSinceActive = 0;
protected:
	static int nextID;
public:
	int ID = 0;
	int KnockOutPower = 0;
	int KnockUpPower = 300;
	HitBoxType Type = HB_TYPE_DAMAGE;
	RealVector2D Center;
	GameObject* Game_Object = nullptr;
	int IgnoreObjectID = -1;
	double Width;
	double Height;
	bool IsActive = false;
	HitBox(RealVector2D center, double width, double height, HitBoxType type);

	HitBox();

	bool JustCollided(HitBox* other);
	void AssignPlayer(GameObject* player);
	void SetSize(const double width, const double height) {
		Box.setOrigin(sf::Vector2f(-Width / 2, -Height / 2));
		Width = width;
		Height = height;
		Box.setSize(sf::Vector2f(width, height));
		Box.setOrigin(sf::Vector2f(width / 2, height / 2));
	}
	void DrawBox(sf::RenderWindow &window){
		if (!IsActive) {
			return;
		}
		circle.setPosition(sf::Vector2f(Center.get_x(), Center.get_y()));
		Box.setPosition(sf::Vector2f(Center.get_x(), Center.get_y()));
		//window.draw(Box);
		//window.draw(circle);
	}
	void RegisterID();
	void SetScale(RealVector2D scale);
	void Disable();
};

void HandleCollisions();

extern std::vector <HitBox*> HitBoxIDArray;
extern std::vector <std::vector< bool>> CanCollide;