#include <iostream>
#include <sstream>
#include <algorithm>

int main()
{
    int answer_1 = 0;
    int answer_2 = 0;
    std::string dimension;
    while (std::cin >> dimension)
    {
        std::istringstream input(dimension);
        int dim[3];
        for (int i = 0; i < 3; i++) 
        {
            std::string d;
            std::getline(input, d, 'x');
            dim[i] = std::stoi(d);
        }
        std::sort(dim, dim + 3);

        answer_1 += dim[0] * dim[1] + 2 * (dim[0] * dim[1] + dim[0] * dim[2] + dim[1] * dim[2]);
        answer_2 += 2 * (dim[0] + dim[1]) + dim[0] * dim[1] * dim[2];
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}