#include "ProjectileBall.h"

ProjectileBall::ProjectileBall() {
	IsActive = false;
	InAirSheet.AssignPlayer(this);
	InitialSheet.AssignPlayer(this);
	FastSheet.AssignPlayer(this);
	EndSheet.AssignPlayer(this);
	InitialSheet.OneTime = true;
	EndSheet.OneTime = true;
	CurrentSheet = &InitialSheet;
}

ProjectileBall::ProjectileBall(const ProjectileBall& other) {
	Parent = other.Parent;
	IsActive = other.IsActive;
	InAirSheet = other.InAirSheet;
	InitialSheet = other.InitialSheet;
	FastSheet = other.FastSheet;
	EndSheet = other.EndSheet;
	InAirSheet.AssignPlayer(this);
	InitialSheet.AssignPlayer(this);
	FastSheet.AssignPlayer(this);
	EndSheet.AssignPlayer(this);
	EndSheet.OneTime = true;
	InitialSheet.OneTime = true;
	CurrentSheet = &InitialSheet;
	AttackHitBox = other.AttackHitBox;
	ReboundHitBox = other.ReboundHitBox;
	AttackHitBox.AssignPlayer(this);
	ReboundHitBox.AssignPlayer(this);
}

void ProjectileBall::Instantiate(RealVector2D velocity) {
	Position = Parent->Position;
	InAirSheet.Time = 0;
	EndSheet.Time = 0;
	FastSheet.Time = 0;
	InitialSheet.Time = 0;
	IsActive = true;
	Velocity = velocity;
	CurrentSheet = &InitialSheet;
	AttackHitBox.IgnoreObjectID = Parent->ID;
	ReboundHitBox.IgnoreObjectID = Parent->ID;
	AttackHitBox.IsActive = true;
	ReboundHitBox.IsActive = true;
}

void ProjectileBall::GoBack() {
	IsActive = false;
	Position = Parent->Position;
	Velocity = { 0,0 };
	AttackHitBox.IsActive = false;
	ReboundHitBox.IsActive = false;
}

void ProjectileBall::AssignParent(GameObject* parent) {
	Parent = parent;
	Effect_Manager = parent->Effect_Manager;
}

void ProjectileBall::Rebound() {
	Velocity = Velocity * (-1);
}