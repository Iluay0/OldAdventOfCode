#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	int score = 0;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, ' ');
		char opponent = split[0][0];
		char own = split[1][0];
		opponent += 'Z' - 'C';

		score += (own - 'X') + 1;
		if (own == opponent)
			score += 3;
		else if (opponent == own - 1 || opponent == own + 2)
			score += 6;
	}
	std::cout << "Final Score: " << score << "\n";
}