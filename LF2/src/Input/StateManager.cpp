#include "StateManager.h"
#include "Players/bandit.h"


void StateManager::AssignPlayer(Bandit* player) {
	Player = player;
}
void StateManager::TryStateChange(PlayerStates state, const double lastPressed, const int data, const double startTime) { //called when we try to change state by our input
	if (IsChangePossible[Player->CurrentState][state]) {
		Player->ChangeState(state, lastPressed, data);
	}
}
//called when we have to change state forcefully (usually called based upon things happening in game and not on our inputs)
void StateManager::ForceStateChange(PlayerStates state, const int data, const double startTime) {
	if (Player->CurrentState != state) {
		Player->ChangeState(state, 10, data, startTime);
	}
}

