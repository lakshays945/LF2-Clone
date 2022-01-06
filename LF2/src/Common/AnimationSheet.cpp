#include "Character.h"

int AnimationSheet::GetCorrectIndex() { //returns index of correct sprite
	if (Time >= DrawTimes[DrawTimes.size() - 1]) {
		Time = 0;
		if (OneTime) {
			//On completion of an OneTime animation -1 index is returned
			return -1;
		}
		return 0;
	}
	for (int i = 0; i < DrawTimes.size(); i++) {
		if (Time < DrawTimes[i]) {
			return i;
		}
	}
	DEBUG_ERROR("ANIMATION_SHEET.cpp -> NO INDEX WAS CORRECT");
	return 0; //No sprite found (Maybe Bug)
}

void AnimationSheet::AssignTextures(sf::Texture &textureSheet, const  std::vector <RealVector2D> &locations, const  std::vector<double> &times, int sizeX, int sizeY) {
	DrawTimes = times;
	for (int i = 0; i < times.size(); i++) {
		HasHitBox.push_back(false);
		HBData.push_back({ 0,0,RealVector2D(0,0),0});
		Sprites.push_back(sf::Sprite());
		Sprites[i].setTexture(textureSheet);
		Sprites[i].setTextureRect(sf::IntRect(locations[i].get_x(), locations[i].get_y(), sizeX, sizeY));
		Sprites[i].setOrigin(sf::Vector2f(sizeX/2, sizeY/2));
	}
	for (int i = 0; i < times.size(); i++) {
		Sprites[i].setScale(sf::Vector2f(2, 2));
	}
}
void AnimationSheet::AssignPlayer(GameObject* player) {
	Player = player;
}
void AnimationSheet::AssignHitbox(const int index, RealVector2D offset, const int width, const int height, int knockPower) {
	HasHitBox[index] = true;
	HBData[index].width = width*Player->Scale.get_x();
	HBData[index].height = height*Player->Scale.get_x();
	HBData[index].offset = offset*Player->Scale;
	HBData[index].KnockPower = knockPower;
}

void AnimationSheet::SetScale(RealVector2D scale) {
	for (int i = 0; i < HBData.size(); i++) {
		if (HasHitBox[i]) {
			HBData[i].width *= scale.get_x();
			HBData[i].height *= scale.get_y();
			HBData[i].offset = HBData[i].offset * scale;
		}
	}
}