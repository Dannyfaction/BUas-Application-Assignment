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

void Spawner::SpawnEnemy(sf::Vector2u imageCount, sf::Vector2f position, int rotation, int health, float shootCooldown)
{
	enemies.push_back(Enemy(imageCount, position, rotation, health, shootCooldown));
}

void Spawner::SpawnPlayerBall(sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction)
{
	playerBalls.push_back(Ball(size, position, direction));
}

void Spawner::SpawnEnemyBall(sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction)
{
	enemyBalls.push_back(Ball(size, position, direction));
}

void Spawner::SpawnHealth(sf::Vector2f size, sf::Vector2f position)
{
	health.push_back(Health(size, position));
}

void Spawner::SpawnBackground(sf::Vector2f size, sf::Vector2f position)
{
	backgrounds.push_back(Background(size, position));
}

void Spawner::SpawnWall(sf::Texture * texture, sf::Vector2f size, sf::Vector2f position, bool rotate)
{
	walls.push_back(Wall(texture, size, position, rotate));
}

void Spawner::RemovePlayer(int spawnID)
{
	for (int i = 0; i < player.size(); i++)
	{
		if (player[i].GetSpawnID() == spawnID) {
			player.erase(player.begin()+i);
		}
	}
}

void Spawner::RemoveEnemy(int spawnID)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].GetSpawnID() == spawnID) {
			enemies.erase(enemies.begin() + i);
		}
	}
}

void Spawner::RemoveBall(int spawnID)
{
	for (int i = 0; i < playerBalls.size(); i++)
	{
		if (playerBalls[i].GetSpawnID() == spawnID) {
			playerBalls.erase(playerBalls.begin() + i);
		}
	}

	for (int i = 0; i < enemyBalls.size(); i++)
	{
		if (enemyBalls[i].GetSpawnID() == spawnID) {
			enemyBalls.erase(enemyBalls.begin() + i);
		}
	}
}
