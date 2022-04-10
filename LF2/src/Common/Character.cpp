#include "Character.h"

std::vector <Character*> CharacterIDArray;

double FALL_GRAVITY_SCALE = (600) / (DEFAULT_GRAVITY_CONSTANT * 0.7);


//Constructor 
Character::Character() {
	DamageHitBox = HitBox(Position, 42, 74, HB_TYPE_DAMAGE);
	DamageHitBox.AssignPlayer(this);
	DamageHitBox.RegisterID();
	DamageHitBox.IsActive = true;
	AttackHitBox = HitBox(Position, 15, 15, HB_TYPE_ATTACK);
	AttackHitBox.AssignPlayer(this);
	AttackHitBox.RegisterID();
	WallHitBox = HitBox(Position, 54, 74, HB_TYPE_WALL);
	WallHitBox.AssignPlayer(this);
	WallHitBox.RegisterID();
	BurningHitBox = HitBox(Position, 42, 74, HB_TYPE_FIRE);
	BurningHitBox.AssignPlayer(this);
	BurningHitBox.RegisterID();
	BurningHitBox.KnockOutPower = 200;
	JumpGravityFactor = JUMP_GRAVITY_FACTOR;
	JumpSpeedY = DEFAULT_JUMP_VELOCITY;
	DashSpeedX = DEFAULT_DASH_VELOCITY_X;
	RunSpeed = DEFAULT_RUN_VELOCITY;
	for (int i = 0; i < 17; i++) {
		JoystickToKeyboard[i] = sf::Keyboard::Unknown;
	}
	for (int i = 0; i < STATECOUNT; i++) {
		WeaponPosOffsets[i] = RealVector2D(0, 0);
	}
}

int Character::nextCharacterID = 0;

void Character::RegisterCharacter() {
	CharacterID = nextCharacterID;
	CharacterIDArray.push_back(this);
	nextCharacterID++;
}

void Character::SetScale(RealVector2D scale) {
	Scale = scale;
	IdleSheet.SetScale(Scale);
	WalkingSheet.SetScale(Scale);
	RunningSheet.SetScale(Scale);
	JumpingSheet.SetScale(Scale);
	HittingSheet[0].SetScale(Scale);
	HittingSheet[1].SetScale(Scale);
	HittingSheet[2].SetScale(Scale);
	Getting_HitSheet[0].SetScale(Scale);
	Getting_HitSheet[1].SetScale(Scale);
	FallingBackSheet.SetScale(Scale);
	JumpingAttackSheet.SetScale(Scale);
	DashSheet.SetScale(Scale);
	SpecialAttack1Sheet.SetScale(Scale);
	SpecialAttack2Sheet.SetScale(Scale);
	FallingBackSheet.SetScale(Scale);
	FallingFrontSheet.SetScale(Scale);
	AttackHitBox.SetScale(Scale);
	DamageHitBox.SetScale(Scale);
}

