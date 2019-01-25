#include "Player.h"
#include "SpawnID.h"
#include "TextureManager.h"
#include "Spawner.h"
#include "UserInterface.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, float shootCooldown) :
	animation(texture, imageCount, switchTime)
{
	spawnID = SpawnID::getInstance().GetNewID();

	this->speed = speed;
	this->health = health;
	this->shootCooldown = shootCooldown;
	shootCooldownTimer = 0.0f;
	hitProtectionTimer = 0.0f;

	row = 0;

	body.setSize(sf::Vector2f(85.0f, 85.0f));
	body.setOrigin(body.getSize() /2.0f);
	body.setPosition(0.0f, 0.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//If the player has no more health, load the game over screen
	if (health <= 0) {
		UserInterface::getInstance().LoadGameOverScreen();
	}
	//Count down the hit protection timer
	if (hitProtectionTimer > 0) {
		hitProtectionTimer -= deltaTime;
	}
	//Count down the shoot cooldown timer
	if(shootCooldownTimer > 0)
	{
		shootCooldownTimer -= deltaTime;
	}

	if(velocity.x > 0)
	{
		velocity.x -= speed;
	}else if(velocity.x < 0)
	{
		velocity.x += speed;
	}
	if (velocity.y > 0)
	{
		velocity.y -= speed;
	}else if(velocity.y < 0)
	{
		velocity.y += speed;
	}

	//Change the velocity of the player once a movement key has been pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		if(velocity.y > -speed)
		{
			velocity.y -= speed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))){
		if (velocity.x > -speed)
		{
			velocity.x -= speed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		if (velocity.y < speed)
		{
			velocity.y += speed;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
		if (velocity.x < speed)
		{
			velocity.x += speed;
		}
	}

	//Throw a ball once the Spacebar key is pressed and the player is not on a cooldown anymore
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) & shootCooldownTimer <= 0) {
		shootCooldownTimer = shootCooldown;
		//Spawn a ball with the following information; Size, Position and the Direction
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
	}
	else if(velocity.x < 0.0f){
		row = 3;
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

	animation.Update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
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
	}else if (direction.y > 0.0f) {
		//Collision on the top
		velocity.y = 0.0f;
	}


}

//Translates the current animation of the player to the direction the ball should be going towards
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