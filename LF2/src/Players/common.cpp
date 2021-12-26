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

void AnimationSheet::AssignTextures() {
	for (int i = 0; i < Textures.size(); i++) {
		Sprites[i].setTexture(Textures[i]);
		Sprites[i].setOrigin(sf::Vector2f(40, 40));
	}
}
void AnimationSheet::AssignPlayer(Bandit* player) {
	Player = player;
}
