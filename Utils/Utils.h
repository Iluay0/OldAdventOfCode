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
#include <map>
#include <deque>
#include <set>
#include <windows.h>
#include <ctype.h>

class Utils
{
public:
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
    static std::string join(const std::list<std::string>& list, char delimiter);
    static int listSum(std::list<int> list);
    static int binaryToInt(long long n);
    static void replaceAll(std::string& str, const std::string& from, const std::string& to);
    static bool isShuffledSubstring(std::string A, std::string B);
};