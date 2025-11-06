#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <numeric>
#include <sstream>
#include <map>

using namespace std;

static void part1() {
    ifstream input("input3A.txt");
    set<int> sizes;
    if (input.is_open()) {
        string temp;
        while (getline(input, temp, ',')) {
            sizes.insert(stoi(temp));
        }
    }
    input.close();
    cout << accumulate(sizes.begin(), sizes.end(), 0);
}

static void part2() {
    ifstream input("input3B.txt");
    set<int> sizes;
    if (input.is_open()) {
        string temp;
        while (getline(input, temp, ',')) {
            sizes.insert(stoi(temp));
        }
    }
    input.close();
    int output = 0;
    for (auto it = sizes.begin(); it != next(sizes.begin(), 20); it++) {
        output += *it;
    }
    cout << output;
}

static void part3() {
    ifstream input("input3C.txt");
    map<int, int> sizes;
    if (input.is_open()) {
        string temp;
        while (getline(input, temp, ',')) {
            if (sizes.count(stoi(temp))) {
                sizes[stoi(temp)]++;
            }
            else {
                sizes[stoi(temp)] = 1;
            }
        }
    }
    input.close();
    int output = 0;
    for (auto it = sizes.begin(); it != sizes.end(); it++) {
        output = max(output, it->second);
    }
    cout << output;
}