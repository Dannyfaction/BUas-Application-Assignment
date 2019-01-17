#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Ball.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f position, int rotation,float shootCooldown, sf::RectangleShape &target);
	~Enemy();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void SetTextureRotation(int rotation, sf::Texture* texture, sf::Vector2u imageCount);

	float shootCooldown;
	std::vector<Ball> balls;

private:
	sf::RectangleShape body;
	sf::Texture enemyTexture;
	sf::Texture ballTexture;
	sf::RectangleShape &target;

	float shootCooldownTimer;
	int rotation;
};

