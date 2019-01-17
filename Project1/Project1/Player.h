#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Ball.h"


class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, float shootCooldown);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f DirectionFromAnimationRow();

	sf::Vector2f GetPosition() {return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	std::vector<Ball> balls;
	sf::RectangleShape body;

private:
	sf::Texture ballTexture;

	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	float shootCooldown;
	float shootTimer;
};

