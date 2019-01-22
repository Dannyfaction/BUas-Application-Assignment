#include "GameOverScreen.h"
#include "TextureManager.h"


GameOverScreen::GameOverScreen(sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(TextureManager::getInstance().GetGameOverTexture());
	body.setPosition(position);
}


GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
