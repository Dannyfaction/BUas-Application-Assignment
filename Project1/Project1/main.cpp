#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Spawner.h"
#include "Wall.h"
#include "Background.h"
#include "WaveManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "UserInterface.h"

static const float VIEW_WIDTH = 900.0f;
static const float VIEW_HEIGHT = 900.0f;

//Whenever the window gets resized, prevent the window from being stretched out
void ResizeView(sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Snowball Battle", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	TextureManager::getInstance().LoadTextures();
	FontManager::getInstance().LoadFonts();

	//Spawn the player with the following information: Texture, Imagecount(of the texture), switchtime (animation speed), movementspeed, health and shootcooldown.
	Spawner::getInstance().SpawnPlayer(TextureManager::getInstance().GetPlayerTexture(), sf::Vector2u(4, 8), 0.3f, 200.0f, 300, 1.0f);

	UserInterface::getInstance().LoadUserInterface(view);
	float const backgroundRows = 5;
	float const backgroundColumns = 5;
	float backgroundCenterXOffset = backgroundColumns * 500.0f / 2.0F;
	float backgroundCenterYOffset = backgroundRows * 500.0f / 2.0F;

	//Spawn multiple instances of the background texture to fill up the playing field
	for (int i = 0; i < backgroundRows; i++)
	{
		for (int j = 0; j < backgroundColumns; j++)
		{
			Spawner::getInstance().SpawnBackground(sf::Vector2f(500.0f, 500.0f), sf::Vector2f(j  * 500.0f - backgroundCenterXOffset, i * 500.0f - backgroundCenterYOffset));
		}
	}

	//Spawn 4 "ice" walls all around the center of the playing field
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(0.0f, -400.0f), false);
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(0.0f, 400.0f), false);
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(-400.0f, 0.0f), true);
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(400.0f, 0.0f), true);

	Spawner::getInstance().SpawnWaveManager(Spawner::getInstance().player[0].body);

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f) {
			deltaTime = 1.0f / 20.0f;
		}

		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}
		//If the game has not ended yet, update all of the spawned classes and User interface
		if (Spawner::getInstance().gameOverScreen.size() <= 0 && Spawner::getInstance().gameEndText.size() <= 0){
			Spawner::getInstance().Update(deltaTime);
			UserInterface::getInstance().UpdateUserInterface(view);
		}

		sf::Vector2f direction;

		//Check if the player collides with any of the walls
		for (Wall& wall : Spawner::getInstance().walls)
		{
			if (wall.GetCollider().CheckCollision(Spawner::getInstance().player[0].GetCollider(), direction, 1.0f)) {
				//Push the player back into the direction it came from
				Spawner::getInstance().player[0].OnCollision(direction);
			}
		}

		//Lock the view onto the player
		view.setCenter(Spawner::getInstance().player[0].GetPosition());


		//Check if the enemy's snowballs collide with the player
		for (Ball& ball : Spawner::getInstance().enemyBalls) {
			if (ball.GetCollider().CheckCollision(Spawner::getInstance().player[0].GetCollider(), direction, 0.0f)) {
				//If the player is not under 'hit protection', reduce the health of the player on the UI
				if (Spawner::getInstance().player[0].hitProtectionTimer <= 0) {
					Spawner::getInstance().ReduceHealth();
				}
				//Reduce the health of the object that is hit and remove the snowball
				ball.OnCollision(direction, Spawner::getInstance().player[0].health, Spawner::getInstance().player[0].hitProtectionTimer);
			}
		}
		//Check if the player's snowballs collide with an enemy
		for (Ball& ball : Spawner::getInstance().playerBalls) {
			for (Enemy& enemy : Spawner::getInstance().enemies)
			{
				if (ball.GetCollider().CheckCollision(enemy.GetCollider(), direction, 0.0f)) {
					//Reduce the health of the object that is hit and remove the snowball
					ball.OnCollision(direction, enemy.health, enemy.hitProtectionTimer);
				}
			}
		}

		window.clear(sf::Color(150, 150, 150));
		window.setView(view);

		//Draw all spawnable objects on the screen
		for (Background& background : Spawner::getInstance().backgrounds) {
			background.Draw(window);
		}
		for (Wall& wall : Spawner::getInstance().walls) {
			wall.Draw(window);
		}
		for (Player& player : Spawner::getInstance().player) {
			player.Draw(window);
		}
		for (Enemy& enemy : Spawner::getInstance().enemies)
		{
			enemy.Draw(window);
		}
		for (Ball& ball : Spawner::getInstance().enemyBalls) {
			ball.Draw(window);
		}
		for (Ball& ball : Spawner::getInstance().playerBalls) {
			ball.Draw(window);
		}
		for (Health& health : Spawner::getInstance().health) {
			health.Draw(window);
		}
		for (WaveText& waveText : Spawner::getInstance().waveText) {
			waveText.Draw(window);
		}
		for (GameOverScreen& gameOverScreen : Spawner::getInstance().gameOverScreen) {
			gameOverScreen.Draw(window);
		}
		for (GameEndText& gameEndText : Spawner::getInstance().gameEndText) {
			gameEndText.Draw(window);
		}
		for (HowToPlay& howToPlay : Spawner::getInstance().howToPlay) {
			howToPlay.Draw(window);
		}

		window.display();
	}

	return 0;
}