#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Math/RealVector2D.h>
#include "GameObject/GameObject.h"

enum PlayerStates {
	IDLE = 0, WALKING = 1, RUNNING = 2, JUMPING = 3,HITTING = 4, GETTING_HIT = 5, 
	FALLINGBACK = 6, JUMPINGATTACK = 7, RUNATTACK = 8, DASH = 9, SPECIALATTACK1 = 10, SPECIALATTACK2 = 11, SPECIALATTACK3 = 12, FALLINGFRONT = 13, FREEZED = 14, STATECOUNT,
};

struct HitBoxData {
	double width = 0;
	double height = 0;
	RealVector2D offset;
	int KnockPower = -50;
	int KnockPowerUp = 300;
};

class AnimationSheet {
public:
	GameObject* Player = nullptr;  //a pointer to GameObject to which sheet is assigned
	//One time means complete animation has to be played exaclty one time before we can do anything with our inputs
	bool OneTime = false;
	std::vector <sf::Sprite> Sprites;
	std::vector <double> DrawTimes; // the Nth element of this vector will give time at which Nth sprite is now done being drawn
	std::vector <bool> HasHitBox;
	std::vector <HitBoxData> HBData;
	double MaxTime = 0; //Time taken to draw all sprites (Summation ot DrawTimes(i))
	double Time = 0; //Time passed since 1st sprite is drawn (resets to 0 if >= MaxTime)
	void AssignTextures(sf::Texture& textureSheet, const std::vector <RealVector2D>& locations, const std::vector<double>& times, int sizeX, int sizeY);
	void AssignHitbox(const int index, RealVector2D offset, const int width, const int height, int knockPower = -10, int knockPowerUp = 300);
	void AssignPlayer(GameObject* player);
	void SetScale(RealVector2D scale);
	int GetCorrectIndex();
};
