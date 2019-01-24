#include "WaveManager.h"
#include <iostream>
#include <random>
#include "Spawner.h"
#include "UserInterface.h"


WaveManager::WaveManager(sf::RectangleShape &playerBody) : playerBody(playerBody)
{
	currentWave = 0;
	elapsedTimeSinceLastWave = 0;
	elapsedTimeSinceLastEnemy = 0;
	spawnedEnemiesAmount = 0;
	waveCooldown = 0.0f;
	diedEnemiesAmount = 0;

	enemyTexture.loadFromFile("Textures/Enemy_EditedV2.0.png");

	SetWaveData();
	NextWave();
}


WaveManager::~WaveManager()
{

}

void WaveManager::Update(float deltaTime)
{
	elapsedTimeSinceLastWave += deltaTime;
	elapsedTimeSinceLastEnemy += deltaTime;
	SpawnWave();

	if (diedEnemiesAmount >= waveDatas[currentWave - 1].amountOfEnemies) {
		NextWave();
	}
}

void WaveManager::SetWaveData()
{
	//WaveData holds the information of each wave (Amount of enemies, time between enemy spawns, health, snowball throw rate)

	//Wave 1
	waveDatas.push_back(WaveData(3, 3.0f, 100, 3.0f));

	//Wave 2
	waveDatas.push_back(WaveData(5, 4.5f, 200, 2.5f));

	//Wave 3
	waveDatas.push_back(WaveData(6, 6.0f, 300, 2.0f));

	//Wave 4 (final)
	waveDatas.push_back(WaveData(8, 6.0f, 300, 1.75f));
}

void WaveManager::SpawnWave()
{
	//This function gets called every frame and checks whether it can spawn an enemy during a wave
	if (currentWave <= waveDatas.size())
	{
		if (elapsedTimeSinceLastWave > waveCooldown)
		{
			if (spawnedEnemiesAmount < waveDatas[currentWave - 1].amountOfEnemies)
			{
				if (elapsedTimeSinceLastEnemy > waveDatas[currentWave - 1].timeBetweenSpawns)
				{
					spawnedEnemiesAmount++;
					elapsedTimeSinceLastEnemy = 0;
					SpawnEnemy();
				}
			}
		}
	}
}

void WaveManager::NextWave()
{
	if (currentWave < waveDatas.size()) {
		elapsedTimeSinceLastWave = 0;
		waveCooldown = 3;
		currentWave++;
		spawnedEnemiesAmount = 0;
		diedEnemiesAmount = 0;
		UserInterface::getInstance().SpawnWaveText(currentWave);
	}
	else {
		//spawn finish
		UserInterface::getInstance().SpawnGameEnd();
	}
}

void WaveManager::SpawnEnemy()
{
	sf::Vector2f enemyPosition;

	srand(time(0));
	//Generate a random number between 1 and 4 which determines on which of the four sides the enemy is spawned
	int randomEnemyDirection = std::rand() % 4 + 1;

	//Generate a random number between -300 and 300 which determines where exactly the enemy is spawned on one of the four sides
	int randomEnemyPosition = std::rand() % 600 + -300;

	int health = waveDatas[currentWave - 1].health;
	//Randomize the shootcooldown a little bit so all the enemies won't shoot at the same time
	float minimumEnemyShootCooldown = waveDatas[currentWave - 1].shootCooldown - 0.25f;
	float maximumEnemyShootCooldown = waveDatas[currentWave - 1].shootCooldown + 0.25f;
	//Following formula taken from a Stackoverflow answer https://stackoverflow.com/questions/686353/random-float-number-generation
	float randomizedEnemyShootCooldown = minimumEnemyShootCooldown + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maximumEnemyShootCooldown - minimumEnemyShootCooldown)));

	switch(randomEnemyDirection)
	{
	case 1:
		enemyPosition = sf::Vector2f(randomEnemyPosition, -500);
		break;
	case 2:
		enemyPosition = sf::Vector2f(500, randomEnemyPosition);
		break;
	case 3:
		enemyPosition = sf::Vector2f(randomEnemyPosition, 500);
		break;
	case 4:
		enemyPosition = sf::Vector2f(-500, randomEnemyPosition);
		break;
	}

	//Spawn an enemy with the following information; Texture, Position, Direction, health, ShootCooldown and ShootTarget
	//spawnedEnemies.push_back(Enemy(&enemyTexture, sf::Vector2u(1,4), enemyPosition, randomEnemyDirection, health, randomizedEnemyShootCooldown, playerBody));
	Spawner::getInstance().SpawnEnemy(sf::Vector2u(1, 4), enemyPosition, randomEnemyDirection, health, randomizedEnemyShootCooldown);
}
