#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::Part1(std::list<std::string> inputs)
{
	std::map<int, PacketGroup> packetList;
	auto join = Utils::join(inputs, '\n');
	auto packets = Utils::split(join, "\n\n");

	int packetGroupId = 1;
	for (auto& it : packets)
	{
		PacketGroup packetGroup(packetGroupId);
		auto elements = Utils::split(it, "\n");

		int index = 0;
		packetGroup.left.read(elements[0], index);
		index = 0;
		packetGroup.right.read(elements[1], index);

		packetList.insert({ packetGroupId, packetGroup });
		packetGroupId++;
	}

	int sum = 0;
	for (auto& it : packetList)
	{
		CompareResult result = it.second.compare();
		if (result == CompareResult::RightOrder)
			sum += it.first;
		else if (result == CompareResult::Same)
			throw;
		std::cout << std::endl;
	}
	std::cout << "Sum: " << sum;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	std::list<Element> packets;
	for (auto& it : inputs)
	{
		if (it == "")
			continue;

		int index = 0;
		Element element;
		element.read(it, index);
		packets.push_back(element);
	}

	std::list<Element> packetsOrdered;
	for (auto& it : packets)
	{
		if (packetsOrdered.empty())
		{
			packetsOrdered.push_back(it);
			continue;
		}

		bool broke = false;
		for (auto iter = packetsOrdered.begin(); iter != packetsOrdered.end(); ++iter)
		{
			if (it.compare(*iter, "") == CompareResult::WrongOrder)
			{
				packetsOrdered.insert(iter, it);
				broke = true;
				break;
			}
		}
		if (!broke)
			packetsOrdered.push_back(it);
	}
	std::reverse(packetsOrdered.begin(), packetsOrdered.end());
		
	int index = 1;
	for (auto& it : packetsOrdered)
	{
		if (it.toString() == "[[2]]" || it.toString() == "[[6]]")
			std::cout << "DIVIDER PACKET: Index: " << index << std::endl;

		std::cout << it.toString() << std::endl;
		index++;
	}
}