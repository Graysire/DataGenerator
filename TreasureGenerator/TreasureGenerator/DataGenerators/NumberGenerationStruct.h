#ifndef NumberGenerationStruct_H
#define NumberGenerationStruct_H

struct Dice
{
	Dice() : numDice(1), numSides(8), baseNum(0), multiplier(1)
	{
	}
	Dice(const Dice& obj) : numDice(obj.numDice), numSides(obj.numSides), baseNum(obj.baseNum), multiplier(obj.multiplier)
	{
	}
	Dice(Dice&& obj) noexcept : numDice(obj.numDice), numSides(obj.numSides), baseNum(obj.baseNum), multiplier(obj.multiplier)
	{
		obj.numDice = 0;
		obj.numSides = 0;
		obj.baseNum = 0;
		obj.multiplier = 0;
	}
	Dice(unsigned short numDice, unsigned short numSides, short baseNum, unsigned short multiplier) : numDice(numDice), numSides(numSides), baseNum(baseNum), multiplier(multiplier)
	{
	}

	Dice operator=(const Dice& obj)
	{
		return Dice(obj);
	}

	unsigned short numDice;
	unsigned short numSides;
	short baseNum;
	unsigned short multiplier;
};

#endif // !NumberGenerationStruct_H
