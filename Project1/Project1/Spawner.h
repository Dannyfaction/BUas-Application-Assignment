#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

class Spawner
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static Spawner &getInstance() {
		static Spawner instance;
		return instance;
	}
	void Update(float deltaTime);

	void SpawnPlayer(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, int health, float shootCooldown);
	void SpawnEnemy(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f position, int rotation, int health, float shootCooldown, sf::RectangleShape &target);
	void SpawnPlayerBall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction);
	void SpawnEnemyBall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Vector2f direction);

	//Player GetPlayer() { return player[player.begin]; }


private:
	Spawner() {}

public:
	Spawner(Spawner const&) = delete;
	void operator=(Spawner const&) = delete;

	std::vector<Player> player;
	std::vector<Enemy> enemies;
	std::vector<Ball> playerBalls;
	std::vector<Ball> enemyBalls;
};

