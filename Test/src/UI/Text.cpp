#include "Text.h"


UI_Text::UI_Text(const std::string &fontFile, const std::string& value, int size) {
	Type = UI_TYPE_TEXT;
	Font.loadFromFile(fontFile);
	Text.setFont(Font);
	Text.setString(value);
	Text.setCharacterSize(size);
	AlignAtCenter();
}
UI_Text::UI_Text() {
	Type = UI_TYPE_TEXT;
}

UI_Text::UI_Text(const UI_Text& other){
	Font = other.Font;
	Text.setFont(Font);
	Text.setFillColor(other.Text.getFillColor());
	Text.setCharacterSize(other.Text.getCharacterSize());
	Text.setString(other.Text.getString());
	AlignAtCenter();
}

void UI_Text::AlignAtCenter(){
	Text.setOrigin(floor(Text.getLocalBounds().width / 2.0 + 0.5), floor(Text.getLocalBounds().height / 2.0 + 0.5));
}

void UI_Text::Animate(sf::RenderWindow& window, const double dt) {
	if (!IsActive) {
		return;
	}
	Text.setPosition(Position.get_x(), Position.get_y());
	window.draw(Text);
}

void UI_Text::SetText(const std::string& fontFile, const std::string& value, int size){
	Font.loadFromFile(fontFile);
	Text.setFont(Font);
	Text.setString(value);
	Text.setCharacterSize(size);
	AlignAtCenter();

}

void UI_Text::operator=(const UI_Text& other){
	Font = other.Font;
	Text.setFont(Font);
	Text.setFillColor(other.Text.getFillColor());
	Text.setCharacterSize(other.Text.getCharacterSize());
	Text.setString(other.Text.getString());
	AlignAtCenter();
}
