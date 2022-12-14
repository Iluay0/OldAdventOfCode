#include "../../Utils/Utils.h"
#include "Exercise.h"

enum BlockType
{
	Rock = 0,
	Sand
};

struct Block
{
	BlockType blockType;
	uint16_t x;
	uint16_t y;

	Block(uint16_t xx, uint16_t yy, BlockType type)
	{
		x = xx;
		y = yy;
		blockType = type;
	}
};

void render(const std::vector<Block>& blocks, const std::pair<uint16_t, uint16_t>& minMaxX, const std::pair<uint16_t, uint16_t>& minMaxY, Block* pCurrentBlock)
{
	std::string render = "";
	for (uint16_t y = minMaxY.first; y <= minMaxY.second + 2; y++)
	{
		for (uint16_t x = minMaxX.first; x <= minMaxX.second; x++)
		{
			if (x == pCurrentBlock->x && y == pCurrentBlock->y)
			{
				render += "\x1b[31mo\x1b[0m";
				continue;
			}
			if (y == minMaxY.second + 2)
			{
				render += "\x1b[35m#\x1b[0m";
				continue;
			}
			auto it = std::find_if(blocks.begin(), blocks.end(),
				[&x, &y](const Block& block) {
					return block.x == x && block.y == y;
				});

			std::string shape = ".";
			if (it != blocks.end())
			{
				switch (it->blockType)
				{
					case BlockType::Rock:
						shape = "\x1b[35m#\x1b[0m";
						break;
					case BlockType::Sand:
						shape = "\x1b[33mo\x1b[0m";
						break;
				}
			}

			render += shape;
		}
		render += "\n";
	}

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	std::cout << render;
}

void read(const std::list<std::string>& inputs, std::vector<Block>& blocks, std::pair<uint16_t, uint16_t>& minMaxX, std::pair<uint16_t, uint16_t>& minMaxY)
{
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " -> ");
		bool firstIter = true;
		for (auto& it2 : split)
		{
			auto blockPos = Utils::split(it2, ",");
			Block block(stoi(blockPos[0]), stoi(blockPos[1]), BlockType::Rock);

			if (!firstIter)
			{
				Block* prevBlock = &blocks.back();
				if (prevBlock->x + 1 < block.x)
				{
					for (uint16_t x = prevBlock->x + 1; x < block.x; x++)
					{
						Block newBlock(x, stoi(blockPos[1]), BlockType::Rock);
						blocks.push_back(newBlock);
					}
				}
				else if (prevBlock->x - 1 > block.x)
				{
					for (uint16_t x = prevBlock->x - 1; x > block.x; x--)
					{
						Block newBlock(x, stoi(blockPos[1]), BlockType::Rock);
						blocks.push_back(newBlock);
					}
				}
				else if (prevBlock->y + 1 < block.y)
				{
					for (uint16_t y = prevBlock->y + 1; y < block.y; y++)
					{
						Block newBlock(stoi(blockPos[0]), y, BlockType::Rock);
						blocks.push_back(newBlock);
					}
				}
				else if (prevBlock->y - 1 > block.y)
				{
					for (uint16_t y = prevBlock->y - 1; y > block.y; y--)
					{
						Block newBlock(stoi(blockPos[0]), y, BlockType::Rock);
						blocks.push_back(newBlock);
					}
				}
			}

			blocks.push_back(block);

			if (block.x < minMaxX.first)
				minMaxX.first = block.x;
			else if (block.x > minMaxX.second)
				minMaxX.second = block.x;

			if (block.y < minMaxY.first)
				minMaxY.first = block.y;
			else if (block.y > minMaxY.second)
				minMaxY.second = block.y;

			firstIter = false;
		}
	}

	minMaxX.first--;
	minMaxX.second++;
}

