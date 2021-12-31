#include <SFML/Graphics.hpp>
#include "Players/bandit.h"
#include "Effects/EffectManager.h"
#include <iostream>
static double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;
int main() {
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Little Fighter 2");
	//initialzing debug console window
	main_log = new DbgWindow("DebugWindow");
	DEBUG_SUCCESS("Launching game......");

	Bandit Player;
	Bandit Player2;
	EffectManager Eff_Manager(&window);
	Player.AssignEffectManager(&Eff_Manager);
	DEBUG_TRACE("spawning player 1");
	Player2.AssignEffectManager(&Eff_Manager);
	DEBUG_TRACE("spawning player 2");
	int times = 0;
	Player2.Position = { 400,400 };
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
			}
			if (event.type == sf::Event::KeyReleased) {
				Player.Input_Manager.GetInputUp(event.key.code);
			}
		}
		window.clear(sf::Color(50, 60, 30));
		Player.Input_Manager.Update(DeltaTime);
		HandleCollisions();
		Player.Update(DeltaTime, window);
		Player2.Update(DeltaTime, window);
		Eff_Manager.Update(DeltaTime);
		window.display();
	}
	return 0;
}