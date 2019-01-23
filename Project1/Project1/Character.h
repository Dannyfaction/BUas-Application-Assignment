#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Character
{
public:
	Character();
	~Character();

	int health;
	float hitProtectionTimer;
	int spawnID;
	sf::RectangleShape body;
	//std::vector<Ball> balls;
};