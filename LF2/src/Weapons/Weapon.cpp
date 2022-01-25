#include "Weapon.h"

std::vector<Weapon*> WeaponIDArray;

int Weapon::nextID = 0;

Weapon::Weapon(){
	AttackHitBox = HitBox(Position, 40, 40, HB_TYPE_ATTACK);
	PickUpHitBox = HitBox(Position, 40, 40, HB_TYPE_TRIGGER);
	PickUpHitBox.IsActive = true;
	AttackHitBox.AssignPlayer(this);
	PickUpHitBox.AssignPlayer(this);
	AttackHitBox.RegisterID();
	PickUpHitBox.RegisterID();
	RegisterGameObject(GO_Weapon);
	CurrentSheet = &OnFloorSheet;
	WobbleSheet.OneTime = true;
	RegisterWeaponID();
}

void Weapon::ChangeState(WeaponStates state, int data){
	CurrentSheet->Time = 0;
	CurrentState = state;
	switch (state) {
		case WPN_IDLE:
			CurrentSheet = &IdleSheet[data];
			break;
		case WPN_WALKING:
			CurrentSheet = &WalkingSheet[data];
			break;
		case WPN_RUNNING:
			CurrentSheet = &RunningSheet[data];
			break;
		case WPN_JUMPING:
			CurrentSheet = &JumpingSheet;
			break;
		case WPN_DASH:
			CurrentSheet = &DashSheet;
			break;
		case WPN_ON_FLOOR:
			AttackHitBox.IgnoreObjectID = -1;
			PickUpHitBox.IsActive = true;
			PickUpHitBox.Center = Position;
			AttackHitBox.Disable();
			CurrentSheet = &OnFloorSheet;
			break;
		case WPN_HITTING:
			CurrentSheet = &HittingSheet[data];
			break;
		case WPN_GETTING_HIT:
			CurrentSheet = &GettingHitSheet[data];
			break;
		case WPN_IN_AIR:
			CurrentSheet = &InAirSheet;
			break;
		case WPN_JUMP_ATTACK:
			CurrentSheet = &JumpAttackSheet;
			break;
		case WPN_SPL_ATTACK:
			CurrentSheet = &SpecialAttackSheet;
			break;
	}
}

void Weapon::AssignParent(GameObject* parent){
	CurrentParent = parent;
	Direction = CurrentParent->Direction;
	PickUpHitBox.Disable();
	AttackHitBox.IgnoreObjectID = CurrentParent->ID;
}

void Weapon::Update(const double dt){

}

void Weapon::Animate(sf::RenderWindow& window, const double dt){
	if (CurrentState == WPN_IN_AIR) {
		InAirCalculations(dt);
	}
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		Stop();
		ChangeState(WPN_ON_FLOOR);
		CorrectIndex = 0;
	}
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	current->setScale(Scale.get_x() * Direction, Scale.get_y());
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	if (CurrentSheet->HasHitBox[CorrectIndex]) {
		AttackHitBox.IsActive = true;
		int dx = CurrentSheet->HBData[CorrectIndex].offset.get_x() * Direction;
		int dy = CurrentSheet->HBData[CorrectIndex].offset.get_y();
		AttackHitBox.SetSize(CurrentSheet->HBData[CorrectIndex].width, CurrentSheet->HBData[CorrectIndex].height);
		AttackHitBox.Center = Position + RealVector2D(dx, dy);
		AttackHitBox.KnockOutPower = CurrentSheet->HBData[CorrectIndex].KnockPower;
		AttackHitBox.KnockUpPower = CurrentSheet->HBData[CorrectIndex].KnockPowerUp;
		AttackHitBox.DrawBox(window);
	}
	else if(CurrentState != WPN_IN_AIR) {
		AttackHitBox.Disable();
	}
	if (!Hide) {
		window.draw(*current);
		PickUpHitBox.DrawBox(window);
		AttackHitBox.DrawBox(window);
	}
}

void Weapon::SetPosition(RealVector2D position, double z_Position){
	if (CurrentParent != nullptr) {
		Direction = CurrentParent->Direction;
	}
	Position = position;
	AttackHitBox.Center = position;
	PickUpHitBox.Center = position;
	Z_Position = z_Position;
}

void Weapon::OnCollision(int otherID, int selfID){
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (self->ID == AttackHitBox.ID && (other->Type == HB_TYPE_DAMAGE || other->Type == HB_TYPE_WALL) && other->Game_Object->ID != AttackHitBox.IgnoreObjectID && CurrentState == WPN_IN_AIR) {
		Throw(RealVector2D(-Velocity.get_x()/8, -100), false);
		AttackHitBox.Disable();
	}
	else if (self->ID == AttackHitBox.ID && (other->Game_Object->GO_Type == GO_Projectile || (other->Type == HB_TYPE_ATTACK && other->Game_Object->GO_Type == GO_Weapon)) && CurrentState == WPN_IN_AIR) {
		Throw(RealVector2D(-Velocity.get_x() / 8, -100), false);
		AttackHitBox.Disable();
	}
}

void Weapon::OnCollisionExit(int otherID, int selfID){

}

void Weapon::InAirCalculations(const double dt){
	Velocity = Velocity + GravityVector * (dt*GravityFactor);
	Position = Position + Velocity * dt;
	AttackHitBox.Center = Position;
	if (Position.get_y() + 15 > TargetPos.get_y() && Velocity.get_y() > 0) {
		CurrentSheet = &WobbleSheet;
	}
	if (Position.get_y() > TargetPos.get_y() && Velocity.get_y() > 0) {
		Stop();
		Position = RealVector2D(Position.get_x(),TargetPos.get_y());
		//ChangeState(WPN_ON_FLOOR);
	}
}

void Weapon::Throw(RealVector2D velocity, bool attack){
	Hide = false;
	CurrentParent = nullptr;
	Velocity = velocity;
	TargetPos = RealVector2D(Velocity.get_x()*InAirTime + Position.get_x(),25 + Z_Position) ;
	InAirTime = 2 * Velocity.get_y() / (DEFAULT_GRAVITY_CONSTANT * GravityFactor);
	if (attack) {
		AttackHitBox.IsActive = true;
	}
	else {
		AttackHitBox.Disable();
	}
	AttackHitBox.KnockOutPower = 150;
	AttackHitBox.KnockUpPower = 200;
	AttackHitBox.SetSize(40, 40);
	AttackHitBox.Center = Position;
	PickUpHitBox.Disable();
	ChangeState(WPN_IN_AIR);
}

void Weapon::Stop(){
	Velocity.SetMagnitude(0);
}

void Weapon::Translate(const double dt){
	Position = Position + Velocity * dt;
}

void Weapon::RegisterWeaponID(){
	WeaponID = nextID;
	WeaponIDArray.push_back(this);
	nextID++;
}
