#pragma once
#include "Element.h"

class UI_Image : public UI_Element {
public:	
	bool IsActive = true;
	UI_Image(sf::Sprite &image);
	UI_Image();
	sf::Sprite Image;
	void AlignAtCenter();
	void Animate(sf::RenderWindow& window, const double dt);
	void SetImage(sf::Sprite &image);
};
