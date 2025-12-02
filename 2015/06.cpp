#include <iostream>
#include <vector>
#include <regex>
#include <set>

enum Move
{
    UNKNOWN,
    TURN_OFF,
    TURN_ON,
    TOGGLE,
};

struct Rect
{
    int start_x, start_y;
    int end_x, end_y;

    int light_1 = -1;
    int light_2 = -1;

    Rect(int start_x, int start_y, int end_x, int end_y, int light_1, int light_2) : start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y), light_1(light_1), light_2(light_2) {}

    Rect(int start_x, int start_y, int end_x, int end_y) : start_x(start_x), start_y(start_y), end_x(end_x), end_y(end_y) {}

    bool operator<(const Rect& other) const {
        return std::tie(start_x, end_x, start_y, end_y) < std::tie(other.start_x, other.end_x, other.start_y, other.end_y);
    }

    bool intersects(const Rect& other) const
    {
        if (end_x < other.start_x || other.end_x < start_x) return false;
        if (end_y < other.start_y || other.end_y < start_y) return false;
        return true;
    }

    void split(const Rect& other, std::set<Rect>& splits) const
    {
        if (!this->intersects(other))
        {
            splits.insert(*this);
            return;
        }

        std::vector<int> x;
        x.push_back(start_x);
        if (other.start_x > start_x) x.push_back(other.start_x);
        if (other.end_x < end_x) x.push_back(other.end_x + 1);
        x.push_back(end_x + 1);

        std::vector<int> y;
        y.push_back(start_y);
        if (other.start_y > start_y) y.push_back(other.start_y);
        if (other.end_y < end_y) y.push_back(other.end_y + 1);
        y.push_back(end_y + 1);

        for (int i = 0; i < x.size() - 1; i++)
        {
            for (int j = 0; j < y.size() - 1; j++)
            {
                splits.emplace(x[i], y[j], x[i + 1] - 1, y[j + 1] - 1, light_1, light_2);
            }
        }
        return;        
    }

    void apply_move(Move move)
    {
        switch (move)
        {
            case TURN_OFF:
                this->light_1 = 0;
                this->light_2 = std::max(0, this->light_2 - 1);
                break;
            case TURN_ON:
                this->light_1 = 1;
                this->light_2++;
                break;
            case TOGGLE:
                this->light_1 = 1 - this->light_1;
                this->light_2 += 2;
                break;
            default:
                throw std::runtime_error(std::string("Unhandled Move: ") + std::to_string(move));
        }
    }

    void print() const
    {
        std::cout << "Rect(" << start_x << "," << start_y << " through " << end_x << "," << end_y << ") :: light_1=" << light_1 << ", light_2=" << light_2 << std::endl;
    }
};

int main()
{
    std::set<Rect> rects;
    rects.emplace(0, 0, 999, 999, 0, 0);

    std::string instruction;
    std::regex re("(turn off|turn on|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");

    while (std::getline(std::cin, instruction))
    {
        std::smatch match;
        if (!std::regex_search(instruction, match, re)) std::cout << "DIDN'T MATCH :: " << instruction << std::endl;
        Move move;
        if (match[1] == "turn off") move = TURN_OFF;
        else if (match[1] == "turn on") move = TURN_ON;
        else move = TOGGLE;

        int x1 = std::stoi(match[2]), y1 = std::stoi(match[3]);
        int x2 = std::stoi(match[4]), y2 = std::stoi(match[5]);

        Rect instr_rect(x1, y1, x2, y2);

        std::set<Rect> new_rects;
        for (Rect curr_rect: rects)
        {
            curr_rect.split(instr_rect, new_rects);
        }
        rects.clear();
        for (Rect r: new_rects)
        {
            if (r.intersects(instr_rect)) r.apply_move(move);
            rects.insert(r);
        }
    }
    int answer_1 = 0;
    int answer_2 = 0;

    for (const Rect& r: rects)
    {
        int area = (r.end_y - r.start_y + 1) * (r.end_x - r.start_x + 1);
        answer_1 += r.light_1 * area;
        answer_2 += r.light_2 * area;
    }

    std::cout << "Answer 1 :: " << answer_1 << std::endl;
    std::cout << "Answer 2 :: " << answer_2 << std::endl;
}