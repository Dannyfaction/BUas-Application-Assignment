#pragma once
#include <SFML/Graphics.hpp>

class WaveData
{
public:
	WaveData(int amountOfEnemies, float timeBetweenSpawns, int health, float shootCooldown);
	~WaveData();

	int amountOfEnemies;
	float timeBetweenSpawns;
	int health;
	float shootCooldown;
};