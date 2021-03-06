#include "UserInterface.h"
#include "Spawner.h"

void UserInterface::LoadUserInterface(sf::View& view)
{
	topLeftScreenPosition = -sf::Vector2f(view.getSize().x/2, view.getSize().y/2);
	heartSize = sf::Vector2f(75, 75);
	heartOffset = sf::Vector2f(20, 20);
	textOffset = sf::Vector2f(0, -200);
	howToPlayOffset = sf::Vector2f(300, -300);
	heartPosition = sf::Vector2f(topLeftScreenPosition.x + heartSize.x / 2 + heartOffset.x, topLeftScreenPosition.y + heartSize.y / 2 + heartOffset.y);

	SpawnHowToPlay();
}

//Function that gets called every frame to make sure that the UserInterface stays in place on the screen when the player moves around
void UserInterface::UpdateUserInterface(sf::View& view)
{
	topLeftScreenPosition = -sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2);
	heartPosition = sf::Vector2f(topLeftScreenPosition.x + heartSize.x / 2 + heartOffset.x, topLeftScreenPosition.y + heartSize.y / 2 + heartOffset.y);
	sf::Vector2f heartPositionBasedOnPlayerPosition = heartPosition + Spawner::getInstance().player[0].body.getPosition();


	for (int i = 0; i < Spawner::getInstance().health.size(); i++)
	{
		Spawner::getInstance().health[i].body.setPosition(heartPositionBasedOnPlayerPosition.x + ((heartSize.x + heartOffset.x) * i) , heartPositionBasedOnPlayerPosition.y);
	}

	for (int i = 0; i < Spawner::getInstance().waveText.size(); i++)
	{
		Spawner::getInstance().waveText[i].text.setPosition(Spawner::getInstance().player[0].body.getPosition() + textOffset);
	}

	for (int i = 0; i < Spawner::getInstance().howToPlay.size(); i++)
	{
		Spawner::getInstance().howToPlay[i].body.setPosition(Spawner::getInstance().player[0].body.getPosition() + howToPlayOffset);
	}
}

void UserInterface::LoadGameOverScreen()
{
	sf::Vector2f gameOverScreenSize = sf::Vector2f(800, 700);
	Spawner::getInstance().SpawnGameOverScreen(gameOverScreenSize, Spawner::getInstance().player[0].body.getPosition());
}

void UserInterface::SpawnHowToPlay()
{
	sf::Vector2f howToPlaySize = sf::Vector2f(500, 300);
	Spawner::getInstance().SpawnHowToPlay(howToPlaySize, howToPlayOffset);
}

void UserInterface::SpawnHealth()
{
	//Spawn player health in the top left of the screen
	for (int i = 0; i < Spawner::getInstance().player[0].health / 100; i++)
	{
		Spawner::getInstance().SpawnHealth(heartSize, sf::Vector2f(heartPosition.x + (heartSize.x + heartOffset.x) * i, heartPosition.y));
	}
}

//At the start of every wave, spawn a text above the center of the screen showing the current wave
void UserInterface::SpawnWaveText(int currentWave)
{
	std::string message = "Wave " + std::to_string(currentWave);
	sf::Color textColor = sf::Color::Red;
	Spawner::getInstance().SpawnWaveText(50, Spawner::getInstance().player[0].body.getPosition() + textOffset, message, textColor);

}

//When there are no waves left, show the player that the game has been completed
void UserInterface::SpawnGameEnd()
{
	std::string message = "You completed the game, congratulations!";
	sf::Color textColor = sf::Color::Green;
	Spawner::getInstance().SpawnGameEndText(30, Spawner::getInstance().player[0].body.getPosition() + textOffset, message , textColor);
}