void Character::ChangeState(PlayerStates state, const double lastPressed, const double data, const double startTime) {
	CurrentSheet->Time = 0; //resetting the sheet currently being used (as it will be changed soon)
	CurrentState = state;
	switch (state) {
	case IDLE:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_IDLE,WeaponHolderType);
			CurrentWeapon->Hide = false;
		}
		CurrentSheet = &IdleSheet;
		break;
	case WALKING:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_WALKING, WeaponHolderType);
		}
		CurrentSheet = &WalkingSheet;
		break;
	case RUNNING:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_RUNNING, WeaponHolderType);
		}
		Run(lastPressed, data);
		CurrentSheet = &RunningSheet;
		break;
	case JUMPING:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_JUMPING);
		}
		CurrentSheet = &JumpingSheet;
		break;
	case HITTING:
		Attack(lastPressed);
		if (CurrentWeapon == nullptr) {
			CurrentSheet = &HittingSheet[ComboStreak];
		}
		else {
			if (ComboStreak == 2) {
				ComboStreak = 0;
			}
			if (CurrentSheet == &RunningSheet && ((Direction == 1 && Input_Manager.IsKeyPressed(PlayerControl.RightKey)) || (Direction == -1 && Input_Manager.IsKeyPressed(PlayerControl.LeftKey)))) {
				CurrentWeapon->ChangeState(WPN_HITTING, 0);
				State_Manager.ForceStateChange(THROWWEAPON);
			}
			else {
				CurrentWeapon->ChangeState(WPN_HITTING, ComboStreak);
				CurrentSheet = &WPNAttackSheet[ComboStreak];
			}
		}
		Velocity = RealVector2D(30 * Direction, 0);
		//Position = Position + RealVector2D(Direction * 10, 0);
		break;
	case GETTING_HIT:
		Velocity = RealVector2D(data, 0);
		if (CurrentSheet == &Getting_HitSheet[0]) {
			CurrentSheet = &Getting_HitSheet[1];
			if (CurrentWeapon != nullptr) {
				CurrentWeapon->ChangeState(WPN_GETTING_HIT, 1);
			}
		}
		else {
			CurrentSheet = &Getting_HitSheet[0];
			if (CurrentWeapon != nullptr) {
				CurrentWeapon->ChangeState(WPN_GETTING_HIT, 0);
			}
		}
		break;
	case FALLINGBACK:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Throw(RealVector2D(0, -100));
			CurrentWeapon = nullptr;
		}
		CurrentSheet = &FallingBackSheet;
		FallBack(lastPressed,data);
		//Effect_Manager->AnimateEffect(EFFECT_ANIMATION_IMPACT, Position + Velocity*(0.15), 2);
		break;
	case FALLINGFRONT:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Throw(RealVector2D(0, -100));
			CurrentWeapon = nullptr;
		}
		CurrentSheet = &FallingFrontSheet;
		FallFront(lastPressed,data);
		//Effect_Manager->AnimateEffect(EFFECT_ANIMATION_IMPACT, Position + Velocity*(0.15), 2);
		break;
	case JUMPINGATTACK:
		if (CurrentWeapon == nullptr) {
			CurrentSheet = &JumpingAttackSheet;
		}
		else {
			CurrentSheet = &WPNJumpAttackSheet;
			CurrentWeapon->ChangeState(WPN_JUMP_ATTACK);
		}
		return;//special
	case DASH:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_DASH);
		}
		CurrentSheet = &DashSheet;
		Dash();
		break;
	case SPECIALATTACK1:
		if (SpecialAttackMP[0] <= ManaPoints) { ManaPoints -= SpecialAttackMP[0]; }
		else { State_Manager.ForceStateChange(IDLE); return; }
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_SPL_ATTACK);
			CurrentWeapon->Hide = true;
		}
		CurrentSheet = &SpecialAttack1Sheet;
		break;
	case SPECIALATTACK2:
		if (SpecialAttackMP[1] <= ManaPoints) { ManaPoints -= SpecialAttackMP[1]; }
		else { State_Manager.ForceStateChange(IDLE); return; }
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_SPL_ATTACK);
			CurrentWeapon->Hide = true;
		}
		CurrentSheet = &SpecialAttack2Sheet;
		break;
	case SPECIALATTACK3:
		if (SpecialAttackMP[2] <= ManaPoints) { ManaPoints -= SpecialAttackMP[2]; }
		else { State_Manager.ForceStateChange(IDLE); return; }
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_SPL_ATTACK);
			CurrentWeapon->Hide = true;
		}
		CurrentSheet = &SpecialAttack3Sheet;
		break;
	case SPECIALATTACK4:
		if (SpecialAttackMP[3] <= ManaPoints) { ManaPoints -= SpecialAttackMP[3]; }
		else { State_Manager.ForceStateChange(IDLE); return; }
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->ChangeState(WPN_SPL_ATTACK);
			CurrentWeapon->Hide = true;
		}
		CurrentSheet = &SpecialAttack4Sheet;
		break;
	case FREEZED:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Throw(RealVector2D(0, -100));
			CurrentWeapon = nullptr;
		}
		CurrentSheet = &FreezedSheet;
		break;
	case THROWWEAPON:
		CurrentSheet = &WPNThrowSheet;
		CurrentWeapon->ChangeState(WPN_HITTING);
		break;
	case WEAPONPICK:
		Stop();
		CurrentSheet = &WeaponPickSheet;
		PickWeapon();
		break;
	case GUARD:
		Stop();
		CurrentSheet = &GuardSheet;
		break;
	default:
		break;
	}
	CurrentSheet->Time = startTime;
	TimeSinceLastState = startTime;
}

