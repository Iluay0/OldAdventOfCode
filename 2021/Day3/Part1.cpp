#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	int gamma = 0;
	int epsilon = 0;

	std::vector<int> occurences;
	for (auto& it : inputs)
	{
		int count = 0;
		for (auto& it2 : it)
		{
			while (occurences.size() <= count)
				occurences.push_back(0);

			if (it2 == '1')
				occurences[count]++;
			else
				occurences[count]--;

			count++;
		}
	}

	std::string gammaString = "";
	std::string epsilonString = "";
	for (auto& it : occurences)
	{
		if (it >= 0)
		{
			gammaString += "1";
			epsilonString += "0";
		}
		else
		{
			gammaString += "0";
			epsilonString += "1";
		}
	}

	gamma = Utils::binaryToInt(stoll(gammaString));
	epsilon = Utils::binaryToInt(stoll(epsilonString));

	std::cout << gamma * epsilon << "\n";
}