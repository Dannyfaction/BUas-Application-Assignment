#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Spawner.h"
#include "Wall.h"
#include "Background.h"
#include "WaveManager.h"
#include "TextureManager.h"
#include "UserInterface.h"

static const float VIEW_WIDTH = 900.0f;
static const float VIEW_HEIGHT = 900.0f;

void ResizeView(sf::RenderWindow& window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Project1", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	TextureManager::getInstance().LoadTextures();

	Spawner::getInstance().SpawnPlayer(TextureManager::getInstance().GetPlayerTexture(), sf::Vector2u(4, 8), 0.3f, 200.0f, 300, 1.0f);

	UserInterface::getInstance().LoadUserInterface(window);
	float const backgroundRows = 5;
	float const backgroundColumns = 5;
	float backgroundCenterXOffset = backgroundColumns * 500.0f / 2.0F;
	float backgroundCenterYOffset = backgroundRows * 500.0f / 2.0F;

	for (int i = 0; i < backgroundRows; i++)
	{
		for (int j = 0; j < backgroundColumns; j++)
		{
			Spawner::getInstance().SpawnBackground(sf::Vector2f(500.0f, 500.0f), sf::Vector2f(j  * 500.0f - backgroundCenterXOffset, i * 500.0f - backgroundCenterYOffset));
		}
	}

	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(0.0f, -400.0f), false);
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(0.0f, 400.0f), false);
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(-400.0f, 0.0f), true);
	Spawner::getInstance().SpawnWall(TextureManager::getInstance().GetWallTexture(), sf::Vector2f(875.0f, 100.0f), sf::Vector2f(400.0f, 0.0f), true);

	WaveManager waveManager(Spawner::getInstance().player[0].body);

	float deltaTime = 0.0f;
	sf::Clock clock;

	/*sf::Vector2u textureSize = playerTexture.getSize();
	textureSize.x /= 3;
	textureSize.y /= 9;


	player.setTextureRect(sf::IntRect(textureSize.x * 2, textureSize.y * 8, textureSize.x, textureSize.y));
	*/

	//player.setFillColor(sf::Color::Red);
	//player.setOrigin(player.getSize().x/2, player.getSize().y/2);

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
				//std::cout << "New window width: " << evnt.size.width << " New window height: " << evnt.size.height << std::endl;
				//printf("New window width: %i New window height: %i\n", evnt.size.width, evnt.size.height);
				ResizeView(window, view);
				break;
			}
		}
		if (!Spawner::getInstance().player[0].GetDeadState()) {
			//player.Update(deltaTime);
			Spawner::getInstance().Update(deltaTime);

			waveManager.Update(deltaTime);
			UserInterface::getInstance().UpdateUserInterface(window);
		}
		sf::Vector2f direction;

		for (Wall& wall : Spawner::getInstance().walls)
		{
			if (wall.GetCollider().CheckCollision(Spawner::getInstance().player[0].GetCollider(), direction, 1.0f)) {
				Spawner::getInstance().player[0].OnCollision(direction);
			}
		}


		view.setCenter(Spawner::getInstance().player[0].GetPosition());

		//player.setTextureRect(animation.uvRect);

		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));

		}
		*/

		for (Ball& ball : Spawner::getInstance().enemyBalls) {
			if (ball.GetCollider().CheckCollision(Spawner::getInstance().player[0].GetCollider(), direction, 0.0f)) {
				//Spawner::getInstance().player[0].OnCollision(direction);
				Spawner::getInstance().ReduceHealth();
				ball.OnCollision(direction, Spawner::getInstance().player[0].health);
			}
		}
		for (Ball& ball : Spawner::getInstance().playerBalls) {
			for (Enemy& enemy : Spawner::getInstance().enemies)
			{
				if (ball.GetCollider().CheckCollision(enemy.GetCollider(), direction, 0.0f)) {
					//player.OnCollision(direction);
					ball.OnCollision(direction, enemy.health);
				}
			}
		}

		window.clear(sf::Color(150, 150, 150));
		window.setView(view);

		for (Background& background : Spawner::getInstance().backgrounds) {
			background.Draw(window);
		}
		for (Wall& wall : Spawner::getInstance().walls) {
			wall.Draw(window);
		}

		Spawner::getInstance().player[0].Draw(window);

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
		for (GameOverScreen& gameOverScreen : Spawner::getInstance().gameOverScreen) {
			gameOverScreen.Draw(window);
		}

		window.display();
	}

	return 0;
}