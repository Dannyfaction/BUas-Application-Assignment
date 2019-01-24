#pragma once
#include <SFML/Graphics.hpp>

class Character
{
public:
	Character();
	~Character();

	int health;
	float hitProtectionTimer;
	int spawnID;
	sf::RectangleShape body;
};