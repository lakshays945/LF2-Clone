#include "HitBox.h"
#include "bandit.h"

#define COLLISION_THRESHOLD 25

bool HitBox::IsColliding(HitBox* other) {
	if (!IsActive || !other->IsActive) {
		return false;
	}
	if (abs(Player->Position.get_y() - other->Player->Position.get_y()) > COLLISION_THRESHOLD) {
		return false;
	}
	if (abs(Center.get_x() - other->Center.get_x()) <= (Width + other->Width) / 2 && abs(Center.get_y() - other->Center.get_y()) <= (Height + other->Height) / 2) {
		ImmuneList.push_back(other);
		return true;
	}
	return false;
}
void HitBox::AssignPlayer(Bandit* player) {
	Player = player;
}