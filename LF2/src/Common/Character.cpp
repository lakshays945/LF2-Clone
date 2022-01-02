#include "Character.h"

std::vector <Character*> CharacterIDArray;

//Constructor 
Character::Character() {
	JumpGravityFactor = JUMP_GRAVITY_FACTOR;
	JumpSpeedY = DEFAULT_JUMP_VELOCITY;
	DashSpeedX = DEFAULT_DASH_VELOCITY_X;
	RunSpeed = DEFAULT_RUN_VELOCITY;
}

int Character::nextCharacterID = 0;

void Character::RegisterCharacter() {
	CharacterID = nextCharacterID;
	CharacterIDArray.push_back(this);
	nextCharacterID++;
}

void Character::ChangeState(PlayerStates state, const double lastPressed, const double data, const double startTime) {
	CurrentSheet->Time = 0; //resetting the sheet currently being used (as it will be changed soon)
	CurrentState = state;
	switch (state) {
	case IDLE:
		CurrentSheet = &IdleSheet;
		break;
	case WALKING:
		CurrentSheet = &WalkingSheet;
		break;
	case RUNNING:
		Run(lastPressed, data);
		CurrentSheet = &RunningSheet;
		break;
	case JUMPING:
		CurrentSheet = &JumpingSheet;
		break;
	case HITTING:
		Attack(lastPressed);
		CurrentSheet = &HittingSheet[ComboStreak];
		break;
	case GETTING_HIT:
		//Effect_Manager->AnimateEffect(EFFECT_ANIMATION_IMPACT, Position, 4);
		Effect_Manager->AnimateEffect(EFFECT_ANIMATION_BLOOD, Position,0);
		//Effect_Manager->DrawEffect(EFFECT_IMAGE_BLOOD, Position, 0.3,2);
		CurrentSheet = &Getting_HitSheet;
		break;
	case FALLING:
		CurrentSheet = &FallingSheet;
		break;
	case JUMPINGATTACK:
		CurrentSheet = &JumpingAttackSheet;
		return;//special
	case DASH:
		CurrentSheet = &DashSheet;
		Dash();
		break;
	case SPECIALATTACK1:
		CurrentSheet = &SpecialAttack1Sheet;
		break;
	case SPECIALATTACK2:
		CurrentSheet = &SpecialAttack2Sheet;
		break;
	default:
		break;
	}
	CurrentSheet->Time = startTime;
	TimeSinceLastState = startTime;
}

