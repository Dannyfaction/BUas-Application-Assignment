#include "HowToPlay.h"
#include "TextureManager.h"
#include "Spawner.h"

HowToPlay::HowToPlay(sf::Vector2f size, sf::Vector2f position)
{
	lifetime = 0;
	maxLifetime = 3;

	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(TextureManager::getInstance().GetHowToPlayTexture());
	body.setPosition(position);
}

HowToPlay::~HowToPlay()
{
}

void HowToPlay::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void HowToPlay::Update(float deltaTime)
{
	lifetime += deltaTime;
	//After a few seconds, remove the How To Play tooltip
	if (lifetime >= maxLifetime) {
		Spawner::getInstance().RemoveHowToPlay();
	}
}
