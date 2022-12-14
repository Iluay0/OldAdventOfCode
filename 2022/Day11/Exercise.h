#pragma once

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

class Exercise
{
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};