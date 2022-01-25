#include "Text.h"


UI_Text::UI_Text(const std::string& value, int size) {
	Type = UI_TEXT;
	Text.setString(value);
	Text.setCharacterSize(size);
}
UI_Text::UI_Text() {}

void UI_Text::Animate(sf::RenderWindow& window) {
	if (!IsActive) {
		return;
	}
	Text.setPosition(Position.get_x(), Position.get_y());
	window.draw(Text);
}