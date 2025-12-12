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


void part1(std::vector<std::string>& data) {

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
        std::vector<std::string> data = {};
        solve(data);
    }

    return 0;
}
