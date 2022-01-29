#include "Button.h"

UI_Button::UI_Button(const std::string& imageFile, const sf::IntRect& imageLocationData, const std::string& textValue, unsigned int textSize){
	B_Image.Texture.loadFromFile(imageFile);
	B_Image.Image.setTexture(B_Image.Texture);
	B_Image.Image.setTextureRect(imageLocationData);
	B_Text.Text.setString(textValue);
	B_Text.Text.setCharacterSize(textSize);
	B_Image.Position = Position;
	B_Text.Position = Position;
}

void UI_Button::Animate(sf::RenderWindow& window){
	if (!IsActive) {
		return;
	}
	Listener.Listen();
	B_Image.SetPosition(Position);
	B_Text.SetPosition(Position);
	B_Image.Animate(window);
	B_Text.Animate(window);
}
