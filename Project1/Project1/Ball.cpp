#include "Ball.h"
#include <iostream>
#include "Player.h"


Ball::Ball(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction, std::vector<Ball> &balls) : balls(balls)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);

	this->direction = direction;

	lifetime = 0.0f;
	maxLifetime = 5.0f;
	speed = 250.0f;
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
		balls.erase(balls.begin());
	}
}

void Ball::OnCollision(sf::Vector2f direction)
{
	std::cout << "COLLISION";
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
