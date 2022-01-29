#include <SFML/Graphics.hpp>
#include "Effects/EffectManager.h"
#include "Players/Dennis/Dennis.h"
#include "Players/Davis/Davis.h"
#include "Players/Deep/Deep.h"
#include "Players/Firen/Firen.h"
#include "Players/Freeze/Freeze.h"
#include "Players/John/John.h"
#include "Players/Woody/Woody.h"
#include "Weapons/BaseBallBat.h"
#include "Weapons/HookWeapon.h"
#include "Weapons/IceSword.h"
double DeltaTime = 0.016666667;
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
	EffectManager Eff_Manager(&window);
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
		Player1Control.SpecialAttack4Key = sf::Keyboard::I;
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
		Player2Control.SpecialAttack4Key = sf::Keyboard::H;
	}
	Freeze Player1;
	Dennis Player2;
	/*Dennis Player3;
	Deep Player4;
	Freeze Player5;
	Davis Player6;
	John Player7;*/
	BaseBallBat Bat;
	HookWeapon Hook;
	//Player.SetScale({ 1.2f,1.2f });
	//Player2.SetScale({ 1.2f,1.2f });
	Player1.SetControls(Player1Control);
	Player2.SetControls(Player2Control);
	Player1.AssignEffectManager(&Eff_Manager);
	Player2.AssignEffectManager(&Eff_Manager);
	Player2.Position = { 200,400 };
	/*Player3.AssignEffectManager(&Eff_Manager);
	Player4.AssignEffectManager(&Eff_Manager);
	Player5.AssignEffectManager(&Eff_Manager);
	Player6.AssignEffectManager(&Eff_Manager);
	Player7.AssignEffectManager(&Eff_Manager);
	Player3.Position = { 300,400 };
	Player4.Position = { 400,400 };
	Player5.Position = { 500,400 };
	Player6.Position = { 600,400 };
	Player7.Position = { 700,400 };*/
	Bat.SetPosition({200,100}, 75);
	Hook.SetPosition({ 200,200 }, 175);
	std::vector <GameObject*> Temp;
	sf::Clock Clock;
	while (window.isOpen()) {
		DeltaTime = (Clock.getElapsedTime()).asSeconds();
		Clock.restart();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				Player1.Input_Manager.GetInputDown(event.key.code);
				Player2.Input_Manager.GetInputDown(event.key.code);
				//Player3.Input_Manager.GetInputDown(event.key.code);
				//Player4.Input_Manager.GetInputDown(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				Player1.Input_Manager.GetInputUp(event.key.code);
				Player2.Input_Manager.GetInputUp(event.key.code);
				//Player3.Input_Manager.GetInputUp(event.key.code);
				//Player4.Input_Manager.GetInputUp(event.key.code);
			}
		}
		window.clear(sf::Color(180, 180, 180));
		Player1.Input_Manager.Update(DeltaTime);
		Player2.Input_Manager.Update(DeltaTime);
		/*Player3.Input_Manager.Update(DeltaTime);
		Player4.Input_Manager.Update(DeltaTime);
		Player5.Input_Manager.Update(DeltaTime);
		Player6.Input_Manager.Update(DeltaTime);
		Player7.Input_Manager.Update(DeltaTime);*/
		HandleCollisions();
		//UpdateInputs();
		Player1.Update(DeltaTime, window);
		Player2.Update(DeltaTime, window);
		/*Player3.Update(DeltaTime, window);
		Player4.Update(DeltaTime, window);
		Player5.Update(DeltaTime, window);
		Player6.Update(DeltaTime, window);
		Player7.Update(DeltaTime, window);*/
		Temp = GameObjectIDArray;
		std::sort(Temp.begin(), Temp.end(), SortObjects);
		for (int i = 0; i < GameObjectIDArray.size(); i++) {
			Temp[i]->Animate(window, DeltaTime);
		}
		Eff_Manager.Update(DeltaTime);
		window.display();
		//DEBUG_INFO("Fps = {}", 1 / DeltaTime);
	}
	return 0;
}