#include "../../Utils/Utils.h"
#include "Exercise.h"

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
		std::cout << getSize() << " " << getPath() <<  "\n";
		if (getSize() < size)
		{
			std::cout << "skip\n";
			return nullptr;
		}

		Directory* pDir = this;
		for (auto& it : subDirectories)
		{
			Directory* pPotentialDir = it.getSubDirectoryWithSmallestSizeMoreThan(size, max);
			if (pPotentialDir && pPotentialDir->getSize() < max)
			{
				pDir = pPotentialDir;
				max = pDir->getSize();
			}
		}
		return pDir;
	}

	std::string getPath()
	{
		if (!pParentDirectory || name == "")
			return name;

		return pParentDirectory->getPath() + "/" + name;
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

void createDir(Directory* pCurDir, std::string dest)
{
	Directory subDir(dest);
	subDir.pParentDirectory = pCurDir;
	pCurDir->subDirectories.push_back(subDir);
}

void createFile(Directory* pCurDir, std::string name, int size)
{
	File file(name, size);
	pCurDir->files.push_back(file);
}

void cd(Directory*& pCurDir, std::string dest)
{
	if (dest[0] == '/') // todo: implement rootDir and homeDir?
		return;

	if (dest == "..")
	{
		pCurDir = pCurDir->pParentDirectory;
		return;
	}

	auto itDir = std::find_if(pCurDir->subDirectories.begin(), pCurDir->subDirectories.end(),
		[&dest](const Directory& subDir) {
			return subDir.name == dest;
		});

	if (itDir == pCurDir->subDirectories.end())
	{
		createDir(pCurDir, dest);
		cd(pCurDir, dest);
	}
	else
		pCurDir = &*itDir;

	return;
}

void Exercise::Part1(std::list<std::string> inputs)
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

	std::cout << rootDir.getTotalSizeOfSubDirectoriesWithSizeLessThan(100000);
}

void Exercise::Part2(std::list<std::string> inputs)
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
		auto pDirSmallestSize = rootDir.getSubDirectoryWithSmallestSizeMoreThan(sizeToFree, 70000000);
		std::cout << pDirSmallestSize->getSize();
	}
	else
		std::cout << "Already enough size free";
}