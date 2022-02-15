#include "Background.h"

AnimationSheet ForestBGSheet;
sf::Texture ForestBGTexFile;
sf::Sprite ForestBGSpr;
BackGround::BackGround(){
	if (ForestBGTexFile.getSize() == sf::Vector2u(0, 0)) {
		ForestBGTexFile.loadFromFile("Resource/ForestBG.png");
		ForestBGSpr.setTexture(ForestBGTexFile);
		ForestBGSheet.AssignTextures(ForestBGTexFile, std::vector<RealVector2D>(1, RealVector2D(0, 0)), std::vector<double>(1, 100), 1200, 500);
	}
}

void BackGround::Animate(sf::RenderWindow& window, const double dt){
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
}

void BackGround::LoadAnimationSheet(AnimationSheet BG) {
	BGSheet = BG;
	CurrentSheet = &BGSheet;
}
