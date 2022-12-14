#include "../../Utils/Utils.h"
#include "Exercise.h"

// #define __RENDER

void Exercise::renderBg()
{
	std::string render = "";
	for (uint16_t y = minMaxY.first; y <= minMaxY.second + 2; y++)
	{
		for (uint16_t x = minMaxX.first; x <= minMaxX.second; x++)
		{
			if (y == minMaxY.second + 2)
			{
				render += "\x1b[35m#\x1b[0m";
				continue;
			}
			auto it = std::find_if(blocks.begin(), blocks.end(),
				[&x, &y](const Block& block) {
					return block.x == x && block.y == y;
				});

			std::string shape = " ";
			if (it != blocks.end())
			{
				switch (it->blockType)
				{
					case BlockType::Rock:
						shape = "\x1b[35m#\x1b[0m";
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
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Exercise::renderSand()
{
	for (auto& it : blocks)
	{
		if (it.blockType != BlockType::Sand)
			continue;

		COORD coord;
		coord.X = it.x - minMaxX.first;
		coord.Y = it.y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		std::cout << "\x1b[33mo\x1b[0m";
	}
}

void Exercise::renderCurrentBlock(Block* pCurrentBlock, bool eraseBlock)
{
	COORD coord;
	coord.X = pCurrentBlock->x - minMaxX.first;
	coord.Y = pCurrentBlock->y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (eraseBlock)
		std::cout << " ";
	else
		std::cout << "\x1b[31mo\x1b[0m";
}

void Exercise::read(const std::list<std::string>& inputs)
{
	minMaxX = { 500, 500 };
	minMaxY = { 0, 0 };
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

Block Exercise::getNextBlockBelow(Block& sandBlock)
{
	std::vector<Block> matches;
	std::remove_copy_if(blocks.begin(), blocks.end(),
		std::back_inserter(matches), [&sandBlock](const Block& block) {
			return block.x != sandBlock.x;
		});

	Block nextBlock = sandBlock;
	for (auto& it : matches)
	{
		if (it.y > sandBlock.y && (nextBlock.y == sandBlock.y || it.y < nextBlock.y))
			nextBlock = it;
	}
	return nextBlock;
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);

#ifdef __RENDER
	Utils::SetFontSize(6);
	renderBg();
#endif
	Block sandBlock(500, 0, BlockType::Sand);
	while (true)
	{
		Block nextBlock = getNextBlockBelow(sandBlock);
#ifdef __RENDER
		renderCurrentBlock(&sandBlock, true);
#endif

		if (sandBlock.y + 1 < nextBlock.y)
			sandBlock.setPos(sandBlock.x, nextBlock.y - 1);
		else
		{
			auto it = std::find_if(blocks.begin(), blocks.end(),
				[&sandBlock](const Block& block) {
					return sandBlock.x - 1 == block.x && sandBlock.y + 1 == block.y;
				});

			if (it == blocks.end())
				sandBlock.setPos(sandBlock.x - 1, sandBlock.y + 1);
			else
			{
				auto it = std::find_if(blocks.begin(), blocks.end(),
					[&sandBlock](const Block& block) {
						return sandBlock.x + 1 == block.x && sandBlock.y + 1 == block.y;
					});

				if (it == blocks.end())
					sandBlock.setPos(sandBlock.x + 1, sandBlock.y + 1);
				else
				{
					blocks.push_back(sandBlock);
#ifdef __RENDER
					renderSand();
#endif
					sandBlock = Block(sandBlock.lastX, sandBlock.lastY, BlockType::Sand);
				}
			}
		}

		if (sandBlock.y > minMaxY.second + 1)
			break;
#ifdef __RENDER
		renderCurrentBlock(&sandBlock);
#endif
	}
#ifdef __RENDER
	renderSand();
	renderCurrentBlock(&sandBlock);
#endif

	std::cout << "Sand blocks resting: " << std::count_if(blocks.begin(), blocks.end(),
		[](const Block& block) {
			return block.blockType == BlockType::Sand;
		}) << std::endl;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	read(inputs);

#ifdef __RENDER
	Utils::SetFontSize(6);
	renderBg();
#endif
	Block sandBlock(500, 0, BlockType::Sand);
	while (true)
	{
		Block nextBlock = getNextBlockBelow(sandBlock);
#ifdef __RENDER
		renderCurrentBlock(&sandBlock, true);
#endif

		if (sandBlock.y + 1 < nextBlock.y)
			sandBlock.setPos(sandBlock.x, nextBlock.y + 1);
		else
		{
			auto it = std::find_if(blocks.begin(), blocks.end(),
				[&sandBlock](const Block& block) {
					return sandBlock.x - 1 == block.x && sandBlock.y + 1 == block.y;
				});

			if (it == blocks.end())
				sandBlock.setPos(sandBlock.x - 1, sandBlock.y + 1);
			else
			{
				auto it = std::find_if(blocks.begin(), blocks.end(),
					[&sandBlock](const Block& block) {
						return sandBlock.x + 1 == block.x && sandBlock.y + 1 == block.y;
					});

				if (it == blocks.end())
					sandBlock.setPos(sandBlock.x + 1, sandBlock.y + 1);
				else
				{
					if (sandBlock.x == 500 && sandBlock.y == 0)
					{
						blocks.push_back(sandBlock);
						break;
					}

					if (sandBlock.x < minMaxX.first)
					{
#ifdef __RENDER
						renderBg();
#endif
						minMaxX.first = sandBlock.x;
					}
					else if (sandBlock.x > minMaxX.second)
					{
#ifdef __RENDER
						renderBg();
#endif
						minMaxX.second = sandBlock.x;
					}

#ifdef __RENDER
					renderSand();
#endif
					blocks.push_back(sandBlock);
					sandBlock = Block(sandBlock.lastX, sandBlock.lastY, BlockType::Sand);
					continue;
				}
			}
		}
#ifdef __RENDER
		renderCurrentBlock(&sandBlock);
#endif
		if (sandBlock.y == minMaxY.second + 1)
		{
			blocks.push_back(sandBlock);
			sandBlock = Block(sandBlock.lastX, sandBlock.lastY, BlockType::Sand);
		}
	}
#ifdef __RENDER
	renderBg();
	renderSand();
	renderCurrentBlock(&sandBlock);
#endif

	std::cout << "Sand blocks resting: " << std::count_if(blocks.begin(), blocks.end(),
		[](const Block& block) {
			return block.blockType == BlockType::Sand;
		}) << std::endl;
}