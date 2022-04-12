#pragma once
#include <SFML/Graphics.hpp>
#include "Common/AnimationSheet.h"

struct KeyboardControls {
	sf::Keyboard::Key UpKey, DownKey, LeftKey, RightKey, JumpKey, AttackKey, GuardKey, SpecialAttack1Key, SpecialAttack2Key, SpecialAttack3Key, SpecialAttack4Key;
};


class Character;
class InputManager {
private:
	Character* Player = nullptr; //a pointer to player to which InputManager is assigned
	double LastPressed[sf::Keyboard::KeyCount]; //stores time since key was pressed last time
	double LastReleased[sf::Keyboard::KeyCount]; //stores time since key was released last time
	double DoubleKeyTimes[sf::Keyboard::KeyCount]; //max time delay to register a double press
	double KeyData[sf::Keyboard::KeyCount]; //data related to key (Might be useful in future)
	bool IsPressed[sf::Keyboard::KeyCount]; //tells if key is currently being pressed
	PlayerStates KeyToState[sf::Keyboard::KeyCount]; //store state related to each key 
	PlayerStates DoubleKeyToState[sf::Keyboard::KeyCount]; //stores state related to double press of key

	/* Array[sf::KeyBoard::'KEY'] will give data about 'KEY' from the Array
	   ForEg. LastPressed[sf::KeyBoard::A] will give us time passed since  'A' was pressed last time */
public:
	//constructor
	InputManager();
	void AssignPlayer(Character* player);
	sf::Keyboard::Key JustPressedKey;
	//fxn to increase lastpressed and lastreleased of each key by dt
	void Update(const double dt);
	void GetInputDown(sf::Keyboard::Key key);
	void GetInputUp(sf::Keyboard::Key key);
	bool IsKeyPressed(sf::Keyboard::Key key);
	double GetLastPressed(sf::Keyboard::Key key);
	void SetControls(KeyboardControls control);
};

int GetJoystickButton(int val, int axis);
