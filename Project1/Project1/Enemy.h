#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Collider.h"
//#include "Ball.h"

class Enemy: public Character
{
public:
	Enemy(sf::Vector2u imageCount, sf::Vector2f position, int rotation, int health, float shootCooldown);
	~Enemy();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void SetTextureRotation(int rotation, sf::Texture* texture, sf::Vector2u imageCount);
	int GetSpawnID() { return spawnID; }
	void RemoveSelf();

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	float shootCooldown;

private:
	int spawnID;

	sf::RectangleShape target;

	float shootCooldownTimer;
	int rotation;
};

