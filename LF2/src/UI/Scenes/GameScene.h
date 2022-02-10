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

class Scene_Game_Scene : public UI_SCENE {
public:
	Scene_Game_Scene();
	Character* Player1 = nullptr;
	Character* Player2 = nullptr;
	std::vector<GameObject*> Temp;
	bool Paused = false;
	void Animate(sf::RenderWindow& window, const double dt);
	void StartGame(int player1, int player2);
	void ExitGameScene();
	void Update(const double dt);
};
