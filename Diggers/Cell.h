#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

struct Cell
{
	sf::RectangleShape shape;
	int health = 1;
	void nextFrame()
	{
		shape.setTextureRect({ shape.getTextureRect().left + shape.getTextureRect().width,
			shape.getTextureRect().top, shape.getTextureRect().width, shape.getTextureRect().height });
	}
};