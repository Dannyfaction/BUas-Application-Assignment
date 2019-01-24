#pragma once
#include <SFML/Graphics.hpp>

class GameEndText
{
public:
	GameEndText(int size, sf::Vector2f position, std::string message, sf::Color color);
	~GameEndText();

	void Draw(sf::RenderWindow& window);

	sf::Text text;
};

