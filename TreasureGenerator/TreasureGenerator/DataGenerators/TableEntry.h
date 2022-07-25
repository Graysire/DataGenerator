#ifndef TableEntry_H
#define TableEntry_H

#include "EntryData.h"
#include <vector>

class TableEntry
{
public:
	TableEntry(EntryData* data, int freq);
	TableEntry(EntryData* data);
	TableEntry(const TableEntry& obj);
	TableEntry(TableEntry&& obj) noexcept;
	virtual ~TableEntry();

	virtual void GetResult(std::vector<EntryData*>& resultData);

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
