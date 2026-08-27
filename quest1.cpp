#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

static void part1() {
    ifstream input("input1A.txt");
    string temp = "";
    int sum = 0;
    if (input.is_open()) {
        while (input >> temp) {
            int index = 0;
            unordered_set<int> visited = { 0 };
            stringstream ss(temp);
            while (getline(ss, temp, ',')) {
                int length = stoi(temp);
                if (length < index && !visited.count(index - length)) {
                    index -= length;
                    visited.insert(index);
                }
                else {
                    index += length;
                    visited.insert(index);
                }
            }
            sum += index;
        }
    }
    input.close();
    cout << sum;
}

static void part2() {
}

static void part3() {
}

int main() {
    part1();
}