void Character::Update(const double dt, sf::RenderWindow& window) {
	if (ManaPoints < 100) ManaPoints += 4 * dt;
	if (TimeSinceLastState < MAX_LAST_TIME) {
		TimeSinceLastState += dt;
	}
	if (InvincibleTime < 10) {
		InvincibleTime += dt;
		if (InvincibleTime > 0.75) {
			Invincible = false;
			DamageHitBox.IsActive = true;
		}
	}
	if (CurrentState != GUARD && GuardResistance < 100) {
		GuardResistance += dt * 50.0;
	}
	if (CurrentWeapon != nullptr) {
		CurrentWeapon->Direction = Direction;
	}

	switch (CurrentState) {
	case IDLE:
		AddForce(dt);
		Translate(dt);
		Z_Position = Position.get_y();
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
		}
		break;
	case WALKING:
		AddForce(dt);
		Translate(dt);
		Z_Position = Position.get_y();
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
		}
		break;
	case RUNNING:
		Translate(dt);
		Z_Position = Position.get_y();
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
		}
		break;
	case JUMPING:
		JumpCalculation(dt, TimeSinceLastState);
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
		}
		break;
	case HITTING:
		if (TimeSinceLastState < 0.2) {
			Translate(dt);
		}
		if (CurrentWeapon != nullptr) {
			if (ComboStreak == 0) {
				CurrentWeapon->Z_Position = Z_Position + 1;
			}
			else {
				CurrentWeapon->Z_Position = Z_Position - 1;
			}
		}
		break;
	case GETTING_HIT:
		if (TimeSinceLastState < 0.2) {
			Translate(dt);
		}
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
		}
		break;
	case FALLINGBACK:
		FallBackCalculations(dt, TimeSinceLastState);
		break;
	case FALLINGFRONT:
		FallFrontCalculations(dt, TimeSinceLastState);
		break;
	case JUMPINGATTACK:
		JumpCalculation(dt, TimeSinceLastState);
		break;
	case DASH:
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
		}
		DashCalculations(dt, TimeSinceLastState);
		break;
	case SPECIALATTACK1:
		SpecialAttack1Calculations(dt, TimeSinceLastState);
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position - 1;
		}
		break;
	case SPECIALATTACK2:
		SpecialAttack2Calculations(dt, TimeSinceLastState);
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position - 1;
		}
		break;
	case SPECIALATTACK3:
		SpecialAttack3Calculations(dt, TimeSinceLastState);
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position - 1;
		}
		break;
	case SPECIALATTACK4:
		SpecialAttack4Calculations(dt, TimeSinceLastState);
		if (CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position - 1;
		}
		break;
	case FREEZED:
		FreezeCalculations(dt, TimeSinceLastState);
		break;
	case THROWWEAPON:
		if (TimeSinceLastState > 0.2 && CurrentWeapon != nullptr) {
			CurrentWeapon->Z_Position = Z_Position + 1;
			CurrentWeapon->Throw(RealVector2D(Direction * 800, 0),true);
			CurrentWeapon = nullptr;
		}
		break;
	case GUARD:
		if (TimeSinceLastState < 0.4) {
			Translate(dt);
		}
		break;
	default:
		break;
	}
	//Animate(window, dt); //after determining position and other stuff then animate() will be called
}

void Character::Attack(const double lastPressed) {
	Velocity.SetMagnitude(0);
	Up = 0; Down = 0; Left = 0; Down = 0;
	if (lastPressed < COMBO_THRESHOLD) {
		ComboStreak++;
	}
	else {
		ComboStreak = 0;
	}
	if (ComboStreak > 2)
		ComboStreak = 0;
}

void Character::Jump(const double lastPressed) {
	LastPosition = Position + Velocity * JUMP_DURATION;
	Z_Velocity = Velocity.get_y();
	Velocity = Velocity + RealVector2D(0, JumpSpeedY);
}

