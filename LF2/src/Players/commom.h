#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
enum State {
	IDLE = 0, WALKING = 1, RUNNING = 2, JUMPING = 3,
	HITTING = 4, GETTING_HIT = 5, FALLING = 6
}; //Handle with care dont change order (Can add on top of it)

class AnimationSheet {
public:
	std::vector <sf::Texture> Textures;
	std::vector <sf::Sprite> Sprites;
	std::vector <double> DrawTimes; // the Nth element of this vector will give time at which Nth sprite is now done being drawn
	double MaxTime = 0; //Time taken to draw all sprites (Summation ot DrawTimes(i))
	double Time = 0; //Time passed since 1st sprite is drawn (resets to 0 if >= MaxTime)
	void AssignTextures() {
		for (int i = 0; i < Textures.size(); i++){
			Sprites[i].setTexture(Textures[i]);
		}
	}
	int GetCorrectIndex(){ //returns index of correct sprite
		if (Time >= DrawTimes[DrawTimes.size()-1]) {
			Time = 0;
			return 0;
		}
		for (int i = 0; i < DrawTimes.size(); i++) {
			if (Time < DrawTimes[i]) {
				return i;
			}
		}
		return 0; //No sprite found (Maybe Bug)
	}
};