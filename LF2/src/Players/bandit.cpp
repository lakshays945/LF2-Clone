#include "bandit.h"


Bandit::Bandit() //Constructor (Mainly assigning images to animationSheet is done)
	:Position(RealVector2D(100, 100)), Velocity(RealVector2D(10, 10)) {
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
	for (int i = 0; i < 4; i++) { //Setting textures for idle sheet
		IdleSheet.Textures.push_back(sf::Texture());
		IdleSheet.Sprites.push_back(sf::Sprite());
		IdleSheet.DrawTimes.push_back(IdleTimes[i]);
		IdleSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(IdleLocations[i][0], IdleLocations[i][1], 80, 80));
	}
	for (int i = 0; i < 6; i++) { //Setting textures for walking sheet
		WalkingSheet.Textures.push_back(sf::Texture());
		WalkingSheet.Sprites.push_back(sf::Sprite());
		WalkingSheet.DrawTimes.push_back(WalkingTimes[i]);
		WalkingSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(WalkingLocations[i][0], WalkingLocations[i][1], 80, 80));
	}
	for (int i = 0; i < 5; i++) {
		HittingSheet[0].Textures.push_back(sf::Texture());
		HittingSheet[0].Sprites.push_back(sf::Sprite());
		HittingSheet[0].DrawTimes.push_back(Attack1Times[i]);
		HittingSheet[0].Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(Attack1Locations[i][0], Attack1Locations[i][1], 80, 80));
	}
	for (int i = 0; i < 3; i++) {
		HittingSheet[1].Textures.push_back(sf::Texture());
		HittingSheet[1].Sprites.push_back(sf::Sprite());
		HittingSheet[1].DrawTimes.push_back(Attack2Times[i]);
		HittingSheet[1].Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(Attack2Locations[i][0], Attack2Locations[i][1], 80, 80));
	}
	for (int i = 0; i < 3; i++) {
		HittingSheet[2].Textures.push_back(sf::Texture());
		HittingSheet[2].Sprites.push_back(sf::Sprite());
		HittingSheet[2].DrawTimes.push_back(Attack3Times[i]);
		HittingSheet[2].Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(Attack3Locations[i][0], Attack3Locations[i][1], 80, 80));
	}
	for (int i = 0; i < 3; i++) {
		JumpingSheet.Textures.push_back(sf::Texture());
		JumpingSheet.Sprites.push_back(sf::Sprite());
		JumpingSheet.DrawTimes.push_back(JumpingTimes[i]);
		JumpingSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(JumpingLocations[i][0], JumpingLocations[i][1], 80, 80));
	}
	for (int i = 0; i < 4; i++) {
		RunningSheet.Textures.push_back(sf::Texture());
		RunningSheet.Sprites.push_back(sf::Sprite());
		RunningSheet.DrawTimes.push_back(RunningTimes[i]);
		RunningSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(RunningLocations[i][0], RunningLocations[i][1], 80, 80));
	}
	for (int i = 0; i < 4; i++) {
		JumpingAttackSheet.Textures.push_back(sf::Texture());
		JumpingAttackSheet.Sprites.push_back(sf::Sprite());
		JumpingAttackSheet.DrawTimes.push_back(JumpingAttackTimes[i]);
		JumpingAttackSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(JumpingAttackLocations[i][0], JumpingAttackLocations[i][1], 80, 80));
	}
	for (int i = 0; i < 1; i++) {
		DashSheet.Textures.push_back(sf::Texture());
		DashSheet.Sprites.push_back(sf::Sprite());
		DashSheet.DrawTimes.push_back(DashTimes[i]);
		DashSheet.Textures[i].loadFromFile("src/Resource/Dennis.png", sf::IntRect(DashLocations[i][0], DashLocations[i][1], 80, 80));
	}
	IdleSheet.AssignTextures();
	WalkingSheet.AssignTextures();
	HittingSheet[0].AssignTextures();
	JumpingSheet.AssignTextures();
	RunningSheet.AssignTextures();
	JumpingAttackSheet.AssignTextures();
	JumpingSheet.OneTime = true;
	//JumpingAttackSheet.OneTime = true;
	HittingSheet[0].OneTime = true;
	HittingSheet[1].AssignTextures();
	HittingSheet[1].OneTime = true;
	HittingSheet[2].AssignTextures();
	HittingSheet[2].OneTime = true;
	DashSheet.AssignTextures();
	DashSheet.OneTime = true;
	CurrentSheet = &IdleSheet;
}




