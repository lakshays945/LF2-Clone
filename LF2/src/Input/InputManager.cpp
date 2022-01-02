#include "InputManager.h"
#include "Common/Character.h"


InputManager::InputManager() {
	//initialising above arrays
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		LastPressed[i] = 10;
		LastReleased[i] = 10;
		KeyToState[i] = IDLE;
		IsPressed[i] = false;
		DoubleKeyTimes[i] = -1;
		DoubleKeyToState[i] = IDLE;
		KeyData[i] = 0;
	}
	//Set Controls and key related stuff
	KeyToState[sf::Keyboard::W] = WALKING;
	KeyToState[sf::Keyboard::A] = WALKING;
	KeyToState[sf::Keyboard::S] = WALKING;
	KeyToState[sf::Keyboard::D] = WALKING;
	KeyToState[sf::Keyboard::Q] = HITTING;
	KeyToState[sf::Keyboard::Space] = JUMPING;
	KeyToState[sf::Keyboard::T] = SPECIALATTACK1;
	KeyToState[sf::Keyboard::Y] = SPECIALATTACK2;
	DoubleKeyToState[sf::Keyboard::D] = RUNNING;
	DoubleKeyToState[sf::Keyboard::A] = RUNNING;
	DoubleKeyTimes[sf::Keyboard::D] = 0.3;
	DoubleKeyTimes[sf::Keyboard::A] = 0.3;
	KeyData[sf::Keyboard::D] = 1;
	KeyData[sf::Keyboard::A] = -1;
	KeyData[sf::Keyboard::Space] = 1;

}

void InputManager::AssignPlayer(Character* player) {
	Player = player;
}

//fxn to increase lastpressed and lastreleased of each key by dt
void InputManager::Update(const double dt) {
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		if (LastPressed[i] < 10) { //we dont increase after 10 as it's not required
			LastPressed[i] += dt;
		}
		if (LastReleased[i] < 10) { //we dont increase after 10 as it's not required
			LastReleased[i] += dt;
		}
	}
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key) {
	return IsPressed[key];
}
double InputManager::GetLastPressed(sf::Keyboard::Key key) {
	return LastPressed[key];
}
void InputManager::GetInputDown(sf::Keyboard::Key key) { //called when a key is pressed and does required stuff

	if (key == -1 || IsPressed[key]) { //if key is already pressed there is no sense to register it again in GetInputDown fucntion
		return;
	}
	IsPressed[key] = true;
	if (LastPressed[key] <= DoubleKeyTimes[key]) {
		//if double press is registered
		Player->State_Manager.TryStateChange(DoubleKeyToState[key], LastPressed[key], KeyData[key]);
	}
	else {
		//if single press is registered
		if (Player->CurrentState == JUMPING && KeyToState[key] == HITTING && Player->TimeSinceLastState > 0.2) {
			Player->State_Manager.TryStateChange(JUMPINGATTACK, LastPressed[key], KeyData[key]);
		}
		else {
			Player->State_Manager.TryStateChange(KeyToState[key], LastPressed[key], KeyData[key]);
		}
	}
	LastPressed[key] = 0; //reset to 0 at end of fxn
}

void InputManager::GetInputUp(sf::Keyboard::Key key) {
	IsPressed[key] = false;
	LastReleased[key] = 0; //reset to 0 at end of fxn
}
