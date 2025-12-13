#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <unordered_set>
#include <vector>
#include <filesystem>

template<typename printable>void printarray(std::vector<printable>&arr){for(auto i:arr){std::cout<<i<<std::endl;}}
std::vector<std::string>split(const std::string&s,const char d=0){std::vector<std::string>o;std::string t;if(s.empty()){return o;}for(const char c:s){if(d==0){o.push_back(std::string(c,1));}else if(c==d and t.length()!=0){o.push_back(t);t.clear();}else if(c!=d){t+=c;}}t.empty()?(void)0:o.push_back(t);return o;}
std::vector<std::string>parse_file(std::ifstream&f){std::vector<std::string>o;std::string l;while(std::getline(f,l)){if(l.empty())continue;o.push_back(l);}return o;}


const inline uint64_t dxy_to64(const uint32_t x,const uint32_t y) {const auto nx=((uint64_t)x)<<32;return nx | (uint64_t)y;}
const inline uint64_t dxy_to64(const std::array<uint32_t,2> v){return dxy_to64(v[0],v[1]);}
const inline std::array<uint32_t,2>d64_toxy(const uint64_t v){const uint32_t x = v>>32;return {x, (uint32_t)v & 0xffffffff};}

void part1(std::vector<std::string>& data) {
    
    long total= 0;
    uint width = {0};
    std::unordered_set<uint64_t> travelers;

    if (not data.empty())
        if (not data.begin() -> empty())
            width = data.begin()->length();
  
    // first search where the stater is located
    for (uint8_t i{0}; i<width; i++) {
        if (data[0][i] == 'S'){
            // printf("starter is found at %d\n", i);
            // fflush(stdout);
            travelers.insert(dxy_to64(i,1));
            break;
        }
    }
    // perform a step
    ulong line = 0;
    for (; line < data.size(); line++) {
        int stotal = 0;
        std::unordered_set<uint64_t> next_travelers{};
        for (const auto& d: travelers) {
            std::array<uint32_t,2> pos = d64_toxy(d);
            if (pos[0] > width) continue;
            char land = data[pos[1]][pos[0]];
            if (land == '^') {
                pos[1] += 1;
                // check which direction the new traveler will move
                int8_t npos = pos[0] < width - 1? 1 : -1;
                auto ntrav = pos;
                ntrav[0] += npos;
                next_travelers.insert(dxy_to64(ntrav)); // then add the new traveler
                // check if the  pos is not out of bound then include it and increment stotal, else do nothing
                pos[0]--;
                if (0 <= pos[0]) {
                    stotal++; // inc the sub total
                    next_travelers.insert(dxy_to64(pos));
                }
            } else if (land == '.') {
                pos[1] += 1;
                next_travelers.insert(dxy_to64(pos));
            }
        }
        travelers = next_travelers;
        total += stotal;
    }
    std::printf("total %ld", total);
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
