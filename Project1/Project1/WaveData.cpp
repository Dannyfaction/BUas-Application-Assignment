#include "WaveData.h"

//a Class which simply holds information about waves
WaveData::WaveData(int amountOfEnemies, float timeBetweenSpawns, int health, float shootCooldown)
{
	this->amountOfEnemies = amountOfEnemies;
	this->timeBetweenSpawns = timeBetweenSpawns;
	this->health = health;
	this->shootCooldown = shootCooldown;
}


WaveData::~WaveData()
{
}
