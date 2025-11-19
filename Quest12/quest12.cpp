#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <queue>

using namespace std;

namespace quest12 {
    vector<vector<int>> grid;

    static void parseInput(string fileName) {
        ifstream input(fileName);
        if (input.is_open()) {
            string temp;
            while (input >> temp) {
                vector<int> row;
                for (char c : temp) {
                    row.push_back(c - '0');
                }
                grid.push_back(row);
            }
        }
        input.close();
    }

    vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    static void part1() {
        parseInput("input12A.txt");
        queue<pair<int, int>> bfs;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        bfs.push({ 0, 0 });
        int output = 0;
        while (!bfs.empty()) {
            pair<int, int> next = bfs.front();
            bfs.pop();
            if (visited[next.first][next.second]) continue;
            visited[next.first][next.second] = true;
            output++;
            for (pair<int, int> direction : directions) {
                pair<int, int> adjacent = { next.first + direction.first, next.second + direction.second };
                if (adjacent.first < 0 || adjacent.first >= grid.size() || adjacent.second < 0 || adjacent.second >= grid[0].size()) {
                    continue;
                }
                if (grid[adjacent.first][adjacent.second] <= grid[next.first][next.second]) {
                    bfs.push(adjacent);
                }
            }
        }
        cout << output;
    }

    static void part2() {
        parseInput("input12B.txt");
        queue<pair<int, int>> bfs;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        bfs.push({ 0, 0 });
        bfs.push({ grid.size() - 1, grid[0].size() - 1 });
        int output = 0;
        while (!bfs.empty()) {
            pair<int, int> next = bfs.front();
            bfs.pop();
            if (visited[next.first][next.second]) continue;
            visited[next.first][next.second] = true;
            output++;
            for (pair<int, int> direction : directions) {
                pair<int, int> adjacent = { next.first + direction.first, next.second + direction.second };
                if (adjacent.first < 0 || adjacent.first >= grid.size() || adjacent.second < 0 || adjacent.second >= grid[0].size()) {
                    continue;
                }
                if (grid[adjacent.first][adjacent.second] <= grid[next.first][next.second]) {
                    bfs.push(adjacent);
                }
            }
        }
        cout << output;
    }

    int findAdj(int y, int x) {
        vector<vector<int>> newGrid = grid;
        queue<pair<int, int>> bfs;
        vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
        bfs.push({ y, x });
        int output = 0;
        while (!bfs.empty()) {
            pair<int, int> next = bfs.front();
            bfs.pop();
            if (visited[next.first][next.second]) continue;
            visited[next.first][next.second] = true;
            output++;
            for (pair<int, int> direction : directions) {
                pair<int, int> adjacent = { next.first + direction.first, next.second + direction.second };
                if (adjacent.first < 0 || adjacent.first >= grid.size() || adjacent.second < 0 || adjacent.second >= grid[0].size()) {
                    continue;
                }
                if (newGrid[adjacent.first][adjacent.second] == -1) continue;
                if (newGrid[adjacent.first][adjacent.second] <= newGrid[next.first][next.second]) {
                    bfs.push(adjacent);
                }
            }
        }
        return output;
    }


    static void part3() {
        parseInput("input12C.txt");
        int output = 0;
        for (int i = 0; i < 3; i++) {
            int curMax = 0;
            pair<int, int> maxPair;
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[0].size(); x++) {
                    bool possible = true;
                    for (pair<int, int> direction : directions) {
                        pair<int, int> adjacent = { y + direction.first, x + direction.second };
                        if (adjacent.first < 0 || adjacent.first >= grid.size() || adjacent.second < 0 || adjacent.second >= grid[0].size()) {
                            continue;
                        }
                        if (grid[adjacent.first][adjacent.second] > grid[y][x]) {
                            possible = false;
                            break;
                        }
                    }
                    if (!possible) continue;
                    int adj = findAdj(y, x);
                    if (adj > curMax) {
                        curMax = adj;
                        maxPair = { y, x };
                    }
                }
            }
            output += curMax;
            queue<pair<int, int>> bfs;
            bfs.push(maxPair);
            while (!bfs.empty()) {
                pair<int, int> next = bfs.front();
                bfs.pop();
                if (grid[next.first][next.second] == -1) continue;
                for (pair<int, int> direction : directions) {
                    pair<int, int> adjacent = { next.first + direction.first, next.second + direction.second };
                    if (adjacent.first < 0 || adjacent.first >= grid.size() || adjacent.second < 0 || adjacent.second >= grid[0].size()) {
                        continue;
                    }
                    if (grid[adjacent.first][adjacent.second] <= grid[next.first][next.second]) {
                        bfs.push(adjacent);
                    }
                }
                grid[next.first][next.second] = -1;
            }
        }
        cout << output;
    }
}