#pragma once
#include <SFML/Graphics.hpp>

class Gamestate
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static Gamestate &getInstance() {
		static Gamestate instance;
		return instance;
	}

	void StartGame();
	void ResetGame();


private:
	Gamestate() {}

public:
	Gamestate(Gamestate const&) = delete;
	void operator=(Gamestate const&) = delete;
};