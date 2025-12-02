#include <iostream>

static std::string vowels = "aeiou";

bool nice_1(const std::string& input)
{
    std::string restricted = "acpx";
    int num_vowels = 0;
    bool rep = false;
    for (int idx = 0; idx < input.length() - 1; idx++)
    {
        num_vowels += (vowels.find(input[idx]) != std::string::npos);
        rep |= (input[idx] == input[idx + 1]);
        if (restricted.find(input[idx]) != std::string::npos && input[idx + 1] == input[idx] + 1) return false;
    }
    num_vowels += (vowels.find(input.back()) != std::string::npos);
    return (num_vowels >= 3 && rep);
}

bool nice_2(const std::string& input)
{
    bool has_xyx = false;
    for (int idx = 0; idx < input.length() - 2; idx++)
    {
        if (input[idx] != input[idx + 2]) continue;
        has_xyx = true;
        break;
    }
    if (!has_xyx) return false;

    for (int idx = 0; idx < input.length() - 1; idx++)
    {
        if (input.substr(idx + 2).find(input.substr(idx, 2)) != std::string::npos) return true;
    }
    return false;
}

int main()
{
    std::string input;
    int answer_1 = 0;
    int answer_2 = 0;

    while (std::cin >> input)
    {
        answer_1 += nice_1(input);
        answer_2 += nice_2(input);
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}