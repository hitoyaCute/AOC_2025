#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
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
        output.push_back(line);
    }
    return output;
}

std::string optimize_bank(std::string bank, int size=12) {
    if (size == 0) return "";
    if (auto max = std::max_element(bank.begin(), bank.end() - size + 1); max != bank.end() - size + 1)  {
        // std::clog << "max: " << *max << '\n';
     
        auto index = max - bank.begin();
        return std::string{*max} + optimize_bank(
            bank.substr(
                index + 1,
                bank.length() - index + 1
            ), size-1);
    }
    return "";
}

void part2(std::vector<std::string> data){
    unsigned long long total = 0;
    for (auto bank : data) {
        std::string d = optimize_bank(bank);
        // std::cout << bank << " '" << d << "' int:" << std::atoll(d.c_str()) << std::endl;
        total += std::atoll(d.c_str());
    }
    std::cout << total << std::endl;
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
        std::vector<std::string> data = {"987654321111111","811111111111119","234234234234278","818181911112111"};
        part2(data);
    }

    return 0;
}


