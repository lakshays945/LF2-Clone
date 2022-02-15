#include "GameScene.h"

bool SortObjects(GameObject* g1, GameObject* g2) {
	return (g1->Z_Position < g2->Z_Position);
}

Character* GetPlayerFromIndex(int index) {
	switch (index){
	case 0: {return new Dennis; }
	case 1: {return new Davis; }
	case 2: {return new Firen; }
	case 3: {return new Freeze; }
	case 4: {return new John; }
	case 5: {return new Woody; }
	case 6: {return new Deep; }
	default: {return new Dennis; DEBUG_ERROR("NO INDEX MATCHED"); }
	}
}

Scene_Game_Scene::Scene_Game_Scene() {
	Player1HealthBar.SetPosition(RealVector2D(100, 100));
	Player2HealthBar.SetPosition(RealVector2D(1000, 100));
	Player1StaminaBar.SetPosition(RealVector2D(100, 150));
	Player2StaminaBar.SetPosition(RealVector2D(1000, 150));
}

void Scene_Game_Scene::Animate(sf::RenderWindow& window, double dt) {
	if (!IsActive) {
		return;
	}
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::P) {
				Paused = !Paused;
			}
			else if (event.key.code == sf::Keyboard::E) {
				Manager->CurrentScene = 0;
				ExitGameScene();
				return;
			}
		}
		if (event.type == sf::Event::JoystickButtonPressed) {
			Player1->Input_Manager.GetInputDown(Player1->JoystickToKeyboard[GetJoystickButton(event.joystickButton.button, -1)]);
			DEBUG_INFO("BUtton = {}", event.joystickButton.button);
		}
		if (event.type == sf::Event::JoystickButtonReleased) {
			Player1->Input_Manager.GetInputUp(Player1->JoystickToKeyboard[GetJoystickButton(event.joystickButton.button, -1)]);
		}
		if (event.type == sf::Event::JoystickMoved) {
			int action = GetJoystickButton(sf::Joystick::getAxisPosition(0, event.joystickMove.axis), event.joystickMove.axis);
			if (action >= 17) {
				Player1->Input_Manager.GetInputUp(Player1->JoystickToKeyboard[action - 7]);
				Player1->Input_Manager.GetInputUp(Player1->JoystickToKeyboard[action - 6]);
			}
			else {
				Player1->Input_Manager.GetInputDown(Player1->JoystickToKeyboard[action]);
			}
			DEBUG_INFO("Button = {}", action);
		}
		if (event.type == sf::Event::KeyPressed && !Paused) {
			Player1->Input_Manager.GetInputDown(event.key.code);
			Player2->Input_Manager.GetInputDown(event.key.code);
			//Player3.Input_Manager.GetInputDown(event.key.code);
			//Player4.Input_Manager.GetInputDown(event.key.code);
		}
		if (event.type == sf::Event::KeyReleased) {
			Player1->Input_Manager.GetInputUp(event.key.code);
			Player2->Input_Manager.GetInputUp(event.key.code);
			//Player3.Input_Manager.GetInputUp(event.key.code);
			//Player4.Input_Manager.GetInputUp(event.key.code);
		}
	}
	if (!sf::Joystick::isConnected(0)) {
		DEBUG_INFO("Dissconnected");
	}
	if (Paused) dt = 0;
	Player1->Input_Manager.Update(dt);
	Player2->Input_Manager.Update(dt);
	/*Player3.Input_Manager.Update(DeltaTime);
	Player4.Input_Manager.Update(DeltaTime);
	Player5.Input_Manager.Update(DeltaTime);
	Player6.Input_Manager.Update(DeltaTime);
	Player7.Input_Manager.Update(DeltaTime);*/
	HandleCollisions();
	//UpdateInputs();
	Player1->Update(dt, window);
	Player2->Update(dt, window);
	/*Player3.Update(DeltaTime, window);
	Player4.Update(DeltaTime, window);
	Player5.Update(DeltaTime, window);
	Player6.Update(DeltaTime, window);
	Player7.Update(DeltaTime, window);*/
	Temp = GameObjectIDArray;
	std::sort(Temp.begin(), Temp.end(), SortObjects);
	GameBG.Animate(window, dt);
	for (int i = 0; i < GameObjectIDArray.size(); i++) {
		Temp[i]->Animate(window, dt);
	}
	Player1HealthBar.UpdateSize(Player1->HealthPoints/6.0);
	Player2HealthBar.UpdateSize(Player2->HealthPoints/6.0);
	Player1StaminaBar.UpdateSize(Player1->ManaPoints);
	Player2StaminaBar.UpdateSize(Player2->ManaPoints);
	Player1HealthBar.Animate(window, dt);
	Player2HealthBar.Animate(window, dt);
	Player1StaminaBar.Animate(window, dt);
	Player2StaminaBar.Animate(window, dt);
}