void Character::JumpCalculation(const double dt, const double t) {
	//take off phase
	if (((t-INITIAL_JUMP_PAUSE)*(t-dt-INITIAL_JUMP_PAUSE)) <= 0) {
		Jump(0);
	}
	//in air phase
	if (t > INITIAL_JUMP_PAUSE && t < INITIAL_JUMP_PAUSE + JUMP_DURATION) {
		Z_Position = Z_Position + Z_Velocity * dt;
		Velocity = Velocity + GravityVector * (dt * JumpGravityFactor);
		while(!WallIDs.empty()) {
			int WallID = WallIDs.front();
			WallIDs.pop();
			Velocity = Velocity + RealVector2D(0, -Z_Velocity);
			if ((Position.get_x() > HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() < 0) || (Position.get_x() < HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() > 0) && (abs(HitBoxIDArray[WallID]->Game_Object->Z_Position - Z_Position) < 23)) {
				Velocity = RealVector2D(0, Velocity.get_y());
				LastPosition = RealVector2D(Position.get_x(), LastPosition.get_y());
			}
			LastPosition = RealVector2D(LastPosition.get_x(), LastPosition.get_y() - (JUMP_DURATION - (t - INITIAL_JUMP_PAUSE) ) * Z_Velocity*1.1);
			Z_Velocity = 0;
		}
		Translate(dt);
	}
	//landing phase
	else if (t > INITIAL_JUMP_PAUSE + JUMP_DURATION) {
		if (CurrentState == JUMPINGATTACK) {
			State_Manager.ForceStateChange(JUMPING, 0, t);
		}
		if (!WallIDs.empty()) {
			Position = LastPosition;
		}
		else {
			Position = RealVector2D(Position.get_x(), LastPosition.get_y());
		}
		DamageHitBox.Center = Position;
	}
	//checking if we should go to dash
	if(t > INITIAL_JUMP_PAUSE + JUMP_DURATION + 0.1){
		if (Input_Manager.GetLastPressed(PlayerControl.JumpKey) < 0.2 && (Input_Manager.IsKeyPressed(PlayerControl.RightKey) ^ Input_Manager.IsKeyPressed(PlayerControl.LeftKey))) {
			State_Manager.ForceStateChange(DASH, 0);
		}
	}
}

void Character::Dash() {
	int U = Input_Manager.IsKeyPressed(PlayerControl.UpKey);
	int D = Input_Manager.IsKeyPressed(PlayerControl.DownKey);
	int R = Input_Manager.IsKeyPressed(PlayerControl.RightKey);
	int L = Input_Manager.IsKeyPressed(PlayerControl.LeftKey);
	//InputManager::GetDeviceState(this->deviceID);
	RealVector2D DashVelocity((R - L) * DashSpeedX, DEFAULT_DASH_VELOCITY_Y*(1+U-D));
	Z_Velocity = DEFAULT_DASH_VELOCITY_Y * (U - D);
	LastPosition = Position + (DashVelocity-RealVector2D(0,DEFAULT_DASH_VELOCITY_Y)) * DASH_DURATION;
	Velocity = DashVelocity;
}

void Character::DashCalculations(const double dt, const double t) {
	//in air phase
	if (t < DASH_DURATION) {
		Z_Position = Z_Position + Z_Velocity * dt;
		Velocity = Velocity + GravityVector * (dt * DASH_GRAVITY_SCALE);
		while(!WallIDs.empty()) {
			int WallID = WallIDs.front();
			WallIDs.pop();
			Velocity = Velocity + RealVector2D(0, -Z_Velocity);
			if ((Position.get_x() > HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() < 0) || (Position.get_x() < HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() > 0) && (abs(HitBoxIDArray[WallID]->Game_Object->Z_Position - Z_Position) < 23)) {
				Velocity = RealVector2D(0, Velocity.get_y());
				LastPosition = RealVector2D(Position.get_x(), LastPosition.get_y());
			}
			LastPosition = RealVector2D(LastPosition.get_x(), LastPosition.get_y() - (DASH_DURATION-t) * Z_Velocity*1.1);
			Z_Velocity = 0;
		}
		Translate(dt);
	}
	//landed phase
	else if(t >= DASH_DURATION + 0.1) {
		Position = LastPosition;
		Z_Position = Position.get_y();
		if (Input_Manager.GetLastPressed(PlayerControl.JumpKey) < 0.05 && (Input_Manager.IsKeyPressed(PlayerControl.RightKey)^Input_Manager.IsKeyPressed(PlayerControl.LeftKey))) {
			ChangeState(DASH, 0);
		}
	}
}

void Character::Run(const double lastPressed, int dir) {
	Velocity = RealVector2D(DEFAULT_RUN_VELOCITY * dir, 0);
}

void Character::Stop() {
	Velocity.SetMagnitude(0);
}

