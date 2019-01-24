#pragma once
#include <SFML/Graphics.hpp>

class HowToPlay
{
public:
	HowToPlay(sf::Vector2f size, sf::Vector2f position);
	~HowToPlay();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

	sf::RectangleShape body;

private:
	float lifetime;
	float maxLifetime;
};