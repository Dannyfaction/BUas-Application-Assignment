#include "Background.h"
#include "TextureManager.h"


Background::Background(sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(0, 0);
	body.setTexture(TextureManager::getInstance().GetBackGroundTexture());
	body.setPosition(position);
}


Background::~Background()
{
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
