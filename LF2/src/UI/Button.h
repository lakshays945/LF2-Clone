#pragma once
#include "Element.h"
#include "Image.h"
#include "Text.h"
#include <functional>

class Scene;
class UI_Button : public UI_Element {
public:
	Scene* ParentScene = nullptr;
	UI_Button(sf::Sprite& image, const std::string& textFont, const std::string& textValue, int textSize);
	UI_Button();
	UI_Button(const UI_Button& other);
	UI_Listener Listener;
	UI_Image B_Image;
	UI_Text B_Text;
	int NextScene = 0;
	std::function <int()> OnClick;
	double Time = 0;
	double TimeDelay = 0.2;
	int OnHover(int a) {
		if (B_Text.Text.getFillColor() != sf::Color::Green) {
			B_Text.Text.setFillColor(sf::Color::Green);
			B_Image.Image.setColor(sf::Color::White);
		}
		return 0;
	}
	void AlignAtCenter();
	void UpdateListenerSize();
	void Animate(sf::RenderWindow& window, const double dt);
	void operator=(const UI_Button& other);
};
