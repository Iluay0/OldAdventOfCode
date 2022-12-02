#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	int score = 0;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, ' ');
		char opponent = split[0][0];
		char choice = split[1][0];
		opponent += 'Z' - 'C';

		char own = opponent;
		if (choice == 'X')
		{
			own = opponent - 1;
			if (own < 'X')
				own += 3;
		}
		else if (choice == 'Z')
		{
			own = opponent + 1;
			if (own > 'Z')
				own -= 3;
		}

		score += (own - 'X') + 1;
		if (own == opponent)
			score += 3;
		else if (opponent == own - 1 || opponent == own + 2)
			score += 6;
	}
	std::cout << "Final Score: " << score << "\n";
}