#include "cRandom.h"


cRandom cRandom::Range = cRandom(cRandom::RandomSeed());

uint32_t cRandom::RandomSeed()
{
	std::random_device device;
	return device();
}
