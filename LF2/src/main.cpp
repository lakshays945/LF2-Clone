#include <SFML/Graphics.hpp>
#include "Players/bandit.h"
#include <iostream>
static double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;
int main() {
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Little Fighter 2");
	HitBox temp(RealVector2D(600, 400), 20, 40);
	Bandit Player;
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
		if (Player.DamageHitBox.IsColliding(temp)) {
			std::cout << "Player->temp\n";
		}
		if (temp.IsColliding(Player.DamageHitBox)) {
			std::cout << "temp->Player\n";
		}
		window.clear(sf::Color(50, 60, 30));
		Player.Input_Manager.Update(DeltaTime);
		temp.DrawBox(window);
		Player.Update(DeltaTime, window);
		window.display();
	}
	return 0;
}