void Bandit::ChangeState(PlayerStates state, const double lastPressed, const double data) {
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
		LastPosition = Position + Velocity;
		Jump(lastPressed);
		CurrentSheet = &JumpingSheet;
		break;
	case HITTING:
		Attack(lastPressed);
		CurrentSheet = &HittingSheet[ComboStreak];
		break;
	case GETTING_HIT:
		CurrentSheet = &Getting_HitSheet;
		break;
	case FALLING:
		CurrentSheet = &FallingSheet;
		break;
	case JUMPINGATTACK:
		CurrentSheet = &JumpingAttackSheet;
		return;//special
	case DASH:
		if (Velocity.get_y() > 400 && Velocity.get_y() < 570) {
			LastPosition = Position + RealVector2D(data * DEFAULT_DASH_VELOCITY_X, 0) * 0.4;
		}
		else {
			LastPosition = Position + RealVector2D(data * DEFAULT_DASH_VELOCITY_X, Velocity.get_y() - 480) * 0.4;
		}
		CurrentSheet = &DashSheet;
		JumpToDash(data);
		break;
	default:
		break;
	}
	TimeSinceLastState = 0;
}

void Bandit::Update(const double dt, sf::RenderWindow& window) {
	if (TimeSinceLastState < MAX_LAST_TIME) {
		TimeSinceLastState += dt;
	}
	switch (CurrentState) {
	case IDLE:
		AddForce(dt);
		Translate(dt);
		break;
	case WALKING:
		AddForce(dt);
		Translate(dt);
		break;
	case RUNNING:
		Translate(dt);
		break;
	case JUMPING:
		Velocity = Velocity + GravityVector * dt;
		Translate(dt);
		if (TimeSinceLastState >= JumpingTimes[2]) {
			Position = LastPosition;
			if (Input_Manager.GetLastPressed(sf::Keyboard::Space) < 0.2 && Input_Manager.IsKeyPressed(sf::Keyboard::D)) {
				State_Manager.ForceStateChange(DASH, 1);
			}
			else if (Input_Manager.GetLastPressed(sf::Keyboard::Space) < 0.2 && Input_Manager.IsKeyPressed(sf::Keyboard::A)) {
				State_Manager.ForceStateChange(DASH, -1);
			}
			//State_Manager.ForceStateChange(IDLE);
		}
		break;
	case HITTING:
		break;
	case GETTING_HIT:

		break;
	case FALLING:

		break;
	case JUMPINGATTACK:
		Velocity = Velocity + GravityVector * dt;
		Translate(dt);
		if (TimeSinceLastState >= JumpingTimes[2]) {
			Position = LastPosition;
			if (Input_Manager.GetLastPressed(sf::Keyboard::Space) < 0.2 && Input_Manager.IsKeyPressed(sf::Keyboard::D)) {
				State_Manager.ForceStateChange(DASH, 1);
				break;
			}
			else if (Input_Manager.GetLastPressed(sf::Keyboard::Space) < 0.2 && Input_Manager.IsKeyPressed(sf::Keyboard::A)) {
				State_Manager.ForceStateChange(DASH, -1);
				break;
			}
			Stop();
			State_Manager.ForceStateChange(IDLE);
		}
		break;
	case DASH:
		Velocity = Velocity + GravityVector * dt;
		Translate(dt);
		if (TimeSinceLastState >= DashTimes[0]) {
			Position = LastPosition;
		}
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
	Velocity = RealVector2D(Velocity.get_x(), DEFAULT_JUMP_VELOCITY + Velocity.get_y());
}

void Bandit::JumpCalculation(const double dt, const double t) {

}

void Bandit::JumpToDash(int dir) {
	Velocity = RealVector2D(DEFAULT_DASH_VELOCITY_X * dir, DEFAULT_DASH_VELOCITY_Y + Velocity.get_y());
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
}
void Bandit::Animate(sf::RenderWindow& window, const double dt) { //give it an animation sheet (not as a parameter) and window and it will animate
	CurrentSheet->Time += dt;
	sf::Sprite* current = &CurrentSheet->Sprites[CurrentSheet->GetCorrectIndex()];
	if (Velocity.get_x() < 0) {
		Direction = -1;
	}
	else if (Velocity.get_x() > 0) {
		Direction = 1;
	}
	current->setScale(sf::Vector2f((float)Direction, 1.0f));
	current->setPosition(sf::Vector2f(Position.get_x(), Position.get_y()));
	window.draw(*current);
}