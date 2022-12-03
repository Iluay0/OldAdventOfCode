#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	int sum = 0;
	for (auto& it : inputs)
	{
		std::string firstHalf = it.substr(0, it.length() / 2);
		std::string secondHalf = it.substr(it.length() / 2);

		std::set<char> charsInBothCompartiments;
		for (auto& itemFirstHalf : firstHalf)
		{
			for (auto& itemSecondHalf : secondHalf)
			{
				if (itemFirstHalf == itemSecondHalf)
					charsInBothCompartiments.insert(itemFirstHalf);
			}
		}

		for (auto& it2 : charsInBothCompartiments)
		{
			if (it2 >= 'A' && it2 <= 'Z')
				sum += (it2 - 'A') + 27;
			else if (it2 >= 'a' && it2 <= 'z')
				sum += (it2 - 'a') + 1;
		}
	}

	std::cout << sum;
}