#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	int aim = 0;
	int horizontal = 0;
	int depth = 0;

	for (auto& it : inputs)
	{
		std::vector<std::string> split = Utils::split(it, ' ');

		if (split[0] == "forward")
		{
			horizontal += stoi(split[1]);
			depth += stoi(split[1]) * aim;
		}
		else if (split[0] == "down")
			aim += stoi(split[1]);
		else if (split[0] == "up")
			aim -= stoi(split[1]);
	}

	std::cout << horizontal * depth << "\n";
}