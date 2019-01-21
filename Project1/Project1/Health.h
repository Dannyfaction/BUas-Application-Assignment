#pragma once
#include <SFML/Graphics.hpp>
//#include "Collider.h"

class Health
{
public:
	Health(sf::Vector2f size, sf::Vector2f position);
	~Health();

	void Draw(sf::RenderWindow& window);
	//Collider GetCollider() { return Collider(body); }
	sf::RectangleShape body;

private:

	//sf::Sprite wallSprite;
};