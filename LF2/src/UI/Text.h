#pragma once
#include "Element.h"

class UI_Text : public UI_Element {

public:
	sf::Text Text;
	sf::Font Font;
	UI_Text(const std::string &fontFile, const std::string& value, int size);
	UI_Text();
	UI_Text(const UI_Text& other);
	void AlignAtCenter();
	void Animate(sf::RenderWindow& window, const double dt);
	void SetText(const std::string& fontFile, const std::string& value, int size);
	void operator=(const UI_Text& other);
};

