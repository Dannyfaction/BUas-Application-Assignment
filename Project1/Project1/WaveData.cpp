#include "WaveData.h"



WaveData::WaveData(int amountOfEnemies, float timeBetweenSpawns, float shootCooldown)
{
	this->amountOfEnemies = amountOfEnemies;
	this->timeBetweenSpawns = timeBetweenSpawns;
	this->shootCooldown = shootCooldown;
}


WaveData::~WaveData()
{
}
