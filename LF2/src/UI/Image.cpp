#include "Image.h"

UI_Image::UI_Image(const std::string& fileName, sf::IntRect locationData) {
	Type = UI_TYPE_IMAGE;
	Texture.loadFromFile(fileName);
	Image.setTexture(Texture);
	Image.setTextureRect(locationData);
	Image.setOrigin(locationData.width / 2, locationData.height / 2);
}
UI_Image::UI_Image() {}

void UI_Image::Animate(sf::RenderWindow &window){
	if(!IsActive){
		return;
	}
	Image.setPosition(Position.get_x(), Position.get_y());
	window.draw(Image);
}