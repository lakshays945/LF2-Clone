#pragma once
#include <SFML/Graphics.hpp>
#include "Math/RealVector2D.h"


enum UI_Types {
	UI_TEXT = 0, UI_IMAGE = 1, UI_BUTTON = 2
};

class UI_Element {
public:
	UI_Types Type;
	RealVector2D Position;
	RealVector2D Scale;
	bool IsActive = true;
	void SetPosition(RealVector2D position);
	virtual void Animate(sf::RenderWindow& window)=0;

};

class UI_Listener {
public:
	UI_Element* Parent = nullptr;
	void OnLeftClick();
	void OnRightClick();
	void OnHover();
	void Listen();
	
	void AssignParent(UI_Element* parent);
	int Width = 10, Height = 10;
};

