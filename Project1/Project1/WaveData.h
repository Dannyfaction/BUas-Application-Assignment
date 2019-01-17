#pragma once
#include <SFML/Graphics.hpp>

class WaveData
{
public:
	WaveData(int amountOfEnemies, float timeBetweenSpawns, float shootCooldown);
	~WaveData();

	int amountOfEnemies;
	float timeBetweenSpawns;
	float shootCooldown;
};