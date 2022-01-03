#pragma once
#include "Math/Utilities.h"
#include "Effects/EffectManager.h"

class GameObject {
protected:
	static int nextID;
public:
	int HealthPoints = 0;
	GameObject();
	void RegisterGameObject();
	int ID;
	int Direction = 1;  //direction of object (1 is right , -1 is left)
	bool IsActive = true;
	RealVector2D Position = {100,100};
	RealVector2D Velocity = { 0,0 };
	RealVector2D Scale = {1,1};
	double Z_Position = Position.get_y();
	virtual void OnCollision(int otherID, int selfID) = 0;
	virtual void Animate(sf::RenderWindow& window, const double dt) = 0;
	EffectManager* Effect_Manager = nullptr;
	void AssignEffectManager(EffectManager* effectManager);
};

extern std::vector <GameObject*> GameObjectIDArray;
