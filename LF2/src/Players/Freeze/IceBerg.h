#pragma once
#include "GameObject/GameObject.h"
#include "Common/AnimationSheet.h"
#include "Common/HitBox.h"

//Nope Dont Go in Here :(
class IceBerg : public GameObject {
public:
	IceBerg();
	AnimationSheet InitialSheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	HitBox WallHitBox;
	HitBox AttackHitBox;
	GameObject* Parent;
	void SetIceTextures(int index);
	double AttackDuration = 0.5;
	double TotalTime = 0;
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(GameObject* parent);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
	void Animate(sf::RenderWindow& window, const double dt);
	int Index = 0;
};

extern const std::vector<RealVector2D> InitialLocations1;
extern const std::vector <double> InitialTimes1;
extern const std::vector<RealVector2D> InitialLocations2;
extern const std::vector <double> InitialTimes2;
extern const std::vector<RealVector2D> InitialLocations3;
extern const std::vector <double> InitialTimes3;