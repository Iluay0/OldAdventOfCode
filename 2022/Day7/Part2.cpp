#include "../../Utils/Utils.h"
#include "Part2.h"

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

	Directory* getDirectoryWithSmallestSizeMoreThan(int size)
	{
		if (getSize() < size)
			return nullptr;

		Directory* pDir = this;
		for (auto& it : subDirectories)
		{
			int subDirSize = it.getSize();
			if (subDirSize >= size && size < pDir->getSize())
				pDir = &it;

			Directory* pPotentialDir = it.getDirectoryWithSmallestSizeMoreThan(size);
			if (pPotentialDir)
				pDir = pPotentialDir;
		}
		return pDir;
	}

	Directory(std::string dirName)
	{
		name = dirName;
	}
};

void Part2::Run(std::list<std::string> inputs)
{
	Directory rootDir("");
	Directory* pCurDir = &rootDir;

	bool ls = false;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " ");
		if (split[0] == "$")
		{
			split.erase(split.begin());
			ls = false;
		}

		if (split[0] == "cd")
			cd(pCurDir, split[1]);
		else if (split[0] == "ls")
		{
			ls = true;
			continue;
		}
		else if (ls)
		{
			if (split[0] == "dir")
				createDir(pCurDir, split[1]);
			else
				createFile(pCurDir, split[1], stoi(split[0]));
		}
	}

	int freeSize = 70000000 - rootDir.getSize();
	int sizeToFree = 30000000 - freeSize;

	if (sizeToFree > 0)
	{
		auto pDirSmallestSize = rootDir.getDirectoryWithSmallestSizeMoreThan(sizeToFree);
		std::cout << pDirSmallestSize->getSize();
	}
	else
		std::cout << "Already enough size free";
}