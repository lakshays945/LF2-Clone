#include "Element.h"
#include "Button.h"

sf::Texture ButtonsTexFile;
sf::Texture PlayersTexFile;
sf::Texture BackGroundTexFile;
sf::Texture GameOverTexFile;

sf::Sprite ButtonsSpr;
sf::Sprite PlayersSpr;
sf::Sprite BackGroundSpr;
sf::Sprite GameOverSpr;

UI_Element::UI_Element(){
	if (ButtonsTexFile.getSize() == sf::Vector2u(0, 0)) {
		std::cout << __FUNCTION__;
		ButtonsTexFile.loadFromFile("Images/Buttons.png");
		ButtonsSpr.setTexture(ButtonsTexFile);
	}
	if (PlayersTexFile.getSize() == sf::Vector2u(0, 0)) {
		PlayersTexFile.loadFromFile("Images/PlayerImages.png");
		PlayersSpr.setTexture(PlayersTexFile);
	}
	if (BackGroundTexFile.getSize() == sf::Vector2u(0, 0)) {
		BackGroundTexFile.loadFromFile("Images/UIBack.jpg");
		BackGroundSpr.setTexture(BackGroundTexFile);
		BackGroundSpr.setScale(3, 2.23);
	}
	if (GameOverTexFile.getSize() == sf::Vector2u(0, 0)) {
		GameOverTexFile.loadFromFile("Images/Rectangle.png");
		GameOverSpr.setTexture(GameOverTexFile);
	}
}

void UI_Element::SetPosition(RealVector2D position){
	Position = position;
}


void UI_Listener::AssignParent(UI_Button* parent){
	Parent = parent;
}

void UI_Listener::Listen(const sf::RenderWindow &window) {
	bool IsMouseOn = (abs(sf::Mouse::getPosition(window).x - Parent->Position.get_x()) <= (Width / 2) && abs(sf::Mouse::getPosition(window).y - Parent->Position.get_y()) <= (Height / 2));
	if (IsMouseOn) {
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			CanClick = true;
		}
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && CanClick) {
			CanClick = false;
			Clicked = true;
		}
		else {
			Parent->OnHover(0);
		}
	}
	else {
		CanClick = false;
		if (Parent->B_Text.Text.getFillColor() != sf::Color(150,150,150)) {
			Parent->B_Text.Text.setFillColor(sf::Color(150, 150, 150));
			Parent->B_Image.Image.setColor(sf::Color(255,255,255,200));
		}
	}
}
