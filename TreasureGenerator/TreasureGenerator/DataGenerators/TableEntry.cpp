#include "TableEntry.h"

TableEntry::TableEntry(EntryData* data, int frequency) : data(data), frequency(frequency)
{
}

TableEntry::TableEntry(EntryData* data) : TableEntry(data, 100)
{
}

TableEntry::TableEntry(const TableEntry& obj) : TableEntry(obj.data, obj.frequency)
{
}

TableEntry::~TableEntry()
{
	delete data;
}

std::string TableEntry::GetResultString()
{
	return data->GetResultString();
}

int TableEntry::GetFrequency()
{
	return frequency;
}

void TableEntry::SetFrequency(int frequency)
{
	this->frequency = frequency;
}

std::string TableEntry::GetName()
{
	return data->GetName();
}

void TableEntry::SetName(std::string name)
{
	data->SetName(name);
}

bool TableEntry::operator==(const TableEntry &other)
{
	if (other.data->GetName() == data->GetName())
	{
		return true;
	}
	return false;
}