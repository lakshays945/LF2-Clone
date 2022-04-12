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
	if (!IsPressed[key]) return;
	IsPressed[key] = false;
	LastReleased[key] = 0; //reset to 0 at end of fxn
}

void InputManager::SetControls(KeyboardControls control) {
	KeyToState[control.UpKey] = WALKING;
	KeyToState[control.DownKey] = WALKING;
	KeyToState[control.RightKey] = WALKING;
	KeyToState[control.LeftKey] = WALKING;
	KeyToState[control.AttackKey] = HITTING;
	KeyToState[control.JumpKey] = JUMPING;
	KeyToState[control.SpecialAttack1Key] = SPECIALATTACK1;
	KeyToState[control.SpecialAttack2Key] = SPECIALATTACK2;
	KeyToState[control.SpecialAttack3Key] = SPECIALATTACK3;
	KeyToState[control.SpecialAttack4Key] = SPECIALATTACK4;
	KeyToState[control.GuardKey] = GUARD;
	KeyToState[sf::Keyboard::F] = FREEZED;
	KeyToState[sf::Keyboard::G] = FALLINGBACK;
	DoubleKeyToState[control.RightKey] = RUNNING;
	DoubleKeyToState[control.LeftKey] = RUNNING;
	DoubleKeyTimes[control.RightKey] = 0.3;
	DoubleKeyTimes[control.LeftKey] = 0.3;
	KeyData[control.RightKey] = 1;
	KeyData[control.LeftKey] = -1;
	KeyData[control.JumpKey] = 1;
}

int GetJoystickButton(int val, int axis) {
	DEBUG_INFO("axis = {}", axis);
	if (axis == -1) return val;
	sf::Joystick::Axis ax = (sf::Joystick::Axis)axis;
	if (ax == 0) {
		if (val >= 90) return 10;
		if (val <= -90) return 11;
		return 17;
	}
	else if (ax == 1) {
		if (val >= 90) return 13;
		if (val <= -90) return 12;
		return 19;
	}
	/*else if (ax == sf::Joystick::Axis::Z) {
		if (val >= 90) return 14;
		if (val <= -90) return 15;
		return 21;
	}*/
	return 16;
}