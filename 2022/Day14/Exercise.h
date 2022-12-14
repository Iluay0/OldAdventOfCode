#pragma once

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
	uint16_t lastX;
	uint16_t lastY;

	Block(uint16_t xx, uint16_t yy, BlockType type)
	{
		x = xx;
		y = yy;
		blockType = type;
		lastX = 500;
		lastY = 0;
	}

	void saveLastPos()
	{
		lastX = x;
		lastY = y;
	}

	void setPos(uint16_t xx, uint16_t yy, bool save = true)
	{
		if (save)
			saveLastPos();
		x = xx;
		y = yy;
	}
};

class Exercise
{
	std::vector<Block> blocks;
	std::pair<uint16_t, uint16_t> minMaxX;
	std::pair<uint16_t, uint16_t> minMaxY;

	void renderBg();
	void renderSand();
	void renderCurrentBlock(Block* pCurrentBlock, bool eraseBlock = false);

	void read(const std::list<std::string>& inputs);

	Block getNextBlockBelow(Block& sandBlock);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};