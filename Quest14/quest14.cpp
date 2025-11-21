#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

namespace quest14 {
    vector<vector<bool>> grid;

    static void parseInput(string fileName) {
        ifstream input(fileName);
        if (input.is_open()) {
            string temp;
            while (input >> temp) {
                vector<bool> row;
                for (char c : temp) {
                    row.push_back(c == '#');
                }
                grid.push_back(row);
            }
        }
        input.close();
    }

    vector<pair<int, int>> diagonals = { {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

    static void part1() {
        parseInput("input14A.txt");
        int output = 0;
        for (int i = 0; i < 10; i++) {
            int numActive = 0;
            vector<vector<bool>> newGrid = grid;
            for (int row = 0; row < grid.size(); row++) {
                for (int col = 0; col < grid[0].size(); col++) {
                    int activeDiagonals = 0;
                    for (pair<int, int> diagonal : diagonals) {
                        pair<int, int> newTile = { diagonal.first + row, diagonal.second + col };
                        if (newTile.first < 0 || newTile.first >= grid.size() ||
                            newTile.second < 0 || newTile.second >= grid[0].size()) continue;
                        if (grid[newTile.first][newTile.second]) activeDiagonals++;
                    }
                    newGrid[row][col] = activeDiagonals % 2 == grid[row][col];
                    if (newGrid[row][col]) numActive++;
                }
            }
            grid = newGrid;
            output += numActive;
        }
        cout << output;
    }

    static void part2() {
        parseInput("input14B.txt");
        long long output = 0;
        for (int i = 0; i < 2025; i++) {
            int numActive = 0;
            vector<vector<bool>> newGrid = grid;
            for (int row = 0; row < grid.size(); row++) {
                for (int col = 0; col < grid[0].size(); col++) {
                    int activeDiagonals = 0;
                    for (pair<int, int> diagonal : diagonals) {
                        pair<int, int> newTile = { diagonal.first + row, diagonal.second + col };
                        if (newTile.first < 0 || newTile.first >= grid.size() ||
                            newTile.second < 0 || newTile.second >= grid[0].size()) continue;
                        if (grid[newTile.first][newTile.second]) activeDiagonals++;
                    }
                    newGrid[row][col] = activeDiagonals % 2 == grid[row][col];
                    if (newGrid[row][col]) numActive++;
                }
            }
            grid = newGrid;
            output += numActive;
        }
        cout << output;
    }

    static void part3() {
        parseInput("input14C.txt");
        set<vector<vector<bool>>> cache;
        vector<pair<int, int>> indices;
        vector<vector<bool>> bigGrid(34, vector<bool>(34, false));
        long long output = 0, index = 0;
        for (int i = 0; i < 1000000000; i++) {
            int numActive = 0;
            vector<vector<bool>> newGrid = bigGrid;
            for (int row = 0; row < bigGrid.size(); row++) {
                for (int col = 0; col < bigGrid[0].size(); col++) {
                    int activeDiagonals = 0;
                    for (pair<int, int> diagonal : diagonals) {
                        pair<int, int> newTile = { diagonal.first + row, diagonal.second + col };
                        if (newTile.first < 0 || newTile.first >= bigGrid.size() ||
                            newTile.second < 0 || newTile.second >= bigGrid[0].size()) continue;
                        if (bigGrid[newTile.first][newTile.second]) activeDiagonals++;
                    }
                    newGrid[row][col] = activeDiagonals % 2 == bigGrid[row][col];
                    if (newGrid[row][col]) numActive++;
                }
            }
            bigGrid = newGrid;
            bool exit = false;
            for (int row = 13; row < 20; row++) {
                for (int col = 13; col < 20; col++) {
                    if (bigGrid[row][col] != grid[row - 13][col - 13]) exit = true;
                    if (exit) break;
                }
                if (exit) break;
            }
            if (exit) continue;
            indices.push_back({ i, numActive });
            if (cache.count(bigGrid)) {
                index = i;
                break;
            }
            cache.insert(bigGrid);
            output += numActive;
        }
        long long newOutput = output;
        int cycle = index - indices[0].first;
        while (index + cycle < 1000000000) {
            newOutput += output;
            index += cycle;
        }
        for (int i = indices.size() - 1; i > 0; i--) {
            indices[i].first -= indices[i - 1].first;
        }
        indices[0].first = 0;
        for (pair<int, int> i : indices) {
            index += i.first;
            if (index >= 1000000000) break;
            newOutput += i.second;
        }
        cout << newOutput;
    }
}