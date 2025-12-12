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


void part1(const std::vector<std::string>& data) {
    std::vector<
        std::vector<long> // number array
    > lists{};

    const int width = split(data[0], ' ').size();
    for (int i{0}; i<width;i++){
        lists.push_back({});
    }

    printf("reserved done\n");
    std::fflush(stdout);

    for (int i{0}; i < data.size() - 1; ++i) {
        auto line = data[i];
        auto temp = split(line.c_str(), ' ');

        for (int j{0}; j < width; ++j) {
            lists[j].push_back({std::atol(temp[j].c_str())});
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

void part2(std::vector<std::string>& data) {
    long long total = 0;

    const int width = data[0].length();
    const int height = data.size();

    std::vector<std::string> current_arr{};

    for (int x{width - 1}; x >= 0; --x) {

        std::string current_num = "";
        
        for (int y{0}; y < height - 1; ++y) {
            const char d = data[y][x];
            if (d != ' ')
                current_num.push_back(d);
        }

        const char op = data[height-1][x];

        long sub_total{0};
        switch (op) {
            case ' ': {
                printf("added '%s'\n", current_num.c_str());
                current_num.empty() ? (void)0 : current_arr.push_back(current_num);
                break;
            } case '+': {
                current_arr.push_back(current_num.c_str());
                for (auto d:current_arr) {
                    // printf("   adding '%s' to %ld\n", d.c_str(), sub_total);
                    sub_total += std::atol(d.c_str());
                }
                current_arr.clear();
                break;
            } case '*': {
                sub_total = 1;
                current_arr.push_back(current_num.c_str());
                for (auto d:current_arr) {
                    // printf("   multiplying %ld by %s\n", sub_total, d.c_str());
                    sub_total *= std::atol(d.c_str());
                }
                current_arr.clear();
                break;
            }
        }

        total += sub_total;
    }
    std::printf("total %lld", total);
}

bool test = 0;
int main(int argc, char* argv[]) {
    auto solve = part2;
    if (not test) {
        std::filesystem::path exec_path = argv[0];
        auto file = std::ifstream(exec_path.parent_path() / "data.txt");
        if (!file.is_open()) std::cerr << "Error opening the file" << std::endl;
        std::vector<std::string> data = parse_file(file);
        solve(data);
    } else {
        std::vector<std::string> data = {
            "123 328  51 64 ",
            " 45 64  387 23 ",
            "  6 98  215 314",
            "*   +   *   +  "};
        solve(data);
    }

    return 0;
}
