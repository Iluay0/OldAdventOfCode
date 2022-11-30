#include "Utils/Utils.h"
#include "2021/Day2/Part1.h"
#include "2021/Day2/Part2.h"

int main()
{
    std::ifstream ifs("input.txt", std::ifstream::in);

    std::list<std::string> inputs;
    for (std::string line; std::getline(ifs, line); )
    {
        inputs.push_back(line);
    }

    Part2::Run(inputs);
}