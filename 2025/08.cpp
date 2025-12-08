#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

class DSU
{
private:
    std::vector<int> parent;
    std::vector<int> rank;
public:
    DSU(int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        rank.resize(n, 1);
    }

    int find(int a)
    {
        if (a >= parent.size()) throw std::runtime_error("find input out of bound");
        if (parent[a] == a) return a;
        parent[a] = find(parent[a]);
        return parent[a];
    }

    void merge(int a, int b)
    {
        if (a >= parent.size() || b >= parent.size()) throw std::runtime_error("Merge input out of bound");
        int pa = find(a), pb = find(b);
        if (pa == pb) return;
        if (rank[pa] < rank[pb]) std::swap(pa, pb);
        parent[pb] = pa;
        rank[pa] += rank[pb];
    }

    bool all_merged()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            if (parent[i] != i) continue;
            if (rank[i] != parent.size()) return false;
        }
        return true;
    }

    int64_t get_answer_1(int num_largest)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> s;
        for (int i = 0; i < parent.size(); i++)
        {
            if (parent[i] != i) continue;
            s.push(rank[i]);
            if (s.size() > num_largest) s.pop();
        }
        int64_t answer_1 = 1;
        while (s.size())
        {
            answer_1 *= s.top();
            s.pop();
        }
        return answer_1;
    }
};


int64_t distance(int64_t a, int64_t b)
{
    int64_t dist = 0;
    int64_t mask = (1 << 20) - 1;
    dist += ((a >> 40) - (b >> 40)) * ((a >> 40) - (b >> 40));
    dist += (((a >> 20) & mask) - ((b >> 20) & mask)) * (((a >> 20) & mask) - ((b >> 20) & mask));
    dist += ((a & mask) - (b & mask)) * ((a & mask) - (b & mask));
    return dist;
}

int main()
{
    std::string input;
    std::vector<int64_t> boxes;
    std::vector<std::tuple<int64_t, int, int>> pair_dist;
    int num_connections = 1000;
    int num_largest_circuit = 3;
    int64_t answer_1 = 0;
    int64_t answer_2 = 0;

    while (std::getline(std::cin, input))
    {
        std::istringstream ss(input);
        std::string coordinate;
        int64_t location = 0;
        while (std::getline(ss, coordinate, ',')) location = (location << 20) + std::stoull(coordinate);
        for (int i; i < boxes.size(); i++) pair_dist.emplace_back(distance(boxes[i], location), i, boxes.size());
        boxes.push_back(location);
    }
    std::sort(pair_dist.begin(), pair_dist.end());
    DSU dsu(boxes.size());

    int i = 0;
    while (true)
    {
        auto [_, a, b] = pair_dist[i];
        i++;
        dsu.merge(a, b);
        if (i == num_connections - 1) answer_1 = dsu.get_answer_1(num_largest_circuit);
        if (dsu.all_merged())
        {
            answer_2 = (boxes[a] >> 40) * (boxes[b] >> 40);
            break;
        }
    }
    for (; i < num_connections; i++)
    {
        auto [_, a, b] = pair_dist[i];
        dsu.merge(a, b);
        if (i == num_connections - 1) answer_1 = dsu.get_answer_1(num_largest_circuit);
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}