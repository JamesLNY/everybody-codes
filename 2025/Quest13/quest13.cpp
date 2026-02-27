#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <sstream>

using namespace std;

static void part1() {
    deque<int> wheel = { 1 };
    ifstream input("input13A.txt");
    if (input.is_open()) {
        int temp;
        bool right = true;
        while (input >> temp) {
            if (right) {
                wheel.push_back(temp);
            }
            else {
                wheel.push_front(temp);
            }
            right = !right;
        }
    }
    int top = (wheel.size() - 1) / 2;
    int index = (top + 2025) % wheel.size();
    cout << wheel[index];
}

static void part2() {
    deque<int> wheel = { 1 };
    ifstream input("input13B.txt");
    if (input.is_open()) {
        string temp;
        stringstream ss;
        bool right = true;
        while (input >> temp) {
            ss.clear();
            ss.str(temp);
            getline(ss, temp, '-');
            int start = stoi(temp);
            getline(ss, temp, '-');
            int end = stoi(temp);
            if (right) {
                for (int i = start; i <= end; i++) {
                    wheel.push_back(i);
                }
            }
            else {
                for (int i = start; i <= end; i++) {
                    wheel.push_front(i);
                }
            }
            right = !right;
        }
    }
    int top = find(wheel.begin(), wheel.end(), 1) - wheel.begin();
    int index = (top + 20252025) % wheel.size();
    cout << wheel[index];
}

static void part3() {
    // start, size
    deque<pair<int, int>> wheel = { {1, 1} };
    long long top = 0;
    long long size = 1;
    ifstream input("input13C.txt");
    if (input.is_open()) {
        string temp;
        stringstream ss;
        bool right = true;
        while (input >> temp) {
            ss.clear();
            ss.str(temp);
            getline(ss, temp, '-');
            int start = stoi(temp);
            getline(ss, temp, '-');
            int end = stoi(temp);
            if (right) {
                wheel.push_back({ start, end - start + 1 });
            }
            else {
                top += 1;
                wheel.push_front({ end, end - start + 1 });
            }
            size += end - start + 1;
            right = !right;
        }
    }
    long long change = 202520252025ll % size;
    for (int i = 0; i < wheel.size(); i++) {
        int index = (top + i) % wheel.size();
        pair<int, int> cog = wheel[index];
        if (cog.second >= change) {
            if (index < top) {
                cout << cog.first - change;
            }
            else {
                cout << cog.first + change;
            }
            break;
        }
        else {
            change -= cog.second;
        }
    }
}