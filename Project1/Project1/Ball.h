#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Ball
{
public:
	Ball(sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction);
	~Ball();
	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction, int &health);
	void Draw(sf::RenderWindow& window);
	int GetSpawnID() { return spawnID; }
	void RemoveSelf();

	Collider GetCollider() { return Collider(body); }

private:
	int spawnID;

	sf::RectangleShape body;
	sf::Vector2f direction;

	float lifetime;
	float maxLifetime;
	float speed;
	float damage;

};