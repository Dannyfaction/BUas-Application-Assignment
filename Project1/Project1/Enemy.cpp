#include "Enemy.h"
#include <iostream>


Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f position, int rotation, float shootCooldown, sf::RectangleShape &target) : target(target)
{
	this->shootCooldown = shootCooldown;
	this->rotation = rotation;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position.x, position.y);
	body.setTexture(texture);

	shootCooldownTimer = 0;

	SetTextureRotation(rotation, texture, imageCount);

	//TODO make a Texture Manager
	//ballTexture.loadFromFile("Textures/Snowball.png");
}


Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	shootCooldownTimer += deltaTime;

	//Once the enemy is not on shootcooldown anymore, shoot a snowball
	if (shootCooldownTimer >= shootCooldown) {
		//The direction the ball is going to be 'thrown' in
		sf::Vector2f targetDirection = sf::Vector2f(target.getPosition() - body.getPosition());

		//Normalize the Vector so that the length is 1 (preventing the ball from flying away at high speeds instead of using the Speed value initialized in ball.cpp)
		float length = sqrt((targetDirection.x * targetDirection.x) + (targetDirection.y * targetDirection.y));
		targetDirection = sf::Vector2f(targetDirection.x / length, targetDirection.y / length);

		//Spawn a snowball with the following information; Texture, Size, Position, Direction
		balls.push_back(Ball(&ballTexture, sf::Vector2f(25.0f, 25.0f), sf::Vector2f(body.getPosition().x, body.getPosition().y), targetDirection, balls));

		//Reset the cooldown timer
		shootCooldownTimer = 0;
	}

	for (Ball& ball : balls) {
		ball.Update(deltaTime);
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemy::SetTextureRotation(int rotation, sf::Texture* texture, sf::Vector2u imageCount)
{
	sf::IntRect uvRect;
	sf::Vector2u currentImage;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

	switch(rotation)
	{
	case 1:
		currentImage.x = 0;
		currentImage.y = 0;
		break;
	case 2:
		currentImage.x = 0;
		currentImage.y = 1;
		break;
	case 3:
		currentImage.x = 0;
		currentImage.y = 2;
		break;
	case 4:
		currentImage.x = 0;
		currentImage.y = 3;
		break;
	}

	uvRect.top = currentImage.y * uvRect.height;
	uvRect.left = currentImage.x * uvRect.width;

	body.setTextureRect(uvRect);
}
