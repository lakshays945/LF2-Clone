#include "Tornado.h"

sf::Texture TornadoTexFile;

const std::vector<RealVector2D> TornadoLocations = { {0,0}, {160,0}, {320,0}, {480,0}, {640,0}, {0,160}, {160,160}, {320,160}, {640,0}, {0,160}, {160,160}, {320,160}, {640,0}, {0,160}, {160,160}, {320,160},{480,160}, {640,160} }; //158 x 158
const std::vector <double> TornadoTimes = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8 };

Tornado::Tornado(){
	IsActive = false;
	if (TornadoTexFile.getSize() == sf::Vector2u(0, 0)) {
		TornadoTexFile.loadFromFile("Resource/Tornado.png");
	}
	TornadoSheet.AssignTextures(TornadoTexFile, TornadoLocations, TornadoTimes, 158, 158);
	TornadoSheet.OneTime = true;
}

void Tornado::Instantiate(RealVector2D position){
	IsActive = true;
	Position = position;
	TornadoSheet.Time = 0;
}

void Tornado::GoBack(){
	IsActive = false;
	Position = Parent->Position;
}

void Tornado::AssignParent(GameObject* parent){
	Parent = parent;
}

void Tornado::OnCollision(int otherID, int selfID){

}

void Tornado::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	TornadoSheet.Time += dt;
	int CorrectIndex = TornadoSheet.GetCorrectIndex();
	if (CorrectIndex == -1) {
		GoBack();
		return;
	}
	TornadoSheet.Sprites[CorrectIndex].setScale(Scale.get_x() * Direction, Scale.get_y());
	TornadoSheet.Sprites[CorrectIndex].setPosition(Position.get_x(), Position.get_y() - 40);
	window.draw(TornadoSheet.Sprites[CorrectIndex]);
}
