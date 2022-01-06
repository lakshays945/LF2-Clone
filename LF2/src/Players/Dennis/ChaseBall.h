#pragma once
#include "Common/ProjectileBall.h"
#include "Common/Character.h"

class ChaseBall : public ProjectileBall {
public:
	ChaseBall();
	double TotalTime = 0;
	double MeanY;
	double InitialY;
	bool BeforeMean = true;
	bool Rebounded = false;
	Character* Target = nullptr;
	void Animate(sf::RenderWindow& window, const double dt);
	bool SetTarget();
	void OnCollision(int otherID, int selfID);
	void CalculateVelocity(const double dt);
};