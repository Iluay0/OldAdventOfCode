#pragma once

#include <iostream>
#include <filesystem>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ranges>
#include <filesystem>
#include <sstream>
#include <chrono>
#include <regex>

class Utils
{
public:
    static std::vector<std::string> split(const std::string& str, char delimiter);
    static int listSum(std::list<int> list);
    static int binaryToLL(long long n);
};