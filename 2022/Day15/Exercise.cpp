#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " ");

		std::string posX = split[2];
		posX.erase(0, 2);
		posX.pop_back();
		std::string posY = split[3];
		posY.erase(0, 2);
		posY.pop_back();

		Sensor sensor(stoi(posX), stoi(posY));

		posX = split[split.size() - 2];
		posX.erase(0, 2);
		posX.pop_back();
		posY = split[split.size() - 1];
		posY.erase(0, 2);
		sensor.closestBeacon = Beacon(stoi(posX), stoi(posY));

		sensors.insert({ {sensor.x, sensor.y}, sensor });
	}
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);
	int calcY = 2000000;
	std::pair<int, int> posMinMax = { INT_MAX, INT_MAX };
	for (auto& it : sensors)
	{
		int max = it.second.distanceToBeacon() - it.second.distanceToPos(it.second.x, calcY);
		int x = it.second.x - max;
		if ((posMinMax.first == INT_MAX || posMinMax.first > x))
			posMinMax.first = x;

		x = it.second.x + max;
		if ((posMinMax.second == INT_MAX || posMinMax.second < x))
			posMinMax.second = x;
	}
	std::cout << posMinMax.second - posMinMax.first;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	read(inputs);
	std::pair<int, int> posMinMax = { 0, 4000000 };
	std::pair<int, int> beaconPos;

	for (int y = 0; y < posMinMax.second; y++)
	{
		std::vector<std::pair<int, int>> scanRanges;
		for (auto& it : sensors)
		{
			int scanRange = it.second.getScanRangeY(y);
			if (scanRange >= 0)
				scanRanges.push_back({ it.second.x - scanRange, it.second.x + scanRange });
		}

		std::pair<int, int> row = scanRanges.front();
		for (auto& it : scanRanges)
		{
			if (it.first <= row.second + 1 && it.second >= row.second - 1)
				row.second = it.second;
			if (it.second >= row.first - 1 && it.first <= row.first + 1)
				row.first = it.first;
			if (it.first <= row.first - 1 && it.second >= row.second + 1)
				row = it;
		}

		if (row.first > posMinMax.first)
		{
			beaconPos = { row.first - 1, y };
			break;
		}
		if (row.second < posMinMax.second)
		{
			beaconPos = { row.second + 1, y };
			break;
		}
	}

	std::cout << "Beacon position = " << beaconPos.first << "," << beaconPos.second << std::endl;
	std::cout << "Tuning frequency = " << (__int64)beaconPos.first * 4000000ll + (__int64)beaconPos.second;
}