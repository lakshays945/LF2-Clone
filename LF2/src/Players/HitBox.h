#pragma once
#include "Math/Utilities.h"
#include <math.h>
#include "SFML/Graphics.hpp"
#include <vector>

class Bandit;
class HitBox {
	sf::RectangleShape Box;
	sf::CircleShape circle;
	double TimeSinceActive = 0;
	Bandit* Player;
public:
	RealVector2D Center;
	double Width;
	double Height;
	bool IsActive = true;
	std::vector <HitBox *> ImmuneList;
	HitBox(RealVector2D center, double width, double height)
	:Center(center), Width(width), Height(height) {
		Box.setSize(sf::Vector2f(width, height));
		Box.setFillColor(sf::Color::Transparent);
		Box.setOutlineThickness(-2);
		Box.setOutlineColor(sf::Color(255, 0, 0));
		Box.setOrigin(sf::Vector2f(width/2, height/2));
		circle.setPosition(sf::Vector2f(center.get_x(), center.get_y()));
		circle.setFillColor(sf::Color(0, 0, 0, 255));
		circle.setRadius(1);
		//circle.setOrigin(sf::Vector2f(3.0 / 2, 3.0 / 2));
	}

	HitBox(){}

	bool IsColliding(HitBox* other);
	
	void AssignPlayer(Bandit* player);

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