#include "GameState.h"
#include "Spawner.h"
#include "TextureManager.h"
#include "UserInterface.h"

void Gamestate::StartGame()
{
	Spawner::getInstance().SpawnPlayer(TextureManager::getInstance().GetPlayerTexture(), sf::Vector2u(4, 8), 0.3f, 200.0f, 300, 1.0f);
	UserInterface::getInstance().SpawnHealth();
}

void Gamestate::ResetGame()
{
	for (int i = 0; i < Spawner::getInstance().player.size(); i++)
	{
		Spawner::getInstance().player.erase(Spawner::getInstance().player.begin() + i);
	}

	int enemySize = Spawner::getInstance().enemies.size();
	for (int i = 0; i < enemySize; i++)
	{
		Spawner::getInstance().enemies.erase(Spawner::getInstance().enemies.begin());
	}

	int playerBallsSize = Spawner::getInstance().playerBalls.size();
	for (int i = 0; i < playerBallsSize; i++)
	{
		Spawner::getInstance().playerBalls.erase(Spawner::getInstance().playerBalls.begin());
	}

	int enemyBallSize = Spawner::getInstance().enemyBalls.size();
	for (int i = 0; i < enemyBallSize; i++)
	{
		Spawner::getInstance().enemyBalls.erase(Spawner::getInstance().enemyBalls.begin());
	}

	for (int i = 0; i < Spawner::getInstance().gameOverScreen.size(); i++)
	{
		Spawner::getInstance().gameOverScreen.erase(Spawner::getInstance().gameOverScreen.begin() + i);
	}

	StartGame();

	Spawner::getInstance().waveManager[0].Initialize();
}
