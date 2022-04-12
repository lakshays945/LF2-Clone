#pragma once
#include <SFML/Graphics.hpp>
#include "Math/RealVector2D.h"
#include <iostream>
#include <conio.h>

#define NUMBEROF(array_) (sizeof(array_)/sizeof(*array_) )

extern sf::Texture ButtonsTexFile;
extern sf::Texture PlayersTexFile;
extern sf::Texture BackGroundTexFile;

extern sf::Sprite ButtonsSpr;
extern sf::Sprite PlayersSpr;
extern sf::Sprite BackGroundSpr;
extern sf::Sprite GameOverSpr;

class UI_Button;
class Scene;
enum UI_Types {
	UI_TYPE_TEXT = 0, UI_TYPE_IMAGE = 1, UI_TYPE_BUTTON = 2
};

class UI_Element {
public:	
	UI_Element();
	UI_Types Type;
	RealVector2D Position;
	RealVector2D Scale;
	bool IsActive = true;
	void SetPosition(RealVector2D position);
	virtual void Animate(sf::RenderWindow& window, const double dt)=0;

};

class UI_Listener {
public:
	bool Clicked = false;
	bool CanClick = false;
	UI_Button* Parent = nullptr;
	void Listen(const sf::RenderWindow &window);
	void AssignParent(UI_Button* parent);
	int Width = 10, Height = 10;
};

