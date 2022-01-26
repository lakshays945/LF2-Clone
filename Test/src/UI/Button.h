#pragma once
#include "Element.h"
#include "Image.h"
#include "Text.h"

class UI_Button : public UI_Element {
public:
	UI_Button(const std::string& imageFile, const sf::IntRect& imageLocationData, const std::string& textValue, int textSize);
	UI_Listener Listener;
	UI_Image Image;
	UI_Text Text;
	void Animate(sf::RenderWindow& window);
};