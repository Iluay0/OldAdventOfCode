#pragma once

struct Pair
{
	int begin;
	int end;

	void SetValues(const std::string& input)
	{
		auto values = Utils::split(input, ("-"));
		begin = stoi(values[0]);
		end = stoi(values[1]);
	}

	bool IsContainedBy(const Pair& pair)
	{
		if (pair.begin <= begin && pair.end >= end)
			return true;
		return false;
	}

	bool IsOverlappingWith(const Pair& pair)
	{
		if (pair.begin <= end && pair.end >= begin)
			return true;
		return false;
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