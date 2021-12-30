#pragma once
#include "Math/Utilities.h"
#include <math.h>
#include "SFML/Graphics.hpp"
#include <vector>
#include "GameObject/GameObject.h"

class HitBox {
	sf::RectangleShape Box;
	sf::CircleShape circle;
	double TimeSinceActive = 0;
	GameObject* Game_Object = nullptr;
protected:
	static int nextID;
	int ID;
public:
	RealVector2D Center;
	double Width;
	double Height;
	bool IsActive = true;
	std::vector <HitBox *> ImmuneList;
	HitBox(RealVector2D center, double width, double height);

	HitBox();

	bool IsColliding(HitBox* other);
	
	void AssignPlayer(GameObject* player);

	void SetSize(const double width, const double height) {
		Box.setOrigin(sf::Vector2f(-Width / 2, -Height / 2));
		Width = width;
		Height = height;
		Box.setSize(sf::Vector2f(width, height));
		Box.setOrigin(sf::Vector2f(width / 2, height / 2));
	}

	void DrawBox(sf::RenderWindow &window){
		circle.setPosition(sf::Vector2f(Center.get_x(), Center.get_y()));
		Box.setPosition(sf::Vector2f(Center.get_x(), Center.get_y()));
		window.draw(Box);
		window.draw(circle);
	}
};