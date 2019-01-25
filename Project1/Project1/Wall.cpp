#include "Wall.h"



Wall::Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool rotate)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	//Repeat the texture in the x axis 4 times
	body.setTextureRect(sf::IntRect(0, 0, texture->getSize().x*4, texture->getSize().y));

	if (rotate)
	{
		body.setRotation(90.0f);
	}
}


Wall::~Wall()
{
}

void Wall::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
