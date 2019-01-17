#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider other, sf::Vector2f& direction, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize()
	{
		//Check if the body has been rotated 90 degrees. If so, then flip the X and Y so that the collisions work correctly
		if(body.getRotation() == 90.0f)
		{
			return sf::Vector2f(body.getSize().y, body.getSize().x) / 2.0f;
		}else
		{
			return body.getSize() / 2.0f;
		}
	}

private:
	sf::RectangleShape& body;
};

