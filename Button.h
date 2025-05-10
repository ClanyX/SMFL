#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

	//Class to create button as a instance
	//Param: size, position, label, font

class Button
{
private:
	sf::RectangleShape shape;
	sf::Text text;

public:
	//Constructor & Destructor
	Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& label, const sf::Font& font)
		: text(font)
	{
		shape.setSize(size);
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(position);

		text.setString(label);
		text.setFillColor(sf::Color::White);
		text.setPosition({ position.x + 10.f, position.y + 10.f });
	}

	//Function
	void draw(sf::RenderWindow& window) const;

	bool isClicked(const sf::Vector2f& mousePos) const;
};

