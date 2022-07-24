#ifndef NumberGenerationStruct_H
#define NumberGenerationStruct_H

struct Dice
{
	Dice() : numDice(1), numSides(8), baseNum(0), multiplier(1)
	{
	}
	Dice(unsigned short numDice, unsigned short numSides, short baseNum, unsigned short multiplier) : numDice(numDice), numSides(numSides), baseNum(baseNum), multiplier(multiplier)
	{
	}
	unsigned short numDice;
	unsigned short numSides;
	short baseNum;
	unsigned short multiplier;
};

#endif // !NumberGenerationStruct_H
