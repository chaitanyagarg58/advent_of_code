#include <iostream>

int main()
{
    std::string input;
    int answer_1 = 0;
    int answer_2 = 0;

    int encoded_size = 0;
    int in_code_size = 0;
    int in_memory_size = 0;
    while (std::cin >> input)
    {
        in_code_size += input.size();
        for (int i = 1; i < input.size() - 1; i++)
        {
            in_memory_size++;
            if (input[i] == '\\')
            {
                if (input[i + 1] == 'x') i += 3;
                else i += 1;
            }
        }
        encoded_size += 2;
        for (int i = 0; i < input.size(); i++)
        {
            encoded_size++;
            if (input[i] == '\\' || input[i] == '"') encoded_size++;
        }
    }
    answer_1 = in_code_size - in_memory_size;
    answer_2 = encoded_size - in_code_size;

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}