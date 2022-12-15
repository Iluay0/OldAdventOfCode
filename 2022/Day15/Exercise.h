#pragma once

struct Beacon
{
	int x;
	int y;

	Beacon()
	{
		x = 0;
		y = 0;
	}

	Beacon(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
};

struct Sensor
{
	int x;
	int y;
	Beacon closestBeacon;

	Sensor(int xx, int yy)
	{
		x = xx;
		y = yy;
	}

	int distanceToPos(int xx, int yy)
	{
		return abs(x - xx) + abs(y - yy);
	}

	int distanceToBeacon()
	{
		return distanceToPos(closestBeacon.x, closestBeacon.y);
	}

	int getScanRangeY(int yy)
	{
		int distToBeacon = distanceToBeacon();
		int distToPos = distanceToPos(x, yy);
		return distToBeacon - distToPos;
	}
};

class Exercise
{
	std::map<std::pair<int, int>, Sensor> sensors;

	void read(std::list<std::string> inputs);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};