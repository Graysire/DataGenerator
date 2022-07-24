#include "VariableTableEntry.h"

VariableTableEntry::VariableTableEntry(EntryData* data, int freq) : TableEntry(data, freq)
{
}
VariableTableEntry::VariableTableEntry(EntryData* data) : TableEntry(data)
{
}
VariableTableEntry::VariableTableEntry(EntryData* data, Dice dice, int freq) : TableEntry(data, freq), dice(dice)
{
}
VariableTableEntry::VariableTableEntry(const VariableTableEntry& obj) : TableEntry(obj), dice(obj.dice)
{
}

VariableTableEntry::~VariableTableEntry()
{
}

std::string VariableTableEntry::GetResultString()
{
	unsigned int sum = dice.baseNum;
	for (int i = 0; i < dice.numDice; i++)
	{
		sum += RNG::GetNum(1, dice.numSides);
	}
	sum *= dice.multiplier;

	return data->GetResultString(sum);
}

Dice VariableTableEntry::GetDice()
{
	return dice;
}

void VariableTableEntry::SetDice(Dice dice)
{
	this->dice = dice;
}