#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::Part1(std::list<std::string> inputs)
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

void Exercise::Part2(std::list<std::string> inputs)
{
	int sum = 0;
	std::vector<char> chars;
	int i = 0;
	while (true)
	{
		auto it = inputs.begin();
		std::advance(it, i);

		if (i % 3 == 0)
		{
			if (i != 0)
			{
				if (chars[0] >= 'A' && chars[0] <= 'Z')
					sum += (chars[0] - 'A') + 27;
				else if (chars[0] >= 'a' && chars[0] <= 'z')
					sum += (chars[0] - 'a') + 1;
			}

			if (i >= inputs.size())
				break;

			chars.clear();

			for (auto& it2 : *it)
				chars.push_back(it2);
		}
		else
		{
			if (i >= inputs.size())
				break;

			std::vector<char> charsLeft;
			for (auto& it2 : *it)
			{
				auto itChar = std::find(chars.begin(), chars.end(), it2);
				if (itChar != chars.end())
					charsLeft.push_back(*itChar);
			}

			chars = charsLeft;
		}
		i++;
	}

	std::cout << sum;
}