void Character::AddForce(const double dt) { //for movement based upon inputs
	Up = Input_Manager.IsKeyPressed(PlayerControl.UpKey);
	Down = Input_Manager.IsKeyPressed(PlayerControl.DownKey);
	Right = Input_Manager.IsKeyPressed(PlayerControl.RightKey);
	Left = Input_Manager.IsKeyPressed(PlayerControl.LeftKey);
	if ((Up + Down + Right + Left == 0) || (Up - Down == 0 && Right - Left == 0)) {
		Velocity.SetMagnitude(0);
		State_Manager.ForceStateChange(IDLE);
		return;
	}
	State_Manager.ForceStateChange(WALKING);
	RealVector2D Force((Right - Left) * DEFAULT_FORCE_SCALE, (Down - Up) * DEFAULT_FORCE_SCALE);
	Velocity = Velocity + Force * dt;
	if (Velocity.Magnitude() > MaxSpeed) {
		Velocity.SetMagnitude(MaxSpeed);
	}
}

void Character::Translate(const double dt) {
	Position = Position + Velocity * dt;
	if (Z_Position < WallUp) {
		Position = Position + RealVector2D(0, WallUp - Z_Position);
		LastPosition = RealVector2D(LastPosition.get_x(), Position.get_y());
		Z_Position = WallUp;
	}
	else if (Z_Position > WallDown) {
		Position = Position + RealVector2D(0, WallDown - Z_Position);
		LastPosition = RealVector2D(LastPosition.get_x(), Position.get_y());
		Z_Position = WallDown;
	}
	Position = RealVector2D(std::max(std::min(WallRight, Position.get_x()), WallLeft),Position.get_y());
	bool Xwall = false, Ywall = false;
	while(!WallIDs.empty()) {
		int WallID = WallIDs.front();
		WallIDs.pop();
		if (Ywall && Xwall) {
			continue;
		}
		RealVector2D pos = HitBoxIDArray[WallID]->Center;
		double w1 = HitBoxIDArray[WallID]->Width;
		double w2 = DamageHitBox.Width;
		double dx = abs(DamageHitBox.Center.get_x() - pos.get_x());
		if ((dx < (w1 + w2) / 2 && abs(DamageHitBox.Center.get_x() - Direction*10 - pos.get_x()) >= (w1 + w2) / 2) && (abs(HitBoxIDArray[WallID]->Game_Object->Z_Position - Z_Position) < 23)) {
			if (!Xwall && !Ywall) {
				Position = Position - RealVector2D(Velocity.get_x(), 0) * dt;
				Xwall = true;
			}
		}
		else {
			if (!Ywall) {
				if ((Position.get_y() > HitBoxIDArray[WallID]->Game_Object->Z_Position && Velocity.get_y() < 0) || (Position.get_y() < HitBoxIDArray[WallID]->Game_Object->Z_Position && Velocity.get_y() > 0)) {
					Position = Position - RealVector2D(0, Velocity.get_y()) * dt;
					Ywall = true;
				}
			}
		}
	}
	if (CurrentWeapon != nullptr) {
		CurrentWeapon->Z_Position = Z_Position + 1;
	}
	DamageHitBox.Center = Position;
}

void Character::GettingHitCalculations(const double dt, const double t)
{
}

