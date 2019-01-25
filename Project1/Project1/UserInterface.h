#pragma once
#include <SFML/Graphics.hpp>

class UserInterface
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static UserInterface &getInstance() {
		static UserInterface instance;
		return instance;
	}

	void LoadUserInterface(sf::RenderWindow& window);
	void UpdateUserInterface(sf::RenderWindow& window);
	void LoadGameOverScreen();

	void SpawnHowToPlay();
	void SpawnHealth();
	void SpawnWaveText(int currentWave);
	void SpawnGameEnd();

private:
	UserInterface() {}

public:
	UserInterface(UserInterface const&) = delete;
	void operator=(UserInterface const&) = delete;

private:
	std::vector<sf::RectangleShape> healthBar;

	sf::Vector2f topLeftScreenPosition;

	sf::Vector2f heartSize;
	sf::Vector2f heartOffset;
	sf::Vector2f howToPlayOffset;
	sf::Vector2f textOffset;
	sf::Vector2f heartPosition;
};