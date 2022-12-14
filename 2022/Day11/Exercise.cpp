#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::Part1(std::list<std::string> inputs)
{
	std::string input = Utils::join(inputs, '\n');
	std::vector<std::string> monkeysStr = Utils::split(input, "\n\n");

	std::map<int, Monkey> monkeys;
	for (auto& it : monkeysStr)
	{
		std::vector<std::string> lines = Utils::split(it, "\n");
		int id = -1;
		for (std::smatch m; std::regex_search(lines[0], m, std::regex("[^0-9]*([0-9]+).*")); lines[0] = m.suffix())
		{
			id = stoi(m[1]);
		}
		
		Monkey monkey = Monkey(id);
		monkey.parse(it);
		monkeys.insert({ id, monkey });
	}

	for (int i = 1; i <= 20; i++)
	{
		for (auto& it : monkeys)
		{
			for (auto& it2 : it.second.items)
			{
				it2 = it.second.operation.calc(it2);
				it2 /= 3;
				int index = it.second.test.getResult(it2);
				auto itMap = monkeys.find(index);
				if (itMap != monkeys.end())
					itMap->second.items.push_back(it2);
				it.second.inspectionCount++;
			}
			it.second.items.clear();
		}
	}

	std::vector<__int64> inspectionCounts;
	for (auto& it : monkeys)
	{
		inspectionCounts.push_back(it.second.inspectionCount);
	}

	std::sort(inspectionCounts.begin(), inspectionCounts.end(), std::greater<>());
	std::cout << inspectionCounts[0] << " * " << inspectionCounts[1] << " = " << inspectionCounts[0] * inspectionCounts[1];
}

void Exercise::Part2(std::list<std::string> inputs)
{
	std::string input = Utils::join(inputs, '\n');
	std::vector<std::string> monkeysStr = Utils::split(input, "\n\n");

	std::map<int, Monkey> monkeys;
	for (auto& it : monkeysStr)
	{
		std::vector<std::string> lines = Utils::split(it, "\n");
		int id = -1;
		for (std::smatch m; std::regex_search(lines[0], m, std::regex("[^0-9]*([0-9]+).*")); lines[0] = m.suffix())
		{
			id = stoi(m[1]);
		}

		Monkey monkey = Monkey(id);
		monkey.parse(it);
		monkeys.insert({ id, monkey });
	}

	__int64 commonDivisor = 1;
	for (auto& it : monkeys)
	{
		commonDivisor *= it.second.test.divisor;
	}
	for (int i = 1; i <= 10000; i++)
	{
		for (auto& it : monkeys)
		{
			for (auto& it2 : it.second.items)
			{
				it2 = it.second.operation.calc(it2);
				it2 %= commonDivisor;
				int index = it.second.test.getResult(it2);
				auto itMap = monkeys.find(index);
				if (itMap != monkeys.end())
					itMap->second.items.push_back(it2);
				it.second.inspectionCount++;
			}
			it.second.items.clear();
		}
	}

	std::vector<__int64> inspectionCounts;
	for (auto& it : monkeys)
	{
		inspectionCounts.push_back(it.second.inspectionCount);
	}

	std::sort(inspectionCounts.begin(), inspectionCounts.end(), std::greater<>());
	std::cout << inspectionCounts[0] << " * " << inspectionCounts[1] << " = " << inspectionCounts[0] * inspectionCounts[1];
}