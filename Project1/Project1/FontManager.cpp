#include "FontManager.h"
#include <iostream>

void FontManager::LoadFonts()
{
	if (!waveFont.loadFromFile("Fonts/arial.ttf")) {
		std::cout << "couldn't load font \n";
	}
}