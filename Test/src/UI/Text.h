#pragma once
#include "Element.h"

class UI_Text : public UI_Element {

public:
	sf::Text Text;
	UI_Text(const std::string& value, int size);
	UI_Text();
	void Animate(sf::RenderWindow& window);
};

