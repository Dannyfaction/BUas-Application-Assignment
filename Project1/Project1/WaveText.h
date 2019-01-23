#pragma once
#include <SFML/Graphics.hpp>

class WaveText
{
public:
	WaveText(int size, sf::Vector2f position, std::string message, sf::Color color);
	~WaveText();

	void Draw(sf::RenderWindow& window);
	void Update(float deltaTime);

private:
	sf::Text text;

	float lifetime;
	float maxLifetime;
};

