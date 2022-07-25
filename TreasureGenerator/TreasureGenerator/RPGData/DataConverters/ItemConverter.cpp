#include "ItemConverter.h"
#include <algorithm>

unsigned short ItemConverter::minShufflePercent = 5;
unsigned short ItemConverter::maxShufflePercent = 95;
unsigned short ItemConverter::numShuffles = 1;
bool ItemConverter::roundUp = true;
ItemConverterSort ItemConverter::sortOrder = ItemConverterSort::SortDescending;
ItemConverterDistribution ItemConverter::distribution = ItemConverterDistribution::DistConcentrated;
ItemConverterShuffle ItemConverter::shuffle = ItemConverterShuffle::ShuffleDown;

std::vector<Item> ItemConverter::ConvertItems(std::vector<Item*> itemsToConvert, std::vector<Item*> itemsToConvertTo)
{
	std::vector<Item> result;

	switch (ItemConverter::sortOrder)
	{
	case SortDescending:
		std::sort(itemsToConvert.begin(), itemsToConvert.end(), [](Item* i, Item* j) -> bool { return i->GetValue() > j->GetValue(); });
		std::sort(itemsToConvertTo.begin(), itemsToConvertTo.end(), [](Item* i, Item* j) -> bool { return i->GetValue() > j->GetValue(); });
		break;
	case SortAscending:
		std::sort(itemsToConvert.begin(), itemsToConvert.end(), [](Item* i, Item* j) -> bool { return i->GetValue() < j->GetValue(); });
		std::sort(itemsToConvertTo.begin(), itemsToConvertTo.end(), [](Item* i, Item* j) -> bool { return i->GetValue() < j->GetValue(); });
		break;
	case SortRandom:
		std::random_shuffle(itemsToConvert.begin(), itemsToConvert.end());
		std::random_shuffle(itemsToConvertTo.begin(), itemsToConvertTo.end());
	case NoSort:
	default:
		break;
	}

	unsigned long minValue = ULONG_MAX;
	int minIndex = -1;

	//create the result array of all possible items
	for(int i = 0; i < itemsToConvertTo.size(); i++)
	{
		Item copy = Item(*itemsToConvertTo[i]);
		copy.SetQuantity(0);
		result.push_back(copy);
		if (copy.GetValue() < minValue)
		{
			minValue = copy.GetValue();
			minIndex = i;
		}
	}

	//Keep track of any fractional value that can't be converted to ensure the minimum loss of value
	unsigned long long spareValue = 0;

	for each (Item * item in itemsToConvert)
	{
		//Add to the value
		spareValue += (unsigned long long)item->GetQuantity() * item->GetValue();
		if (spareValue == 0)
		{
			continue;
		}
		switch (ItemConverter::distribution)
		{
		case DistConcentrated:
			for (int i = 0; i < itemsToConvertTo.size(); i++)
			{
				//Convert the spare value
				result[i].SetQuantity(result[i].GetQuantity() + (spareValue / itemsToConvertTo[i]->GetValue()));
				//set the remaining spare value to the remainder
				spareValue %= itemsToConvertTo[i]->GetValue();
				if (spareValue < minValue)
				{
					break;
				}
			}
			break;
		case DistEven:
			while (spareValue >= minValue)
			{
				// TODO - Compress range of values as spareValue shrinks past them to reduce excess runs of the loop
				// This will significantly improve performance with several large currencies, especially if sorted
				for (int i = 0; i < itemsToConvertTo.size(); i++)
				{
					if (itemsToConvertTo[i]->GetValue() <= spareValue)
					{
						result[i].SetQuantity(result[i].GetQuantity() + 1);
						//set the remaining spare vlaue to the remainder
						spareValue -= itemsToConvertTo[i]->GetValue();
					}
				}
			}
			break;
		case DistAlternating:
			while (spareValue >= minValue)
			{
				// TODO - Compress range of values as spareValue shrinks past them to reduce excess runs of the loop
				// This will significantly improve performance with several large currencies, especially if sorted
				double middle = (itemsToConvertTo.size() - 1) / 2.0;
				for (int i = 0; i <= middle; i++)
				{
					if (itemsToConvertTo[i]->GetValue() <= spareValue)
					{
						result[i].SetQuantity(result[i].GetQuantity() + 1);
						spareValue -= itemsToConvertTo[i]->GetValue();
					}

					int j = itemsToConvertTo.size() - 1 - i;
					if (itemsToConvertTo[j]->GetValue() <= spareValue)
					{
						result[j].SetQuantity(result[j].GetQuantity() + 1);
						spareValue -= itemsToConvertTo[j]->GetValue();
					}
				}
			}
			break;
		case DistRandom:
			while (spareValue >= minValue)
			{
				// TODO - Compress range of values as spareValue shrinks past them to reduce excess runs of the loop
				// This will significantly improve performance with several large currencies, especially if sorted
				long long index = RNG::GetNum(0, itemsToConvertTo.size() - 1);
				if (itemsToConvertTo[index]->GetValue() <= spareValue)
				{
					result[index].SetQuantity(result[index].GetQuantity() + 1);
					spareValue -= itemsToConvertTo[index]->GetValue();
				}
			}
			break;
		default:
			break;
		}
	}

	if (spareValue > 0 && roundUp)
	{
		result[minIndex].SetQuantity(result[minIndex].GetQuantity() + 1);
	}

	if (result.size() < 2)
	{
		return result;
	}

	for (int i = 0; i < numShuffles; i++)
	{
		switch (shuffle)
		{
		case ShuffleDown:
			for (int k = 0; k < result.size() - 1; k++)
			{
				ShuffleItemPair(result[k], result[k + 1]);
			}
			break;
		case ShuffleUp:
			for (unsigned long long k = result.size() - 1; k > 0; k--)
			{
				ShuffleItemPair(result[k], result[k - 1]);
			}
			break;
		case ShuffleUpDown:
			for (int k = 0; k < result.size(); k++)
			{
				if (k == 0)
				{
					ShuffleItemPair(result[k], result[k + 1]);
				}
				else if (k == result.size() - 1)
				{
					ShuffleItemPair(result[k], result[k - 1]);
				}
				else if (RNG::GetNum(0, 1) == 0)
				{
					ShuffleItemPair(result[k], result[k + 1]);
				}
				else
				{
					ShuffleItemPair(result[k], result[k - 1]);
				}
			}
			break;
		case ShuffleAlternator:
		{
			float middle = (result.size() - 1) / 2.0;
			for (int k = 0; k < middle; k++)
			{
				ShuffleItemPair(result[k], result[k + 1]);
				ShuffleItemPair(result[result.size() - 1 - k], result[result.size() - 2 - k]);
			}
			break;
		}
		case ShuffleRandom:
		{
			int firstIndex = RNG::GetNum(0, result.size() - 1);
			int secondIndex = RNG::GetNum(0, result.size() - 1);
			while (firstIndex == secondIndex || result[firstIndex].GetQuantity() == 0)
			{
				firstIndex = RNG::GetNum(0, result.size() - 1);
				secondIndex = RNG::GetNum(0, result.size() - 1);
			}

			ShuffleItemPair(result[firstIndex], result[secondIndex]);
			break; 
		}
		case NoShuffle:
		default:
			break;
		};
	}

	std::vector<Item> finalResult;
	for (int i = 0; i < result.size(); i++)
	{
		if (result[i].GetQuantity() != 0)
		{
			finalResult.push_back(result[i]);
		}
	}

	return finalResult;
}

