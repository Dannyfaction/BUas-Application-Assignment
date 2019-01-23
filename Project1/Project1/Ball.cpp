#include "Ball.h"
#include <iostream>
//#include "GlobalEventDispatcher.h"
#include "SpawnID.h"
#include "Spawner.h"
#include "TextureManager.h"

Ball::Ball(sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction)
{
	spawnID = SpawnID::getInstance().GetNewID();
	std::cout << "Spawned ball with ID: " << spawnID << "\n";

	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setTexture(TextureManager::getInstance().GetBallTexture());

	this->direction = direction;

	lifetime = 0.0f;
	maxLifetime = 5.0f;
	speed = 250.0f;
	damage = 100.0f;
}

Ball::~Ball()
{
}

void Ball::Update(float deltaTime)
{
	lifetime += deltaTime;
	body.move(direction * speed * deltaTime);
	if(lifetime > maxLifetime)
	{
		//Destroy the ball once its maximum lifetime has been reached
		RemoveSelf();
	}
}

void Ball::OnCollision(sf::Vector2f direction, int &health, float &hitProtectionTimer)
{
	//Decrease health on either the enemy or the player if they're not currently on HitProtection (prevents multiple balls from hitting that target in  the same second)
	if (hitProtectionTimer <= 0) {
		health -= damage;
		hitProtectionTimer = 1.0f;
	}

	RemoveSelf();

}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Ball::RemoveSelf()
{
	Spawner::getInstance().RemoveBall(spawnID);
}
