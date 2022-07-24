#include "EntryData.h"

EntryData::EntryData() : name("Generic Entry"), quantity(1)
{
}

EntryData::EntryData(std::string name) : name(name), quantity(1)
{
}

EntryData::EntryData(std::string name, unsigned int quantity) : name(name), quantity(quantity)
{
}

EntryData::EntryData(const EntryData& obj) : EntryData(obj.name, obj.quantity)
{
}

EntryData::EntryData(EntryData&& obj) noexcept : EntryData(obj.name, obj.quantity)
{
	obj.name = "";
	obj.quantity = 0;
}

std::string EntryData::GetResultString(unsigned int quantity)
{
	this->quantity = quantity;

	return GetResultString();
}

std::string EntryData::GetResultString()
{
	std::ostringstream result;
	result.setf(std::ios::left);
	result.width(QuantityWidth);
	result << quantity << " ";
	result.width(NameWidth);
	result << name << " ";

	return result.str();
}

std::string EntryData::GetName()
{
	return name;
}

void EntryData::SetName(std::string name)
{
	this->name = name;
}

int EntryData::GetQuantity()
{
	return quantity;
}

void EntryData::SetQuantity(unsigned int quantity)
{
	this->quantity = quantity;
}