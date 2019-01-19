#pragma once

class SpawnID
{
public:
	//Singleton written with the help of this Stackoverflow answer https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	static SpawnID &getInstance() {
		static SpawnID instance;
		return instance;
	}

	int SpawnIDCounter = 0;
	int GetNewID();

private:
	SpawnID() {}

public:
	SpawnID(SpawnID const&) = delete;
	void operator=(SpawnID const&) = delete;
};

