#ifndef TableEntry_H
#define TableEntry_H

#include "EntryData.h"

class TableEntry
{
public:
	TableEntry(EntryData* data, int freq);
	TableEntry(EntryData* data);
	TableEntry(const TableEntry& obj);
	virtual ~TableEntry();

	virtual std::string GetResultString();

	int GetFrequency();
	void SetFrequency(int freq);
	std::string GetName();
	void SetName(std::string name);

	bool operator==(const TableEntry &other);
protected:
	int frequency;
	EntryData* data;
};

#endif // !TableEntry_H
