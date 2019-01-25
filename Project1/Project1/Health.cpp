#include "Health.h"
#include "TextureManager.h"


Health::Health(sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(TextureManager::getInstance().GetHeartTexture());
	body.setPosition(position);
}

Health::~Health()
{
}

void Health::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
