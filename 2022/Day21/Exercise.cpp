#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	std::regex rgx("(\\w+): (\\w+) (.) (\\w+)");
	std::regex rgx2("(\\w+): ([0-9]+)");
	std::smatch match;
	for (auto& it : inputs)
	{
		const std::string s = it;
		if (std::regex_search(s.begin(), s.end(), match, rgx))
		{
			Monkey monkey(match[1], match[2], match[4], match[3].str()[0]);
			monkeys.insert({ monkey.name, monkey });
		}
		else if (std::regex_search(s.begin(), s.end(), match, rgx2))
		{
			Monkey monkey(match[1], stoll(match[2]));
			monkeys.insert({ monkey.name, monkey });
		}
	}
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);

	while (monkeys["root"].value == INT64_MAX)
	{
		for (auto& it : monkeys)
		{
			if (it.second.value != INT64_MAX)
				continue;

			auto& firstMonkey = monkeys[it.second.firstMonkey];
			auto& secondMonkey = monkeys[it.second.secondMonkey];

			if (firstMonkey.value == INT64_MAX || secondMonkey.value == INT64_MAX)
				continue;

			it.second.setValue(firstMonkey.value, secondMonkey.value);
		}
	}
	std::cout << monkeys["root"].value;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	read(inputs);
	monkeys["humn"].value = INT64_MAX;
	monkeys["root"].oper = '=';

	while (monkeys["root"].value == INT64_MAX)
	{
		for (auto& it : monkeys)
		{
			if (it.second.value != INT64_MAX)
				continue;

			if (it.second.name == "humn")
				continue;

			auto& firstMonkey = monkeys[it.second.firstMonkey];
			auto& secondMonkey = monkeys[it.second.secondMonkey];

			if (it.second.oper != '=')
			{
				if (firstMonkey.value == INT64_MAX || secondMonkey.value == INT64_MAX)
					continue;
			}
			else
			{
				std::string missingMonkey = "";
				if (firstMonkey.value != INT64_MAX)
				{
					it.second.setValue(firstMonkey.value, INT64_MAX);
					secondMonkey.setValueReverse(it.second.value, firstMonkey.value, 2, it.second.oper);
					missingMonkey = secondMonkey.name;
				}
				else if (secondMonkey.value != INT64_MAX)
				{
					it.second.setValue(secondMonkey.value, INT64_MAX);
					firstMonkey.setValueReverse(it.second.value, secondMonkey.value, 1, it.second.oper);
					missingMonkey = firstMonkey.name;
				}

				if (missingMonkey != "")
				{
					while (monkeys["humn"].value == INT64_MAX)
					{
						for (auto& it2 : monkeys)
						{
							if (it2.second.name != missingMonkey)
								continue;

							auto& firstMonkey = monkeys[it2.second.firstMonkey];
							auto& secondMonkey = monkeys[it2.second.secondMonkey];

							if (firstMonkey.value == INT64_MAX)
							{
								firstMonkey.setValueReverse(it2.second.value, secondMonkey.value, 1, it2.second.oper);
								missingMonkey = firstMonkey.name;
							}
							else if (secondMonkey.value == INT64_MAX)
							{
								secondMonkey.setValueReverse(it2.second.value, firstMonkey.value, 2, it2.second.oper);
								missingMonkey = secondMonkey.name;
							}
						}
					}
				}
				continue;
			}

			it.second.setValue(firstMonkey.value, secondMonkey.value);
		}
	}
	std::cout << monkeys["humn"].value;
}