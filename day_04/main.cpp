#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <filesystem>
#include <array>

template <typename printable>
void printarray(std::vector<printable> arr) {
    for (auto i: arr) {
        std::cout << i << std::endl;
    }
}
std::vector<std::string> parse_file(std::ifstream& file) {
    std::vector<std::string> output;
    std::string line;
    while (std::getline(file, line)) {
        output.push_back(line);
    }
    return output;
}
/// 
/// pos[y,x]
bool is_roll_accessable(const std::vector<std::string>& data, std::array<ulong,2> pos) {
    const int8_t adj_arr[8][2]{
        {-1,-1},{-1, 0},{-1, 1},
        { 0,-1},        { 0, 1},
        { 1,-1},{ 1, 0},{ 1, 1}
    };
    if (data[pos[0]].at(pos[1]) == '.') {
        return false;
    }
    ulong width = data[0].length();
    ulong heigth = data.size();
    int32_t adj_rolls = 0;
    for (const auto adj: adj_arr) {
        ulong y = adj[0]+pos[0];
        ulong x = adj[1]+pos[1];
        if (x > width-1 or x < 0) continue;
        if (y > heigth-1 or y < 0) continue;

        if (data[y].at(x) == '@')
            adj_rolls++;
        
    }
    if (adj_rolls < 4) return true;
    return false;
}

void part1(const std::vector<std::string>& data) {
    std::vector<std::string> current{data};
    std::vector<std::string> next_step{data};

    

    ulong width{0},heigth{data.size()};
    long total_rools{0};
    // printarray(data);
    // std::cout << data.size() << std::endl;
    while (true) {
        bool added = 0;
        for (ulong y{0}; y < heigth; y++) {
            width = current[y].length();
            // std::cout << "    width: " << width << std::endl;
            for (ulong x{0}; x < width; x++) {
                if (is_roll_accessable(current, {y,x})) {
                    total_rools+=1;
                    added = 1;
                    next_step[y][x] = '.';
                    // std::cout << data[y] << " " << data[y].at(x) << x << std::endl;
                }
            }
        }
        current = std::vector<std::string>(next_step);
        if (not added) break;
    }
    std::cout << total_rools << std::endl;
}

bool test = 0;
int main(int argc, char* argv[]) {
    if (not test) {
        std::filesystem::path exec_path = argv[0];
        auto file = std::ifstream(exec_path.parent_path() / "data.txt");
        if (!file.is_open()) std::cerr << "Error opening the file" << std::endl;
        auto data = parse_file(file);
        part1(data);
    } else {
        std::vector<std::string> data = {
            "..@@.@@@@.",
            "@@@.@.@.@@",
            "@@@@@.@.@@",
            "@.@@@@..@.",
            "@@.@@@@.@@",
            ".@@@@@@@.@",
            ".@.@.@.@@@",
            "@.@@@.@@@@",
            ".@@@@@@@@.",
            "@.@.@@@.@."};
        part1(data);
    }

    return 0;
}

