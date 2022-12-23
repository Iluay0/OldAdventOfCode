﻿#include "Utils/Utils.h"
#include "2022/Day23/Exercise.h"

int main()
{
    std::ifstream ifs("input.txt", std::ifstream::in);

    std::list<std::string> inputs;
    for (std::string line; std::getline(ifs, line); )
    {
        inputs.push_back(line);
    }

    Exercise::inst()->Part2(inputs);
}