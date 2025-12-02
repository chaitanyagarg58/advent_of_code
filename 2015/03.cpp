#include <iostream>
#include <unordered_set>
#include <vector>

uint32_t apply_move(uint32_t start_location, char move)
{
    switch (move)
    {
        case '>':
        {
            return start_location + 1;
        }
        case '<':
        {
            return start_location - 1;
        }
        case '^':
        {
            return start_location + (1 << 16);
        }
        case 'v':
        {
            return start_location - (1 << 16);
        }
        default:
        {
            throw std::runtime_error(std::string("Unhandled Move: ") + move);
        }
    }
}

int solve(const std::string& input, int num_santa = 1)
{
    std::vector<uint32_t> locations = std::vector<uint32_t>(num_santa, 0);
    std::unordered_set<uint32_t> visited;
    visited.insert(0);
    for (int i = 0; i < input.length(); i++)
    {
        char move = input[i];
        uint32_t& location = locations[i % num_santa];
        location = apply_move(location, move);
        visited.insert(location);
    }
    return visited.size();
}

int main()
{
    std::string input;
    std::cin >> input;

    int answer_1 = solve(input);
    int answer_2 = solve(input, 2);

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;

}