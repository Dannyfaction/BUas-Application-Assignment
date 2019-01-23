#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Background.h"
#include "Wall.h"
#include "Health.h"
#include "WaveManager.h"
#include "GameOverScreen.h"

class Spawner
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static Spawner &getInstance() {
		static Spawner instance;
		return instance;
	}
	void Update(float deltaTime);

	void SpawnPlayer(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, float shootCooldown);
	void SpawnEnemy(sf::Vector2u imageCount, sf::Vector2f position, int rotation, int health, float shootCooldown);
	void SpawnPlayerBall(sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction);
	void SpawnEnemyBall(sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction);

	void SpawnHealth(sf::Vector2f size, sf::Vector2f position);

	void SpawnBackground(sf::Vector2f size, sf::Vector2f position);
	void SpawnWall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool rotate);

	void SpawnWaveManager(sf::RectangleShape &playerBody);
	void SpawnGameOverScreen(sf::Vector2f size, sf::Vector2f position);

	void RemovePlayer(int spawnID);
	void RemoveEnemy(int spawnID);
	void RemoveBall(int spawnID);

	void ReduceHealth();

private:
	Spawner() {}

public:
	Spawner(Spawner const&) = delete;
	void operator=(Spawner const&) = delete;

	std::vector<Player> player;
	std::vector<Enemy> enemies;
	std::vector<Ball> playerBalls;
	std::vector<Ball> enemyBalls;
	
	std::vector<Background> backgrounds;
	std::vector<Wall> walls;

	std::vector<Health> health;

	std::vector<WaveManager> waveManager;
	std::vector<GameOverScreen> gameOverScreen;
};

