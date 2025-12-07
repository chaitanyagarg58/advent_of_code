#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> manifold;
    std::string layer;
    while (std::getline(std::cin, layer))
    {
        manifold.push_back(layer);
    }
    std::vector<std::pair<long long, long long>> beams;
    beams.push_back(std::make_pair(manifold[0].find('S'), 1));
    long long answer_1 = 0;
    long long answer_2 = 1;

    for (int i = 2; i < manifold.size(); i++)
    {
        std::vector<std::pair<long long, long long>> next_beams;
        std::string& layer = manifold[i];
        for (auto [j, count]: beams)
        {
            int n = next_beams.size();
            if (layer[j] == '^')
            {
                answer_2 += count;
                if (n >= 1 && (next_beams[n - 1].first == j - 1)) next_beams[n - 1].second += count;
                else if (n >= 2 && (next_beams[n - 2].first == j - 1)) next_beams[n - 2].second += count;
                else if (n && next_beams.back().first == j)
                {
                    auto tmp = next_beams.back();
                    next_beams.back() = std::make_pair(j - 1, count);
                    next_beams.push_back(tmp);
                }
                else next_beams.push_back(std::make_pair(j - 1, count));
                next_beams.push_back(std::make_pair(j + 1, count));
                answer_1++;
            }
            else
            {
                if (n && next_beams.back().first == j) next_beams.back().second += count;
                else next_beams.push_back(std::make_pair(j, count));
            }
        }
        beams = std::move(next_beams);
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}