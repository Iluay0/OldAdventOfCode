#include "../../Utils/Utils.h"
#include "Exercise.h"

size_t Exercise::circularGet(std::vector<Number>& l, __int64 amount, int offset)
{
    if (amount < 0)
        amount = -(abs(amount) % ((int)l.size() - offset));
    while (amount < 0)
        amount += l.size() - offset;
    return amount % ((int)l.size() - offset);
}

void Exercise::Part1(std::list<std::string> inputs)
{
    int i = 0;
    std::vector<Number> numbers;
    for (auto& it : inputs)
    {
        Number number(i, stoi(it));
        numbers.push_back(number);
        i++;
    }

    i = 0;
    while (true)
    {
        auto it = std::find_if(numbers.begin(), numbers.end(),
            [&i](const Number& number) {
                return number.index == i;
            });

        if (it == numbers.end())
            break;

        int distance = it - numbers.begin();
        int newIndex = circularGet(numbers, distance + it->value);

        Number number(i, it->value);
        numbers.erase(it);

        numbers.insert(numbers.begin() + newIndex, number);
        i++;
    }

    auto it = std::find_if(numbers.begin(), numbers.end(),
        [](const Number& number) {
            return number.value == 0;
        });

    if (it != numbers.end())
    {
        int offset = it - numbers.begin();
        std::cout << numbers[circularGet(numbers, offset + 1000, 0)].value +
            numbers[circularGet(numbers, offset + 2000, 0)].value +
            numbers[circularGet(numbers, offset + 3000, 0)].value << std::endl;
    }
}

void Exercise::Part2(std::list<std::string> inputs)
{
    int i = 0;
    std::vector<Number> numbers;
    __int64 decryptionKey = 811589153ll;
    for (auto& it : inputs)
    {
        Number number(i, stoi(it) * decryptionKey);
        numbers.push_back(number);
        i++;
    }

    for (int i = 1; i <= 10; i++)
    {
        int j = 0;
        while (true)
        {
            auto it = std::find_if(numbers.begin(), numbers.end(),
                [&j](const Number& number) {
                    return number.index == j;
                });

            if (it == numbers.end())
                break;

            int distance = it - numbers.begin();
            int newIndex = circularGet(numbers, distance + it->value);

            Number number(j, it->value);
            numbers.erase(it);

            numbers.insert(numbers.begin() + newIndex, number);
            j++;
        }
    }

    auto it = std::find_if(numbers.begin(), numbers.end(),
        [](const Number& number) {
            return number.value == 0;
        });

    if (it != numbers.end())
    {
        int offset = it - numbers.begin();
        std::cout << numbers[circularGet(numbers, offset + 1000, 0)].value +
            numbers[circularGet(numbers, offset + 2000, 0)].value +
            numbers[circularGet(numbers, offset + 3000, 0)].value << std::endl;
    }
}