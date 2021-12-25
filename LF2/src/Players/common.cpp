#include "bandit.h"
int AnimationSheet::GetCorrectIndex() { //returns index of correct sprite
	if (Time >= DrawTimes[DrawTimes.size() - 1]) {
		Time = 0;
		if (OneTime) {
			//On completion of an OneTime animation state of Player is changed to IDLE
			Player->Stop();
			Player->State_Manager.ForceStateChange(IDLE);
		}
		return 0;
	}
	for (int i = 0; i < DrawTimes.size(); i++) {
		if (Time < DrawTimes[i]) {
			return i;
		}
	}
	return 0; //No sprite found (Maybe Bug)
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
		if (Player->CurrentState == JUMPING && KeyToState[key] == HITTING) {
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

void StateManager::TryStateChange(State state, const double lastPressed, const int data) { //called when we try to change state by our input
	if (IsChangePossible[Player->CurrentState][state]) {
		Player->ChangeState(state,lastPressed,data);
	}
}
//called when we have to change state forcefully (usually called based upon things happening in game and not on our inputs)
void StateManager::ForceStateChange(State state, const int data) {
	if (Player->CurrentState != state) {
		Player->ChangeState(state,10,data);
	}
}

