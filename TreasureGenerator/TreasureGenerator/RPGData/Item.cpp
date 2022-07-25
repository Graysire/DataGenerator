#include "Item.h"
#include <sstream>

#define QUANTITYMULT (printEach ? 1 : quantity)

bool Item::printEach = true;

Item::Item() : EntryData("Generic Item", 1), value(0), weight(0)
{

}

Item::Item(std::string name, unsigned long value, unsigned long weight) : EntryData(name, 1), value(value), weight(weight)
{

}

Item::Item(std::string name, unsigned int quantity, unsigned long value, unsigned long weight) : EntryData(name, quantity), value(value), weight(weight)
{

}

Item::Item(const Item& obj) : EntryData(obj), value(obj.value), weight(obj.weight)
{
}

Item::Item(Item&& obj) noexcept : EntryData(std::move(obj)), value(obj.value), weight(obj.weight)
{
	obj.value = 0;
	obj.weight = 0;
}

Item Item::operator=(const Item& obj)
{
	return Item(obj);
}

std::string Item::GetResultString(unsigned int quantity)
{
	return EntryData::GetResultString(quantity);
}

std::string Item::GetResultString()
{
	std::ostringstream result;
	result << EntryData::GetResultString();

	result.setf(std::ios::right);
	result.width(FirstDescriptorWidth);
	result << (QUANTITYMULT * value / 1000.0) << "sp ";
	result.width(SecondDescriptorWidth);
	result << (QUANTITYMULT * weight / 1000.0) << "lb";

	return result.str();
}

void Item::GetResult(unsigned int quantity, std::vector<EntryData*>& resultData)
{
	this->quantity = quantity;
	GetResult(resultData);
}
void Item::GetResult(std::vector<EntryData*>& resultData)
{
	resultData.push_back(new Item(*this));
}


unsigned long Item::GetValue()
{
	return value;
}

void Item::SetValue(unsigned long value)
{
	this->value = value;
}

unsigned long Item::GetWeight()
{
	return weight;
}

void Item::SetWeight(unsigned long weight)
{
	this->weight = weight;
}

void Item::SetPrintEach(bool printEach)
{
	Item::printEach = printEach;
}