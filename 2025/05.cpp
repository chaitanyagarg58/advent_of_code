#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main()
{
    std::string input;
    std::vector<std::pair<long long, long long>> intervals;
    while (std::getline(std::cin, input))
    {
        if (input == "") break;
        int delim = input.find('-');
        long long start = std::stoll(input.substr(0, delim));
        long long end = std::stoll(input.substr(delim + 1));
        intervals.emplace_back(start, end);
    }
    std::sort(intervals.begin(), intervals.end(), [](std::pair<long long, long long> a, std::pair<long long, long long> b) -> bool {
        return a.first == b.first ? a.second >= b.second : a.first < b.first;
    });
    std::vector<std::pair<long long, long long>> merged_intervals;
    long long answer_1 = 0;
    long long answer_2 = 0;
    for (int i = 0; i < intervals.size(); i++)
    {
        if (i + 1 < intervals.size() && intervals[i + 1].first <= intervals[i].second + 1)
        {
            intervals[i + 1] = {intervals[i].first, std::max(intervals[i].second, intervals[i + 1].second)};
        }
        else
        {
            merged_intervals.emplace_back(intervals[i].first, intervals[i].second);
            answer_2 += merged_intervals.back().second - merged_intervals.back().first + 1;
        }
    }

    while (std::getline(std::cin, input))
    {
        long long query = std::stoll(input);
        int idx = std::upper_bound(merged_intervals.begin(), merged_intervals.end(), std::make_pair(query, LONG_LONG_MAX)) - merged_intervals.begin();
        idx--;
        if (idx >= 0 && merged_intervals[idx].second >= query) answer_1++;
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}