#include <iostream>

int find_next_digit(const std::string& bank, int start_idx, int num_digits_remaining)
{
    if (bank.length() - start_idx < num_digits_remaining) throw std::runtime_error(std::string("Num digits remaining is less than num available digits"));
    
    int idx[10];
    for (int& i: idx) i = -1;

    for (int i = bank.length() - num_digits_remaining; i >= start_idx; i--) idx[bank[i] - '0'] = i;
    for (int i = 9; i >= 0; i--) if (idx[i] != -1) return idx[i];

    throw std::runtime_error(std::string("Should Never reach here"));
}

long long get_max_num(const std::string& bank, int num_digits)
{
    long long num = 0;
    int start_idx = 0;
    while (num_digits > 0)
    {
        int idx = find_next_digit(bank, start_idx, num_digits);
        num = num * 10 + (bank[idx] - '0');
        start_idx = idx + 1;
        num_digits--;
    }
    return num;
}

int main()
{
    std::string bank;
    long long answer_1 = 0;
    long long answer_2 = 0;

    while (std::cin >> bank)
    {
        answer_1 += get_max_num(bank, 2);
        answer_2 += get_max_num(bank, 12);
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}