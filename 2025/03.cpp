#include <iostream>
#include <queue>

long long get_max_num(const std::string& bank, int num_digits)
{
    long long num = 0;
    std::queue<int> idx[10];
    for (int i = 0; i < bank.length(); i++) idx[bank[i] - '0'].push(i);

    int start_idx = 0;
    while (num_digits > 0)
    {
        for (int i = 9; i >= 0; i--)
        {
            while (idx[i].size() && idx[i].front() < start_idx) idx[i].pop();
            if (idx[i].size() && idx[i].front() <= bank.length() - num_digits)
            {
                num = num * 10 + (bank[idx[i].front()] - '0');
                start_idx = idx[i].front() + 1;
                idx[i].pop();
                num_digits--;
                break;
            }
        }
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