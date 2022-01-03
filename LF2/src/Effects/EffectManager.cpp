#include "EffectManager.h"
#include <iostream>
#define RANDOM_SCALE 5

std::vector <sf::Sprite> SpriteVector;
std::vector <double> TimeVector;
std::vector <EffectAnimation> AnimationEffectVector;
EffectAnimation BloodAnimation;
EffectAnimation ImpactAnimation;

int EffectAnimation::GetCorrectIndex() { //returns index of correct sprite
	if (Time >= DrawTimes[DrawTimes.size() - 1]) {
		Time = 0;
		return -1;
	}
	for (int i = 0; i < DrawTimes.size(); i++) {
		if (Time < DrawTimes[i]) {
			return i;
		}
	}
	return 0; //No sprite found (Maybe Bug)
}

EffectManager::EffectManager(sf::RenderWindow* window) {
	Window = window;
	BloodSheet.loadFromFile("Resource/bloodEffect.png");
	Blood_1.setTexture(BloodSheet);
	Blood_2.setTexture(BloodSheet);
	Blood_3.setTexture(BloodSheet);
	Blood_1.setTextureRect(sf::IntRect(45, 15, 35, 35));
	Blood_2.setTextureRect(sf::IntRect(300, 20, 35, 35));
	Blood_3.setTextureRect(sf::IntRect(430, 20, 35, 35));
	Blood_1.setOrigin(sf::Vector2f(35 / 2, 35 / 2));
	Blood_2.setOrigin(sf::Vector2f(35 / 2, 35 / 2));
	Blood_3.setOrigin(sf::Vector2f(35 / 2, 35 / 2));
	BloodAnimation.TextureSheet.loadFromFile("Resource/bloodanimation.png");
	for (int i = 0; i < 3; i++) {
		BloodAnimation.AnimationSprites.push_back(sf::Sprite());
		BloodAnimation.AnimationSprites[i].setTexture(BloodAnimation.TextureSheet);
		BloodAnimation.AnimationSprites[i].setTextureRect(sf::IntRect(BloodAnimationLocations[i][0], BloodAnimationLocations[i][1], BloodAnimationSizes[i][0], BloodAnimationSizes[i][1]));
		BloodAnimation.AnimationSprites[i].setOrigin(sf::Vector2f(BloodAnimationSizes[i][0] / 2.0, BloodAnimationSizes[i][1] / 2.0));
		BloodAnimation.AnimationSprites[i].setScale(sf::Vector2f(0.125, 0.125));
		BloodAnimation.DrawTimes.push_back(BloodAnimationTimes[i]);
	}
	ImpactAnimation.TextureSheet.loadFromFile("Resource/explosion.png");
	for (int i = 0; i < 3; i++) {
		ImpactAnimation.AnimationSprites.push_back(sf::Sprite());
		ImpactAnimation.AnimationSprites[i].setTexture(ImpactAnimation.TextureSheet);
		ImpactAnimation.AnimationSprites[i].setTextureRect(sf::IntRect(ImpactAnimationLocations[i][0], ImpactAnimationLocations[i][1], ImpactAnimationSizes[i][0], ImpactAnimationSizes[i][1]));
		ImpactAnimation.AnimationSprites[i].setOrigin(sf::Vector2f(ImpactAnimationSizes[i][0] / 2.0, ImpactAnimationSizes[i][1] / 2.0));
		ImpactAnimation.AnimationSprites[i].setScale(sf::Vector2f(0.5, 0.5));
		ImpactAnimation.DrawTimes.push_back(ImpactAnimationTimes[i]);
	}
}

void EffectManager::DrawEffect(EffectTypeImage type, RealVector2D position, double totalTime, int random) {

	//adding Randomness
	srand(time(NULL));
	int randomnessX = rand() % RANDOM_SCALE; randomnessX *= random;
	int randomnessY = rand() % RANDOM_SCALE; randomnessY *= random;
	int dirX = rand() % 2;
	if (dirX == 0) dirX--;
	int dirY = rand() % 2;
	if (dirY == 0) dirY--;

	//std::cout << randomnessX*dirX << ' ' << randomnessY*dirY << '\n';

	TimeVector.push_back(totalTime);
	switch (type) {
	case EFFECT_IMAGE_BLOOD:
		Blood_1.setPosition(sf::Vector2f(position.get_x() + dirX*randomnessX, position.get_y() + dirY*randomnessY));
		SpriteVector.push_back(Blood_1);
		break;
	default:
		break;
	}
}

void EffectManager::AnimateEffect(EffectTypeAnimation type, RealVector2D position, int random) {
	srand(time(NULL));
	int randomnessX = rand() % RANDOM_SCALE; randomnessX *= random;
	int randomnessY = rand() % RANDOM_SCALE; randomnessY *= random;
	int dirX = rand() % 2;
	if (dirX == 0) dirX--;
	int dirY = rand() % 2;
	if (dirY == 0) dirY--;
	position = position + RealVector2D(randomnessX * dirX, randomnessY * dirY);
	EffectAnimation AnimationEffect;
	switch (type) {
		case EFFECT_ANIMATION_BLOOD:
			AnimationEffect = BloodAnimation;
			break;
		case EFFECT_ANIMATION_IMPACT:
			AnimationEffect = ImpactAnimation;
			break;
		default:
			break;
	}
	AnimationEffect.SetPosition(position);
	AnimationEffectVector.push_back(AnimationEffect);
}

void EffectManager::Update(const double dt) {
	for (int i = 0; i < TimeVector.size(); i++) {
		TimeVector[i] -= dt;
		if (TimeVector[i] <= 0) {
			TimeVector.erase(TimeVector.begin() + i);
			SpriteVector.erase(SpriteVector.begin() + i);
		}
	}
	int n = SpriteVector.size();
	for (int i = 0; i < n; i++) {
		Window->draw(SpriteVector[i]);
	}
	for (int i = 0; i < AnimationEffectVector.size(); i++) {
		AnimationEffectVector[i].Time += dt;
		int index = AnimationEffectVector[i].GetCorrectIndex();
		if (index == -1) {
			AnimationEffectVector.erase(AnimationEffectVector.begin() + i);
			continue;
		}
		Window->draw(AnimationEffectVector[i].AnimationSprites[index]);
	}
}