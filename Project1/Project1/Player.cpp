#include "Player.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, float shootCooldown) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->shootCooldown = shootCooldown;
	
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() /2.0f);
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);

	//Snowball Texture found with a google image search https://fr.kisspng.com/png-qt9l43/
	ballTexture.loadFromFile("Textures/Snowball.png");
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if(shootTimer > 0.0f)
	{
		shootTimer -= deltaTime;
	}

	if(velocity.x > 0.0f)
	{
		velocity.x -= speed;
	}else if(velocity.x < 0.0f)
	{
		velocity.x += speed;
	}
	if (velocity.y > 0.0f)
	{
		velocity.y -= speed;
	}else if(velocity.y < 0.0f)
	{
		velocity.y += speed;
	}
	//velocity.x *= 0.5f;
	//velocity.y *= 0.5f;

	//Change the velocity of the player once a movement key has been pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if(velocity.y > -speed)
		{
			velocity.y -= speed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (velocity.x > -speed)
		{
			velocity.x -= speed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (velocity.y < speed)
		{
			velocity.y += speed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (velocity.x < speed)
		{
			velocity.x += speed;
		}
	}

	//Throw a ball once the Spacebar key is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) & shootTimer <= 0) {
		shootTimer = shootCooldown;
		//Spawn a ball with the following information; Texture, Size, Position, Direction and the <vector>balls reference so that it can remove itself
		balls.push_back(Ball(&ballTexture, sf::Vector2f(25.0f, 25.0f), sf::Vector2f(body.getPosition().x, body.getPosition().y), DirectionFromAnimationRow()));
	}

	//If in the previous frame you were walking and this frame you stopped walking, change to Idle animation
	if(row == 7 | row == 3 | row == 1 | row == 5)
	{
		if(velocity.x == 0.0f & velocity.y == 0.0f)
		{
			row--;
		}
	}

	//If you are walking to the right
	if (velocity.x > 0.0f) {
		row = 7;
		//faceRight = true;
	}
	else if(velocity.x < 0.0f){
		row = 3;
		//faceRight = false;
	}

	//If you are walking to the left
	if (velocity.y > 0.0f)
	{
		row = 1;
	}
	else if (velocity.y < 0.0f)
	{
		row = 5;
	}
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

	for (Ball& ball : balls) {
		ball.Update(deltaTime);
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		//Collision on the left
		velocity.x = 0.0f;
	}else if(direction.x > 0.0f) {
		//Collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) {
		//Collision on the bottom
		velocity.y = 0.0f;
		//canJump = true;
	}else if (direction.y > 0.0f) {
		//Collision on the top
		velocity.y = 0.0f;
	}
}

sf::Vector2f Player::DirectionFromAnimationRow()
{
	sf::Vector2f direction;

	switch (row)
	{
	case 0:
	case 1:
		direction = sf::Vector2f(0.0f, 1.0f);
		break;
	case 2:
	case 3:
		direction = sf::Vector2f(-1.0f, 0.0f);
		break;
	case 4:
	case 5:
		direction = sf::Vector2f(0.0f, -1.0f);
		break;
	case 6:
	case 7:
		direction = sf::Vector2f(1.0f, 0.0f);
		break;
	default:
		direction = sf::Vector2f(0.0f, -1.0f);
		break;
	}

	return  direction;
}
