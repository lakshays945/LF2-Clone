#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <Math/RealVector2D.h>

enum PlayerStates {
	IDLE = 0, WALKING = 1, RUNNING = 2, JUMPING = 3,
	HITTING = 4, GETTING_HIT = 5, FALLING = 6, JUMPINGATTACK = 7, RUNATTACK = 8, DASH = 9 ,STATECOUNT,
};

class Bandit;
class AnimationSheet {

private:
	Bandit* Player = nullptr; //a pointer to player to which sheet is assigned
public:
	//One time means complete animation has to be played exaclty one time before we can do anything with our inputs
	bool OneTime = false;
	int HitBoxIndex = INT16_MAX;
	std::vector <sf::Texture> Textures;
	std::vector <sf::Sprite> Sprites;
	std::vector <double> DrawTimes; // the Nth element of this vector will give time at which Nth sprite is now done being drawn
	RealVector2D HitboxOffset;
	int HitboxWidth, HitboxHeight;
	double MaxTime = 0; //Time taken to draw all sprites (Summation ot DrawTimes(i))
	double Time = 0; //Time passed since 1st sprite is drawn (resets to 0 if >= MaxTime)
	void AssignTextures();
	void AssignHitbox(const int index, RealVector2D offset, const int width, const int height);
	void AssignPlayer(Bandit* player);
	int GetCorrectIndex();
};
