#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

static vector<vector<int>> map;
static pair<int, int> center, start;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (input >> temp) {
            vector<int> row;
            for (int i = 0; i < temp.size(); i++) {
                char c = temp[i];
                if (c == '@') {
                    row.push_back(0);
                    center = { i, map.size() };
                }
                else if (c == 'S') {
                    row.push_back(0);
                    start = { i, map.size() };
                }
                else {
                    row.push_back(c - '0');
                }
            }
            map.push_back(row);
        }
    }
    input.close();
}

static void part1() {
    parseInput("input17A.txt");
    int R = 10, output = 0;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (pow(x - center.first, 2) + pow(y - center.second, 2) <= pow(R, 2)) {
                output += map[y][x];
            }
        }
    }
    cout << output;
}

static vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

static void part2() {
    parseInput("input17B.txt");
    queue<pair<int, int>> possible;
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    possible.push(center);
    int R = 0, currMax = 0, output = 0;;
    while (R <= map.size() / 2) {
        int num = possible.size();
        int curr = 0;
        while (num--) {
            pair<int, int> coords = possible.front();
            possible.pop();
            int x = coords.first, y = coords.second;
            if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size()) continue;
            if (pow(x - center.first, 2) + pow(y - center.second, 2) > pow(R, 2)) {
                possible.push(coords);
                continue;
            }
            if (visited[y][x]) continue;
            visited[y][x] = true;
            curr += map[y][x];
            for (pair<int, int> direction : directions) {
                possible.push({ x + direction.first, y + direction.second });
            }
        }
        if (curr > currMax) {
            currMax = curr;
            output = R * currMax;
        }
        R++;
    }
    cout << output;
}

static vector<pair<int, int>> newDirections = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

static int dijkstra(int R) {
    R--;
    vector<vector<int>> distances(map.size(), vector<int>(map[0].size(), numeric_limits<int>::max()));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;
    q.push({ 0, start });
    while (!q.empty()) {
        int dist = q.top().first;
        pair<int, int> coord = q.top().second;
        q.pop();

        if (coord.second < 0 || coord.second >= map.size() || coord.first < 0 || coord.first >= map[0].size()) continue;

        if ((coord.first - center.first) * (coord.first - center.first) + (coord.second - center.second) * (coord.second - center.second) <= R * R) continue;

        if (distances[coord.second][coord.first] <= map[coord.second][coord.first] + dist) continue;
        distances[coord.second][coord.first] = dist + map[coord.second][coord.first];

        for (pair<int, int> direction : newDirections) {
            pair<int, int> next = { coord.first + direction.first, coord.second + direction.second };
            if (next.second < 0 || next.second >= map.size() || next.first < 0 || next.first >= map[0].size()) continue;
            if (next.second > center.second && next.first == center.first && direction.first == -1) continue;
            q.push({ distances[coord.second][coord.first], next });
        }
    }
    vector<vector<int>> distancesRight(map.size(), vector<int>(map[0].size(), numeric_limits<int>::max()));
    q.push({ 0, start });
    while (!q.empty()) {
        int dist = q.top().first;
        pair<int, int> coord = q.top().second;
        q.pop();

        if ((coord.first - center.first) * (coord.first - center.first) + (coord.second - center.second) * (coord.second - center.second) <= R * R) continue;

        if (distancesRight[coord.second][coord.first] <= map[coord.second][coord.first] + dist) continue;
        distancesRight[coord.second][coord.first] = dist + map[coord.second][coord.first];

        for (pair<int, int> direction : newDirections) {
            pair<int, int> next = { coord.first + direction.first, coord.second + direction.second };
            if (next.second < 0 || next.second >= map.size() || next.first < 0 || next.first >= map[0].size()) continue;
            if (next.second > center.second && next.first == center.first && direction.first == 1) continue;
            q.push({ distancesRight[coord.second][coord.first], next });
        }
    }
    int min = numeric_limits<int>::max();
    for (int y = center.second + R + 1; y < distances.size(); y++) {
        if (distancesRight[y][center.first] + distances[y][center.first] - map[y][center.first] < min) {
            min = distancesRight[y][center.first] + distances[y][center.first] - map[y][center.first];
        }
    }
    return min;
}

static void part3() {
    parseInput("input17C.txt");
    int minVal = numeric_limits<int>::max(), minIndex = numeric_limits<int>::max();
    for (int i = map.size() / 2 - start.second; i > 0; i--) {
        int result = dijkstra(i);
        if (result < 0) continue;
        if (result >= i * 30) continue;
        if (result < minVal) {
            minVal = result;
            minIndex = i;
        }
    }
    cout << minVal * (minIndex - 1);
}