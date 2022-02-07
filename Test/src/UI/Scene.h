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
class UI_SCENE {
public:
	bool IsActive = false;
	UI_SCENE_ID SceneID;
	int* currentSceneIndex = nullptr;
	virtual void Update(const double dt) = 0;
	virtual void Animate(sf::RenderWindow& window, const double dt) = 0;
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
	UI_Button Buttons[4];
	UI_Image Background;
	UI_Image PlayerSelectImage[2];
	void Animate(sf::RenderWindow& window, const double dt);
	void Update(const double dt);
};

void InitialisizeScenes();

extern std::vector<UI_SCENE*> SceneManager;
extern int CurrentSceneIndex;