void Exercise::Part1(std::list<std::string> inputs)
{
	std::vector<Block> blocks;
	std::pair<uint16_t, uint16_t> minMaxX = { 500, 500 };
	std::pair<uint16_t, uint16_t> minMaxY = { 0, 0 };
	read(inputs, blocks, minMaxX, minMaxY);

	Block sandBlock(500, 0, BlockType::Sand);
	while (true)
	{
		auto it = std::find_if(blocks.begin(), blocks.end(),
			[&sandBlock](const Block& block) {
				return sandBlock.x == block.x && sandBlock.y + 1 == block.y;
			});

		if (it == blocks.end())
			sandBlock.y++;
		else
		{
			auto it = std::find_if(blocks.begin(), blocks.end(),
				[&sandBlock](const Block& block) {
					return sandBlock.x - 1 == block.x && sandBlock.y + 1 == block.y;
				});

			if (it == blocks.end())
			{
				sandBlock.x--;
				sandBlock.y++;
			}
			else
			{
				auto it = std::find_if(blocks.begin(), blocks.end(),
					[&sandBlock](const Block& block) {
						return sandBlock.x + 1 == block.x && sandBlock.y + 1 == block.y;
					});

				if (it == blocks.end())
				{
					sandBlock.x++;
					sandBlock.y++;
				}
				else
				{
					blocks.push_back(sandBlock);
					sandBlock = Block(500, 0, BlockType::Sand);
				}
			}
		}

		if (sandBlock.y > minMaxY.second + 1)
			break;
		render(blocks, minMaxX, minMaxY, &sandBlock);
	}
	render(blocks, minMaxX, minMaxY, &sandBlock);

	std::cout << "Sand blocks resting: " << std::count_if(blocks.begin(), blocks.end(),
		[](const Block& block) {
			return block.blockType == BlockType::Sand;
		}) << std::endl;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	std::vector<Block> blocks;
	std::pair<uint16_t, uint16_t> minMaxX = { 500, 500 };
	std::pair<uint16_t, uint16_t> minMaxY = { 0, 0 };
	read(inputs, blocks, minMaxX, minMaxY);

	Block sandBlock(500, 0, BlockType::Sand);
	while (true)
	{
		if (sandBlock.y == minMaxY.second + 1)
		{
			blocks.push_back(sandBlock);
			sandBlock = Block(500, 0, BlockType::Sand);
			continue;
		}

		auto it = std::find_if(blocks.begin(), blocks.end(),
			[&sandBlock](const Block& block) {
				return sandBlock.x == block.x && sandBlock.y + 1 == block.y;
			});

		if (it == blocks.end())
			sandBlock.y++;
		else
		{
			auto it = std::find_if(blocks.begin(), blocks.end(),
				[&sandBlock](const Block& block) {
					return sandBlock.x - 1 == block.x && sandBlock.y + 1 == block.y;
				});

			if (it == blocks.end())
			{
				sandBlock.x--;
				sandBlock.y++;
			}
			else
			{
				auto it = std::find_if(blocks.begin(), blocks.end(),
					[&sandBlock](const Block& block) {
						return sandBlock.x + 1 == block.x && sandBlock.y + 1 == block.y;
					});

				if (it == blocks.end())
				{
					sandBlock.x++;
					sandBlock.y++;
				}
				else
				{
					if (sandBlock.x == 500 && sandBlock.y == 0)
					{
						blocks.push_back(sandBlock);
						break;
					}

					if (sandBlock.x < minMaxX.first)
						minMaxX.first = sandBlock.x;
					else if (sandBlock.x > minMaxX.second)
						minMaxX.second = sandBlock.x;

					blocks.push_back(sandBlock);
					sandBlock = Block(500, 0, BlockType::Sand);
					continue;
				}
			}
		}
		render(blocks, minMaxX, minMaxY, &sandBlock);
	}
	render(blocks, minMaxX, minMaxY, &sandBlock);

	std::cout << "Sand blocks resting: " << std::count_if(blocks.begin(), blocks.end(),
		[](const Block& block) {
			return block.blockType == BlockType::Sand;
		}) << std::endl;
}