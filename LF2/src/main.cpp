#include <SFML/Graphics.hpp>
#include "Effects/EffectManager.h"
//#include "GameObject/GameObject.h"
#include "Players/Dennis/Dennis.h"
#include "Players/Davis/Davis.h"
#include "Players/Firen/Firen.h"
#include "Players/Freeze/Freeze.h"
#include <iostream>
static double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;

bool SortObjects(GameObject* g1, GameObject* g2) {

	return (g1->Z_Position < g2->Z_Position);
}
Controls Player1Control;
Controls Player2Control;
int main() {
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Little Fighter 2");
	//initialzing debug console window
	main_log = new DbgWindow("DebugWindow");
	DEBUG_SUCCESS("Launching game......");
	{
		Player1Control.UpKey = sf::Keyboard::W;
		Player1Control.DownKey = sf::Keyboard::S;
		Player1Control.RightKey = sf::Keyboard::D;
		Player1Control.LeftKey = sf::Keyboard::A;
		Player1Control.AttackKey = sf::Keyboard::Q;
		Player1Control.JumpKey = sf::Keyboard::Space;
		Player1Control.SpecialAttack1Key = sf::Keyboard::T;
		Player1Control.SpecialAttack2Key = sf::Keyboard::Y;
		Player1Control.SpecialAttack3Key = sf::Keyboard::U;
	}
	{
		Player2Control.UpKey = sf::Keyboard::Up;
		Player2Control.DownKey = sf::Keyboard::Down;
		Player2Control.RightKey = sf::Keyboard::Right;
		Player2Control.LeftKey = sf::Keyboard::Left;
		Player2Control.AttackKey = sf::Keyboard::Enter;
		Player2Control.JumpKey = sf::Keyboard::RShift;
		Player2Control.SpecialAttack1Key = sf::Keyboard::K;
		Player2Control.SpecialAttack2Key = sf::Keyboard::L;
		Player2Control.SpecialAttack3Key = sf::Keyboard::J;
	}
	Firen Player2;
	Dennis Player;
	//Player.SetScale({ 1.2f,1.2f });
	//Player2.SetScale({ 1.2f,1.2f });
	Player.SetControls(Player1Control);
	Player2.SetControls(Player2Control);
	Davis Player3;
	Firen Player4;
	EffectManager Eff_Manager(&window);
	Player.AssignEffectManager(&Eff_Manager);
	Player2.AssignEffectManager(&Eff_Manager);
	Player3.AssignEffectManager(&Eff_Manager);
	Player4.AssignEffectManager(&Eff_Manager);
	Player2.Position = { 400,400 };
	Player3.Position = { 500,400 };
	Player4.Position = { 600,400 };
	sf::Clock Clock;
	while (window.isOpen()) {
		DeltaTime = (Clock.getElapsedTime()).asSeconds();
		Clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				Player.Input_Manager.GetInputDown(event.key.code);
				Player2.Input_Manager.GetInputDown(event.key.code);
				//Player3.Input_Manager.GetInputDown(event.key.code);
				//Player4.Input_Manager.GetInputDown(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				Player.Input_Manager.GetInputUp(event.key.code);
				Player2.Input_Manager.GetInputUp(event.key.code);
				//Player3.Input_Manager.GetInputUp(event.key.code);
				//Player4.Input_Manager.GetInputUp(event.key.code);
			}
		}
		window.clear(sf::Color(50, 60, 30));
		Player.Input_Manager.Update(DeltaTime);
		Player2.Input_Manager.Update(DeltaTime);
		Player3.Input_Manager.Update(DeltaTime);
		Player4.Input_Manager.Update(DeltaTime);
		HandleCollisions();
		//UpdateInputs();
		Player.Update(DeltaTime, window);
		Player2.Update(DeltaTime, window);
		Player3.Update(DeltaTime, window);
		Player4.Update(DeltaTime, window);
		std::vector <GameObject*> Temp = GameObjectIDArray;
		std::sort(Temp.begin(), Temp.end(), SortObjects);
		for (int i = 0; i < GameObjectIDArray.size(); i++) {
			Temp[i]->Animate(window, DeltaTime);
		}
		Eff_Manager.Update(DeltaTime);
		window.display();
	}
	return 0;
}