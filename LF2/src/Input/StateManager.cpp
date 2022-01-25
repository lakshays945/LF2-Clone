#include "StateManager.h"
#include "Common/Character.h"


void StateManager::AssignPlayer(Character* player) {
	Player = player;
}
void StateManager::TryStateChange(PlayerStates state, const double lastPressed, const int data, const double startTime) { //called when we try to change state by our input
	if (IsChangePossible[Player->CurrentState][state]) {
		if (state == HITTING && Player->WeaponsInRangeID.size() > 0 && Player->CurrentWeapon == nullptr) {
			Player->ChangeState(WEAPONPICK,lastPressed,data);
		}
		else if ((state == GETTING_HIT && Player->Z_Position != Player->Position.get_y()) || (Player->CurrentState == FREEZED)) {
			if (Player->CurrentState == FREEZED) {
				Player->DeFreeze();
			}
			if (lastPressed > 0) {
				Player->ChangeState(FALLINGFRONT, 100, 200);
				DEBUG_INFO("HERE1");
			}
			else {
				Player->ChangeState(FALLINGBACK, 100, 200);
				DEBUG_INFO("HERE2");
			}
		}
		else {
			Player->ChangeState(state, lastPressed, data);
		}
	}
}
//called when we have to change state forcefully (usually called based upon things happening in game and not on our inputs)
void StateManager::ForceStateChange(PlayerStates state, const int data, const double startTime) {
	if (Player->CurrentState != state) {
		Player->ChangeState(state, 10, data, startTime);
	}
}

