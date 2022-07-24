#ifndef VariableTableEntry_H
#define VariableTableEntry_H

#include "TableEntry.h"
#include "NumberGenerationStruct.h"
#include "RNG.h"

class VariableTableEntry : public TableEntry
{
public:
	VariableTableEntry(EntryData* data, int freq);
	VariableTableEntry(EntryData* data);
	VariableTableEntry(EntryData* data, Dice dice, int freq);
	VariableTableEntry(const VariableTableEntry& obj);
	VariableTableEntry(VariableTableEntry&& obj) noexcept;
	virtual ~VariableTableEntry();

	virtual std::string GetResultString();

	Dice GetDice();
	void SetDice(Dice dice);
private:
	Dice dice;
};

#endif // !VariableTableEntry_H
