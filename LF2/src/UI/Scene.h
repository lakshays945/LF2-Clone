#pragma once
#include "Button.h"

enum UI_SCENE_ID {
	_SCENE_ID_MAIN_MENU,
	_SCENE_ID_SETTINGS,
	//_SCENE_ID_LOADING,
	//_SCENE_ID_START_GAME,
	_SCENE_ID_PAUSE_GAME,
	_SCENE_ID_CHARACTER_SELECTION,
	_SCENE_ID_BACKGROUND_SELECTION,
};
class SceneManager;
class UI_SCENE {
public:
	bool IsActive = false;
	UI_SCENE_ID SceneID;
	SceneManager* Manager = nullptr;
	virtual void Update(const double dt) = 0;
	virtual void Animate(sf::RenderWindow& window, const double dt) = 0;
};

class SceneManager {
public:
	SceneManager(){}
	std::vector<UI_SCENE*> SceneIDArray;
	int CurrentScene = 0;
	void InitialisizeScenes();
};

class Scene_Main_Menu : public UI_SCENE {
public:
	Scene_Main_Menu();
	UI_Button Buttons[3];
	UI_Image Background;
	void Update(const double dt);
	void Animate(sf::RenderWindow& window, const double dt);
};

class Scene_Character_Select : public UI_SCENE {
public:
	Scene_Character_Select();
	UI_Button Buttons[6];
	UI_Image Background;
	UI_Image PlayerSelectImage[2];
	int Player1 = 0, Player2 = 0;
	void Animate(sf::RenderWindow& window, const double dt);
	void Update(const double dt);
};
