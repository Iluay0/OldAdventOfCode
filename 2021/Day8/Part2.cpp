#include "../../Utils/Utils.h"
#include "Part2.h"

struct NumberP2
{
	int value;
	int structureSize;
	std::vector<std::string> structures;

	NumberP2()
	{
		value = -1;
	}

	NumberP2(int v, int s)
	{
		value = v;
		structureSize = s;
	}
};

NumberP2* GetNumber(std::vector<NumberP2>& numbers, int value)
{
	auto it = std::find_if(numbers.begin(), numbers.end(),
		[&value](const NumberP2& number)
		{
			return number.value == value;
		});

	if (it != numbers.end())
		return &*it;

	return nullptr;
}

void FixNumbers(std::vector<NumberP2>& numbers)
{
	for (auto& it : numbers)
	{
		switch (it.value)
		{
			case 0:
			{
				NumberP2* pNumberFour = GetNumber(numbers, 4);
				if (!pNumberFour)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					int compare = 0;
					for (auto& it3 : pNumberFour->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found != std::string::npos)
						{
							compare++;
						}
					}

					if (compare == 4)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}
				
				NumberP2* pNumberOne = GetNumber(numbers, 1);
				if (!pNumberOne)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					bool remove = false;
					for (auto& it3 : pNumberOne->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found == std::string::npos)
						{
							remove = true;
							break;
						}
					}

					if (remove)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}

			} break;
			case 3:
			{
				NumberP2* pNumberSeven = GetNumber(numbers, 7);
				if (!pNumberSeven)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					bool remove = false;
					for (auto& it3 : pNumberSeven->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found == std::string::npos)
						{
							remove = true;
							break;
						}
					}

					if (remove)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}

			} break;
			case 5:
			{
				NumberP2* pNumberFour = GetNumber(numbers, 4);
				if (!pNumberFour)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					int compare = 0;
					for (auto& it3 : pNumberFour->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found != std::string::npos)
						{
							compare++;
						}
					}

					if (compare != 3)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}

			} break;
			case 6:
			{
				NumberP2* pNumberFour = GetNumber(numbers, 4);
				if (!pNumberFour)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					int compare = 0;
					for (auto& it3 : pNumberFour->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found != std::string::npos)
						{
							compare++;
						}
					}

					if (compare == 4)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}

				NumberP2* pNumberFive = GetNumber(numbers, 5);
				if (!pNumberFive)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					bool remove = false;
					for (auto& it3 : pNumberFive->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found == std::string::npos)
						{
							remove = true;
							break;
						}
					}

					if (remove)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}

			} break;
			case 9:
			{
				NumberP2* pNumberFive = GetNumber(numbers, 5);
				if (!pNumberFive)
					throw;

				for (auto it2 = it.structures.begin(); it2 != it.structures.end() /* !!! */;)
				{
					bool remove = false;
					for (auto& it3 : pNumberFive->structures[0])
					{
						std::size_t found = (*it2).rfind(it3);
						if (found == std::string::npos)
						{
							remove = true;
							break;
						}
					}

					if (remove)
					{
						it2 = it.structures.erase(it2);
					}
					else
						it2++;
				}

			} break;
		}

		if (it.structures.size() == 1)
		{
			for (auto& it3 : numbers)
			{
				if (it3.value != it.value && it3.structureSize == it.structures[0].size())
				{
					it3.structures.erase(
						std::remove_if(
							it3.structures.begin(), it3.structures.end(),
							[&it](const std::string& structure)
							{
								return it.structures[0] == structure;
							}
						), it3.structures.end()
					);
				}
			}
		}
	}
}

void Part2::Run(std::list<std::string> inputs)
{
	std::list<int> outputs;

	for (auto& it : inputs)
	{
		std::vector<NumberP2> numbers = {
			NumberP2(0, 6),
			NumberP2(1, 2),
			NumberP2(2, 5),
			NumberP2(3, 5),
			NumberP2(4, 4),
			NumberP2(5, 5),
			NumberP2(6, 6),
			NumberP2(7, 3),
			NumberP2(8, 7),
			NumberP2(9, 6)
		};

		auto split = Utils::split(it, ' ');
		bool bInput = true;
		std::string number = "";
		for (auto& it2 : split)
		{
			if (it2 == "|")
			{
				bInput = false;

				FixNumbers(numbers);
				continue;
			}

			if (bInput)
			{
				std::for_each(numbers.begin(), numbers.end(),
					[&it2](NumberP2& number)
					{
						if (number.structureSize == it2.size())
							number.structures.push_back(it2);
					});
			}
			else
			{
				auto itNumber = std::find_if(numbers.begin(), numbers.end(),
					[&it2](NumberP2& numberP2)
					{
						if (numberP2.structures.size() != 1)
							throw;

						if (numberP2.structures[0].size() != it2.size())
							return false;

						return Utils::isShuffledSubstring(numberP2.structures[0], it2);
					});

				if (itNumber != numbers.end())
					number += std::to_string(itNumber->value);
			}
		}

		outputs.push_back(stoi(number));
		number = "";
	}

	int total = 0;
	for (auto& it : outputs)
	{
		total += it;
		std::cout << "Number: " << it << "\n";
	}

	std::cout << "Total: " << total << "\n";
}