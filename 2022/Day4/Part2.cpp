#include "../../Utils/Utils.h"
#include "Part2.h"

struct Pair
{
	int begin;
	int end;

	void SetValues(const std::string& input)
	{
		auto values = Utils::split(input, ('-'));
		begin = stoi(values[0]);
		end = stoi(values[1]);
	}

	bool IsOverlappingWith(const Pair& pair)
	{
		if (pair.begin <= end && pair.end >= begin)
			return true;
		return false;
	}
};

void Part2::Run(std::list<std::string> inputs)
{
	int amount = 0;
	for (auto& it : inputs)
	{
		auto pairs = Utils::split(it, (','));
		Pair pairOne;
		pairOne.SetValues(pairs[0]);
		Pair pairTwo;
		pairTwo.SetValues(pairs[1]);

		if (pairOne.IsOverlappingWith(pairTwo))
			amount++;
	}
	std::cout << amount;
}