#include "SpawnID.h"

//This class simply assigns a new SpawnID to certain classes so that we can easily distinguish them from each other

int SpawnID::GetNewID()
{
	SpawnIDCounter++;
	return SpawnIDCounter;
}
