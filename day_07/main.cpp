#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sys/types.h>
#include <vector>
#include <filesystem>

template <typename printable>
void printarray(std::vector<printable> arr) {
    for (auto i: arr) {
        std::cout << i << std::endl;
    }
}

std::vector<std::string> split(const std::string& s, const char delim = 0) {
    std::vector<std::string> out{};
    std::string temp;

    if (s.empty()){
        return out;
    }
    for (const char c : s) {
        if (delim == 0) {
            out.push_back(std::string(c,1));
        } else if (c == delim and temp.length() != 0) {
            out.push_back(temp);
            temp.clear();
        } else if (c != delim) {
            temp += c;
        }
    }
    temp.empty() ? (void)0: out.push_back(temp);
    
    return out;
}


std::vector<std::string> parse_file(std::ifstream& file) {
    std::vector<std::string> output;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        output.push_back(line);
    }
    return output;
}


struct traveler {
    std::array<uint8_t,2> pos = {0,0};
    traveler() = default;
    traveler(std::array<uint8_t,2> inp): pos{inp}{}
    traveler(uint8_t x, uint8_t y): pos{x,y}{}

    /*
    move 1 strp down but return true if its deletable means it hit a splitter or out of bound
    this will update the data on the dumps if its deletable
    */
    bool move(std::vector<std::string>& board, std::unique_ptr<traveler>& dumps) {
        int width, heigth;
        width = board[0].length();
        heigth = board.size();
        if (0 <= pos[0] and pos[0] <= width and // check if x is in bound
            0 <= pos[1] and pos[1] <= heigth) { // check if y is in bound
            switch (board[pos[1]+1][pos[0]]) {
                case '^': // splitter
                    pos[0] -= 1;
                    // *dumps = traveler{pos[0],static_cast<uint8_t>(pos[1]+1)};
                    return true;
                case '.':// move down and do nothing
                    pos[1] += 1;
                    // dumps.reset();
                    return false;
                // just unknown but continue anyways
                default: dumps.reset(); std::cout << board[pos[1]+1][pos[0]] << std::endl;return false;
            }
        // outside of the board
        } else dumps.reset();return true;
    }
};


void part1(std::vector<std::string>& data) {
    
    int width = {0};
    if (not data.empty())
        if (not data.begin() -> empty())
            width = data.begin()->length();
    std::vector<traveler> travelers = {};
  
    // first search where the stater is located
    for (uint8_t i{0}; i<width; i++) {
        if (data[0][i] == 'S'){
            printf("starter is found at %d\n", i);
            fflush(stdout);
            travelers.push_back({i,0});
            break;
        }
    }

    auto travelers_c = travelers;

    int total{0};
    int y = 0;
    while (true) {
        int s = 0;
        for (int i{0}; i < travelers.size(); i++) {

            auto& t = travelers[i];
            std::unique_ptr<traveler> second = std::make_unique<traveler>(t);
            // if traveler can be remove and if it created a new traveler
            bool r = t.move(data, second);
            printf("%d traveler's spos %d, %d size %d\n", i, travelers[i].pos[0], travelers[i].pos[1], r);
            fflush(stdout);
            // hit a splitter
            if (r and second) {
                t.pos[0] -= 1; // change the current element
                // travelers_c.push_back(t); // and push to the vector
                travelers_c.push_back(*second); // add new element
                s += 1;
            // out side the bounds
            } else if (r and second == 0) {// removable but did not hit  splitter
                std::cout << "deleting" << std::endl;
                travelers_c.erase(travelers.begin() + i);
            // if both are 0
            }
        }
        travelers = travelers_c;
        if (++y >= width) break;
        total += s;
    }
    std::printf("total %d", total);
}


bool test = 1;
int main(int argc, char* argv[]) {
    auto solve = part1;
    if (not test) {
        std::filesystem::path exec_path = argv[0];
        auto file = std::ifstream(exec_path.parent_path() / "data.txt");
        if (!file.is_open()) std::cerr << "Error opening the file" << std::endl;
        std::vector<std::string> data = parse_file(file);
        solve(data);
    } else {
        std::vector<std::string> data = {
            ".......S.......",
            "...............",
            ".......^.......",
            "...............",
            "......^.^......",
            "...............",
            ".....^.^.^.....",
            "...............",
            "....^.^...^....",
            "...............",
            "...^.^...^.^...",
            "...............",
            "..^...^.....^..",
            "...............",
            ".^.^.^.^.^...^.",
            "..............."};
        solve(data);
    }

    return 0;
}
