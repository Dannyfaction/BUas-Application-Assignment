#include "WaveText.h"
#include "Spawner.h"
#include "FontManager.h"
#include <iostream>


WaveText::WaveText(int size, sf::Vector2f position, std::string message, sf::Color color)
{
	text.setCharacterSize(size);
	text.setPosition(position);
	text.setString(message);
	text.setFillColor(color);
	text.setFont(*FontManager::getInstance().GetWaveFont());
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

	lifetime = 0;
	maxLifetime = 3;
}


WaveText::~WaveText()
{
}

void WaveText::Draw(sf::RenderWindow & window)
{
	window.draw(text);
}

void WaveText::Update(float deltaTime)
{
	lifetime += deltaTime;
	if (lifetime >= maxLifetime) {
		Spawner::getInstance().RemoveWaveText();
		std::cout << "removed text \n";
	}
}
