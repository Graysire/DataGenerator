#ifndef RandomNumberGenerator_H
#define RandomNumberGenerator_H

#include <random>

class RNG
{
private:
	static std::mt19937_64 rngEngine;
public:
	static long long GetNum(long long min, long long max);
	static void SetSeed(unsigned long long seed);
};

#endif // !RandomNumberGenerator_H
