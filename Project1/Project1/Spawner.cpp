#include "Spawner.h"

void Spawner::Update(float deltaTime)
{
	for (int i = 0; i < player.size(); i++)
	{
		player[i].Update(deltaTime);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i].Update(deltaTime);
	}

	for (int i = 0; i < playerBalls.size(); i++)
	{
		playerBalls[i].Update(deltaTime);
	}

	for (int i = 0; i < enemyBalls.size(); i++)
	{
		enemyBalls[i].Update(deltaTime);
	}


}

void Spawner::SpawnPlayer(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, float shootCooldown)
{
	player.push_back(Player(texture, imageCount, switchTime, speed, health, shootCooldown));
}

void Spawner::SpawnEnemy(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f position, int rotation, int health, float shootCooldown, sf::RectangleShape & target)
{
	enemies.push_back(Enemy(texture, imageCount, position, rotation, health, shootCooldown, target));
}

void Spawner::SpawnPlayerBall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction)
{
	playerBalls.push_back(Ball(texture, size, position, direction));
}

void Spawner::SpawnEnemyBall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction)
{
	enemyBalls.push_back(Ball(texture, size, position, direction));
}
