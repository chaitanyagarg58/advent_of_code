#include <iostream>
#include <map>
#include <unordered_map>
#include <regex>
#include <variant>
#include <queue>
#include <vector>

enum Gate
{
    RSHIFT,
    LSHIFT,
    OR,
    AND,
    NOT,
    COPY,
};

std::map<Gate, std::regex> gates = {
    {RSHIFT, std::regex("^(\\w+) RSHIFT (\\w+) -> (\\w+)$")},
    {LSHIFT, std::regex("^(\\w+) LSHIFT (\\w+) -> (\\w+)$")},
    {OR, std::regex("^(\\w+) OR (\\w+) -> (\\w+)$")},
    {AND, std::regex("^(\\w+) AND (\\w+) -> (\\w+)$")},
    {NOT, std::regex("^NOT (\\w+)() -> (\\w+)$")},
    {COPY, std::regex("^(\\w+)() -> (\\w+)$")},
};

bool is_uint(const std::string& input)
{
    if (input.length() == 0) return false;
    for (const char& c: input) if (c < '0' || c > '9') return false;
    return true;
}

struct Config
{
    std::variant<uint16_t, std::string> input_1;
    std::variant<uint16_t, std::string> input_2;
    Gate gate;
    std::string output;

    Config(std::string input_1, std::string input_2, Gate gate, std::string output)
    {
        if (is_uint(input_1)) this->input_1 = static_cast<uint16_t>(std::stoul(input_1));
        else this->input_1 = input_1;
        if (is_uint(input_2)) this->input_2 = static_cast<uint16_t>(std::stoul(input_2));
        else this->input_2 = input_2;
        this->gate = gate;
        this->output = output;
    }

    void apply_config(std::unordered_map<std::string, uint16_t>& signals) const
    {
        if (std::holds_alternative<std::string>(input_1) && signals.find(std::get<std::string>(input_1)) == signals.end()) throw std::runtime_error("Can not apply config to given signal");
        uint16_t in_1 = std::holds_alternative<std::string>(input_1) ? signals[std::get<std::string>(input_1)] : std::get<uint16_t>(input_1);
        uint16_t in_2;
        if (gate != NOT && gate != COPY)
        {
            if (std::holds_alternative<std::string>(input_2) && signals.find(std::get<std::string>(input_2)) == signals.end()) throw std::runtime_error("Can not apply config to given signal");
            in_2 = std::holds_alternative<std::string>(input_2) ? signals[std::get<std::string>(input_2)] : std::get<uint16_t>(input_2);
        }

        switch (gate)
        {
            case LSHIFT:
                signals[output] = in_1 << in_2;
                break;
            case RSHIFT:
                signals[output] = in_1 >> in_2;
                break;
            case OR:
                signals[output] = in_1 | in_2;
                break;
            case AND:
                signals[output] = in_1 & in_2;
                break;
            case NOT:
                signals[output] = ~in_1;
                break;
            case COPY:
                signals[output] = in_1;
                break;
            default:
                throw std::runtime_error("Unknown gate");
        }
    }
};

void topological_sort(std::vector<std::string>& wires, const std::unordered_map<std::string, std::array<std::string, 2>>& graph)
{
    std::unordered_map<std::string, int> outdegree;
    for (std::string& wire: wires) outdegree[wire] = 0;
    for (auto& [output, inputs]: graph)
    {
        if (inputs[0].length()) outdegree[inputs[0]]++;
        if (inputs[1].length()) outdegree[inputs[1]]++;
    }
    std::queue<std::string> q;
    for (std::string& wire: wires) if (outdegree[wire] == 0) q.push(wire);

    wires.clear();
    while (q.size())
    {
        std::string wire = q.front();
        q.pop();
        wires.push_back(wire);

        for (const std::string& input: graph.at(wire)) if (input.length() && --outdegree[input] == 0) q.push(input);
    }
    std::reverse(wires.begin(), wires.end());
}

int main()
{
    std::string instruction;
    std::unordered_map<std::string, Config> wire_config;
    std::unordered_map<std::string, std::array<std::string, 2>> dependency_graph;
    std::vector<std::string> wires;
    while (std::getline(std::cin, instruction))
    {
        bool matched = false;
        for (auto& [gate, regex] : gates)
        {
            std::smatch match;
            if (!std::regex_search(instruction, match, regex)) continue;
            wire_config.emplace(match[3], Config(match[1], match[2], gate, match[3]));
            if (!is_uint(match[1])) dependency_graph[match[3]][0] = match[1];
            if (!is_uint(match[2])) dependency_graph[match[3]][1] = match[2];
            wires.push_back(match[3]);
            break;
        }
    }
    topological_sort(wires, dependency_graph);

    std::function<int(std::string)> solve = [&](std::string wire) -> int {
        std::unordered_map<std::string, uint16_t> signals;
        for (const std::string& wire: wires)
        {
            wire_config.at(wire).apply_config(signals);
        }
        return signals[wire];
    };
    int answer_1 = solve("a");
    wire_config.at("b").input_1 = answer_1;
    int answer_2 = solve("a");

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}