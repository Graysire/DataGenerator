#include "Table.h"

Table::Table() : EntryData("Generic Table", 1)
{
	items = new std::vector<TableEntry*>;
	totalFrequency = 0;
}

Table::Table(std::string name, std::vector<TableEntry*> itemList) : EntryData(name, 1)
{
	totalFrequency = 0;
	for each (TableEntry* item in itemList)
	{
		totalFrequency += item->GetFrequency();
	}
	items = new std::vector<TableEntry*>(itemList);
}

Table::Table(const Table& table)
{
	items = new std::vector<TableEntry*>(*table.items);
	totalFrequency = table.totalFrequency;
	quantity = table.quantity;
	name = table.name;
}

Table::~Table()
{
	for each (TableEntry * entry in *items)
	{
		delete entry;
	}
	delete items;
}

std::string Table::GetResultString(unsigned int quantity)
{
	this->quantity = quantity;
	return GetResultString();
}

std::string Table::GetResultString()
{
	std::ostringstream result;
	std::vector<EntryData*> dataList = GetResultVector(quantity);
	for (int i = 0; i < dataList.size(); i++)
	{
		result << dataList[i]->GetResultString() << std::endl;
	}

	for each (EntryData* data in dataList)
	{
		delete data;
	}

	return result.str();
}

void Table::GetResult(unsigned int quantity, std::vector<EntryData*>& resultData)
{
	this->quantity = quantity;
	GetResult(resultData);
}

void Table::GetResult(std::vector<EntryData*>& resultData)
{
	for (int i = 0; i < quantity; i++)
	{
		TableEntry* entry = GetRandomItem();
		if (entry == nullptr)
		{
			return;
		}
		entry->GetResult(resultData);
	}
}

std::vector<EntryData*> Table::GetResultVector(unsigned int numRolls = 1)
{
	std::vector<EntryData*> results;
	GetResult(numRolls, results);
	return results;
}

void Table::AddEntry(TableEntry* item)
{
	items->push_back(item);
	totalFrequency += item->GetFrequency();
}

TableEntry* Table::GetRandomItem()
{
	if (items->size() < 1)
	{
		return nullptr;
	}
	long long selection = RNG::GetNum(1, totalFrequency);

	for each (TableEntry* item in *items)
	{
		selection -= item->GetFrequency();
		if (selection <= 0)
		{
			return item;
		}
	}

	return nullptr;
}