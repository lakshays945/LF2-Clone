#include "FlameThrow.h"
sf::Texture FlameTexFile;

const std::vector<RealVector2D> InitialLocations = { {0,0}, {61,0}, {122,0}, {183,0}, {244,0}, {305,0} };//60 x 60
const std::vector <double> InitialTimes = { 0.1,0.2,0.3,0.4,0.5 };

const std::vector<RealVector2D> InAirLocations = { {0,65}, {61,65}, {122,65}, {183,65}, {244,65}, {305,65} };
const std::vector <double> InAirTimes = { 0.08,0.16,0.24,0.32,0.4 };

const std::vector<RealVector2D> EndLocations = { {0,122}, {61,122}, {122,122} };
const std::vector <double> EndTimes = { 0.1,0.2,0.3 };

FlameThrow::FlameThrow(){
	IsActive = false;
	if (FlameTexFile.getSize() == sf::Vector2u(0, 0)) {
		FlameTexFile.loadFromFile("Resource/FlameThrow.png");
	}
	InitialSheet.AssignTextures(FlameTexFile, InitialLocations, InitialTimes, 60, 58);
	InAirSheet.AssignTextures(FlameTexFile, InAirLocations, InAirTimes, 60, 58);
	EndSheet.AssignTextures(FlameTexFile, EndLocations, EndTimes, 60, 58);
	InitialSheet.OneTime = true;
	EndSheet.OneTime = true;
	AttackHitBox = HitBox(Position, 30, 30, HB_TYPE_FIRE);
	AttackHitBox.KnockOutPower = 100;
	AttackHitBox.KnockUpPower = 300;
	AttackHitBox.Damage = 85;
}

void FlameThrow::OnCollision(int otherID, int selfID) {
}

void FlameThrow::OnCollisionExit(int otherID, int selfID)
{
}

void FlameThrow::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	CurrentSheet->Time += dt;
	TotalTime += dt;
	if (TotalTime > 1) {
		CurrentSheet = &EndSheet;
	}
	Velocity = Velocity + RealVector2D(Direction * 50, 0) * dt;
	Position = Position + Velocity * dt;
	AttackHitBox.Center = Position + RealVector2D(0,10);
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			CurrentSheet = &InAirSheet;
			AttackHitBox.IsActive = true;
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
	AttackHitBox.DrawBox(window);

}
