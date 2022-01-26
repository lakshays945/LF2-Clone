#include "Element.h"

void UI_Element::SetPosition(RealVector2D position){
	Position = position;
}


void UI_Listener::AssignParent(UI_Element* parent)
{
	Parent = parent;
}

void UI_Listener::OnLeftClick()
{
}

void UI_Listener::OnRightClick()
{
}

void UI_Listener::OnHover()
{
}

void UI_Listener::Listen() {
	bool IsMouseOn = (abs(sf::Mouse::getPosition().x - Parent->Position.get_x()) <= (Width / 2) && abs(sf::Mouse::getPosition().x - Parent->Position.get_x()) <= (Height / 2));
	if (IsMouseOn) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			OnLeftClick();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			OnRightClick();
		}
		else {
			OnHover();
		}
	}
}
