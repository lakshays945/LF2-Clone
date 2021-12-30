#pragma once
#include "Math/Utilities.h"

class GameObject {
public:
	RealVector2D Position = {100,100};
	RealVector2D Velocity = { 0,0 };
	RealVector2D Scale = {1,1};
};
