#include "Image.h"

UI_Image::UI_Image(sf::Sprite &image) {
	Type = UI_TYPE_IMAGE;
	Image = image;
	Image.setOrigin(Image.getLocalBounds().width / 2, Image.getLocalBounds().height / 2);
}
UI_Image::UI_Image() {
	Type = UI_TYPE_IMAGE;
}

void UI_Image::AlignAtCenter(){
	Image.setOrigin(Image.getLocalBounds().width / 2, Image.getLocalBounds().height / 2);
}

void UI_Image::Animate(sf::RenderWindow &window, const double dt){
	if(!IsActive){
		return;
	}
	Image.setPosition(Position.get_x(), Position.get_y());
	window.draw(Image);
}

void UI_Image::SetImage(sf::Sprite &image){
	Image = image;
	Image.setOrigin(Image.getLocalBounds().width / 2, Image.getLocalBounds().height / 2);
}