void Character::Animate(sf::RenderWindow& window, const double dt) { //give it an animation sheet (not as a parameter) and window and it will animate
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		if (HealthPoints > 0) {
			Stop();
			State_Manager.ForceStateChange(IDLE);
			CorrectIndex = 0;
		}
		else {
			int index = CurrentSheet->DrawTimes.size() - 2;
			CurrentSheet->Time = CurrentSheet->DrawTimes[index];
			CorrectIndex = index + 1;
		}
		
	}
	sf::Sprite *current = &CurrentSheet->Sprites[CorrectIndex];
	/*sf::CircleShape circle;
	circle.setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	circle.setRadius(2);
	circle.setFillColor(sf::Color(0, 0, 0, 255));*/
	if (Velocity.get_x() < 0 && CurrentState != GETTING_HIT && CurrentState != GUARD) {
		Direction = -1;
	}
	else if (Velocity.get_x() > 0 && CurrentState != GETTING_HIT && CurrentState != GUARD) {
		Direction = 1;
	}
	current->setScale(Scale.get_x()*Direction, Scale.get_y());
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	if (CurrentWeapon != nullptr) {
		RealVector2D offset = RealVector2D((CurrentSheet->WeaponOffsets[CorrectIndex].get_x()) * Direction, CurrentSheet->WeaponOffsets[CorrectIndex].get_y());
		CurrentWeapon->SetPosition(Position + offset, CurrentWeapon->Z_Position);
		CurrentWeapon->Direction = Direction;
	}
	if (CurrentSheet->HasHitBox[CorrectIndex]) {
		AttackHitBox.IsActive = true;
		int dx = CurrentSheet->HBData[CorrectIndex].offset.get_x() * Direction;
		int dy = CurrentSheet->HBData[CorrectIndex].offset.get_y();
		AttackHitBox.SetSize(CurrentSheet->HBData[CorrectIndex].width, CurrentSheet->HBData[CorrectIndex].height);
		AttackHitBox.Center = Position + RealVector2D(dx, dy);
		AttackHitBox.KnockOutPower = CurrentSheet->HBData[CorrectIndex].KnockPower;
		AttackHitBox.KnockUpPower = CurrentSheet->HBData[CorrectIndex].KnockPowerUp;
		AttackHitBox.Damage = CurrentSheet->HBData[CorrectIndex].damage;
		AttackHitBox.DrawBox(window);
	}
	else {
		AttackHitBox.Disable();
	}
	if (Invincible) {
		if (CorrectIndex % 2 == 0 && CurrentState != FALLINGBACK && CurrentState != FALLINGFRONT && HealthPoints>0) {
			return;
		}
	}
	window.draw(*current);
	DamageHitBox.DrawBox(window);
	WallHitBox.DrawBox(window);
	BurningHitBox.DrawBox(window);
	//window.draw(circle);
}

void Character::OnCollision(int otherID, int selfID) {
	HitBox* self = HitBoxIDArray[selfID];
	HitBox* other = HitBoxIDArray[otherID];
	if (self->Type == HB_TYPE_DAMAGE && other->Game_Object != this && CurrentSheet != &BurningSheet) {
		switch (other->Type) {
			case HB_TYPE_ATTACK:
				if (other->KnockOutPower > 0 || HealthPoints-other->Damage <= 0) {
					if (other->KnockOutPower <= 0) other->KnockOutPower = 300;
					if (Direction * other->Game_Object->Direction < 0) {
						if (CurrentState == GUARD && GuardResistance > 0) {
							CurrentSheet->Time = 0.3;
							TimeSinceLastState = 0.3;
							GuardResistance -= 55;
							Velocity = RealVector2D(-Direction * 200, 0);
						}
						else {
							State_Manager.TryStateChange(FALLINGBACK, other->KnockOutPower, other->KnockUpPower);
							HealthPoints -= other->Damage;
						}
					}
					else {
						State_Manager.TryStateChange(FALLINGFRONT, other->KnockOutPower, other->KnockUpPower);
						HealthPoints -= other->Damage;
					}
				}
				else {
					if (Direction * other->Game_Object->Direction < 0 && CurrentState == GUARD && GuardResistance > 0) {
						CurrentSheet->Time = 0.3;
						TimeSinceLastState = 0.3;
						GuardResistance -= 55;
						Velocity = RealVector2D(-Direction * 100, 0);
					}
					else {
						State_Manager.TryStateChange(GETTING_HIT, Direction * other->Game_Object->Direction, -other->KnockOutPower * other->Game_Object->Direction);
						HealthPoints -= other->Damage;
					}
				}
				break;
			case HB_TYPE_FIRE:
				if (Direction * other->Game_Object->Direction < 0) {
					if (CurrentState == GUARD && GuardResistance > 0) {
						CurrentSheet->Time = 0.3;
						TimeSinceLastState = 0.3;
						GuardResistance -= 55;
						Velocity = RealVector2D(-Direction * 200, 0);
					}
					else {
						State_Manager.TryStateChange(FALLINGBACK, other->KnockOutPower, other->KnockUpPower);
						CurrentSheet = &BurningSheet;
						BurningHitBox.Center = Position;
						BurningHitBox.IsActive = true;
						HealthPoints -= other->Damage;
						SetInvincible();
					}
				}
				else {
					State_Manager.TryStateChange(FALLINGFRONT, other->KnockOutPower, other->KnockUpPower);
					CurrentSheet = &BurningSheet;
					BurningHitBox.Center = Position;
					BurningHitBox.IsActive = true;
					HealthPoints -= other->Damage;
					SetInvincible();
				}
				break;
			case HB_TYPE_ICE:
				if (Direction * other->Game_Object->Direction < 0) {
					if (CurrentState == GUARD && GuardResistance > 0) {
						CurrentSheet->Time = 0.3;
						TimeSinceLastState = 0.3;
						GuardResistance -= 55;
						Velocity = RealVector2D(-Direction * 200, 0);
					}
					else {
						WallHitBox.IsActive = true;
						DamageHitBox.SetSize(66, 74);
						HealthPoints -= other->Damage;
						State_Manager.TryStateChange(FREEZED, Direction * other->Game_Object->Direction);
						if (CurrentState == FREEZED) {
							Stop();
						}
					}
				}
				else {
					WallHitBox.IsActive = true;
					DamageHitBox.SetSize(66, 74);
					HealthPoints -= other->Damage;
					State_Manager.TryStateChange(FREEZED, Direction * other->Game_Object->Direction);
					if (CurrentState == FREEZED) {
						Stop();
					}
				}
				break;
			case HB_TYPE_TRIGGER:
				if (other->Game_Object->GO_Type == GO_Weapon) {
					WeaponsInRangeID.push_back(HitBoxIDArray[otherID]->Game_Object->ID);
				}
				break;
			case HB_TYPE_WALL:
				WallIDs.push(otherID);
				break;
		}
	}
	else if (self->Type == HB_TYPE_FIRE && other->Game_Object != this) {

	}
	else if (self->Type == HB_TYPE_WALL && other->Game_Object != this) {
		CanCollide[otherID][selfID] = true;
		CanCollide[selfID][otherID] = true;
	}
	else if(self->Type == HB_TYPE_ATTACK && other->Game_Object != this) {

	}
}

