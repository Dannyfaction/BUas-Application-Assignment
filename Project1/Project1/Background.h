#pragma once
#include <SFML/Graphics.hpp>

class Background
{
public:
	Background(sf::Vector2f size, sf::Vector2f position);
	~Background();

	void Draw(sf::RenderWindow& window);

private:
	sf::RectangleShape body;
};

