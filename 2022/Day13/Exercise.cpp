#include "../../Utils/Utils.h"
#include "Exercise.h"

enum CompareResult
{
	Same = 0,
	RightOrder,
	WrongOrder
};

struct Element
{
	int value;
	std::vector<Element> elementList;

	Element()
	{
		value = -1;
	}

	void read(const std::string& packet, int& index)
	{
		if (index >= packet.size())
			return;

		char current = packet[index];
		index++;
		if (index == 1 && current == '[')
			return read(packet, index);

		if (current == ']')
			return;

		if (current == ',')
			return read(packet, index);

		if (current == '[')
		{
			Element element;
			element.read(packet, index);
			elementList.push_back(element);
		}
		else
		{
			std::string szValue = std::string(1, current);
			while (index < packet.size() && isdigit(packet[index]))
			{
				szValue += packet[index];
				index++;
			}
			Element element;
			element.value = stoi(szValue);
			elementList.push_back(element);
		}
		read(packet, index);
	}

	std::string toString()
	{
		std::string ret = "";
		if (value == -1)
		{
			ret += "[";
			for (auto& it : elementList)
			{
				ret += it.toString();
				if (&it != &elementList.back())
					ret += ",";
			}
			ret += "]";
		}
		else
		{
			if(value != -1)
				ret += std::to_string(value);
		}
		return ret;
	}

	CompareResult compare(Element other, std::string indent = "", bool log = false)
	{
		if (log)
			std::cout << indent << "- Compare " << toString() << " vs " << other.toString() << std::endl;

		size_t iter = min(elementList.size(), other.elementList.size());
		for (size_t i = 0; i < iter; i++)
		{
			if (log)
				std::cout << indent << "  - Compare " << elementList[i].toString() << " vs " << other.elementList[i].toString() << std::endl;
			if (elementList[i].elementList.empty() && other.elementList[i].elementList.empty())
			{
				if (elementList[i].value < other.elementList[i].value)
				{
					if (log)
						std::cout << indent << "    - Left side is smaller, so inputs are in the right order" << std::endl;
					return CompareResult::RightOrder;
				}
				else if(elementList[i].value > other.elementList[i].value)
				{
					if (log)
						std::cout << indent << "    - Right side is smaller, so inputs are not in the right order" << std::endl;
					return CompareResult::WrongOrder;
				}
			}
			else
			{
				if (elementList[i].elementList.empty())
				{
					if (elementList[i].value == -1)
					{
						if (log)
							std::cout << indent << "    - Left side ran out of items, so inputs are in the right order" << std::endl;
						return CompareResult::RightOrder;
					}
					if (log)
						std::cout << indent << "    - Mixed types; convert left and retry comparison" << std::endl;
					Element converted;
					Element content;
					content.value = elementList[i].value;
					converted.elementList.push_back(content);
					return converted.compare(other.elementList[i], indent + "    ", log);
				}
				else if (other.elementList[i].elementList.empty())
				{
					if (other.elementList[i].value == -1)
					{
						if (log)
							std::cout << indent << "    - Right side ran out of items, so inputs are not in the right order" << std::endl;
						return CompareResult::WrongOrder;
					}
					if (log)
						std::cout << indent << "    - Mixed types; convert right and retry comparison" << std::endl;
					Element converted;
					Element content;
					content.value = other.elementList[i].value;
					converted.elementList.push_back(content);
					return elementList[i].compare(converted, indent + "    ", log);
				}
				CompareResult result = elementList[i].compare(other.elementList[i], indent + "    ", log);
				if(result != CompareResult::Same)
					return result;
			}
		}

		if (elementList.size() < other.elementList.size())
		{
			if (log)
				std::cout << indent << "  - Left side ran out of items, so inputs are in the right order" << std::endl;
			return CompareResult::RightOrder;
		}
		else if (other.elementList.size() < elementList.size())
		{
			if (log)
				std::cout << indent << "  - Right side ran out of items, so inputs are not in the right order" << std::endl;
			return CompareResult::WrongOrder;
		}

		return CompareResult::Same;
	}
};

struct PacketGroup
{
	int index;
	Element left;
	Element right;

	PacketGroup(int id)
	{
		index = id;
	}

	CompareResult compare()
	{
		std::cout << "Pair " << index << ":" << std::endl;
		return left.compare(right);
	}
};

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