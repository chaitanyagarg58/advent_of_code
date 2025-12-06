#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

std::pair<long long, long long> solve(std::vector<std::string>& nums, std::string op)
{
    long long answer_1 = op == "+" ? 0 : 1;
    long long answer_2 = answer_1;

    std::vector<std::string> nums_2(nums[0].length(), "");

    for (std::string& num: nums)
    {
        if (op == "+") answer_1 += std::stoll(num);
        else if (op == "*") answer_1 *= std::stoll(num);
        else throw std::runtime_error(std::string("Unhandled operation : ") + op);

        for (int i = 0; i < num.length(); i++)
        {
            nums_2[i].push_back(num[i]);
        }
    }

    for (std::string& num: nums_2)
    {
        if (op == "+") answer_2 += std::stoll(num);
        else if (op == "*") answer_2 *= std::stoll(num);
        else throw std::runtime_error(std::string("Unhandled operation : ") + op);
    }

    return std::make_pair(answer_1, answer_2);
}

int main()
{
    std::vector<std::string> inputs;
    std::string input;

    while (std::getline(std::cin, input))
    {
        input.push_back(' ');
        inputs.push_back(input);
    }

    long long answer_1 = 0;
    long long answer_2 = 0;

    int start_idx = 0;
    for (int i = 0; i < inputs[0].length(); i++)
    {
        bool not_space = false;
        for (const std::string& input: inputs)
        {
            if (input[i] != ' ')
            {
                not_space = true;
                break;
            }
        }
        if (not_space) continue;
        std::vector<std::string> nums;
        for (int j = 0; j < inputs.size() - 1; j++)
        {
            nums.push_back(inputs[j].substr(start_idx, i - start_idx));
        }
        std::string op(1, inputs.back()[start_idx]);
        std::pair<long long, long long> solution = solve(nums, op);
        answer_1 += solution.first;
        answer_2 += solution.second;
        start_idx = i + 1;
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}