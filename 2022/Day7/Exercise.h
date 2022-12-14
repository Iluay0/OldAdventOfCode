#pragma once

struct File
{
	std::string name;
	int size;

	File(std::string fileName, int fileSize)
	{
		name = fileName;
		size = fileSize;
	}
};

struct Directory
{
	std::string name;
	std::list<Directory> subDirectories;
	std::list<File> files;
	Directory* pParentDirectory;
	int totalSize;

	int getSize()
	{
		int size = 0;
		for (auto& it : subDirectories)
			size += it.getSize();
		for (auto& it : files)
			size += it.size;
		totalSize = size;
		return size;
	}

	Directory* getSubDirectoryWithSmallestSizeMoreThan(int size, int max)
	{
		Directory* pDir = this;
		for (auto& it : subDirectories)
		{
			Directory* pPotentialDir = it.getSubDirectoryWithSmallestSizeMoreThan(size, max);
			int dirSize = pPotentialDir->getSize();
			if (pPotentialDir && dirSize > size && dirSize < max)
			{
				pDir = pPotentialDir;
				max = pDir->getSize();
			}
		}
		return pDir;
	}

	int getTotalSizeOfSubDirectoriesWithSizeLessThan(int size)
	{
		int retSize = 0;
		for (auto& it : subDirectories)
		{
			int subDirSize = it.getSize();
			if (subDirSize < size)
				retSize += subDirSize;
			retSize += it.getTotalSizeOfSubDirectoriesWithSizeLessThan(size);
		}
		return retSize;
	}

	Directory(std::string dirName)
	{
		name = dirName;
	}
};

class Exercise
{
	Directory* pCurDir;

	void createDir(std::string dest);
	void createFile(std::string name, int size);
	void cd(std::string dest);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};