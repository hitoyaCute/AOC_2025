#include <cstdio>
#include <cstdlib>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
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

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string temp;

    for (char c : s) {
        if (c == delim and temp.length() != 0) {
            out.push_back(temp);
            temp.clear();
        } else if (c != delim) {
            temp += c;
        }
    }
    out.push_back(temp);
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


void part1(const std::vector<std::string>& data) {
    std::vector<
        std::vector<long> // number array
    > lists;

    const int width = split(data[0], ' ').size();
    lists.reserve(width);

    printf("reserved done\n");
    std::fflush(stdout);

    for (int i{0}; i < data.size() - 1; ++i) {
        auto line = data[i];
        auto temp = split(line.c_str(), ' ');

        for (int j{0}; j < width; ++j) {
            try {
                lists.at(j).push_back({std::atol(temp.at(j).c_str())}); 
            } catch (std::runtime_error) {
                throw std::runtime_error(std::format("something wrong"));
            }
            
        }
    }

    printf("done organizing data\n");
    std::fflush(stdout);
    auto ops = split(data.back(), ' ');

    long long total = 0;
    for (int i{0}; i < ops.size(); ++i) {

        char op = ops[i].at(0);
        long sub_total = op == '*';
        for (auto d:lists[i]) {
            // std::printf("       %ld %c\n", d, op);
            switch (op) {
                case '+': sub_total += d; break;
                case '*': sub_total *= d; break;
                default: throw std::runtime_error(std::format("unknown operator '{0:d}:{0:c}'\n", op));
            } 
        }
        // std::printf("sub_total: %ld\n", sub_total);
        total += sub_total;
    }

    std::printf("total %lld\n", total);
}


bool test = 0;
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
            "123 328  51 64",
            "45 64  387 23",
            "6 98  215 314",
            "*   +   *   +"};
        solve(data);
    }

    return 0;
}
