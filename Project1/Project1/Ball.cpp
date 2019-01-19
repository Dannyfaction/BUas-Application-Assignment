#include "Ball.h"
#include <iostream>
#include "Player.h"
//#include "GlobalEventDispatcher.h"
#include "SpawnID.h"

Ball::Ball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction)
{
	spawnID = SpawnID::getInstance().GetNewID();
	std::cout << "Spawned ball with ID: " << spawnID << "\n";

	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);

	this->direction = direction;

	lifetime = 0.0f;
	maxLifetime = 5.0f;
	speed = 100.0f;
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

void Ball::OnCollision(sf::Vector2f direction, int &health)
{
	health -= damage;
	//Remove urself (ball)

}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Ball::RemoveSelf()
{
	//character.balls.erase(character.balls.begin());
	//balls.erase(balls.begin());
	//GlobalEventDispatcher::getInstance().dispatcher.dispatch(1, GetSpawnID());
}
