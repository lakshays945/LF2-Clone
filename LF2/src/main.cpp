#include <SFML/Graphics.hpp>
#include "Effects/EffectManager.h"
//#include "GameObject/GameObject.h"
#include "Players/Dennis/Dennis.h"
#include "Players/Davis/Davis.h"
#include <iostream>
static double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;

bool SortObjects(GameObject* g1, GameObject* g2) {
	return (g1->Z_Position < g2->Z_Position);
}

int main() {
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Little Fighter 2");
	//initialzing debug console window
	main_log = new DbgWindow("DebugWindow");
	DEBUG_SUCCESS("Launching game......");
	Davis Player;
	Davis Player2;
	Davis Player3;
	Davis Player4;
	EffectManager Eff_Manager(&window);
	Player.AssignEffectManager(&Eff_Manager);
	Player2.AssignEffectManager(&Eff_Manager);
	Player3.AssignEffectManager(&Eff_Manager);
	Player4.AssignEffectManager(&Eff_Manager);
	int times = 0;
	Player2.Position = { 400,400 };
	Player3.Position = { 500,400 };
	Player4.Position = { 400,600 };
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
				//Player2.Input_Manager.GetInputDown(event.key.code);
				//Player3.Input_Manager.GetInputDown(event.key.code);
				//Player4.Input_Manager.GetInputDown(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				Player.Input_Manager.GetInputUp(event.key.code);
				//Player2.Input_Manager.GetInputUp(event.key.code);
				//Player3.Input_Manager.GetInputUp(event.key.code);
				//Player4.Input_Manager.GetInputUp(event.key.code);
			}
		}
		window.clear(sf::Color(50, 60, 30));
		Player.Input_Manager.Update(DeltaTime);
		//Player2.Input_Manager.Update(DeltaTime);
		//Player3.Input_Manager.Update(DeltaTime);
		//Player4.Input_Manager.Update(DeltaTime);
		HandleCollisions();
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