#include <iostream>
#include <vector>
#include <queue>

int main()
{
    std::vector<std::string> grid;
    std::string row;
    while (std::getline(std::cin, row)) grid.push_back(row);
    std::vector<std::vector<int>> blocks(grid.size(), std::vector<int>(grid[0].length(), -1));
    std::queue<int> removal_queue;
    int answer_1 = 0;
    int answer_2 = 0;
    for (int i = 0; i < blocks.size(); i++)
    {
        for (int j = 0; j < blocks[0].size(); j++)
        {
            if (grid[i][j] != '@') continue;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (i + di < 0 || i + di >= blocks.size()) continue;
                    if (j + dj < 0 || j + dj >= blocks[0].size()) continue;
                    blocks[i][j] += (grid[i + di][j + dj] == '@');
                }
            }
            if (blocks[i][j] < 4) removal_queue.push((i << 16) + j);
        }
    }
    answer_1 = removal_queue.size();
    while (removal_queue.size())
    {
        int curr = removal_queue.front();
        int i = curr >> 16;
        int j = curr & ((1 << 16) - 1);
        removal_queue.pop();
        if (blocks[i][j] == -1) continue;
        blocks[i][j] = -1;
        answer_2++;
        for (int di = -1; di <= 1; di++)
        {
            for (int dj = -1; dj <= 1; dj++)
            {
                if (i + di < 0 || i + di >= blocks.size()) continue;
                if (j + dj < 0 || j + dj >= blocks[0].size()) continue;
                if (blocks[i + di][j + dj] <= 0) continue;
                if (--blocks[i + di][j + dj] < 4) removal_queue.push(((i + di) << 16) + (j + dj));
            }
        }
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}