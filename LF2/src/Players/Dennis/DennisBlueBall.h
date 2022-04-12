#pragma once
#include "Common/ProjectileBall.h"

class DennisBlueBall : public ProjectileBall {
public:
	DennisBlueBall();
	//DennisBlueBall(const DennisBlueBall& other);
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};