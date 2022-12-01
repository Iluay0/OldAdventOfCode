#include "Utils.h"

std::vector<std::string> Utils::split(const std::string& str, char delimiter)
{
    auto result = std::vector<std::string>{};

    auto range = str |
        std::ranges::views::split(delimiter) |
        std::ranges::views::transform([](auto&& r) -> std::string {
        const auto data = &*r.begin();
        const auto size = static_cast<std::size_t>(std::ranges::distance(r));

        return std::string{ data, size };
            });

    return { std::ranges::begin(range), std::ranges::end(range) };
}

int Utils::listSum(std::list<int> list)
{
    int sum = 0;
    for (auto& it : list)
        sum += it;
    return sum;
}

int Utils::binaryToInt(long long n)
{
    int dec = 0, i = 0, rem;

    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }

    return dec;
}

void Utils::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

bool Utils::isShuffledSubstring(std::string A, std::string B)
{
    int n = A.length();
    int m = B.length();

    // Return false if length of
    // string A is greater than
    // length of string B
    if (n > m) {
        return false;
    }
    else {

        // Sort string A
        sort(A.begin(), A.end());

        // Traverse string B
        for (int i = 0; i < m; i++) {

            // Return false if (i+n-1 >= m)
            // doesn't satisfy
            if (i + n - 1 >= m)
                return false;

            // Initialise the new string
            std::string str = "";

            // Copy the characters of
            // string B in str till
            // length n
            for (int j = 0; j < n; j++)
                str.push_back(B[i + j]);

            // Sort the string str
            std::sort(str.begin(), str.end());

            // Return true if sorted
            // string of "str" & sorted
            // string of "A" are equal
            if (str == A)
                return true;
        }
    }
}