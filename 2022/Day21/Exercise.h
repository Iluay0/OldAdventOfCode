#pragma once

struct Monkey
{
	std::string name;
	__int64 value;
	std::string firstMonkey;
	std::string secondMonkey;
	char oper;

	Monkey()
	{
		this->name = "";
		this->value = INT64_MAX;
		this->firstMonkey = "";
		this->secondMonkey = "";
		this->oper = '&';
	}

	Monkey(std::string name, std::string firstMonkey, std::string secondMonkey, char oper)
	{
		this->name = name;
		this->firstMonkey = firstMonkey;
		this->secondMonkey = secondMonkey;
		this->oper = oper;
		this->value = INT64_MAX;
	}

	Monkey(std::string name, __int64 value)
	{
		this->name = name;
		this->value = value;
	}

	void setValue(__int64 first, __int64 second)
	{
		switch (oper)
		{
			case '+':
				value = first + second;
				break;
			case '-':
				value = first - second;
				break;
			case '*':
				value = first * second;
				break;
			case '/':
				value = first / second;
				break;
			case '=':
				if (first == INT64_MAX)
					value = second;
				else
					value = first;
				break;
			default:
				throw;
		}
		// std::cout << name << ": " << first << " " << oper << " " << second << " = " << value << std::endl;
	}

	void setValueReverse(__int64 result, __int64 other, int missing, char nextOperator)
	{
		switch (nextOperator)
		{
		case '+':
			value = result - other;
			break;
		case '-':
			if (missing == 1)
				value = result + other;
			else
				value = other - result;
			break;
		case '*':
			value = result / other;
			break;
		case '/':
			if (missing == 1)
				value = other * result;
			else
				value = other / result;
			break;
		case '=':
			value = result;
			break;
		default:
			throw;
		}
		// std::cout << name << " (reverse): " << other << " " << nextOperator << " " << result << " = " << value << std::endl;
	}
};

class Exercise
{
	std::map<std::string, Monkey> monkeys;
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