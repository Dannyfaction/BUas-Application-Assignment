#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Animation.h"
#include "Collider.h"
#include "Ball.h"


class Player: public Character
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, float shootCooldown);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	int GetSpawnID() { return spawnID; }

	sf::Vector2f DirectionFromAnimationRow();

	sf::Vector2f GetPosition() {return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

private:
	int spawnID;
	sf::Texture ballTexture;

	Animation animation;
	unsigned int row;
	float speed;

	sf::Vector2f velocity;

	float shootCooldown;
	float shootCooldownTimer;
};