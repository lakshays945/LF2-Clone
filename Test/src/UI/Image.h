#pragma once
#include "Element.h"

class UI_Image : public UI_Element {
public:	
	bool IsActive = true;
	UI_Image(const std::string& fileName, sf::IntRect locationData);
	UI_Image();
	sf::Texture Texture;
	sf::Sprite Image;
	void Animate(sf::RenderWindow& window);
};
