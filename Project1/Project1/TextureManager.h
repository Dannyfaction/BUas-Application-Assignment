#pragma once
#include <SFML/Graphics.hpp>

class TextureManager
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static TextureManager &getInstance() {
		static TextureManager instance;
		return instance;
	}

	void LoadTextures();
	sf::Texture* GetPlayerTexture() { return &playerTexture; }
	sf::Texture* GetEnemyTexture() { return &enemyTexture; }
	sf::Texture* GetBallTexture() { return &ballTexture; }
	sf::Texture* GetBackGroundTexture() { return &backgroundTexture; }
	sf::Texture* GetWallTexture() { return &wallTexture; }
	sf::Texture* GetHeartTexture() { return &heartTexture; }


private:
	TextureManager() {}

public:
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

private:
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture ballTexture;

	sf::Texture backgroundTexture;
	sf::Texture wallTexture;

	sf::Texture heartTexture;

};

