#include "bandit.h"

#define DEFAULT_RUN_VELOCITY 300
#define DEFAULT_JUMP_VELOCITY -600
#define DEFAULT_DASH_VELOCITY_X 600
#define DEFAULT_DASH_VELOCITY_Y -400
#define DEFAULT_FORCE_SCALE 500*100
#define COMBO_THRESHOLD 0.4
#define MAX_LAST_TIME 20
#define INITIAL_JUMP_PAUSE JumpingTimes[0] //can modify in bandit.h
#define JUMP_DURATION (JumpingTimes[1]-INITIAL_JUMP_PAUSE) //can modify in bandit.h
#define JUMP_LANDING_TIME (JumpingTimes[2]-JUMP_DURATION) //can modify in bandit.h
#define JUMP_GRAVITY_FACTOR -(DEFAULT_JUMP_VELOCITY*2)/(DEFAULT_GRAVITY_CONSTANT*JUMP_DURATION)
#define DASH_DURATION DashTimes[0] //can modify in bandit.h
#define DASH_GRAVITY_SCALE -(DEFAULT_DASH_VELOCITY_Y*2)/(DEFAULT_GRAVITY_CONSTANT*DASH_DURATION)


//Constructor (Mainly assigning images to animationSheet is done)
Bandit::Bandit() {
	TexFile0.loadFromFile("Resource/Dennis.png");
	DamageHitBox = HitBox(Position, 42, 74,TYPE_DAMAGE);
	DamageHitBox.AssignPlayer(this);
	DamageHitBox.RegisterID();
	AttackHitBox = HitBox(Position, 15, 15, TYPE_ATTACK);
	AttackHitBox.AssignPlayer(this);
	AttackHitBox.RegisterID();
	State_Manager.AssignPlayer(this);
	Input_Manager.AssignPlayer(this);
	IdleSheet.AssignPlayer(this);
	WalkingSheet.AssignPlayer(this);
	RunningSheet.AssignPlayer(this);
	JumpingSheet.AssignPlayer(this);
	HittingSheet[0].AssignPlayer(this);
	HittingSheet[1].AssignPlayer(this);
	HittingSheet[2].AssignPlayer(this);
	Getting_HitSheet.AssignPlayer(this);
	FallingSheet.AssignPlayer(this);
	JumpingAttackSheet.AssignPlayer(this);
	DashSheet.AssignPlayer(this);


	IdleSheet.AssignTextures(TexFile0, IdleLocations, IdleTimes);
	WalkingSheet.AssignTextures(TexFile0, WalkingLocations, WalkingTimes);
	HittingSheet[0].AssignTextures(TexFile0, Attack1Locations, Attack1Times);
	HittingSheet[1].AssignTextures(TexFile0, Attack2Locations, Attack2Times);
	HittingSheet[2].AssignTextures(TexFile0, Attack3Locations, Attack3Times);
	JumpingSheet.AssignTextures(TexFile0, JumpingLocations, JumpingTimes);
	RunningSheet.AssignTextures(TexFile0, RunningLocations, RunningTimes);
	JumpingAttackSheet.AssignTextures(TexFile0,JumpingAttackLocations, JumpingAttackTimes);
	DashSheet.AssignTextures(TexFile0, DashLocations, DashTimes);
	Getting_HitSheet.AssignTextures(TexFile0, Getting_HitLocations, Getting_HitTimes);


	JumpingSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].OneTime = true;
	HittingSheet[2].OneTime = true;
	DashSheet.OneTime = true;
	Getting_HitSheet.OneTime = true;


	JumpingAttackSheet.AssignHitbox(1, { 32,2 }, 15, 15);
	HittingSheet[0].AssignHitbox(2, { 17,14 }, 40, 38);
	HittingSheet[1].AssignHitbox(1, { 19,13 }, 46, 52);
	HittingSheet[2].AssignHitbox(2, { 14,14 }, 50, 50);


	CurrentSheet = &IdleSheet;

	DEBUG_SUCCESS("Bandit Successfully Initialised");
}

