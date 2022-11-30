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