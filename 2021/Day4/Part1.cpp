#include "../../Utils/Utils.h"
#include "Part1.h"

struct BingoNumber
{
	int value;
	bool checked;

	BingoNumber()
	{
		value = -1;
		checked = false;
	}
};

struct BingoBoard
{
	std::vector<std::vector<BingoNumber>> lines;

	void callNumber(int number)
	{
		for (auto& it : lines)
		{
			for (auto& it2 : it)
			{
				if (it2.value == number)
					it2.checked = true;
			}
		}
	}

	bool hasRowChecked()
	{
		for (auto& it : lines)
		{
			bool complete = true;
			for (auto& it2 : it)
			{
				if (!it2.checked)
				{
					complete = false;
					break;
				}
			}

			if (complete)
				return true;
		}

		return false;
	}

	bool hasColumnChecked()
	{
		std::vector<bool> columns;

		for (auto& it : lines)
		{
			int count = 0;
			for (auto& it2 : it)
			{
				if (columns.size() <= count)
					columns.push_back(it2.checked);

				columns[count] = columns[count] && it2.checked;

				count++;
			}
		}

		for (auto it : columns)
		{
			if (it)
				return true;
		}

		return false;
	}

	bool hasDiagonalChecked()
	{
		bool complete = true;

		for (int i = 0; i < 5; i++)
		{
			if (!lines[i][i].checked)
			{
				complete = false;
				break;
			}
		}

		if (complete)
			return true;

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i + j != 4)
					continue;

				if (!lines[i][j].checked)
				{
					complete = false;
					break;
				}
			}
		}

		return complete;
	}

	int getUncheckedNumbers()
	{
		int sum = 0;
		for (auto& it : lines)
		{
			for (auto& it2 : it)
			{
				if (!it2.checked)
					sum += it2.value;
			}
		}

		return sum;
	}
};

void Part1::Run(std::list<std::string> inputs)
{
	std::string strPulledNumbers = inputs.front();
	inputs.pop_front();

	std::list<BingoBoard*> boards;
	BingoBoard* pBoard = new BingoBoard;;
	for (auto& it : inputs)
	{
		if (it == "")
		{
			pBoard = new BingoBoard;
			boards.push_back(pBoard);
			continue;
		}

		std::vector<BingoNumber> vecNumbers;
		auto strings = Utils::split(it, ' ');
		for (auto& it2 : strings)
		{
			if (it2 == "")
				continue;

			BingoNumber number;
			number.checked = false;
			number.value = stoi(it2);
			vecNumbers.push_back(number);
		}
		pBoard->lines.push_back(vecNumbers);
	}

	std::vector<std::string> pulledNumbers = Utils::split(strPulledNumbers, ',');
	for (auto& it : pulledNumbers)
	{
		bool finished = false;

		int number = stoi(it);

		for (auto& it2 : boards)
		{
			it2->callNumber(number);
		}

		for (auto& it2 : boards)
		{
			if (it2->hasRowChecked() || it2->hasColumnChecked() || it2->hasDiagonalChecked())
			{
				finished = true;
				std::cout << "line checked, number was " << number << "\n";
				int remainingNumbers = it2->getUncheckedNumbers();
				std::cout << "unchecked numbers sum: " << remainingNumbers << "\n";

				std::cout << "result: " << number * remainingNumbers << "\n";

				break;
			}
		}

		if (finished)
			break;
	}
}