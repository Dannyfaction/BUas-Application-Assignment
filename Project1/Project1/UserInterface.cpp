#include "UserInterface.h"
#include "Spawner.h"
#include <iostream>

void UserInterface::LoadUserInterface(sf::RenderWindow& window)
{
	topLeftScreenPosition = -sf::Vector2f(window.getSize().x/2, window.getSize().y/2);
	heartSize = sf::Vector2f(75, 75);
	heartOffset = sf::Vector2f(20, 20);
	heartPosition = sf::Vector2f(topLeftScreenPosition.x + heartSize.x / 2 + heartOffset.x, topLeftScreenPosition.y + heartSize.y / 2 + heartOffset.y);

	//Spawn player health in the top left of the screen
	for (int i = 0; i < Spawner::getInstance().player[0].health/100; i++)
	{
		Spawner::getInstance().SpawnHealth(heartSize, sf::Vector2f(heartPosition.x + (heartSize.x + heartOffset.x) * i, heartPosition.y));
	}

	//Spawn Wave counter
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
}

void UserInterface::LoadGameOverScreen()
{
	sf::Vector2f gameOverScreenSize = sf::Vector2f(800, 500);
	Spawner::getInstance().SpawnGameOverScreen(gameOverScreenSize, Spawner::getInstance().player[0].body.getPosition());
}
