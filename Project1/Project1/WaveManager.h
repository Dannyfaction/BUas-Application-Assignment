#pragma once
#include <SFML/Graphics.hpp>
#include "WaveData.h"

class WaveManager
{
public:
	WaveManager(sf::RectangleShape &playerBody);
	~WaveManager();

	void Update(float deltaTime);
	void IncreaseDiedEnemiesAmount() { diedEnemiesAmount++; };

private:
	void SetWaveData();
	void SpawnWave();
	void NextWave();
	void SpawnEnemy();

	sf::RectangleShape &playerBody;

	std::vector<WaveData> waveDatas;
	
	int currentWave;
	float waveCooldown;

	float elapsedTimeSinceLastWave;
	float elapsedTimeSinceLastEnemy;

	int spawnedEnemiesAmount;
	int diedEnemiesAmount;

	sf::Texture enemyTexture;
};