void Scene_Game_Scene::StartGame(int player1, int player2){
	Player1 = GetPlayerFromIndex(player1);
	Player2 = GetPlayerFromIndex(player2);
	KeyboardControls Player1Control;
	KeyboardControls Player2Control;
	{
		Player1Control.UpKey = sf::Keyboard::W;
		Player1Control.DownKey = sf::Keyboard::S;
		Player1Control.RightKey = sf::Keyboard::D;
		Player1Control.LeftKey = sf::Keyboard::A;
		Player1Control.AttackKey = sf::Keyboard::Q;
		Player1Control.JumpKey = sf::Keyboard::Space;
		Player1Control.GuardKey = sf::Keyboard::LControl;
		Player1Control.SpecialAttack1Key = sf::Keyboard::T;
		Player1Control.SpecialAttack2Key = sf::Keyboard::Y;
		Player1Control.SpecialAttack3Key = sf::Keyboard::U;
		Player1Control.SpecialAttack4Key = sf::Keyboard::I;

		Player1->JoystickToKeyboard[2] = Player1Control.JumpKey;
		Player1->JoystickToKeyboard[1] = Player1Control.GuardKey;
		Player1->JoystickToKeyboard[3] = Player1Control.AttackKey;
		Player1->JoystickToKeyboard[0] = Player1Control.SpecialAttack1Key;
		Player1->JoystickToKeyboard[5] = Player1Control.SpecialAttack2Key;
		Player1->JoystickToKeyboard[7] = Player1Control.SpecialAttack3Key;
		Player1->JoystickToKeyboard[6] = Player1Control.SpecialAttack4Key;
		Player1->JoystickToKeyboard[10] = Player1Control.RightKey;
		Player1->JoystickToKeyboard[11] = Player1Control.LeftKey;
		Player1->JoystickToKeyboard[12] = Player1Control.UpKey;
		Player1->JoystickToKeyboard[13] = Player1Control.DownKey;
		Player1->JoystickToKeyboard[14] = Player1Control.SpecialAttack3Key;
		Player1->JoystickToKeyboard[15] = Player1Control.SpecialAttack4Key;
	}
	{
		Player2Control.UpKey = sf::Keyboard::Up;
		Player2Control.DownKey = sf::Keyboard::Down;
		Player2Control.RightKey = sf::Keyboard::Right;
		Player2Control.LeftKey = sf::Keyboard::Left;
		Player2Control.AttackKey = sf::Keyboard::Enter;
		Player2Control.JumpKey = sf::Keyboard::RShift;
		Player2Control.GuardKey = sf::Keyboard::RControl;
		Player2Control.SpecialAttack1Key = sf::Keyboard::K;
		Player2Control.SpecialAttack2Key = sf::Keyboard::L;
		Player2Control.SpecialAttack3Key = sf::Keyboard::J;
		Player2Control.SpecialAttack4Key = sf::Keyboard::H;

		Player2->JoystickToKeyboard[0] = Player2Control.JumpKey;
		Player2->JoystickToKeyboard[1] = Player2Control.GuardKey;
		Player2->JoystickToKeyboard[2] = Player2Control.AttackKey;
		Player2->JoystickToKeyboard[3] = Player2Control.SpecialAttack1Key;
		//Player2->JoystickToKeyboard[4] = Player2Control.SpecialAttack1Key;
		Player2->JoystickToKeyboard[5] = Player2Control.SpecialAttack2Key;
		Player2->JoystickToKeyboard[10] = Player2Control.DownKey;
		Player2->JoystickToKeyboard[11] = Player2Control.RightKey;
		Player2->JoystickToKeyboard[12] = Player2Control.UpKey;
		Player2->JoystickToKeyboard[13] = Player2Control.LeftKey;
		Player2->JoystickToKeyboard[14] = Player2Control.SpecialAttack3Key;
		Player2->JoystickToKeyboard[15] = Player2Control.SpecialAttack4Key;
	}
	Player1->SetControls(Player1Control);
	Player2->SetControls(Player2Control);
	Player1->Position = RealVector2D(100, 500);
	Player1->Z_Position = Player1->Position.get_y();
	Player2->Position = RealVector2D(1100, 500);
	Player2->Z_Position = Player2->Position.get_y();
	Player2->Direction = -1;
	GameBG.LoadAnimationSheet(ForestBGSheet);
	GameBG.Position = RealVector2D(600, 550);
}

