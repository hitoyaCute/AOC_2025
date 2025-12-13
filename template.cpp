#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <filesystem>

template<typename printable>void printarray(std::vector<printable>&a){for(auto i:a){std::cout<<i<<std::endl;}}
std::vector<std::string>split(const std::string&s,const char d=0){std::vector<std::string>o;std::string t;if(s.empty()){return o;}for(const char c:s){if(d==0){o.push_back(std::string(c,1));}else if(c==d and t.length()!=0){o.push_back(t);t.clear();}else if(c!=d){t+=c;}}t.empty()?(void)0:o.push_back(t);return o;}
std::vector<std::string>parse_file(std::ifstream&f){std::vector<std::string>o;std::string l;while(std::getline(f,l)){if(l.empty())continue;o.push_back(l);}return o;}




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
