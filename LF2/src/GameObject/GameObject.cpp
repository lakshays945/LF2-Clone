#include "GameObject.h"
#include <vector>

std::vector <GameObject*> GameObjectIDArray;

int GameObject::nextID = 0;
GameObject::GameObject() {
}

void GameObject::RegisterGameObject(GameObjectType goType) {
	GO_Type = goType;
	ID = nextID;
	GameObjectIDArray.push_back(this);
	DEBUG_INFO("GameObject of type {0} registered with ID = {1}",GO_Type, ID);
	nextID++;

}

void GameObject::AssignEffectManager(EffectManager* effectManager){
	Effect_Manager = effectManager;
}