#pragma once
#include <SFML/Graphics.hpp>

class Health
{
public:
	Health(sf::Vector2f size, sf::Vector2f position);
	~Health();

	void Draw(sf::RenderWindow& window);
	sf::RectangleShape body;
};