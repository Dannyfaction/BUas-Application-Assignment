#include "Player.h"
#include <iostream>
//#include "GlobalEventDispatcher.h"
#include "SpawnID.h"
#include "Spawner.h"
#include "TextureManager.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, float shootCooldown) :
	animation(texture, imageCount, switchTime)
{
	spawnID = SpawnID::getInstance().GetNewID();
	std::cout << "Spawned player with ID: " << spawnID << "\n";

	this->speed = speed;
	this->health = health;
	this->shootCooldown = shootCooldown;
	

	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() /2.0f);
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);


	/*
	GlobalEventDispatcher::getInstance().dispatcher.appendListener(1, [](const int & otherSpawnID) {
		RemoveBallByID(otherSpawnID);
	});
	std::cout << "Appended enemy listener for possible ball remove with my ID: " << spawnID << "\n";

	GlobalEventDispatcher::getInstance().dispatcher.appendListener(2, [this](const int & spawnID) {
		RemoveBallByID(spawnID);
	});*/
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
		//balls.push_back(Ball(&ballTexture, sf::Vector2f(25.0f, 25.0f), sf::Vector2f(body.getPosition().x, body.getPosition().y), DirectionFromAnimationRow()));
		Spawner::getInstance().SpawnPlayerBall(sf::Vector2f(25.0f, 25.0f), sf::Vector2f(body.getPosition().x, body.getPosition().y), DirectionFromAnimationRow());
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

	/*
	for (Ball& ball : balls) {
		ball.Update(deltaTime);
	}*/
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

void Player::RemoveSelf()
{
	std::cout << "removed";
	//balls.erase(balls.begin());
}

void Player::RemoveBallByID(int spawnID)
{
	//std::cout << balls.size();
	std::cout << "I am a Listener with the ID: " << spawnID << " and I'm trying to remove a ball" << "\n";
	/*
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].GetSpawnID() == spawnID) {
			std::cout << "Removed ball from player" << "\n";
			balls.erase(balls.begin() + i);
		}
	}*/
	

}
