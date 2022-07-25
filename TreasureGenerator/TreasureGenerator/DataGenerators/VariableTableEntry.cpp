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
VariableTableEntry::VariableTableEntry(VariableTableEntry&& obj) noexcept : TableEntry(std::move(obj)), dice(std::move(dice))
{
}
VariableTableEntry::~VariableTableEntry()
{
}

void VariableTableEntry::GetResult(std::vector<EntryData*>& resultList)
{
	unsigned int sum = dice.baseNum;
	for (int i = 0; i < dice.numDice; i++)
	{
		sum += RNG::GetNum(1, dice.numSides);
	}
	sum *= dice.multiplier;

	data->GetResult(sum, resultList);
}

Dice VariableTableEntry::GetDice()
{
	return dice;
}

void VariableTableEntry::SetDice(Dice dice)
{
	this->dice = dice;
}