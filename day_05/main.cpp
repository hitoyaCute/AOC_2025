#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
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
std::vector<std::string> parse_file(std::ifstream& file) {
    std::vector<std::string> output;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        output.push_back(line);
    }
    return output;
}

bool is_alnum(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    for (char c : str) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

void part1(const std::vector<std::string>& data) {
    int total_fresh{0};
    std::vector<std::array<long,2>> ranges{};
    std::vector<long>    values{};


    // parse ranges and values
    for (auto line:data) {
        if (is_alnum(line)) {

            long val = atol(line.c_str());
            // printf(("alnum: %d true_val:'"+line+"'\n").c_str(),val);
            values.push_back(val);
        } else {
            uint8_t sep = line.find('-');
            std::array<long,2> temp{
                std::atol(line.substr(0, sep).c_str()), 
                std::atol(line.substr(sep+1).c_str())};

            // printf(("range(%d, %d) true_val:'"+line+"'\n").c_str(),temp[0],temp[1]);
            ranges.push_back(temp);
        }
    }
    #define IS_IN_RANGE(x, range)  range[0] <= x and x <= range[1]
    for (auto val: values) {
        for (auto ran: ranges) {
            auto temp = IS_IN_RANGE(val, ran);
            
            if (temp) {
                // std::printf("val:'%ld' range(%ld,%ld)\n",val,ran[0],ran[1]);
                total_fresh += temp;
                break;
            }
        }
    }
    #undef IS_IN_RANGE
    

    std::cout << total_fresh << std::endl;
}

//std::vector<std::pair<int,int>>
void compress_range(std::vector<std::pair<long,long>>& ranges) {
    if (ranges.empty()) return;

    std::sort(ranges.begin(), ranges.end());
    
    std::vector<std::pair<long,long>> merged{};
    merged.push_back(ranges[0]);

    for (size_t i{0}; i < ranges.size(); ++i) {
        auto& last = merged.back();
        auto& current = ranges[i];
        if (current.first <= last.second) {
            last.second = std::max(last.second, current.second);
        } else {
            merged.push_back(current);
        }
    }
    ranges = merged;
}

void part2(const std::vector<std::string>& data) {
    long total_fresh{0};
    std::vector<std::pair<long,long>> ranges;

    // parse ranges and values
    for (auto line:data) {
        if (!is_alnum(line)) {
            const size_t sep = line.find('-');
            const std::pair<long,long> temp {
                std::atol(line.substr(0, sep).c_str()),
                std::atol(line.substr(sep+1).c_str())};
            // printf(("range(%d, %d) true_val:'"+line+"'\n").c_str(),temp[0],temp[1]);
            ranges.emplace_back(temp);
            //printf("ranges(%ld, %ld) temp(%ld, %ld) true_val: %s\n", ranges.back().first, ranges.back().second, temp.first, temp.second, line.c_str());
        }
    }

    compress_range(ranges);
    printf("\n\n");

    for (auto ran: ranges) {
        // printf("%ld,%ld\n", ran.first,ran.second);
        total_fresh += (ran.second - ran.first) + 1;
    }
    std::cout << total_fresh << std::endl;
}

bool test = 0;
int main(int argc, char* argv[]) {
    if (not test) {
        std::filesystem::path exec_path = argv[0];
        auto file = std::ifstream(exec_path.parent_path() / "data.txt");
        if (!file.is_open()) std::cerr << "Error opening the file" << std::endl;
        auto data = parse_file(file);
        part2(data);
    } else {
        std::vector<std::string> data = {
            "3-5",
            "10-14",
            "16-20",
            "12-18",
            "1",
            "5",
            "8",
            "11",
            "17",
            "32"};
        part2(data);
    }

    return 0;
}