void ItemConverter::ShuffleItemPair(Item& itemToShuffle, Item& itemToShuffleTo)
{
	if (itemToShuffle.GetQuantity() == 0)
	{
		return;
	}

	unsigned long valueToConvert = itemToShuffle.GetQuantity() * itemToShuffle.GetValue() * (RNG::GetNum(minShufflePercent * 1000, maxShufflePercent * 1000) / 100000.0);
	unsigned int quantityToConvert = valueToConvert / itemToShuffle.GetValue();
	if (roundUp && valueToConvert % itemToShuffle.GetValue() >= itemToShuffle.GetValue() / 2)
	{
		quantityToConvert++;
	}
	valueToConvert = quantityToConvert * itemToShuffle.GetValue();

	if (valueToConvert % itemToShuffleTo.GetValue() >= itemToShuffle.GetValue())
	{
		unsigned int quantityNotConverted = valueToConvert % itemToShuffleTo.GetValue() / itemToShuffle.GetValue();
		quantityToConvert -= quantityNotConverted;
		valueToConvert -= quantityNotConverted * itemToShuffle.GetValue();
	}

	if (quantityToConvert <= 0)
	{
		return;
	}

	unsigned int quantityToAdd = (quantityToConvert * itemToShuffle.GetValue()) / itemToShuffleTo.GetValue();

	if (roundUp && valueToConvert - quantityToAdd * itemToShuffleTo.GetValue() >= itemToShuffleTo.GetValue() / 2.0)
	{
		quantityToAdd++;
	}

	itemToShuffle.SetQuantity(itemToShuffle.GetQuantity() - quantityToConvert);
	itemToShuffleTo.SetQuantity(itemToShuffleTo.GetQuantity() + quantityToAdd);
}

void ItemConverter::SetMinShufflePercent(unsigned short minShuffle)
{
	if(minShuffle > 100)
	{
		minShufflePercent = 100;
	}
	else
	{
		minShufflePercent = minShuffle;
	}
}

void ItemConverter::SetMaxShufflePercent(unsigned short maxShuffle)
{
	if (maxShuffle > 100)
	{
		maxShufflePercent = 100;
	}
	else
	{
		maxShufflePercent = maxShuffle;
	}
}

void ItemConverter::SetNumShuffles(unsigned short numShuffles)
{
	ItemConverter::numShuffles = numShuffles;
}

void ItemConverter::SetRoundUp(bool roundUp)
{
	ItemConverter::roundUp = roundUp;
}

void ItemConverter::SetSortOrder(ItemConverterSort sortOrder)
{
	ItemConverter::sortOrder = sortOrder;
}

void ItemConverter::SetDistribution(ItemConverterDistribution distribution)
{
	ItemConverter::distribution = distribution;
}

void ItemConverter::SetShuffle(ItemConverterShuffle shuffle)
{
	ItemConverter::shuffle = shuffle;
}