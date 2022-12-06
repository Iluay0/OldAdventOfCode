#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	int count = 0;
	std::list<char> currentChars;
	for (auto& it : inputs)
	{
		for (auto& it2 : it)
		{
			auto itChar = std::find(currentChars.begin(), currentChars.end(), it2);

			if (itChar != currentChars.end())
			{
				currentChars.erase(currentChars.begin(), itChar);
				currentChars.erase(itChar);
			}

			currentChars.push_back(it2);
			count++;
			
			if (currentChars.size() == 14)
				break;
		}
	}

	std::cout << count;
}