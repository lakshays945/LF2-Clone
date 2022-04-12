#pragma once
#include "SFML/Graphics.hpp"
#include "Math/Utilities.h"
#include <time.h>
#include <vector>

//35 x 35
//430,20
//45,15
//300,20

const int BloodAnimationLocations[3][2] = { {153,128}, {651,93}, {2167,64} };
const int BloodAnimationSizes[3][2] = { {211,186},{249,215},{305,271} };
const double BloodAnimationTimes[3] = { 0.1,0.2,0.3 };

const int ImpactAnimationLocations[3][2] = { {860,600}, {1100,598}, {1860,580} };
const int ImpactAnimationSizes[3][2] = { {80,70}, {85,80}, {130,120} };
const double ImpactAnimationTimes[3] = { 0.05,0.1,0.15 };

enum EffectTypeImage {
	EFFECT_IMAGE_BLOOD = 0, EFFECT_IMAGE_FIRE = 1, 
};

enum EffectTypeAnimation {
	EFFECT_ANIMATION_BLOOD = 0, EFFECT_ANIMATION_FIRE = 1, EFFECT_ANIMATION_IMPACT = 2,
};

class EffectAnimation {
public:
	EffectTypeAnimation AnimationType = EFFECT_ANIMATION_BLOOD;
	std::vector<sf::Sprite> AnimationSprites;
	std::vector<double> DrawTimes;
	sf::Texture TextureSheet;
	double Time = 0;
	int GetCorrectIndex();
	void SetPosition(RealVector2D position) {
		for (int i = 0; i < AnimationSprites.size(); i++) {
			AnimationSprites[i].setPosition(sf::Vector2f(position.get_x(), position.get_y()));
		}
	}
};

class EffectManager {
private:
	sf::RenderWindow* Window;
	sf::Texture BloodSheet;
	sf::Sprite Blood_1;
	sf::Sprite Blood_2;
	sf::Sprite Blood_3;
public:
	EffectManager(sf::RenderWindow* window);
	void DrawEffect(EffectTypeImage type, RealVector2D position, double time, int random = 0);
	void AnimateEffect(EffectTypeAnimation type, RealVector2D position, int random = 0);
	void Update(const double dt);
};