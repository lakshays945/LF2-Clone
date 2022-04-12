#pragma once
#include "Math/Utilities.h"
#include "Effects/EffectManager.h"

enum GameObjectType {
	GO_Null = 0, GO_Character = 1, GO_Projectile = 2, GO_Weapon = 3,
};

class GameObject {
public:
	static int nextID;
	GameObjectType GO_Type = GO_Null;
	int HealthPoints = 0;
	GameObject();
	void RegisterGameObject(GameObjectType goType);
	int ID;
	int Direction = 1;  //direction of object (1 is right , -1 is left)
	bool IsActive = true;
	RealVector2D Position = {100,100};
	RealVector2D Velocity = { 0,0 };
	RealVector2D Scale = {1,1};
	double Z_Position = Position.get_y();
	virtual void OnCollision(int otherID, int selfID) = 0;
	virtual void OnCollisionExit(int otherID, int selfID) = 0;
	virtual void Animate(sf::RenderWindow& window, const double dt) = 0;
	EffectManager* Effect_Manager = nullptr;
	void AssignEffectManager(EffectManager* effectManager);
};

extern std::vector <GameObject*> GameObjectIDArray;
void AddGameObject(GameObject* object);