#include "Tornado.h"

sf::Texture TornadoTexFile;

const std::vector<RealVector2D> TornadoLocations = { {0,0}, {160,0}, {320,0}, {480,0}, {640,0}, {0,160}, {160,160}, {320,160}, {640,0}, {0,160}, {160,160}, {320,160}, {640,0}, {0,160}, {160,160}, {320,160}, {640,0}, {0,160}, {160,160}, {320,160}, {640,0}, {0,160}, {160,160}, {320,160}, {480,160}, {640,160} }; //158 x 158
const std::vector <double> TornadoTimes = { 0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6 };

Tornado::Tornado(){
	IsActive = false;
	if (TornadoTexFile.getSize() == sf::Vector2u(0, 0)) {
		TornadoTexFile.loadFromFile("Resource/Tornado.png");
	}
	TornadoSheet.AssignTextures(TornadoTexFile, TornadoLocations, TornadoTimes, 158, 158);
	TornadoSheet.OneTime = true;
	for (int i = 0; i < 100; i++) {
		PlayersIn.push_back(false);
		WeaponsIn.push_back(false);
	}
	AttackHitBox = HitBox(Position, 150, 500, HB_TYPE_ICE);
	AttackHitBox.Damage = 75;
	ForceFieldBox = HitBox(Position, 150, 100, HB_TYPE_TRIGGER);
}

void Tornado::Instantiate(RealVector2D position){
	CollidedPlayers.clear();
	CollidedWeapons.clear();
	IsActive = true;
	Position = position;
	AttackHitBox.IsActive = true;
	ForceFieldBox.IsActive = true;
	Direction = Parent->Direction;
	Z_Position = Position.get_y();
	Velocity = RealVector2D(Direction * 75, 0);
	TornadoSheet.Time = 0;
	for (int i = 0; i < PlayersIn.size(); i++) {
		PlayersIn[i] = false;
		WeaponsIn[i] = false;
	}
	TotalTime = 0;
}

void Tornado::GoBack(){
	IsActive = false;
	Position = Parent->Position;
	AttackHitBox.Disable();
	ForceFieldBox.Disable();
}

void Tornado::AssignParent(Character* parent){
	Parent = parent;
	AttackHitBox.IgnoreObjectID = Parent->ID;
	ForceFieldBox.IgnoreObjectID = Parent->ID;
}

void Tornado::LiftPlayers(const double dt){
	for (int i = 0; i < CollidedPlayers.size(); i++) {
		HitBox* playerBox = &CollidedPlayers[i]->DamageHitBox;
		if (ForceFieldBox.AreColliding(playerBox)) {
			CollidedPlayers[i]->TimeSinceLastState = 0;
			RealVector2D acc = RealVector2D((Position.get_x() - CollidedPlayers[i]->Position.get_x()) * 7, -1200 - TotalTime * 800);
			if (acc.Magnitude() > 2200) {
				acc.SetMagnitude(2200);
			}
			CollidedPlayers[i]->Velocity = CollidedPlayers[i]->Velocity + acc*dt;
		}
		if (CollidedPlayers[i]->Z_Position <= CollidedPlayers[i]->Position.get_y()+5) {
			CollidedPlayers.erase(CollidedPlayers.begin() + i);
		}
	}
}

void Tornado::LiftWeapons(const double dt){
	for (int i = 0; i < CollidedWeapons.size(); i++) {
		if (ForceFieldBox.AreColliding(&CollidedWeapons[i]->AttackHitBox)) {
			RealVector2D acc = RealVector2D((Position.get_x() - CollidedWeapons[i]->Position.get_x()) * 7, -1100 - 200*TotalTime);
			if (acc.Magnitude() > 2200) {
				acc.SetMagnitude(2200);
			}
			CollidedWeapons[i]->Velocity = CollidedWeapons[i]->Velocity + acc * dt;
		}
		CollidedWeapons[i]->Velocity = CollidedWeapons[i]->Velocity + RealVector2D(0, 200) * dt;
	}
}

void Tornado::OnCollision(int otherID, int selfID){

	if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character && HitBoxIDArray[selfID]->Type == HB_TYPE_TRIGGER) {
		Character* otherChar = (Character*)HitBoxIDArray[otherID]->Game_Object;
		if (!PlayersIn[otherChar->CharacterID] && otherChar != Parent) {
			CollidedPlayers.push_back(otherChar);
			otherChar->WallHitBox.Disable();
			otherChar->Stop();
			otherChar->Position = otherChar->Position + RealVector2D(0, -10);
			PlayersIn[otherChar->CharacterID] = true;
		}
	}
	else if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Weapon && HitBoxIDArray[selfID]->Type == HB_TYPE_TRIGGER) {
		Weapon* weapon = (Weapon*)HitBoxIDArray[otherID]->Game_Object;
		if (!WeaponsIn[weapon->WeaponID] && weapon != Parent->CurrentWeapon) {
			CollidedWeapons.push_back(weapon);
			weapon->Position = weapon->Position + RealVector2D(0, -25);
			weapon->Throw(RealVector2D(0, -100), true);
			weapon->AttackHitBox.IgnoreObjectID = Parent->ID;
			WeaponsIn[weapon->WeaponID] = true;
		}
	}
}

void Tornado::OnCollisionExit(int otherID, int selfID){

}

void Tornado::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	TotalTime += dt;
	TornadoSheet.Time += dt;
	Position = Position + Velocity * dt;
	AttackHitBox.Center = Position + RealVector2D(0,-215);
	ForceFieldBox.Center = Position;
	LiftPlayers(dt);
	LiftWeapons(dt);
	int CorrectIndex = TornadoSheet.GetCorrectIndex();
	if (CorrectIndex == -1) {
		GoBack();
		return;
	}
	TornadoSheet.Sprites[CorrectIndex].setScale(Scale.get_x() * Direction, Scale.get_y());
	TornadoSheet.Sprites[CorrectIndex].setPosition(Position.get_x(), Position.get_y() - 40);
	window.draw(TornadoSheet.Sprites[CorrectIndex]);
	AttackHitBox.DrawBox(window);
	ForceFieldBox.DrawBox(window);
}
