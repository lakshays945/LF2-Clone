#pragma once
#include "GameObject/GameObject.h"
#include "Common/AnimationSheet.h"
#include "Common/HitBox.h"

//Nope Dont Go in Here :(
class IceBerg;

class IceBergWall : public GameObject{
public:
	IceBergWall();
	bool IsSetActive = false;
	IceBerg* IceBergArray[3];
	double TotalTime = 0;
	int ActiveBergs[3] = {true,true,true};
	HitBox WallHitBox;
	HitBox AttackHitBox;
	GameObject* Parent;
	void AssignParent(GameObject* parent);
	void Instantiate(RealVector2D position);
	void Animate(sf::RenderWindow& window, const double dt);
	void ReduceSize(int index);
	void GoBack();
	void OnCollision(int otherID, int selfID);
};

class IceBerg : public GameObject {
public:
	IceBerg();
	AnimationSheet InitialSheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	GameObject* Parent;
	IceBergWall* Wall;
	void SetIceTextures(int index);
	double AttackDuration = 0.5;
	double TotalTime = 0;
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(GameObject* parent);
	void AssignWall(IceBergWall* wall);
	void OnCollision(int otherID, int selfID);
	void Animate(sf::RenderWindow& window, const double dt);
	int Index = 0;
};

extern const std::vector<RealVector2D> InitialLocations1;
extern const std::vector <double> InitialTimes1;
extern const std::vector<RealVector2D> InitialLocations2;
extern const std::vector <double> InitialTimes2;
extern const std::vector<RealVector2D> InitialLocations3;
extern const std::vector <double> InitialTimes3;