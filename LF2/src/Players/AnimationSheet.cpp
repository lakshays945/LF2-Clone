#include "bandit.h"

int AnimationSheet::GetCorrectIndex() { //returns index of correct sprite
	if (Time >= DrawTimes[DrawTimes.size() - 1]) {
		Time = 0;
		if (OneTime) {
			//On completion of an OneTime animation state of Player is changed to IDLE
			Player->Stop();
			Player->State_Manager.ForceStateChange(IDLE);
		}
		return 0;
	}
	for (int i = 0; i < DrawTimes.size(); i++) {
		if (Time < DrawTimes[i]) {
			return i;
		}
	}
	return 0; //No sprite found (Maybe Bug)
}

void AnimationSheet::AssignTextures(sf::Texture &textureSheet, const  std::vector <RealVector2D> &locations, const  std::vector<double> &times) {
	DrawTimes = times;
	for (int i = 0; i < times.size(); i++) {
		Sprites.push_back(sf::Sprite());
		Sprites[i].setTexture(textureSheet);
		Sprites[i].setTextureRect(sf::IntRect(locations[i].get_x(), locations[i].get_y(), 80, 80));
		Sprites[i].setOrigin(sf::Vector2f(40, 40));
	}
}
void AnimationSheet::AssignPlayer(Bandit* player) {
	Player = player;
}
void AnimationSheet::AssignHitbox(const int index,RealVector2D offset, const int width, const int height){
	HitBoxIndex = index;
	HitboxOffset = offset;
	HitboxWidth = width;
	HitboxHeight = height;
}
