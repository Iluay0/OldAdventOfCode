#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	std::vector<int> occurences;
	std::vector<std::string> numbersCO2;
	std::vector<std::string> numbersOxygen;
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

		numbersCO2.push_back(it);
	}

	numbersOxygen = numbersCO2;

	std::string oxygenString = "";
	std::string co2String = "";
	int occurence = 0;
	for (auto& it : occurences)
	{
		if (numbersOxygen.size() > 1)
		{
			int count = 0;
			for (auto& it2 : numbersOxygen)
			{
				if (it2[occurence] >= '1')
					count++;
				else
					count--;
			}

			if (count >= 0)
				oxygenString += '1';
			else
				oxygenString += '0';

			numbersOxygen.erase(
				std::remove_if(
					numbersOxygen.begin(), numbersOxygen.end(),
					[&oxygenString](const std::string& numberString)
					{
						return numberString.rfind(oxygenString, 0) != 0;
					}
				), numbersOxygen.end()
			);
		}

		if (numbersCO2.size() > 1)
		{
			int count = 0;
			for (auto& it2 : numbersCO2)
			{
				if (it2[occurence] >= '1')
					count++;
				else
					count--;
			}

			if (count >= 0)
				co2String += '0';
			else
				co2String += '1';

			numbersCO2.erase(
				std::remove_if(
					numbersCO2.begin(), numbersCO2.end(),
					[&co2String](const std::string& numberString)
					{
						return numberString.rfind(co2String, 0) != 0;
					}
				), numbersCO2.end()
			);
		}

		occurence++;
	}

	int oxygen = Utils::binaryToInt(stoll(numbersOxygen.front()));
	int co2 = Utils::binaryToInt(stoll(numbersCO2.front()));

	std::cout << oxygen * co2 << "\n";
}