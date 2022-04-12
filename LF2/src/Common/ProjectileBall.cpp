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
	MaxStrength = other.MaxStrength;
	CurrentStrength = MaxStrength;
}

void ProjectileBall::SetScale(RealVector2D scale) {
	Scale = scale;
	InAirSheet.SetScale(Scale);
	InitialSheet.SetScale(Scale);
	FastSheet.SetScale(Scale);
	EndSheet.SetScale(Scale);
	AttackHitBox.SetScale(Scale);
	ReboundHitBox.SetScale(Scale);
}

void ProjectileBall::Instantiate(RealVector2D position,RealVector2D velocity) {
	if (Parent->Scale != Scale) {
		SetScale(Parent->Scale);
	}
	Rebounded = false;
	Position = position;
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
	CurrentStrength = MaxStrength;
}

void ProjectileBall::GoBack() {
	IsActive = false;
	Position = Parent->Position;
	Velocity = { 0,0 };
	AttackHitBox.Disable();
	ReboundHitBox.Disable();
}

void ProjectileBall::AssignParent(GameObject* parent) {
	Parent = parent;
	Scale = Scale * parent->Scale;
	AttackHitBox.SetScale(Scale);
	ReboundHitBox.SetScale(Scale);
	Effect_Manager = parent->Effect_Manager;
	AttackHitBox.IgnoreObjectID = Parent->ID;
	ReboundHitBox.IgnoreObjectID = Parent->ID;
}

void ProjectileBall::Rebound() {
	AttackHitBox.IgnoreObjectID = -1;
	Velocity = Velocity * (-1);
	Rebounded = true;
}