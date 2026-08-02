#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

static void part1() {
    ifstream input("input3A.txt");
    string inputLine;
    vector<vector<int>> map;
    vector<pair<int, int>> possible = {};
    if (input.is_open()) {
        while (input >> inputLine) {
            vector<int> row;
            for (char c : inputLine) {
                if (c == '#') {
                    row.push_back(1);
                }
                else {
                    row.push_back(0);
                }
            }
            map.push_back(row);
        }
    }
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[0].size(); c++) {
            if (map[r][c] == 1) possible.push_back({r, c});
        }
    }
    input.close();
    int iteration = 2;
    vector<pair<int, int>> adjacencies = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    while (possible.size() > 0) {
        int num = possible.size();
        while (num--) {
            pair<int, int> cell = possible[0];
            possible.erase(possible.begin());
            for (int i = 0; i < 4; i++) {
                if (map[cell.first + adjacencies[i].first][cell.second + adjacencies[i].second] < iteration - 1) {
                    break;
                }
                if (i == 3) {
                    map[cell.first][cell.second] = iteration;
                    possible.push_back({ cell.first, cell.second });
                }
            }
        }
        iteration++;
    }
    int output = 0;
    for (vector<int> row : map) {
        for (int cell : row) {
            output += cell;
        }
    }
    cout << output;
}


static void part2() {
    ifstream input("input3B.txt");
    string inputLine;
    vector<vector<int>> map;
    vector<pair<int, int>> possible = {};
    if (input.is_open()) {
        while (input >> inputLine) {
            vector<int> row;
            for (char c : inputLine) {
                if (c == '#') {
                    row.push_back(1);
                }
                else {
                    row.push_back(0);
                }
            }
            map.push_back(row);
        }
    }
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[0].size(); c++) {
            if (map[r][c] == 1) possible.push_back({ r, c });
        }
    }
    input.close();
    int iteration = 2;
    vector<pair<int, int>> adjacencies = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    while (possible.size() > 0) {
        int num = possible.size();
        while (num--) {
            pair<int, int> cell = possible[0];
            possible.erase(possible.begin());
            for (int i = 0; i < 4; i++) {
                if (map[cell.first + adjacencies[i].first][cell.second + adjacencies[i].second] < iteration - 1) {
                    break;
                }
                if (i == 3) {
                    map[cell.first][cell.second] = iteration;
                    possible.push_back({ cell.first, cell.second });
                }
            }
        }
        iteration++;
    }
    int output = 0;
    for (vector<int> row : map) {
        for (int cell : row) {
            output += cell;
        }
    }
    cout << output;
}


static void part3() {
    ifstream input("input3C.txt");
    string inputLine;
    vector<vector<int>> map;
    vector<pair<int, int>> possible = {};
    if (input.is_open()) {
        while (input >> inputLine) {
            vector<int> row;
            for (char c : inputLine) {
                if (c == '#') {
                    row.push_back(1);
                }
                else {
                    row.push_back(0);
                }
            }
            map.push_back(row);
        }
    }
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < map[0].size(); c++) {
            if (map[r][c] == 1) possible.push_back({ r, c });
        }
    }
    input.close();
    int iteration = 2;
    vector<pair<int, int>> adjacencies = { {1, 0}, { -1, 0 }, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
    while (possible.size() > 0) {
        int num = possible.size();
        while (num--) {
            pair<int, int> cell = possible[0];
            possible.erase(possible.begin());
            for (int i = 0; i < adjacencies.size(); i++) {
                if (cell.first + adjacencies[i].first < 0 || cell.first + adjacencies[i].first >= map.size() ||
                    cell.second + adjacencies[i].second < 0 || cell.second + adjacencies[i].second >= map[0].size()) {
                    break;
                }
                if (map[cell.first + adjacencies[i].first][cell.second + adjacencies[i].second] < iteration - 1) {
                    break;
                }
                if (i == adjacencies.size() - 1) {
                    map[cell.first][cell.second] = iteration;
                    possible.push_back({ cell.first, cell.second });
                }
            }
        }
        iteration++;
    }
    int output = 0;
    for (vector<int> row : map) {
        for (int cell : row) {
            output += cell;
        }
    }
    cout << output;
}

int main() {
    part3();
}