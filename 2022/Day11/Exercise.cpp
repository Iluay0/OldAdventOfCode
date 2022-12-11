#include "../../Utils/Utils.h"
#include "Exercise.h"

struct Operation
{
	char oper;
	__int64 number;

	Operation()
	{
		oper = '+';
		number = 0;
	}

	void parse(const std::string& line)
	{
		std::vector<std::string> words = Utils::split(line, " ");
		if (words.back() == "old")
			oper = '^';
		else
		{
			number = stoll(words.back());
			oper = (*std::prev(std::prev(words.end())))[0];
		}
	}

	__int64 calc(__int64 base)
	{
		if (oper == '^')
			return base * base;
		if (oper == '+')
			return base + number;
		if (oper == '*')
			return base * number;
		return base;
	}
};

struct Test
{
	__int64 divisor;
	int trueResult;
	int falseResult;

	Test()
	{
		divisor = 1;
		trueResult = -1;
		falseResult = -1;
	}

	void parse(const std::string& line)
	{
		std::vector<std::string> words = Utils::split(line, " ");
		if (line.find("Test:") != std::string::npos)
			divisor = stoi(words.back());
		else if (line.find("If true:") != std::string::npos)
			trueResult = stoi(words.back());
		else if (line.find("If false:") != std::string::npos)
			falseResult = stoi(words.back());
	}

	int getResult(__int64 worryLevel)
	{
		if (worryLevel % divisor == 0)
			return trueResult;
		return falseResult;
	}
};

struct Monkey
{
	int id;
	std::list<__int64> items;
	Operation operation;
	Test test;
	__int64 inspectionCount;

	Monkey(int monkeyId)
	{
		id = monkeyId;
		inspectionCount = 0;
	}

	void parse(const std::string& monkeyStr)
	{
		std::vector<std::string> lines = Utils::split(monkeyStr, "\n");
		for (auto& it : lines)
		{
			if (it.find("Starting items:") != std::string::npos)
				parseStartingItems(it);
			else if (it.find("Operation:") != std::string::npos)
				operation.parse(it);
			else if (it.find("Test:") != std::string::npos ||
				it.find("If true:") != std::string::npos ||
				it.find("If false:") != std::string::npos)
				test.parse(it);
		}
	}

	void parseStartingItems(const std::string& line)
	{
		std::stringstream ss;

		ss << line;

		std::string temp;
		int found;
		while (!ss.eof()) {

			ss >> temp;

			if (std::stringstream(temp) >> found)
				items.push_back(found);

			temp = "";
		}
	}
};

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