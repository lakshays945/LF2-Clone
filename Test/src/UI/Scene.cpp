#include "Scene.h"

std::vector<UI_SCENE*> SceneManager;
int CurrentSceneIndex = 0;

Scene_Main_Menu::Scene_Main_Menu() {
	currentSceneIndex = &CurrentSceneIndex;
	SceneID = _SCENE_ID_MAIN_MENU;
	Buttons[0] = UI_Button(ButtonsSpr, "Fonts/Roboto.ttf", "Play", 20);
	Buttons[0].B_Image.Image.setTextureRect(sf::IntRect(15, 425, 275, 55));
	Buttons[0].AlignAtCenter();
	Buttons[0].SetPosition(RealVector2D(600, 200));

	Buttons[1] = UI_Button(Buttons[0].B_Image.Image, "Fonts/Roboto.ttf", "Settings", 20);
	Buttons[1].AlignAtCenter();
	Buttons[1].SetPosition(RealVector2D(600, 400));

	Buttons[2] = UI_Button(Buttons[0].B_Image.Image, "Fonts/Roboto.ttf", "Exit", 20);
	Buttons[2].AlignAtCenter();
	Buttons[2].SetPosition(RealVector2D(600, 600));

	Background.SetImage(BackGroundSpr);
	Background.AlignAtCenter();
	Background.SetPosition(RealVector2D(600, 400));

	for (int i = 1; i < NUMBEROF(Buttons); i++) {
		Buttons[i].UpdateListenerSize();
		Buttons[i].OnClick = [&]() {
			std::cout << "OnLeftClick Called\n";
			return 0;
		};
		Buttons[0].OnClick = [&]() {
			*currentSceneIndex = 1;
			return 0;
		};
		Buttons[2].OnClick = [&]() {
			return 0;
		};
		Buttons[0].UpdateListenerSize();
	}
	//static_assert(NUMBEROF(Buttons) == 3, "error");
}

void Scene_Main_Menu::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
	Background.Animate(window, dt);
	for (int i = 0; i < NUMBEROF(Buttons); i++) {
		Buttons[i].Animate(window, dt);
		if (Buttons[2].Listener.Clicked) {
			window.close();
		}
	}
}

void Scene_Main_Menu::Update(const double dt) {

}

Scene_Character_Select::Scene_Character_Select() {
	currentSceneIndex = &CurrentSceneIndex;
	Background.SetImage(BackGroundSpr);
	Background.AlignAtCenter();
	Background.SetPosition({ 600,400 });

	RealVector2D ProfileLoc[2] = { {175,300},
								   { 1025,300 },
	};

	SceneID = _SCENE_ID_CHARACTER_SELECTION;

	auto ProfileSelector = [=](int i) -> void
	{
		Buttons[i * 2] = UI_Button(ButtonsSpr, "Fonts/Roboto.ttf", "", 1); //LeftButton
		Buttons[i * 2].B_Image.Image.setTextureRect(sf::IntRect(15, 2, 48, 61));
		Buttons[i * 2].AlignAtCenter();
		Buttons[i * 2].SetPosition({ ProfileLoc[i].get_x() - 100,ProfileLoc[i].get_y() });

		Buttons[1 + i * 2] = UI_Button(ButtonsSpr, "Fonts/Roboto.ttf", "", 1); //RightButton
		Buttons[1 + i * 2].B_Image.Image.setTextureRect(sf::IntRect(73, 2, 48, 61));
		Buttons[1 + i * 2].AlignAtCenter();
		Buttons[1 + i * 2].SetPosition({ ProfileLoc[i].get_x() + 100,ProfileLoc[i].get_y() });

		PlayerSelectImage[i].SetImage(PlayersSpr);
		PlayerSelectImage[i].Image.setTextureRect(sf::IntRect(0, 0, 120, 120));
		PlayerSelectImage[i].AlignAtCenter();
		PlayerSelectImage[i].SetPosition(ProfileLoc[i]);

		Buttons[i * 2].OnClick = [&,i]() {
			sf::IntRect rect = PlayerSelectImage[i].Image.getTextureRect();
			if (rect.left > 10) {
				rect.left -= 120;
			}
			else {
				rect.left = 720;
			}
			PlayerSelectImage[i].Image.setTextureRect(rect);
			return 0;
		};

		Buttons[1 + i * 2].OnClick = [&,i]() {
			sf::IntRect rect = PlayerSelectImage[i].Image.getTextureRect();
			if (rect.left < 700) {
				rect.left += 120;
			}
			else {
				rect.left = 0;
			}
			PlayerSelectImage[i].Image.setTextureRect(rect);
			return 0;
		};
	};

	ProfileSelector(0);
	ProfileSelector(1);
	Buttons[4] = UI_Button(ButtonsSpr, "Fonts/Roboto.ttf", "Back", 20);
	Buttons[4].B_Image.Image.setTextureRect(sf::IntRect(15, 425, 275, 55));
	Buttons[4].AlignAtCenter();
	Buttons[4].SetPosition(RealVector2D(600,600));
	Buttons[4].OnClick = [&]() {
		*currentSceneIndex = 0;
		return 0;
	};

	for (int i = 0; i < NUMBEROF(Buttons); i++) {
		Buttons[i].UpdateListenerSize();
	}

}

void Scene_Character_Select::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
	Background.Animate(window, dt);
	PlayerSelectImage[0].Animate(window, dt);
	PlayerSelectImage[1].Animate(window, dt);
	for (int i = 0; i < NUMBEROF(Buttons); i++) {
		Buttons[i].Animate(window, dt);
	}
}

void Scene_Character_Select::Update(const double dt) {

}

void InitialisizeScenes(){
	Scene_Character_Select* CharacterSelect = new Scene_Character_Select;
	Scene_Main_Menu* MainMenu = new Scene_Main_Menu;
	MainMenu->IsActive = true;
	CharacterSelect->IsActive = true;
	SceneManager.push_back(MainMenu);
	SceneManager.push_back(CharacterSelect);
}
