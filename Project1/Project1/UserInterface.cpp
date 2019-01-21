#include "UserInterface.h"

void UserInterface::LoadUserInterface()
{
	//Spawn Health
	//Spawn Wave counter
}

void UserInterface::Draw(sf::RenderWindow & window)
{
	for (int i = 0; i < healthBar.size(); i++)
	{
		window.draw(healthBar[i]);
	}
	//window.draw(body);
}
