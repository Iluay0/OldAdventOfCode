#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	auto input = Utils::join(inputs, '\n');
	std::string delimiter = "\n\n";

	auto stacksStr = input.substr(0, input.find(delimiter));
	input.erase(0, input.find(delimiter) + delimiter.length());
	auto moves = Utils::split(input, "\n");

	std::map<int, std::list<char>> mapStacks;
	auto stacks = Utils::split(stacksStr, "\n");
	stacks.pop_back();

	for (auto& it : stacks)
	{
		int count = 1;
		int stackNumber = 0;
		for (auto& it2 : it)
		{
			if (count == 2)
			{
				stackNumber++;
				if (it2 != ' ')
					mapStacks[stackNumber].push_back(it2);
			}
			count++;

			if (count == 4)
				count = 0;
		}
	}

	for (auto& it : moves)
	{
		if (it == "")
			continue;

		auto split = Utils::split(it, " ");
		int amount = stoi(split[1]);
		int from = stoi(split[3]);
		int to = stoi(split[5]);

		std::list<char> blocks;
		for (int i = 1; i <= amount; i++)
		{
			blocks.push_front(mapStacks[from].front());
			mapStacks[from].pop_front();
		}
		for (auto& it2 : blocks)
			mapStacks[to].push_front(it2);
	}

	std::string result = "";
	for (auto& it : mapStacks)
		result += it.second.front();
	std::cout << result;
}