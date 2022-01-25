#include "FirenExplosion.h"

sf::Texture ExplosionTexFile;

const std::vector<RealVector2D> ExplosionLocations = { {0,44}, {160,44}, {320,44}, {480,44}, {640,44}, {0,204}, {160,204}, {320,204}, {480,204}, {640,204} }; //160 x 160
const std::vector <double> ExplosionTimes = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.6 };

FirenExplosionBox::FirenExplosionBox() {
	IsActive = false;
	ExplosionHitBox = HitBox(Position, 55, 80, HB_TYPE_FIRE);
	ExplosionHitBox.KnockOutPower = 200;
	ExplosionHitBox.KnockUpPower = 500;
}

void FirenExplosionBox::AssignOffset(RealVector2D offset){
	Offset = offset;
	if (Offset.get_x() > 0) {
		Direction = 1;
	}
	else {
		Direction = -1;
	}
}

void FirenExplosionBox::Instantiate(RealVector2D position){
	IsActive = true;
	Position = position + Offset;
	ExplosionHitBox.IsActive = true;
	ExplosionHitBox.Center = Position;
	Z_Position = Position.get_y();
	TotalTime = 0;
}

void FirenExplosionBox::GoBack(){
	IsActive = false;
	ExplosionHitBox.Disable();
	Position = Parent->Position;
}

void FirenExplosionBox::AssignParent(GameObject* parent){
	Parent = parent;
	ExplosionHitBox.IgnoreObjectID = Parent->ID;
}

void FirenExplosionBox::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if (TotalTime > 0.3) {
		GoBack();
		return;
	}
	ExplosionHitBox.DrawBox(window);
	if (TotalTime < 0.1) {
		ExplosionHitBox.Center = ExplosionHitBox.Center + RealVector2D(0, -8) * dt * 50;
		Z_Position -= dt * 400;
	}
}

void FirenExplosionBox::OnCollision(int otherID, int selfID){
	if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character) {
		Character* otherChar = (Character*)HitBoxIDArray[otherID]->Game_Object;
		otherChar->BurningHitBox.IgnoreObjectID = Parent->ID;
	}
}

void FirenExplosionBox::OnCollisionExit(int otherID, int selfID)
{
}

FirenExplosionAnimation::FirenExplosionAnimation() {
	IsActive = false;
	if (ExplosionTexFile.getSize() == sf::Vector2u(0, 0)) {
		ExplosionTexFile.loadFromFile("Resource/FirenExplosion.png");
	}
	ExplosionSheet.AssignTextures(ExplosionTexFile, ExplosionLocations, ExplosionTimes, 160, 160);
	ExplosionSheet.OneTime = true;
}

void FirenExplosionAnimation::Instantiate(RealVector2D position){
	IsActive = true;
	ExplosionSheet.Time = 0;
	Position = position;
	Z_Position = Position.get_y() + 1;
	Direction = Parent->Direction;
}

void FirenExplosionAnimation::GoBack(){
	IsActive = false;
	Position = Parent->Position;
}

void FirenExplosionAnimation::AssignParent(GameObject* parent){
	Parent = parent;
}

void FirenExplosionAnimation::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	ExplosionSheet.Time += dt;
	int CorrectIndex = ExplosionSheet.GetCorrectIndex();
	if (CorrectIndex == -1) {
		GoBack();
		return;
	}
	ExplosionSheet.Sprites[CorrectIndex].setScale(Scale.get_x() * Direction, Scale.get_y());
	ExplosionSheet.Sprites[CorrectIndex].setPosition(Position.get_x(), Position.get_y() - 40);
	window.draw(ExplosionSheet.Sprites[CorrectIndex]);
}

void FirenExplosionAnimation::OnCollision(int otherID, int selfID){

}

void FirenExplosionAnimation::OnCollisionExit(int otherID, int selfID)
{
}
