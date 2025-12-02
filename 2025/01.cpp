#include <iostream>

int main()
{
    std::string move;

    int pos = 50;
    int answer_1 = 0;
    int answer_2 = 0;

    while (std::cin >> move)
    {
        int dir = (move[0] == 'L') ? -1 : 1;
        int dist = std::stoi(move.substr(1));

        int full_rotations = dist / 100;
        dist = dist % 100;

        int new_pos = ((pos + dir * dist) % 100 + 100) % 100;
        if (new_pos == 0) answer_1++;
        
        answer_2 += full_rotations;

        if (dir == 1 && new_pos < pos) answer_2++;
        else if (dir == -1 && pos != 0 && (new_pos == 0 || new_pos > pos)) answer_2++;

        pos = new_pos;
    }
    std::cout << "Part 1:: " << answer_1 << std::endl;
    std::cout << "Part 2:: " << answer_2 << std::endl;
}