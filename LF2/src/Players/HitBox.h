#pragma once
#include "Math/Utilities.h"
#include <math.h>
#include "SFML/Graphics.hpp"


class HitBox {
	sf::RectangleShape Box;
public:
	RealVector2D Center;
	double Width;
	double Height;
	bool IsActive = true;
	HitBox(RealVector2D center, double width, double height)
	:Center(center), Width(width), Height(height) {
		Box.setSize(sf::Vector2f(width, height));
		Box.setFillColor(sf::Color::Transparent);
		Box.setOutlineThickness(-2);
		Box.setOutlineColor(sf::Color(255, 0, 0));
		Box.setOrigin(sf::Vector2f(width/2, height/2));
	}

	HitBox(){}

	bool IsColliding(const HitBox& other)const {
		if (abs(Center.get_x() - other.Center.get_x()) <= (Width + other.Width)/2 && abs(Center.get_y() - other.Center.get_y()) <= (Height + other.Height) / 2) {
			return true;
		}
		return false;
	}

	void TraverseBox() {

	}

	void DrawBox(sf::RenderWindow &window){
		Box.setPosition(sf::Vector2f(Center.get_x(), Center.get_y()));
		window.draw(Box);
	}
};