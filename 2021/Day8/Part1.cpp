#include "../../Utils/Utils.h"
#include "Part1.h"

struct Number
{
	int value;
	int amount;
	std::string structure;
	int structureSize;

	Number()
	{
		value = -1;
		amount = 0;
		structure = "";
	}

	Number(int v, int s)
	{
		value = v;
		amount = 0;
		structureSize = s;
		structure = "";
	}
};

void Part1::Run(std::list<std::string> inputs)
{
	std::list<Number> numbers = {
		Number(0, 6),
		Number(1, 2),
		Number(2, 5),
		Number(3, 5),
		Number(4, 4),
		Number(5, 5),
		Number(6, 6),
		Number(7, 3),
		Number(8, 7),
		Number(9, 6)
	};

	for (auto& it : inputs)
	{
		auto split = Utils::split(it, ' ');
		bool bInput = true;
		for (auto& it2 : split)
		{
			if (it2 == "|")
			{
				bInput = false;
				continue;
			}

			if (bInput)
				continue;

			std::for_each(numbers.begin(), numbers.end(),
				[&it2](Number& number)
				{
					if (number.structureSize == it2.size())
						number.amount++;
				});
		}
	}

	int total = 0;
	for (auto& it : numbers)
	{
		if (it.value == 1 || it.value == 4 || it.value == 7 || it.value == 8)
			total += it.amount;
	}

	std::cout << "Total: " << total;
}