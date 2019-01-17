#pragma once
#include <SFML/Graphics.hpp>
#include "WaveData.h"
#include "Enemy.h"

class WaveManager
{
public:
	WaveManager(sf::RectangleShape &playerBody);
	~WaveManager();

	void Update(float deltaTime);

	std::vector<Enemy> spawnedEnemies;

private:
	void SetWaveData();
	void SpawnWave();
	void SpawnEnemy();

	sf::RectangleShape &playerBody;

	std::vector<WaveData> waveDatas;
	
	int currentWave;
	float waveCooldown;

	float elapsedTimeSinceLastWave;
	float elapsedTimeSinceLastEnemy;

	int spawnedEnemiesAmount;

	sf::Texture enemyTexture;
};

