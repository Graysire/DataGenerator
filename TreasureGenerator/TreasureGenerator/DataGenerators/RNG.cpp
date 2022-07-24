#include "RNG.h"

std::mt19937_64 RNG::rngEngine = std::mt19937_64(std::random_device()());

long long RNG::GetNum(long long min, long long max)
{
	std::uniform_int_distribution<long long> rng(min, max);
	return rng(rngEngine);
}

void RNG::SetSeed(unsigned long long seed)
{
	rngEngine.seed(seed);
}