#ifndef Item_H
#define Item_H

#include "../DataGenerators/EntryData.h"

class Item : public EntryData
{
public:
	Item();
	Item(std::string name, unsigned long value, unsigned long weight);
	Item(std::string name, unsigned int quantity, unsigned long value, unsigned long weight);
	Item(const Item& obj);
	Item(Item&& obj) noexcept;

	Item operator=(const Item& obj);

	virtual std::string GetResultString(unsigned int quantity);
	virtual std::string GetResultString();

	unsigned long GetValue();
	void SetValue(unsigned long value);
	unsigned long GetWeight();
	void SetWeight(unsigned long weight);
	static void SetPrintEach(bool printEach);
protected:
	//Value in 1000ths of a unit
	unsigned long value;
	//Weight ib 1000ths of a unit
	unsigned long weight;
	//Print per quantity or total
	static bool printEach;
};

#endif // !Item_H
