#include "Button.h"
#include "Scene.h"

UI_Button::UI_Button(sf::Sprite &image, const std::string &textFont, const std::string& textValue, int textSize){
	Type = UI_TYPE_BUTTON;
	B_Image.Image = image;
	Listener.AssignParent(this);
	Listener.Width = image.getTextureRect().width;
	Listener.Height = image.getTextureRect().height;
	B_Text.SetText(textFont, textValue, textSize);
	std::cout << Listener.Width << ' ' << Listener.Height << '\n';
}

UI_Button::UI_Button(){
	Type = UI_TYPE_BUTTON;
}

UI_Button::UI_Button(const UI_Button& other){
	B_Image = other.B_Image;
	B_Text = other.B_Text;
	Listener.AssignParent(this);
	Listener.Width = other.Listener.Width;
	Listener.Height = other.Listener.Height;
	Position = other.Position;
	IsActive = other.IsActive;
	OnClick = other.OnClick;
}

void UI_Button::Animate(sf::RenderWindow& window, const double dt){
	if (!IsActive) {
		return;
	}
	if (Listener.Clicked) {
		Time += dt;
		B_Image.Image.setScale(1 + (Time-TimeDelay)/2, 1 + (Time-TimeDelay)/2);
		B_Text.Text.setScale(B_Image.Image.getScale());
		if (Time > TimeDelay) {
			OnClick();
			//if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			Listener.Clicked = false;
			B_Image.Image.setScale(1, 1);
			B_Text.Text.setScale(B_Image.Image.getScale());
			Time = 0;
		}
	}
	Listener.Listen(window);
	B_Image.SetPosition(Position);
	B_Text.SetPosition(Position);
	B_Image.Animate(window,dt);
	B_Text.Animate(window,dt);
}

void UI_Button::operator=(const UI_Button& other){
	B_Image = other.B_Image;
	B_Text = other.B_Text;
	Listener.AssignParent(this);
	Listener.Width = other.Listener.Width;
	Listener.Height = other.Listener.Height;
	Position = other.Position;
	IsActive = other.IsActive;
	OnClick = other.OnClick;
}

void UI_Button::AlignAtCenter(){
	B_Image.AlignAtCenter();
	B_Text.AlignAtCenter();
}

void UI_Button::UpdateListenerSize(){
	Listener.Width = B_Image.Image.getTextureRect().width;
	Listener.Height = B_Image.Image.getTextureRect().height;
}
