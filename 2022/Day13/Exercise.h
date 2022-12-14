#pragma once

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
			if (value != -1)
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
				else if (elementList[i].value > other.elementList[i].value)
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
				if (result != CompareResult::Same)
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

class Exercise
{
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};