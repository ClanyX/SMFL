#include "Button.h"

//Functions
void Button::draw(sf::RenderWindow& window) const
{
	window.draw(shape);
	window.draw(text);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const
{
	return shape.getGlobalBounds().contains(mousePos);
}
