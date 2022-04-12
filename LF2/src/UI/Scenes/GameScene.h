#pragma once
#include "UI/Scene.h"
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
#include "Backgrounds/Background.h"

class UI_HealthBar : public UI_Element {
public:
	UI_HealthBar();
	UI_Image Background;
	UI_Image HealthBar;
	Character* Parent = nullptr;
	int HpPrecent = 100;
	void UpdateSize(int hpPercent);
	void Animate(sf::RenderWindow& window, const double dt);
};

class UI_StaminaBar : public UI_Element {
public:
	UI_StaminaBar();
	UI_Image Background;
	UI_Image StaminaBar;
	Character* Parent = nullptr;
	int StaminaPrecent = 100;
	void UpdateSize(int hpPercent);
	void Animate(sf::RenderWindow& window, const double dt);
};

class Scene_Game_Scene : public UI_SCENE {
public:
	Scene_Game_Scene();
	bool GameEnded = false;
	int Result = 0;
	Character* Player1 = nullptr;
	Character* Player2 = nullptr;
	UI_Image Player1Image;
	UI_Image Player2Image;
	UI_HealthBar Player1HealthBar;
	UI_StaminaBar Player1StaminaBar;
	UI_HealthBar Player2HealthBar;
	UI_StaminaBar Player2StaminaBar;
	BackGround GameBG;
	AnimationSheet OriginalBG;
	int Player1Index = 1;
	int Player2Index = 1;
	UI_Button EndButtons[2];
	UI_Image EndImages[3];
	UI_Text EndTexts[5];

	std::vector<GameObject*> Temp;
	bool Paused = false;
	double TimeSinceEnded = 0;
	void Animate(sf::RenderWindow& window, const double dt);
	void StartGame(int player1, int player2);
	void ExitGameScene();
	void Update(const double dt);
};
