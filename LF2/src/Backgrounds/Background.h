#pragma once
#include "Common/AnimationSheet.h"
class BackGround {
public:
	BackGround();
	float WallRight;
	float WallLeft;
	float WallUp;
	float WallDown;
	RealVector2D Position;
	AnimationSheet BGSheet;
	AnimationSheet* CurrentSheet;
	void Animate(sf::RenderWindow& window, const double dt);
	void LoadAnimationSheet(AnimationSheet BG);
};

extern AnimationSheet ForestBGSheet;
extern sf::Texture ForestBGTexFile;
extern sf::Sprite ForestBGSpr;