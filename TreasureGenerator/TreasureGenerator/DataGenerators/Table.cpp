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
	delete items;
}

std::string Table::GetResultString(int quantity)
{
	this->quantity = quantity;
	return GetResultString();
}

std::string Table::GetResultString()
{
	std::ostringstream result;
	for (int i = 0; i < quantity; i++)
	{
		TableEntry* entry = GetRandomItem();
		if (entry == nullptr)
		{
			return "";
		}
		result << entry->GetResultString() << std::endl;
	}
	return result.str();
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