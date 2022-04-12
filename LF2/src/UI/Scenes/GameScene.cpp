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

	//ending scenes 
	EndImages[0].SetImage(GameOverSpr);
	sf::Color color = EndImages[0].Image.getColor();
	color.a = 150;
	EndImages[0].Image.setColor(color);
	EndImages[0].SetPosition({ 600,400 });
	EndImages[0].AlignAtCenter();

	EndTexts[0].SetText("Fonts/stocky.ttf", "WIN", 50);
	EndTexts[1].SetText("Fonts/stocky.ttf", "LOSE", 50);
	EndTexts[0].Text.setFillColor(sf::Color::Green);
	EndTexts[1].Text.setFillColor(sf::Color::Red);
	EndTexts[0].SetPosition({ 400,275 });
	EndTexts[1].SetPosition({ 800,275 });
	EndTexts[0].AlignAtCenter();
	EndTexts[1].AlignAtCenter();

	EndButtons[0] = UI_Button(ButtonsSpr, "Fonts/Roboto.ttf", "Play Again", 20);
	EndButtons[0].B_Image.Image.setTextureRect(sf::IntRect(15, 425, 275, 55));
	EndButtons[0].AlignAtCenter();
	EndButtons[0].UpdateListenerSize();
	EndButtons[0].SetPosition({ 400,575 });

	EndButtons[0].OnClick = [&]() {
		ExitGameScene();
		StartGame(Player1Index, Player2Index);
		return 0;
	};

	EndButtons[1] = UI_Button(ButtonsSpr, "Fonts/Roboto.ttf", "Main Menu", 20);
	EndButtons[1].B_Image.Image.setTextureRect(sf::IntRect(15, 425, 275, 55));
	EndButtons[1].SetPosition({ 800,575 });
	EndButtons[1].AlignAtCenter();
	EndButtons[1].UpdateListenerSize();

	EndButtons[1].OnClick = [&]() {
		ExitGameScene();
		Manager->CurrentScene = 0;
		return 0;
	};
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
		if (event.type == sf::Event::JoystickButtonPressed && !GameEnded && !Paused) {
			Player1->Input_Manager.GetInputDown(Player1->JoystickToKeyboard[GetJoystickButton(event.joystickButton.button, -1)]);
			DEBUG_INFO("BUtton = {}", event.joystickButton.button);
		}
		if (event.type == sf::Event::JoystickButtonReleased && !GameEnded && !Paused) {
			Player1->Input_Manager.GetInputUp(Player1->JoystickToKeyboard[GetJoystickButton(event.joystickButton.button, -1)]);
		}
		if (event.type == sf::Event::JoystickMoved && !GameEnded && !Paused) {
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
		if (event.type == sf::Event::KeyPressed && !Paused && !GameEnded) {
			Player1->Input_Manager.GetInputDown(event.key.code);
			Player2->Input_Manager.GetInputDown(event.key.code);
		}
		if (event.type == sf::Event::KeyReleased && !GameEnded) {
			Player1->Input_Manager.GetInputUp(event.key.code);
			Player2->Input_Manager.GetInputUp(event.key.code);
		}
	}
	if (Paused) dt = 0;
	if (!GameEnded) {
		Player1->Input_Manager.Update(dt);
		Player2->Input_Manager.Update(dt);
		if (Player1->HealthPoints <= 0 && Player2->HealthPoints <= 0) {
			Player1->Input_Manager = InputManager();
			Player2->Input_Manager = InputManager();
			Result = 0;
			GameEnded = true;
		}
		else if (Player1->HealthPoints <= 0) {
			Player1->Input_Manager = InputManager();
			Player2->Input_Manager = InputManager();
			EndTexts[1].SetPosition({ 400,200 });
			EndTexts[0].SetPosition({ 800,200 });
			Result = -1;
			GameEnded = true;
		}
		else if (Player2->HealthPoints <= 0) {
			Player1->Input_Manager = InputManager();
			Player2->Input_Manager = InputManager();
			EndTexts[0].SetPosition({ 400,200 });
			EndTexts[1].SetPosition({ 800,200 });
			Result = 1;
			GameEnded = true;
		}
	}
	else {
		//double dec = TimeSinceEnded / 100;
		for (int i = 0; i < GameBG.BGSheet.DrawTimes.size(); i++) {
			if (TimeSinceEnded > 4) break;
			sf::Color color = OriginalBG.Sprites[i].getColor();
			color.r = color.r / 3 + (1 / 8.0) * color.r * (4 - TimeSinceEnded);
			color.g = color.g / 3 + (1 / 8.0) * color.g * (4 - TimeSinceEnded);
			color.b = color.b / 3 + (1 / 8.0) * color.b * (4 - TimeSinceEnded);
			GameBG.BGSheet.Sprites[i].setColor(color);
		}
		TimeSinceEnded += dt;
		dt /= 2;
		if (TimeSinceEnded > 5) {
			if (Result == 1) Player1->State_Manager.ForceStateChange(IDLE);
			if (Result == -1) Player2->State_Manager.ForceStateChange(IDLE);
			if ((RealVector2D(400, 300) - Player1->Position).Magnitude() > 5)
				Player1->Velocity = (RealVector2D(400, 300) - Player1->Position).GetUnit() * 500;
			else Player1->Stop();
			if ((RealVector2D(800, 300) - Player2->Position).Magnitude() > 5)
				Player2->Velocity = (RealVector2D(800, 300) - Player2->Position).GetUnit() * 500;
			else Player2->Stop();
			Player1->WallUp = -100;
			Player2->WallUp = -100;
			Player1->Translate(dt);
			Player2->Translate(dt);
		}
	}
	HandleCollisions();
	Player1->Update(dt, window);
	Player2->Update(dt, window);
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
	if (TimeSinceEnded > 4) {
		EndImages[0].Animate(window, dt);
		EndTexts[0].Animate(window, dt);
		EndTexts[1].Animate(window, dt);
		Player1->Animate(window, 0);
		Player2->Animate(window, 0);
		if (TimeSinceEnded > 6) {
			EndButtons[0].Animate(window, 2 * dt);
			EndButtons[1].Animate(window, 2 * dt);
		}
	}
}

void Scene_Game_Scene::StartGame(int player1, int player2){
	Player1Index = player1;
	Player2Index = player2;
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
	OriginalBG = GameBG.BGSheet;
	GameBG.Position = RealVector2D(600, 550);
	GameEnded = false;
	//Player2->HealthPoints = 2;
	//Player1->HealthPoints = 2;
	TimeSinceEnded = 0;
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
