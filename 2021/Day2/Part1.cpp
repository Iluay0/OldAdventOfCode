#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	int horizontal = 0;
	int depth = 0;

	for (auto& it : inputs)
	{
		std::vector<std::string> split = Utils::split(it, ' ');

		if (split[0] == "forward")
			horizontal += stoi(split[1]);
		else if (split[0] == "down")
			depth += stoi(split[1]);
		else if (split[0] == "up")
			depth -= stoi(split[1]);
	}

	std::cout << horizontal * depth << "\n";
}