void Bandit::ChangeState(PlayerStates state, const double lastPressed, const double data, const double startTime) {
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
		Effect_Manager->AnimateEffect(EFFECT_ANIMATION_IMPACT, Position, 4);
		Effect_Manager->AnimateEffect(EFFECT_ANIMATION_BLOOD, Position,3);
		Effect_Manager->DrawEffect(EFFECT_IMAGE_BLOOD, Position, 0.3,2);
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
	default:
		break;
	}
	CurrentSheet->Time = startTime;
	TimeSinceLastState = startTime;
}

void Bandit::Update(const double dt, sf::RenderWindow& window) {
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
	default:
		break;
	}
	Animate(window, dt); //after determining position and other stuff then animate() will be called
}

void Bandit::Attack(const double lastPressed) {
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

void Bandit::Jump(const double lastPressed) {
	LastPosition = Position + Velocity * JUMP_DURATION;
	Velocity = Velocity + RealVector2D(0, DEFAULT_JUMP_VELOCITY);
}

void Bandit::JumpCalculation(const double dt, const double t) {
	//take off phase
	if (((t-INITIAL_JUMP_PAUSE)*(t-dt-INITIAL_JUMP_PAUSE)) <= 0) {
		Jump(0);
	}
	//in air phase
	if (t > INITIAL_JUMP_PAUSE && t < INITIAL_JUMP_PAUSE + JUMP_DURATION) {
		Velocity = Velocity + GravityVector * (dt * JUMP_GRAVITY_FACTOR);
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

void Bandit::Dash() {
	int U = Input_Manager.IsKeyPressed(sf::Keyboard::W);
	int D = Input_Manager.IsKeyPressed(sf::Keyboard::S);
	int R = Input_Manager.IsKeyPressed(sf::Keyboard::D);
	int L = Input_Manager.IsKeyPressed(sf::Keyboard::A);
	RealVector2D DashVelocity((R - L) * DEFAULT_DASH_VELOCITY_X, DEFAULT_DASH_VELOCITY_Y*(1+U-D));
	LastPosition = Position + (DashVelocity-RealVector2D(0,DEFAULT_DASH_VELOCITY_Y)) * DASH_DURATION;
	Velocity = DashVelocity;
}

void Bandit::DashCalculations(const double dt, const double t) {
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

void Bandit::Run(const double lastPressed, int dir) {
	Velocity = RealVector2D(DEFAULT_RUN_VELOCITY * dir, 0);
}

void Bandit::Stop() {
	Velocity.SetMagnitude(0);
}

void Bandit::AddForce(const double dt) { //for movement based upon inputs
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

void Bandit::Translate(const double dt) {
	Position = Position + Velocity * dt;
	DamageHitBox.Center = Position;
}
void Bandit::Animate(sf::RenderWindow& window, const double dt) { //give it an animation sheet (not as a parameter) and window and it will animate
	CurrentSheet->Time += dt;
	int CorrectIndex = CurrentSheet->GetCorrectIndex();
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

void Bandit::OnCollision(int otherID, int selfID) {
	if (IDArray[otherID]->Game_Object == IDArray[selfID]->Game_Object) {
		return;
	}
	if (IDArray[otherID]->Type == TYPE_ATTACK && IDArray[selfID]->Type == TYPE_DAMAGE) {
		State_Manager.ForceStateChange(GETTING_HIT);

	}
}

#undef DEFAULT_RUN_VELOCITY 
#undef DEFAULT_JUMP_VELOCITY
#undef DEFAULT_DASH_VELOCITY_X 
#undef DEFAULT_DASH_VELOCITY_Y
#undef DEFAULT_FORCE_SCALE
#undef COMBO_THRESHOLD
#undef MAX_LAST_TIME
#undef JUMP_DURATION
#undef INITIAL_JUMP_PAUSE
#undef JUMP_LANDING_TIME
#undef GRAVITY_FACTOR
#undef DASH_DURATION 
#undef DASH_GRAVITY_SCALE 