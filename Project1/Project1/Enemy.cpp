#include "Enemy.h"
#include "SpawnID.h"
#include "Spawner.h"
#include "TextureManager.h"

Enemy::Enemy(sf::Vector2u imageCount, sf::Vector2f position, int rotation, int health, float shootCooldown) 
{
	spawnID = SpawnID::getInstance().GetNewID();

	this->shootCooldown = shootCooldown;
	this->health = health;
	this->rotation = rotation;

	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position.x, position.y);
	body.setTexture(TextureManager::getInstance().GetEnemyTexture());

	shootCooldownTimer = 0;
	hitProtectionTimer = 0;

	SetTextureRotation(rotation, TextureManager::getInstance().GetEnemyTexture(), imageCount);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	//Count down the shoot cooldown timer
	if (shootCooldownTimer > 0) {
		shootCooldownTimer -= deltaTime;
	}

	//Count down the hit protection timer
	if (hitProtectionTimer > 0) {
		hitProtectionTimer -= deltaTime;
	}

	//Once the enemy is not on shootcooldown anymore, throw a snowball
	if (shootCooldownTimer <= 0) {

		//The direction the ball is going to be 'thrown' in
		target = Spawner::getInstance().player[0].body;
		sf::Vector2f targetDirection = sf::Vector2f(target.getPosition() - body.getPosition());

		//Normalize the Vector so that the length is 1 (preventing the ball from flying away at high speeds instead of using the Speed value initialized in ball.cpp)
		float length = sqrt((targetDirection.x * targetDirection.x) + (targetDirection.y * targetDirection.y));
		targetDirection = sf::Vector2f(targetDirection.x / length, targetDirection.y / length);

		//Spawn a snowball with the following information; Size, Position, Direction
		Spawner::getInstance().SpawnEnemyBall(sf::Vector2f(25.0f, 25.0f), sf::Vector2f(body.getPosition().x, body.getPosition().y), targetDirection);

		//Reset the cooldown timer
		shootCooldownTimer = shootCooldown;
	}

	if (health <= 0) {
		RemoveSelf();
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

//Makes the enemy face towards the center of the playing field
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

void Enemy::RemoveSelf()
{
	Spawner::getInstance().waveManager[0].IncreaseDiedEnemiesAmount();
	Spawner::getInstance().RemoveEnemy(spawnID);
}