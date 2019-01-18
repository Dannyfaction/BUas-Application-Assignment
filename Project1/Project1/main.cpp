#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Wall.h"
#include "Background.h"
#include "WaveManager.h"

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

	sf::Texture playerTexture;
	//Player texture and animations is an edited version of this Character https://opengameart.org/content/alternate-lpc-character-sprites-george
	playerTexture.loadFromFile("Textures/George_Edited.png");

	Player player(&playerTexture, sf::Vector2u(4, 8), 0.3f, 200.0f, 300, 1.0f);

	sf::Texture backgroundTexture;
	//Seamless Background Texture found with a google image search https://sftextures.com/wp-content/plugins/sf-textures-plugin/sf-textures-preview.php?tiling=Seamless&image=https://sftextures.com/wp-content/uploads/2015/01/snow-white-rough-air-fresh-light-frozen-frosty-ground-clear-seamless-texture-256x256.jpg
	backgroundTexture.loadFromFile("Textures/Seamless_Snow.jpg");

	sf::Texture wallTexture;
	//Wall Texture is an edited version of the following image which was found with a google image search https://www.kisspng.com/png-ice-cube-stock-photography-royalty-free-blue-crush-182395/
	wallTexture.loadFromFile("Textures/Ice_Wall.png");
	wallTexture.setRepeated(true);

	std::vector<Background> backgrounds;

	float const backgroundRows = 5;
	float const backgroundColumns = 5;
	float backgroundCenterXOffset = backgroundColumns * 500.0f / 2.0F;
	float backgroundCenterYOffset = backgroundRows * 500.0f / 2.0F;

	for (int i = 0; i < backgroundRows; i++)
	{
		for (int j = 0; j < backgroundColumns; j++)
		{
			backgrounds.push_back(Background(&backgroundTexture, sf::Vector2f(500.0f, 500.0f), sf::Vector2f(j  * 500.0f - backgroundCenterXOffset, i * 500.0f - backgroundCenterYOffset)));
		}
	}

	std::vector<Wall> walls;
	walls.push_back(Wall(&wallTexture, sf::Vector2f(875.0f, 100.0f), sf::Vector2f(0.0f, -400.0f), false));
	walls.push_back(Wall(&wallTexture, sf::Vector2f(875.0f, 100.0f), sf::Vector2f(0.0f, 400.0f), false));
	walls.push_back(Wall(&wallTexture, sf::Vector2f(875.0f, 100.0f), sf::Vector2f(-400.0f, 0.0f), true));
	walls.push_back(Wall(&wallTexture, sf::Vector2f(875.0f, 100.0f), sf::Vector2f(400.0f, 0.0f), true));

	//walls.push_back(Wall(&wallTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
	//walls.push_back(Wall(&wallTexture, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
	//walls.push_back(Wall(&wallTexture, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

	WaveManager waveManager(player.body);



	//animation.setSmooth(true);

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
				/*
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128) {
					printf("%c", evnt.text.unicode);
				}
				break;
				*/
			}
		}
		player.Update(deltaTime);
		waveManager.Update(deltaTime);

		sf::Vector2f direction;

		//for each Wall in Walls<vector>
		for (Wall& wall: walls)
		{
			if (wall.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f)) {
				player.OnCollision(direction);
			}
		}


		view.setCenter(player.GetPosition());

		//player.setTextureRect(animation.uvRect);

		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));

		}
		*/
		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.move(0.0f, 0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move(0.1f, 0.0f);
		}
		*/

		window.clear(sf::Color(150,150,150));
		window.setView(view);
		for (Background& background : backgrounds) {
			background.Draw(window);
		}
		for (Wall& wall : walls) {
			wall.Draw(window);
		}
		player.Draw(window);
		for (Enemy& enemy : waveManager.spawnedEnemies)
		{
			enemy.Draw(window);
			for (Ball& ball : enemy.balls) {
				ball.Draw(window);

				if (ball.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f)) {
					//player.OnCollision(direction);
					ball.OnCollision(direction, player.health);
				}
			}
		}
		for (Ball& ball : player.balls) {
			ball.Draw(window);

			for (Enemy& enemy : waveManager.spawnedEnemies)
			{
				if (ball.GetCollider().CheckCollision(enemy.GetCollider(), direction, 0.0f)) {
					//player.OnCollision(direction);
					ball.OnCollision(direction, enemy.health);
				}
			}
		}

		window.display();
	}

	return 0;
}