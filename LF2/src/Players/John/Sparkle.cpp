#include "Sparkle.h"

sf::Texture SparkleTexFile;

const std::vector<RealVector2D> InitialLocations = { {250,166},{170,166},{90,166}, {10,166} };//52 x 46
const std::vector <double> InitialTimes = { 0.1,0.2,0.25,0.3 };

const std::vector<RealVector2D> EndLocations = { {330,166},{410,166},{495,166},{575,166} };
const std::vector <double> EndTimes = { 0.1,0.2,0.25,0.3 };

Sparkle::Sparkle(){
	IsActive = false;
	if (SparkleTexFile.getSize() == sf::Vector2u(0, 0)) {
		SparkleTexFile.loadFromFile("Resource/JohnBall.png");
	}
	InitialSheet.AssignTextures(SparkleTexFile, InitialLocations, InitialTimes, 70, 80);
	EndSheet.AssignTextures(SparkleTexFile, EndLocations, EndTimes, 70, 80);
}

void Sparkle::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) return;
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			CurrentSheet = &EndSheet;
			CorrectIndex = 0;
		}
		else {
			GoBack();
			return;
		}
	}
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	current->setScale(Scale.get_x() * Direction, Scale.get_y());
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
}

void Sparkle::OnCollision(int otherID, int selfID){

}

void Sparkle::OnCollisionExit(int otherID, int selfID){

}
