#include <iostream>
#include <sstream>
#include <functional>
#include <unordered_set>

long long solve_range(long long start, long long end, std::unordered_set<long long>&& added = {}, long long num_repeat = 2)
{
    std::function<long long(long long)> transform = [num_repeat](long long num) -> long long {
        std::string x = std::to_string(num);
        std::string ans;
        for (int i = 0; i < num_repeat; i++) ans += x;
        return std::stol(ans);
    };

    std::function<long long(long long)> binary_search = [transform](long long threshold) -> long long
    {
        long long idx = 1;
        while (transform(idx) < threshold) idx *= 2;
        long long low = idx / 2;
        long long high = idx;
        while (low < high)
        {
            long long mid = low + (high - low) / 2;
            if (transform(mid) < threshold) low = mid + 1;
            else high = mid;
        }
        return high;
    };

    long long first = binary_search(start);
    long long last = binary_search(end) - 1;

    long long sum = 0;
    for (int i = first; i <= last; i++)
    {
        long long num = transform(i);
        if (added.count(num)) continue;
        added.insert(num);
        sum += num;
    
    }
    return sum;
}


int main()
{
    std::string input;
    std::cin >> input;
    std::istringstream input_stream(input);
    std::string range;
    long long answer_1 = 0;
    long long answer_2 = 0;
    while (std::getline(input_stream, range, ','))
    {
        int delim = range.find('-');
        long long start = std::stol(range.substr(0, delim));
        long long end = std::stol(range.substr(delim + 1));

        answer_1 += solve_range(start, end);


        std::unordered_set<long long> added;
        answer_2 += solve_range(start, end, std::move(added), 2);
        answer_2 += solve_range(start, end, std::move(added), 3);
        answer_2 += solve_range(start, end, std::move(added), 5);
        answer_2 += solve_range(start, end, std::move(added), 7);
        answer_2 += solve_range(start, end, std::move(added), 11);
        answer_2 += solve_range(start, end, std::move(added), 13);
        answer_2 += solve_range(start, end, std::move(added), 17);
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;

}