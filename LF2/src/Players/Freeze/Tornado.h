#pragma once
#include "Common/Character.h"
#include "Weapons/Weapon.h"
class Tornado : public GameObject {
public:
	Tornado();
	AnimationSheet TornadoSheet;
	Character* Parent = nullptr;
	double TotalTime = 0;
	HitBox AttackHitBox;
	HitBox ForceFieldBox;
	std::vector <Character*> CollidedPlayers;
	std::vector <Weapon*> CollidedWeapons;
	std::vector <bool> PlayersIn;
	std::vector <bool> WeaponsIn;
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(Character* parent);
	void LiftPlayers(const double dt);
	void LiftWeapons(const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
	void Animate(sf::RenderWindow& window, const double dt);
};