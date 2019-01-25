#include "GameEndText.h"
#include "FontManager.h"

GameEndText::GameEndText(int size, sf::Vector2f position, std::string message, sf::Color color)
{
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setString(message);
	text.setFillColor(color);
	text.setFont(*FontManager::getInstance().GetTextFont());
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}


GameEndText::~GameEndText()
{
}

void GameEndText::Draw(sf::RenderWindow & window)
{
	window.draw(text);
}