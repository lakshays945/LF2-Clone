#include "GameObject.h"
#include <vector>

std::vector <GameObject*> GameObjectIDArray;

int GameObject::nextID = 0;
GameObject::GameObject() {
}

void GameObject::RegisterGameObject() {
	ID = nextID;
	GameObjectIDArray.push_back(this);
	DEBUG_INFO("GameObject with ID = {0} registered", ID);
	nextID++;
}

void GameObject::AssignEffectManager(EffectManager* effectManager){
	Effect_Manager = effectManager;
}