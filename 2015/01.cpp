#include <iostream>

int main()
{
    std::string instructions;
    std::cin >> instructions;
    int answer_1 = 0;
    int answer_2 = 0;
    for (int i = 0; i < instructions.length(); i++)
    {
        answer_1 += instructions[i] == '(' ? 1 : -1;
        if (answer_2 == 0 && answer_1 == -1) answer_2 = i + 1;
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}