void Character::OnCollisionExit(int otherID, int selfID){
	//DEBUG_INFO("Player Exited");
	if (HitBoxIDArray[otherID]->Type == HB_TYPE_TRIGGER && HitBoxIDArray[otherID]->Game_Object->GO_Type == GO_Weapon && HitBoxIDArray[selfID]->Type == HB_TYPE_DAMAGE) {
		for (int i = 0; i < WeaponsInRangeID.size(); i++) {
			if (HitBoxIDArray[otherID]->Game_Object->ID == WeaponsInRangeID[i]) {
				//DEBUG_INFO("WPN of ID = {} removed", HitBoxIDArray[otherID]->Game_Object->ID);
				WeaponsInRangeID.erase(WeaponsInRangeID.begin() + i);
				break;
			}
		}
	}
}

void Character::FallBack(int SpeedX, int SpeedY) {
	double x = Position.get_y() - Z_Position;
	double g = FALL_GRAVITY_SCALE * GravityVector.get_y();
	FallDuration = (2 * SpeedY / g + (sqrt(SpeedY * SpeedY - 2 * g * x) - SpeedY) / g);
	CurrentSheet->DrawTimes[1] = 0.1 + FallDuration / 2;
	CurrentSheet->DrawTimes[2] = FallDuration;
	CurrentSheet->DrawTimes[3] = 1.7 + FallDuration;
	BurningSheet.DrawTimes[0] = FallDuration / 2;
	BurningSheet.DrawTimes[1] = FallDuration-0.2;
	BurningSheet.DrawTimes[2] = 1.4 + FallDuration;
	double Vy = -SpeedY;
	Velocity = RealVector2D(SpeedX *(-Direction),Vy);
	DEBUG_INFO("SpeedY = {}", Vy);
	LastPosition = RealVector2D(Position.get_x() + SpeedX * FallDuration * (-Direction), Z_Position);
}

void Character::FallFront(int SpeedX, int SpeedY) {
	double x = Position.get_y() - Z_Position;
	double g = FALL_GRAVITY_SCALE * GravityVector.get_y();
	FallDuration = (2 * SpeedY / g + (sqrt(SpeedY * SpeedY - 2 * g * x) - SpeedY) / g);
	CurrentSheet->DrawTimes[1] = 0.1 + FallDuration / 2;
	CurrentSheet->DrawTimes[2] = FallDuration;
	CurrentSheet->DrawTimes[3] = 1.7 + FallDuration;
	BurningSheet.DrawTimes[0] = FallDuration / 2;
	BurningSheet.DrawTimes[1] = FallDuration - 0.2;
	BurningSheet.DrawTimes[2] = 1.4 + FallDuration;
	double Vy = -SpeedY;
	Velocity = RealVector2D(SpeedX * Direction, Vy);
	LastPosition = RealVector2D(Position.get_x() + SpeedX * FallDuration * Direction, Z_Position);
}