void Scene_Game_Scene::ExitGameScene(){
	delete Player1;
	delete Player2;
	GameObjectIDArray.clear();
	HitBoxIDArray.clear();
	WeaponIDArray.clear();
	CharacterIDArray.clear();
	GameObject::nextID = 0;
	HitBox::nextID = 0;
	Weapon::nextID = 0;
	Character::nextCharacterID = 0;
}

void Scene_Game_Scene::Update(const double dt) {
}

UI_HealthBar::UI_HealthBar(){
	Background = UI_Image(ButtonsSpr);
	Background.Image.setTextureRect(sf::IntRect(0,130,160,40));
	Background.AlignAtCenter();
	HealthBar = UI_Image(ButtonsSpr);
	HealthBar.Image.setTextureRect(sf::IntRect(0, 80, 140, 40));
	HealthBar.AlignAtCenter();
}

void UI_HealthBar::UpdateSize(int hpPercent){
	//DEBUG_INFO("Hp % = {}", hpPercent);
	if (HpPrecent == hpPercent) return;
	HpPrecent = std::max(hpPercent,0);
	HealthBar.Image.setTextureRect(sf::IntRect(0, 80, (140 * HpPrecent) / 100, 40));
}

void UI_HealthBar::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) return;
	Background.Position = Position;
	HealthBar.Position = Position;
	Background.Animate(window, dt);
	HealthBar.Animate(window, dt);
}

UI_StaminaBar::UI_StaminaBar() {
	Background = UI_Image(ButtonsSpr);
	Background.Image.setTextureRect(sf::IntRect(0, 130, 160, 40));
	Background.AlignAtCenter();
	StaminaBar = UI_Image(ButtonsSpr);
	StaminaBar.Image.setTextureRect(sf::IntRect(5, 185, 140, 40));
	StaminaBar.AlignAtCenter();
}

void UI_StaminaBar::UpdateSize(int staminaPercent) {
	//DEBUG_INFO("Hp % = {}", hpPercent);
	if (StaminaPrecent == staminaPercent) return;
	StaminaPrecent = std::max(staminaPercent, 0);
	StaminaBar.Image.setTextureRect(sf::IntRect(5, 185, (140 * StaminaPrecent) / 100, 40));
}

void UI_StaminaBar::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) return;
	Background.Position = Position;
	StaminaBar.Position = Position;
	Background.Animate(window, dt);
	StaminaBar.Animate(window, dt);
}
