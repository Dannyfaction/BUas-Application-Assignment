#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Wall
{
public:
	Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool rotate);
	~Wall();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
};