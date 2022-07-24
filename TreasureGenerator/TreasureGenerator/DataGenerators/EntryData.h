#ifndef EntryData_H
#define EntryData_H

#include <string>
#include <sstream>

class EntryData
{
public:
	EntryData();
	EntryData(std::string name);
	EntryData(std::string name, unsigned int quantity);
	EntryData(const EntryData& obj);
	EntryData(EntryData&& obj) noexcept;

	virtual std::string GetResultString(unsigned int quantity);
	virtual std::string GetResultString();

	std::string GetName();
	void SetName(std::string name);
	int GetQuantity();
	void SetQuantity(unsigned int quantity);
protected:
	std::string name;
	int quantity;
};

enum RESULT_COLUMN_WIDTH
{
	QuantityWidth = 6,
	NameWidth = 20,
	FirstDescriptorWidth = 10,
	SecondDescriptorWidth = 10,
	FinalDescriptorWidth = 400,
};

#endif // !EntryData_H
