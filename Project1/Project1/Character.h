#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Character
{
public:
	Character();
	~Character();

	std::vector<Ball> balls;
};

