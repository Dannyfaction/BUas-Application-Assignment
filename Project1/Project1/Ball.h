#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Ball
{
public:
	Ball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction, std::vector<Ball> &balls);
	~Ball();

	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);
	void Draw(sf::RenderWindow& window);

	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	sf::Vector2f direction;

	std::vector<Ball> &balls;

	float lifetime;
	float maxLifetime;
	float speed;

};