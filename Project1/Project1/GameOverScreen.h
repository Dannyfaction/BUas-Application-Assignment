#pragma once
#include <SFML/Graphics.hpp>

class GameOverScreen
{
public:
	GameOverScreen(sf::Vector2f size, sf::Vector2f position);
	~GameOverScreen();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	sf::RectangleShape body;
};

