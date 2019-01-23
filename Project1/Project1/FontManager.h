#pragma once
#include <SFML/Graphics.hpp>

class FontManager
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static FontManager &getInstance() {
		static FontManager instance;
		return instance;
	}

	void LoadFonts();
	sf::Font* GetWaveFont() { return &waveFont; }



private:
	FontManager() {}

public:
	FontManager(FontManager const&) = delete;
	void operator=(FontManager const&) = delete;

private:
	sf::Font waveFont;
};