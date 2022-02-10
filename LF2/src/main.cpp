#include <SFML/Graphics.hpp>
#include "UI/Scenes/GameScene.h"
#include"UI/Scene.h"

double DeltaTime = 0.016666667;
const int resX = 1200;
const int resY = 800;

int main() {
	sf::RenderWindow window(sf::VideoMode(resX, resY), "Little Fighter 2");
	SceneManager MainSceneManager;
	MainSceneManager.InitialisizeScenes();
	main_log = new DbgWindow("DebugWindow");
	DEBUG_SUCCESS("Launching game......");
	sf::Clock Clock;
	while (window.isOpen()) {
		DeltaTime = (Clock.getElapsedTime()).asSeconds();
		Clock.restart();
		window.clear(sf::Color(180, 180, 180));
		MainSceneManager.SceneIDArray[MainSceneManager.CurrentScene]->Animate(window, DeltaTime);
		window.display();
	}
	return 0;
}