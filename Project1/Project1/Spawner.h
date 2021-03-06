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
#include "WaveText.h"
#include "GameEndText.h"
#include "HowToPlay.h"

class Spawner
{
public:
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

	void SpawnWaveText(int size, sf::Vector2f position, std::string message, sf::Color color);
	void SpawnGameEndText(int size, sf::Vector2f position, std::string message, sf::Color color);

	void SpawnHowToPlay(sf::Vector2f size, sf::Vector2f position);

	void RemovePlayer(int spawnID);
	void RemoveEnemy(int spawnID);
	void RemoveBall(int spawnID);

	void ReduceHealth();

	void RemoveWaveText();
	void RemoveHowToPlay();

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

	std::vector<WaveText> waveText;
	std::vector<GameEndText> gameEndText;
	std::vector<HowToPlay> howToPlay;
};

