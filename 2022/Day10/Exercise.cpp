#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::Part1(std::list<std::string> inputs)
{
	std::vector<int> buffers;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " ");
		buffers.push_back(0);
		if (split[0] == "addx")
			buffers.push_back(stoi(split[1]));
	}

	int x = 1;
	int sum = 0;
	for (int i = 0; i < buffers.size(); i++)
	{
		if (i - 19 >= 0 && (i - 19) % 40 == 0)
			sum += (i + 1) * x;
		x += buffers[i];
	}
	std::cout << sum;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	std::vector<int> buffers;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " ");
		buffers.push_back(0);
		if (split[0] == "addx")
			buffers.push_back(stoi(split[1]));
	}

	int x = 1;
	for (int i = 0; i < buffers.size(); i++)
	{
		int pixel = i % 40;
		if (pixel - 1 <= x && pixel + 1 >= x)
			std::cout << "#";
		else
			std::cout << ".";

		x += buffers[i];
		if ((i + 1) % 40 == 0)
			std::cout << "\n";
	}
}