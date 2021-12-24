#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

enum State {
	IDLE = 0, WALKING = 1, RUNNING = 2, JUMPING = 3,
	HITTING = 4, GETTING_HIT = 5, FALLING = 6, JUMPINGATTACK = 7, RUNATTACK = 8, CROUCH = 9
}; //Handle with care dont change order (Can add on top of it)

class Bandit;
class AnimationSheet {
private:
	Bandit* Player = nullptr; //a pointer to player to which sheet is assigned
public:
	//One time means complete animation has to be played exaclty one time before we can do anything with our inputs
	bool OneTime = false;
	std::vector <sf::Texture> Textures;
	std::vector <sf::Sprite> Sprites;
	std::vector <double> DrawTimes; // the Nth element of this vector will give time at which Nth sprite is now done being drawn
	double MaxTime = 0; //Time taken to draw all sprites (Summation ot DrawTimes(i))
	double Time = 0; //Time passed since 1st sprite is drawn (resets to 0 if >= MaxTime)
	void AssignTextures() {
		for (int i = 0; i < Textures.size(); i++){
			Sprites[i].setTexture(Textures[i]);
			Sprites[i].setOrigin(sf::Vector2f(40, 40));
		}
	}
	void AssignPlayer(Bandit* player) {
		Player = player;
	}
	int GetCorrectIndex();
};

class StateManager {
private:
	Bandit* Player = nullptr;//a pointer to player to which StateManager is assigned

	//IsChangePossible[i][j] tells us if state change is possible from 'i' state to 'j' state
									        //idle  walking  running  jumping  hitting  getting_hit  falling   //jumpattack  //runattack    //coruch
	const bool IsChangePossible[10][10] = { {  0,       1,      1,       1,       1,        1,          1,          1,            1,         1        },   //idle
										    {  0,       0,      1,       1,       1,        1,          1,          1,            1,         1        },   //walking
										    {  0,       1,      0,       1,       1,        1,          1,          1,            1,         1        },   //running
										    {  0,       0,      0,       0,       0,        1,          1,          1,            1,         1        },   //jumping
										    {  0,       0,      0,       0,       0,        1,          1,          0,            1,         1        },   //hitting
										    {  0,       1,      1,       1,       1,        0,          1,          1,            1,         1        },   //getting_hit
										    {  0,       1,      1,       1,       1,        1,          0,          1,            1,         1        },   //falling
										    {  0,       0,      0,       0,       0,        1,          1,          0,            1,         1        },   //jumpattack
											{  0,       1,      1,       1,       1,        1,          1,          1,            0,         1        },   //runattack
											{  0,       1,      1,       1,       1,        1,          1,          1,            1,         0        }, };//crouch

public:

	void AssignPlayer(Bandit* player) {
		Player = player;
	}

	void TryStateChange(State state, const double LastPressed, const int data=0); 
	void ForceStateChange(State state,const int data=0);
};

class InputManager {
private:
	Bandit* Player = nullptr; //a pointer to player to which InputManager is assigned
	double LastPressed[102]; //stores time since key was pressed last time
	double LastReleased[102]; //stores time since key was released last time
	double DoubleKeyTimes[102]; //max time delay to register a double press
	int KeyData[102]; //data related to key (Might be useful in future)
	bool IsPressed[102]; //tells if key is currently being pressed
	State KeyToState[102]; //store state related to each key 
	State DoubleKeyToState[102]; //stores state related to double press of key

	/* Array[sf::KeyBoard::'KEY'] will give data about 'KEY' from the Array
	   ForEg. LastPressed[sf::KeyBoard::A] will give us time passed since  'A' was pressed last time */
public:

	InputManager() {
		//initialising above arrays
		for (int i = 0; i < 102; i++) {
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
		DoubleKeyToState[sf::Keyboard::D] = RUNNING;
		DoubleKeyToState[sf::Keyboard::A] = RUNNING;
		DoubleKeyTimes[sf::Keyboard::D] = 0.3;
		DoubleKeyTimes[sf::Keyboard::A] = 0.3;
		KeyData[sf::Keyboard::D] = 1;
		KeyData[sf::Keyboard::A] = -1;
	}

	void AssignPlayer(Bandit* player) {
		Player = player;
	}

	//fxn to increase lastpressed and lastreleased of each key by dt
	void Update(const double dt) {
		for (int i = 0; i < 102; i++) {
			if (LastPressed[i] < 10) { //we dont increase after 10 as it's not required
				LastPressed[i] += dt;
			}
			if (LastReleased[i] < 10) { //we dont increase after 10 as it's not required
				LastReleased[i] += dt;
			}
		}
	}

	void GetInputDown(sf::Keyboard::Key key);
	void GetInputUp(sf::Keyboard::Key key);
	bool IsKeyPressed(sf::Keyboard::Key key) {
		return IsPressed[key];
	}
};