void Character::Update(const double dt, sf::RenderWindow& window) {
	if (TimeSinceLastState < MAX_LAST_TIME) {
		TimeSinceLastState += dt;
	}
	switch (CurrentState) {
	case IDLE:
		AddForce(dt);
		Translate(dt);
		Z_Position = Position.get_y();
		break;
	case WALKING:
		AddForce(dt);
		Translate(dt);
		Z_Position = Position.get_y();
		break;
	case RUNNING:
		Translate(dt);
		Z_Position = Position.get_y();
		break;
	case JUMPING:
		JumpCalculation(dt, TimeSinceLastState);
		break;
	case HITTING:
		break;
	case GETTING_HIT:

		break;
	case FALLING:

		break;
	case JUMPINGATTACK:
		JumpCalculation(dt, TimeSinceLastState);
		break;
	case DASH:
		DashCalculations(dt, TimeSinceLastState);
		break;
	case SPECIALATTACK1:
		SpecialAttack1Calculations(dt, TimeSinceLastState);
		break;
	case SPECIALATTACK2:
		SpecialAttack2Calculations(dt, TimeSinceLastState);
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
	Velocity = Velocity + RealVector2D(0, JumpSpeedY);
}

void Character::JumpCalculation(const double dt, const double t) {
	//take off phase
	if (((t-INITIAL_JUMP_PAUSE)*(t-dt-INITIAL_JUMP_PAUSE)) <= 0) {
		Jump(0);
	}
	//in air phase
	if (t > INITIAL_JUMP_PAUSE && t < INITIAL_JUMP_PAUSE + JUMP_DURATION) {
		Velocity = Velocity + GravityVector * (dt * JumpGravityFactor);
		Translate(dt);
	}
	//landing phase
	else if (t > INITIAL_JUMP_PAUSE + JUMP_DURATION) {
		if (CurrentState == JUMPINGATTACK) {
			State_Manager.ForceStateChange(JUMPING, 0, t);
		}
		Position = LastPosition;
		DamageHitBox.Center = LastPosition;
	}
	//checking if we should go to dash
	if(t > INITIAL_JUMP_PAUSE + JUMP_DURATION + 0.1){
		if (Input_Manager.GetLastPressed(sf::Keyboard::Space) < 0.2 && (Input_Manager.IsKeyPressed(sf::Keyboard::D) ^ Input_Manager.IsKeyPressed(sf::Keyboard::A))) {
			State_Manager.ForceStateChange(DASH, 0);
		}
	}
}

void Character::Dash() {
	int U = Input_Manager.IsKeyPressed(sf::Keyboard::W);
	int D = Input_Manager.IsKeyPressed(sf::Keyboard::S);
	int R = Input_Manager.IsKeyPressed(sf::Keyboard::D);
	int L = Input_Manager.IsKeyPressed(sf::Keyboard::A);
	RealVector2D DashVelocity((R - L) * DashSpeedX, DEFAULT_DASH_VELOCITY_Y*(1+U-D));
	LastPosition = Position + (DashVelocity-RealVector2D(0,DEFAULT_DASH_VELOCITY_Y)) * DASH_DURATION;
	Velocity = DashVelocity;
}

void Character::DashCalculations(const double dt, const double t) {
	//in air phase
	if (t < DASH_DURATION) {
		Velocity = Velocity + GravityVector * (dt * DASH_GRAVITY_SCALE);
		Translate(dt);
	}
	//landed phase
	else if(t >= DASH_DURATION + 0.1) {
		Position = LastPosition;
		if (Input_Manager.GetLastPressed(sf::Keyboard::Space) < 0.05 && (Input_Manager.IsKeyPressed(sf::Keyboard::D)^Input_Manager.IsKeyPressed(sf::Keyboard::A))) {
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
	Up = Input_Manager.IsKeyPressed(sf::Keyboard::W);
	Down = Input_Manager.IsKeyPressed(sf::Keyboard::S);
	Right = Input_Manager.IsKeyPressed(sf::Keyboard::D);
	Left = Input_Manager.IsKeyPressed(sf::Keyboard::A);
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
	DamageHitBox.Center = Position;
}
void Character::Animate(sf::RenderWindow& window, const double dt) { //give it an animation sheet (not as a parameter) and window and it will animate
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
	if (CorrectIndex == -1) {
		Stop();
		State_Manager.ForceStateChange(IDLE);
		CorrectIndex = 0;
	}
	sf::Sprite* current = &CurrentSheet->Sprites[CorrectIndex];
	/*sf::CircleShape circle;
	circle.setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	circle.setRadius(2);
	circle.setFillColor(sf::Color(0, 0, 0, 255));*/
	if (Velocity.get_x() < 0) {
		Direction = -1;
	}
	else if (Velocity.get_x() > 0) {
		Direction = 1;
	}
	current->setScale(sf::Vector2f((float)Direction, 1.0f));
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
	if (CorrectIndex == CurrentSheet->HitBoxIndex) {
		AttackHitBox.IsActive = true;
		int dx = CurrentSheet->HitboxOffset.get_x() * Direction;
		int dy = CurrentSheet->HitboxOffset.get_y();
		AttackHitBox.SetSize(CurrentSheet->HitboxWidth, CurrentSheet->HitboxHeight);
		AttackHitBox.Center = Position + RealVector2D(dx, dy);
		AttackHitBox.DrawBox(window);
	}
	else {
		AttackHitBox.IsActive = false;
	}
	DamageHitBox.DrawBox(window);
	//window.draw(circle);
}

void Character::OnCollision(int otherID, int selfID) {
	if (HitBoxIDArray[otherID]->Game_Object == HitBoxIDArray[selfID]->Game_Object) {
		return;
	}
	if (HitBoxIDArray[otherID]->Type == TYPE_ATTACK && HitBoxIDArray[selfID]->Type == TYPE_DAMAGE) {
		State_Manager.ForceStateChange(GETTING_HIT);
	}
}
 //Player Specific




#undef DEFAULT_RUN_VELOCITY 
#undef DEFAULT_JUMP_VELOCITY
#undef DEFAULT_DASH_VELOCITY_X 
#undef DEFAULT_DASH_VELOCITY_Y
#undef DEFAULT_FORCE_SCALE
#undef COMBO_THRESHOLD
#undef MAX_LAST_TIME
#undef GRAVITY_FACTOR
#undef DASH_GRAVITY_SCALE 