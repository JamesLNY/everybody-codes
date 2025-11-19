#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

namespace quest4 {
    static void part1() {
        ifstream input("input4A.txt");
        vector<long long> v;
        if (input.is_open()) {
            string temp;
            while (input >> temp) {
                v.push_back(stoi(temp));
            }
        }
        cout << 2025 * v[0] / v[v.size() - 1];
    }

    static void part2() {
        ifstream input("input4B.txt");
        vector<long long> v;
        if (input.is_open()) {
            string temp;
            while (input >> temp) {
                v.push_back(stoi(temp));
            }
        }
        cout << 10000000000000ll * v[v.size() - 1] / v[0] + 1ll;
    }

    static void part3() {
        ifstream input("input4C.txt");
        vector<int> v;
        if (input.is_open()) {
            string temp;
            stringstream inputline;
            while (getline(input, temp)) {
                inputline.str(temp);
                while (getline(inputline, temp, '|')) {
                    v.push_back(stoi(temp));
                }
                inputline.clear();
            }
        }
        long double output = 100;
        for (int i = 0; i < v.size(); i += 2) {
            output *= v[i];
            output /= v[i + 1];
        }
        input.close();
        cout << (long long)floor(output);
    }
}