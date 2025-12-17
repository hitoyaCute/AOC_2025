#include <algorithm>
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

// connectedSet
// a set of set, when inserting new elements, it merges to existing set if they are connected
// else it creates a new set
template<typename T>
struct connectedSet {
    std::vector<std::vector<T>> sets{};

    constexpr connectedSet(): sets() {}
    connectedSet(const connectedSet& other): sets(other.sets) {}
    connectedSet& operator=(const connectedSet& other) = default;

    // check if two elements are connected
    bool is_connected(const T& a, const T& b) {
        // example connection: if the difference between a and b is less than 3
        return std::abs(a - b) <= 3;
    }

    void insert(const T& element) {
        std::vector<int> connected_indices;
        for (size_t i = 0; i < sets.size(); ++i) {
            for (const auto& item : sets[i]) {
                if (is_connected(item, element)) {
                    connected_indices.push_back(i);
                    break;
                }
            }
        }

        if (connected_indices.empty()) {
            sets.push_back({element});
        } else {
            std::vector<T> new_set = {element};
            for (int index : connected_indices) {
                new_set.insert(new_set.end(), sets[index].begin(), sets[index].end());
            }
            // Remove merged sets
            for (int i = connected_indices.size() - 1; i >= 0; --i) {
                sets.erase(sets.begin() + connected_indices[i]);
            }
            sets.push_back(new_set);
        }
    }

    size_t size() const {
        return sets.size();
    }
};



// solution on https://adventofcode.com/2025/day/8
void part1(std::vector<std::string>& data) {

    connectedSet<std::tuple<int,int,int>> Nset;
    std::vector<std::tuple<int,int,int>> points;

    constexpr int allocated_wires = 10; // 10 for sample data, 1000 for real data
    // parse input
    for (const auto& line : data) {
        auto parts = split(line, ',');
        int x = std::stoi(parts[0]);
        int y = std::stoi(parts[1]);
        int z = std::stoi(parts[2]);
        points.emplace_back(x, y, z);
    }
    // sort the points for faster processing
    std::sort(points.begin(), points.end()); 

    // consume the allocated_wires
    for (int i{allocated_wires}; i>0; --i) {
        // search for 2 closest points
        // but since we sorted the points, we can just check the next points
    }
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
            "162,817,812",
            "57,618,57",
            "906,360,560",
            "592,479,940",
            "352,342,300",
            "466,668,158",
            "542,29,236",
            "431,825,988",
            "739,650,466",
            "52,470,668",
            "216,146,977",
            "819,987,18",
            "117,168,530",
            "805,96,715",
            "346,949,466",
            "970,615,88",
            "941,993,340",
            "862,61,35",
            "984,92,344",
            "425,690,689",};
        solve(data);
    }
    return 0;
}



