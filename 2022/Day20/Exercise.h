#pragma once

struct Number
{
	int index;
	__int64 value;

	Number(int index, __int64 value)
	{
		this->index = index;
		this->value = value;
	}
};

class Exercise
{
	size_t circularGet(std::vector<Number>& l, __int64 amount, int offset = 1);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};