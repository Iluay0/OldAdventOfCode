#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::createDir(std::string dest)
{
	Directory subDir(dest);
	subDir.pParentDirectory = pCurDir;
	pCurDir->subDirectories.push_back(subDir);
}

void Exercise::createFile(std::string name, int size)
{
	File file(name, size);
	pCurDir->files.push_back(file);
}

void Exercise::cd(std::string dest)
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
		createDir(dest);
		cd(dest);
	}
	else
		pCurDir = &*itDir;

	return;
}

void Exercise::Part1(std::list<std::string> inputs)
{
	Directory rootDir("");
	pCurDir = &rootDir;

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
			cd(split[1]);
		else if (split[0] == "ls")
		{
			ls = true;
			continue;
		}
		else if (ls)
		{
			if (split[0] == "dir")
				createDir(split[1]);
			else
				createFile(split[1], stoi(split[0]));
		}
	}

	std::cout << rootDir.getTotalSizeOfSubDirectoriesWithSizeLessThan(100000);
}

void Exercise::Part2(std::list<std::string> inputs)
{
	Directory rootDir("");
	pCurDir = &rootDir;

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
			cd(split[1]);
		else if (split[0] == "ls")
		{
			ls = true;
			continue;
		}
		else if (ls)
		{
			if (split[0] == "dir")
				createDir(split[1]);
			else
				createFile(split[1], stoi(split[0]));
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