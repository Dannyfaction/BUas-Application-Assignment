#include "SpawnID.h"

int SpawnID::GetNewID()
{
	SpawnIDCounter++;
	return SpawnIDCounter;
}
