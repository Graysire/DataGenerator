#ifndef Table_H
#define Table_H

#include <vector>
#include "TableEntry.h"
#include "RNG.h"

class Table : public EntryData
{
public:
	Table();
	Table(std::string name, std::vector<TableEntry*> itemList);
	Table(const Table &obj);
	~Table();
	virtual std::string GetResultString(unsigned int quantity);
	virtual std::string GetResultString();
	virtual void GetResult(unsigned int quantity, std::vector<EntryData*>& resultData);
	virtual void GetResult(std::vector<EntryData*>& resultData);
	virtual std::vector<EntryData*> GetResultVector(unsigned int numRolls);
	TableEntry* GetRandomItem();
	void AddEntry(TableEntry* entry);
protected:
	std::vector<TableEntry*>* items;
	long long totalFrequency;
};

#endif // !Table_H
