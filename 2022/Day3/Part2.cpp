#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	int sum = 0;
	std::vector<char> chars;
	int i = 0;
	while(true)
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