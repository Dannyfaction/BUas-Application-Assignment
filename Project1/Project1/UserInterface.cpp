#include "UserInterface.h"
#include "Spawner.h"
#include <iostream>

void UserInterface::LoadUserInterface(sf::RenderWindow& window)
{
	topLeftScreenPosition = -sf::Vector2f(window.getSize().x/2, window.getSize().y/2);
	heartSize = sf::Vector2f(75, 75);
	heartOffset = sf::Vector2f(20, 20);
	waveTextOffset = sf::Vector2f(0, -200);
	heartPosition = sf::Vector2f(topLeftScreenPosition.x + heartSize.x / 2 + heartOffset.x, topLeftScreenPosition.y + heartSize.y / 2 + heartOffset.y);

	SpawnHealth();
}

//Function that gets called every frame to make sure that the UserInterface stays in place on the screen when the player moves around
void UserInterface::UpdateUserInterface(sf::RenderWindow & window)
{
	topLeftScreenPosition = -sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
	heartPosition = sf::Vector2f(topLeftScreenPosition.x + heartSize.x / 2 + heartOffset.x, topLeftScreenPosition.y + heartSize.y / 2 + heartOffset.y);
	sf::Vector2f heartPositionBasedOnPlayerPosition = heartPosition + Spawner::getInstance().player[0].body.getPosition();

	for (int i = 0; i < Spawner::getInstance().health.size(); i++)
	{
		Spawner::getInstance().health[i].body.setPosition(heartPositionBasedOnPlayerPosition.x + ((heartSize.x + heartOffset.x) * i) , heartPositionBasedOnPlayerPosition.y);
	}

	for (int i = 0; i < Spawner::getInstance().waveText.size(); i++)
	{
		Spawner::getInstance().waveText[i].text.setPosition(Spawner::getInstance().player[0].body.getPosition() + waveTextOffset);
	}
}

void UserInterface::LoadGameOverScreen()
{
	sf::Vector2f gameOverScreenSize = sf::Vector2f(800, 500);
	Spawner::getInstance().SpawnGameOverScreen(gameOverScreenSize, Spawner::getInstance().player[0].body.getPosition());
}

void UserInterface::SpawnHealth()
{
	//Spawn player health in the top left of the screen
	for (int i = 0; i < Spawner::getInstance().player[0].health / 100; i++)
	{
		Spawner::getInstance().SpawnHealth(heartSize, sf::Vector2f(heartPosition.x + (heartSize.x + heartOffset.x) * i, heartPosition.y));
	}
}

void UserInterface::SpawnWaveText(int currentWave)
{
	std::string message = "Wave " + std::to_string(currentWave);
	sf::Color textColor = sf::Color::Red;
	//Spawner::getInstance().SpawnWaveText(1, sf::Vector2f(0,0), message, textColor);
	Spawner::getInstance().SpawnWaveText(50, Spawner::getInstance().player[0].body.getPosition() + waveTextOffset, message, textColor);

}
