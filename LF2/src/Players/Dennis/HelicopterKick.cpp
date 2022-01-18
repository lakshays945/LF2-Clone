#include "HelicopterKick.h"
#include "Dennis.h"

HelicopterKick::HelicopterKick() {
	IsActive = false;
	RegisterHitBox = HitBox(Position, 10, 10, HB_TYPE_TRIGGER);
	ProjectileReboundHitBox = HitBox(Position, 60, 40, HB_TYPE_REBOUND);
	for (int i = 0; i < 500; i++) {
		HitCountArray.push_back(0);
	}
}

void HelicopterKick::GoBack(){
	IsActive = false;
	Position = Parent->Position;
	RegisterHitBox.Disable();
	ProjectileReboundHitBox.Disable();
}

void HelicopterKick::OnCollision(int otherID, int selfID){
	if (HitBoxIDArray[otherID]->Game_Object->ID == RegisterHitBox.IgnoreObjectID) {
		return;
	}
	if (HitBoxIDArray[selfID]->Type == HB_TYPE_TRIGGER) {
		if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Character && HitBoxIDArray[otherID]->Type == HB_TYPE_DAMAGE) {
			HitCountArray[otherID]++;
			if (HitCountArray[otherID] > 3) {
				Character* otherChar = (Character*)HitBoxIDArray[otherID]->Game_Object;
				if (otherChar->Direction * Direction < 0) {
					otherChar->State_Manager.TryStateChange(FALLINGBACK,100, 300);
				}
				else {
					otherChar->State_Manager.TryStateChange(FALLINGFRONT,100,300);
				}
				HitCountArray[otherID] = 0;
			}
		}
	}
	else {
		if (HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Projectile) {
			ProjectileBall* otherPro = (ProjectileBall*)HitBoxIDArray[otherID]->Game_Object;
			otherPro->Rebound();
		}
	}
}

void HelicopterKick::AssignParent(Dennis* parent){
	Parent = parent;
	RegisterHitBox.IgnoreObjectID = Parent->ID;
	ProjectileReboundHitBox.IgnoreObjectID = Parent->ID;
}

void HelicopterKick::Instantiate(RealVector2D position){
	IsActive = true;
	RegisterHitBox.IsActive = true;
	ProjectileReboundHitBox.IsActive = true;
	Position = position;
	for (int i = 0; i < HitBoxIDArray.size(); i++) {
		HitCountArray[i] = 0;
	}
	Z_Position = Parent->Z_Position;
	Direction = Parent->Direction;
}

void HelicopterKick::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	Position = Parent->Position;
	RegisterHitBox.SetSize(Parent->AttackHitBox.Width, Parent->AttackHitBox.Height);
	RegisterHitBox.Center = Parent->AttackHitBox.Center;
	RegisterHitBox.IsActive = Parent->AttackHitBox.IsActive;
	ProjectileReboundHitBox.Center = Position + RealVector2D(0, 15);
	if (Parent->CurrentState != SPECIALATTACK3) {
		GoBack();
	}
	RegisterHitBox.DrawBox(window);
	ProjectileReboundHitBox.DrawBox(window);
}

