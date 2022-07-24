#ifndef ItemConverter_H
#define ItemConverter_H

#include <vector>
#include "../Item.h"

enum ItemConverterSort
{
	//sort from highest value to lowest value
	SortDescending,
	//sort from lowest value to highest value
	SortAscending,
	//randomly mix up list
	SortRandom,
	//Don't sort the input lists
	NoSort,
};

enum ItemConverterDistribution
{
	//Convert as much as possible to the first item, repeat for the next items
	DistConcentrated,
	//Convert once to each item before repeating
	DistEven,
	//Convert once to each item in pairs first,last moving to the middle
	DistAlternating,
	//Convert at random
	DistRandom,
};

enum ItemConverterShuffle
{
	//Shuffle performed from first item to last item
	ShuffleDown,
	//Shuffle performed from last item to first item
	ShuffleUp,
	//Shuffle up or down at random
	ShuffleUpDown,
	//Shuffle in pairs moving from first and last towards the middle
	ShuffleAlternator,
	//Shuffle at random
	ShuffleRandom,
	//Don't shuffle items
	NoShuffle,
};

class ItemConverter {
public:
	static std::vector<Item> ConvertItems(std::vector<Item*> itemsToConvert, std::vector<Item*> itemsToConvertTo);

	static void SetMinShufflePercent(unsigned short minShuffle);
	static void SetMaxShufflePercent(unsigned short maxShuffle);
	static void SetNumShuffles(unsigned short numShuffles);
	static void SetRoundUp(bool roundUp);
	static void SetSortOrder(ItemConverterSort sortOrder);
	static void SetDistribution(ItemConverterDistribution distributon);
	static void SetShuffle(ItemConverterShuffle shuffle);
private:
	static void ShuffleItemPair(Item& itemToShuffle, Item& itemToShuffleTo);

	static unsigned short minShufflePercent;
	static unsigned short maxShufflePercent;
	static unsigned short numShuffles;
	static bool roundUp;
	static ItemConverterSort sortOrder;
	static ItemConverterDistribution distribution;
	static ItemConverterShuffle shuffle;
};



#endif // !ItemConverter_H
