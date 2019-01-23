#pragma once
#include "eventdispatcher.h"

class GlobalEventDispatcher
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static GlobalEventDispatcher &getInstance() {
		static GlobalEventDispatcher instance;
		return instance;
	}

	void OnEnemyDeath(int spawnID);

private:
	GlobalEventDispatcher() {}

public:
	GlobalEventDispatcher(GlobalEventDispatcher const&) = delete;
	void operator=(GlobalEventDispatcher const&) = delete;


};