void Character::FallBackCalculations(const double dt, const double t) {
	BurningHitBox.Center = Position;
	if (t > 2*FallDuration/3) {
		BurningHitBox.Disable();
	}
	if (t > FallDuration) {
		SetInvincible();
		Stop();
		if(HealthPoints > 0) Position = LastPosition;
		return;
	}
	if(!WallIDs.empty()) {
		int WallID = WallIDs.front();
		WallIDs.pop();
		if ((Position.get_x() > HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() < 0) || (Position.get_x() < HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() > 0)) {
			Velocity = RealVector2D(0, Velocity.get_y());
			LastPosition = RealVector2D(Position.get_x(), LastPosition.get_y());
		}
	}
	Velocity = Velocity + GravityVector * (dt*FALL_GRAVITY_SCALE);
	Translate(dt);
}

void Character::FallFrontCalculations(const double dt, const double t) {
	BurningHitBox.Center = Position;
	if (t > 2*FallDuration/3) {
		BurningHitBox.Disable();
	}
	if (t > FallDuration) {
		SetInvincible();
		Stop();
		if (HealthPoints > 0) Position = LastPosition;
		return;
	}
	if(!WallIDs.empty()) {
		int WallID = WallIDs.front();
		WallIDs.pop();
		if ((Position.get_x() > HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() < 0) || (Position.get_x() < HitBoxIDArray[WallID]->Center.get_x() && Velocity.get_x() > 0)) {
			Velocity = RealVector2D(0, Velocity.get_y());
			LastPosition = RealVector2D(Position.get_x(), LastPosition.get_y());
		}
	}
	Velocity = Velocity + GravityVector * (dt * FALL_GRAVITY_SCALE);
	Translate(dt);
}

void Character::FreezeCalculations(const double dt, const double t) {
	WallHitBox.Center = Position;
	if (Z_Position > Position.get_y()) {
		Velocity = Velocity + RealVector2D(0, 950) * dt;
		DamageHitBox.Center = Position;
		Translate(dt);
	}
	else {
		if (Velocity.Magnitude() > 350) {
			HealthPoints -= 10;
			DeFreeze();
			State_Manager.TryStateChange(FALLINGBACK, 50, 300);
			Position = RealVector2D(Position.get_x(), Z_Position);
			return;
		}
		Position = RealVector2D(Position.get_x(), Z_Position);
		Stop();
	}
	if (t > 3.2 && HealthPoints > 0) {
		DeFreeze();
		State_Manager.TryStateChange(FALLINGBACK, 50, 100);
	}
}

void Character::SetInvincible() {
	if (HealthPoints <= 0) return;
	Invincible = true;
	DamageHitBox.Disable();
	InvincibleTime = 0;
}

void Character::DeFreeze(){
	HealthPoints -= 10;
	WallHitBox.Disable();
	WallHitBox.IgnoreObjectID = -1;
	DamageHitBox.SetSize(42, 74);
	SetInvincible();
}

void Character::SetControls(KeyboardControls control) {
	PlayerControl = control;
	Input_Manager.SetControls(PlayerControl);
}

void Character::PickWeapon(){
	double minDist = 10000;
	int id = 0;
	for (int i = 0; i < WeaponsInRangeID.size(); i++) {
		if (minDist > Position.DistanceFrom(GameObjectIDArray[WeaponsInRangeID[i]]->Position)) {
			minDist = Position.DistanceFrom(GameObjectIDArray[WeaponsInRangeID[i]]->Position);
			id = WeaponsInRangeID[i];
		}
	}
	CurrentWeapon = (Weapon*)GameObjectIDArray[id];
	CurrentWeapon->AssignParent(this);
}





#undef DEFAULT_RUN_VELOCITY 
#undef DEFAULT_JUMP_VELOCITY
#undef DEFAULT_DASH_VELOCITY_X 
#undef DEFAULT_DASH_VELOCITY_Y
#undef DEFAULT_FORCE_SCALE
#undef COMBO_THRESHOLD
#undef MAX_LAST_TIME
#undef GRAVITY_FACTOR
#undef DASH_GRAVITY_SCALE 