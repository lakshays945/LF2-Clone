#include "JohnShield.h"

sf::Texture JohnShieldTexFile;

const std::vector<RealVector2D> InitialLocations = { {0,332},{82,332}};//80 x 80
const std::vector <double> InitialTimes = { 0.1,0.2};

const std::vector<RealVector2D> SteadyLocations = { {164,332},{246,332}, {328,332} };
const std::vector <double> SteadyTimes = { 0.1,0.2,0.3 };

const std::vector<RealVector2D> EndLocations = { {410,332},{492,332},{574,332} };
const std::vector <double> EndTimes = { 0.1,0.2,0.3 };

JohnShield::JohnShield(){
	IsActive = false;
	if (JohnShieldTexFile.getSize() == sf::Vector2u(0, 0)) {
		JohnShieldTexFile.loadFromFile("Resource/JohnBall.png");
	}
	InitialSheet.AssignPlayer(this);
	SteadySheet.AssignPlayer(this);
	EndSheet.AssignPlayer(this);
	InitialSheet.AssignTextures(JohnShieldTexFile, InitialLocations, InitialTimes, 80, 80);
	SteadySheet.AssignTextures(JohnShieldTexFile, SteadyLocations, SteadyTimes, 80, 80);
	EndSheet.AssignTextures(JohnShieldTexFile, EndLocations, EndTimes, 80, 80);
	InitialSheet.OneTime = true;
	EndSheet.OneTime = true;
	AttackHitBox = HitBox(Position, 35, 50, HB_TYPE_ATTACK);
	AttackHitBox.KnockOutPower = 250;
	AttackHitBox.KnockUpPower = 350;
	CurrentSheet = &InitialSheet;
}

void JohnShield::AssignParent(GameObject* parent){
	Parent = parent;
	AttackHitBox.IgnoreObjectID = Parent->ID;
}

void JohnShield::Instantiate(RealVector2D position){
	IsActive = true;
	AttackHitBox.IsActive = true;
	Position = position;
	Z_Position = Position.get_y();
	AttackHitBox.Center = Position;
	InitialSheet.Time = 0;
	SteadySheet.Time = 0;
	EndSheet.Time = 0;
	CurrentSheet = &InitialSheet;
	Direction = Parent->Direction;
	TotalTime = 0;
}

void JohnShield::GoBack(){
	IsActive = false;
	AttackHitBox.Disable();
	Position = Parent->Position;
}

void JohnShield::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	if (TotalTime > 7) {
		AttackHitBox.Disable();
		CurrentSheet = &EndSheet;
	}
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (CurrentSheet == &InitialSheet) {
			CurrentSheet = &SteadySheet;
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

void JohnShield::OnCollision(int otherID, int selfID){
	if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Projectile && HitBoxIDArray[otherID]->Type != HB_TYPE_REBOUND) {
		ProjectileBall* otherPro = (ProjectileBall*)HitBoxIDArray[otherID]->Game_Object;
		otherPro->Rebound();
		DEBUG_INFO("Rebounded");
		otherPro->AttackHitBox.IgnoreObjectID = Parent->ID;
	}
	else if (HitBoxIDArray[otherID]->Type == HB_TYPE_DAMAGE && HitBoxIDArray[otherID]->Game_Object->ID != Parent->ID) {
		CurrentSheet = &EndSheet;
		AttackHitBox.Disable();
	}
}

void JohnShield::OnCollisionExit(int otherID, int selfID)
{
}
