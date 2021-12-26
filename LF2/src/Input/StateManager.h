#pragma once
#include "Players/commom.h"

class Bandit;
class StateManager {

private:
	Bandit* Player = nullptr;//a pointer to player to which StateManager is assigned

	//IsChangePossible[i][j] tells us if state change is possible from 'i' state to 'j' state

	const bool IsChangePossible[STATECOUNT][STATECOUNT] =
		//idle  walking  running  jumping  hitting  getting_hit  falling   //jumpattack  //runattack    //dash
	{ {  0,       1,      1,       1,       1,        1,          1,          1,            1,         1        },   //idle
	  {  0,       0,      1,       1,       1,        1,          1,          1,            1,         1        },   //walking
	  {  0,       1,      0,       1,       1,        1,          1,          1,            1,         1        },   //running
	  {  0,       0,      0,       0,       0,        1,          1,          1,            1,         1        },   //jumping
	  {  0,       0,      0,       0,       0,        1,          1,          0,            1,         1        },   //hitting
	  {  0,       1,      1,       1,       1,        0,          1,          1,            1,         1        },   //getting_hit
	  {  0,       1,      1,       1,       1,        1,          0,          1,            1,         1        },   //falling
	  {  0,       0,      0,       0,       0,        1,          1,          0,            1,         1        },   //jumpattack
	  {  0,       1,      1,       1,       1,        1,          1,          1,            0,         1        },   //runattack
	  {  0,       0,      0,       0,       0,        1,          1,          0,            0,         0        }, };//dash

public:

	void AssignPlayer(Bandit* player);
	void TryStateChange(PlayerStates state, const double LastPressed, const int data = 0);
	void ForceStateChange(PlayerStates state, const int data = 0);
};
