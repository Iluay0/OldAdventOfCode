#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	size_t maxX = 0;
	currentPosition = { INT_MAX, INT_MAX };
	bool setPassword = false;
	for (auto& it : inputs)
	{
		if (it == "")
		{
			setPassword = true;
			continue;
		}

		if (setPassword)
		{
			password = it;
			continue;
		}

		std::vector<Tile> line;
		for (auto& it2 : it)
		{
			if (it2 == ' ')
				line.push_back(Tile::Empty);
			else if (it2 == '.')
			{
				if (currentPosition.first == INT_MAX)
				{
					currentPosition = { static_cast<int>(line.size()), static_cast<int>(board.size()) };
				}
				line.push_back(Tile::Walkable);
			}
			else if (it2 == '#')
				line.push_back(Tile::Wall);
		}
		if (line.size() > maxX)
			maxX = line.size();
		board.push_back(line);
	}

	for (auto& it : board)
		it.resize(maxX, Tile::Empty);
}

void Exercise::changeDirection(char direction)
{
	if (direction == 'L')
	{
		currentDirection = (Direction)((int)currentDirection - 1);
		if (currentDirection < Direction::Right)
			currentDirection = Direction::Top;
	}
	else if (direction == 'R')
	{
		currentDirection = (Direction)((int)currentDirection + 1);
		if (currentDirection > Direction::Top)
			currentDirection = Direction::Right;
	}
}

void Exercise::move(int amount)
{
	switch (currentDirection)
	{
		case Direction::Right:
		{
			while (amount > 0)
			{
				int x = currentPosition.first + 1;
				if (x >= board[currentPosition.second].size() || board[currentPosition.second][x] == Tile::Empty)
				{
					size_t newX = 0;
					while (board[currentPosition.second][newX] == Tile::Empty)
						newX++;
					if (board[currentPosition.second][newX] == Tile::Wall)
						return;
					currentPosition.first = static_cast<int>(newX);
				}
				else if (board[currentPosition.second][x] == Tile::Wall)
					return;
				else
					currentPosition.first = x;
				amount--;
			}
		} break;
		case Direction::Bottom:
		{
			while (amount > 0)
			{
				int y = currentPosition.second + 1;
				if (y >= board.size() || board[y][currentPosition.first] == Tile::Empty)
				{
					size_t newY = 0;
					while (board[newY][currentPosition.first] == Tile::Empty)
						newY++;
					if (board[newY][currentPosition.first] == Tile::Wall)
						return;
					currentPosition.second = static_cast<int>(newY);
				}
				else if (board[y][currentPosition.first] == Tile::Wall)
					return;
				else
					currentPosition.second = y;
				amount--;
			}
		} break;
		case Direction::Left:
		{
			while (amount > 0)
			{
				int x = currentPosition.first - 1;
				if (x < 0 || board[currentPosition.second][x] == Tile::Empty)
				{
					size_t newX = board[currentPosition.second].size() - 1;
					while (board[currentPosition.second][newX] == Tile::Empty)
						newX--;
					if (board[currentPosition.second][newX] == Tile::Wall)
						return;
					currentPosition.first = static_cast<int>(newX);
				}
				else if (board[currentPosition.second][x] == Tile::Wall)
					return;
				else
					currentPosition.first = x;
				amount--;
			}
		} break;
		case Direction::Top:
		{
			while (amount > 0)
			{
				int y = currentPosition.second - 1;
				if (y < 0 || board[y][currentPosition.first] == Tile::Empty)
				{
					size_t newY = board.size() - 1;
					while (board[newY][currentPosition.first] == Tile::Empty)
						newY--;
					if (board[newY][currentPosition.first] == Tile::Wall)
						return;
					currentPosition.second = static_cast<int>(newY);
				}
				else if (board[y][currentPosition.first] == Tile::Wall)
					return;
				else
					currentPosition.second = y;
				amount--;
			}
		} break;
	}
}

void Exercise::render()
{
	std::string render = "";
	for (int y = 0; y < board.size(); y++)
	{
		for (int x = 0; x < board[y].size(); x++)
		{
			if (currentPosition == std::make_pair(x, y))
			{
				render += "O";
			}
			else
			{
				switch (board[y][x])
				{
					case Tile::Walkable:
						render += ".";
						break;
					case Tile::Wall:
						render += "#";
						break;
					case Tile::Empty:
						render += " ";
						break;
				}
			}
		}
		render += "\n";
	}

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	std::cout << render;
	coord.Y = static_cast<short>(board.size() + 1);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);
	
	std::string builtNumber = "";
	for (auto& it : password)
	{
		if (it == 'R' || it == 'L')
		{
			move(stoi(builtNumber));
			builtNumber = "";
			changeDirection(it);
			continue;
		}
		builtNumber += it;
		render();
	}

	if (builtNumber != "")
		move(stoi(builtNumber));
	render();

	std::cout << (currentPosition.second + 1) * 1000 + (currentPosition.first + 1) * 4 + (int)currentDirection;
}

void Exercise::Part2(std::list<std::string> inputs)
{

}