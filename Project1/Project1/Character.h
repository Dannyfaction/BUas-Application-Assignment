#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Character
{
public:
	Character();
	~Character();

	CharacterType characterType;

	int health;
	sf::RectangleShape body;
	std::vector<Ball> balls;
};

enum class CharacterType
{
	player,
	enemy
};