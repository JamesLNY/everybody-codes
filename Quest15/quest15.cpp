#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

static bool grid[1001][1001];
static bool visited[1001][1001];
static vector<pair<char, int>> instructions;
static vector<pair<int, int>> directions = { {0, -1}, {1, 0}, {0, 1}, {-1,0} };

struct node {
    int x;
    int y;
    int dist;
    node(int xInitial, int yInitial, int distInitial) {
        x = xInitial;
        y = yInitial;
        dist = distInitial;
    }
};

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        input >> temp;
        stringstream ss(temp);
        while (getline(ss, temp, ',')) {
            instructions.push_back({ temp[0], stoi(temp.substr(1)) });
        }
    }
    input.close();
}

static void part1() {
    parseInput("input15A.txt");
    int x = size(grid[0]) / 2, y = size(grid) / 2;
    int dir = 0;
    for (pair<char, int> instruction : instructions) {
        instruction.first == 'L' ? dir-- : dir++;
        dir = (dir + 4) % 4;
        for (int i = 0; i < instruction.second; i++) {
            x += directions[dir].first;
            y += directions[dir].second;
            grid[y][x] = true;
        }
    }
    queue<node> bfs;
    bfs.push(node(size(grid[0]) / 2, size(grid) / 2, 0));
    while (!bfs.empty()) {
        node next = bfs.front();
        bfs.pop();

        if (next.x == x && next.y == y) {
            cout << next.dist;
            break;
        }

        if (next.x < 0 || next.x >= size(grid[0]) || next.y < 0 || next.y >= size(grid)) continue;
        if (grid[next.y][next.x]) continue;

        if (visited[next.y][next.x]) continue;
        visited[next.y][next.x] = true;

        for (pair<int, int> direction : directions) {
            bfs.push(node(direction.first + next.x, direction.second + next.y, next.dist + 1));
        }
    }
}

static void part2() {
    parseInput("input15B.txt");
    int x = size(grid[0]) / 2, y = size(grid) / 2;
    int dir = 0;
    for (pair<char, int> instruction : instructions) {
        instruction.first == 'L' ? dir-- : dir++;
        dir = (dir + 4) % 4;
        for (int i = 0; i < instruction.second; i++) {
            x += directions[dir].first;
            y += directions[dir].second;
            grid[y][x] = true;
        }
    }
    queue<node> bfs;
    bfs.push(node(size(grid[0]) / 2, size(grid) / 2, 0));
    while (!bfs.empty()) {
        node next = bfs.front();
        bfs.pop();

        if (next.x == x && next.y == y) {
            cout << next.dist;
            break;
        }

        if (next.x < 0 || next.x >= size(grid[0]) || next.y < 0 || next.y >= size(grid)) continue;
        if (grid[next.y][next.x]) continue;

        if (visited[next.y][next.x]) continue;
        visited[next.y][next.x] = true;        

        for (pair<int, int> direction : directions) {
            bfs.push(node(direction.first + next.x, direction.second + next.y, next.dist + 1));
        }
    }
}

struct point {
    int x;
    int y;
    point(int xi, int yi) {
        x = xi;
        y = yi;
    }
};

static void part3() {
    parseInput("input15C.txt");
    point cur(0, 0);
    set<int> ix = { -1, 0, -1 }, iy = { -1, 0, -1 };

    int dir = 0;
    for (int i = 0; i < instructions.size(); i++) {
        pair<char, int> instruction = instructions[i];
        instruction.first == 'L' ? dir-- : dir++;
        dir = (dir + 4) % 4;
        cur.x += instruction.second * directions[dir].first;
        cur.y += instruction.second * directions[dir].second;
        ix.insert({ cur.x - 1, cur.x, cur.x + 1 });
        iy.insert({ cur.y - 1, cur.y, cur.y + 1 });
    }

    map<int, int> toC, fromC, toR, fromR;
    int index = 0;
    for (int x : ix) {
        fromC[x] = index;
        toC[index] = x;
        index++;
    }
    index = 0;
    for (int y : iy) {
        fromR[y] = index;
        toR[index] = y;
        index++;
    }

    set<pair<int, int>> walls;

    point prev(0, 0);
    cur = point(0, 0);
    dir = 0;

    for (int i = 0; i < instructions.size(); i++) {
        pair<char, int> instruction = instructions[i];
        instruction.first == 'L' ? dir-- : dir++;
        dir = (dir + 4) % 4;

        cur.x += directions[dir].first * instruction.second;
        cur.y += directions[dir].second * instruction.second;

        int xi = fromC[prev.x], xf = fromC[cur.x], yi = fromR[prev.y], yf = fromR[cur.y];
        for (int x = min(xi, xf); x <= max(xi, xf); x++) {
            for (int y = min(yi, yf); y <= max(yi, yf); y++) walls.insert({ x, y });
        }

        prev = cur;
    }

    walls.erase(pair<int, int> { fromC[0], fromR[0] });
    walls.erase(pair<int, int> { fromC[cur.x], fromR[cur.y] });

    int indexX = 0, indexY = 0;
    point final(fromC[cur.x], fromR[cur.y]);

    queue<node> bfs;
    set<pair<int, int>> visited;

    bfs.push(node(fromC[0], fromR[0], 0));

    while (!bfs.empty()) {
        node next = bfs.front();
        bfs.pop();

        if (next.x == final.x && next.y == final.y) {
            cout << next.dist;
            break;
        }

        if (next.x < 0 || next.x > ix.size() || next.y < 0 || next.y > iy.size()) continue;

        if (walls.count({ next.x, next.y })) continue;
        if (visited.count({ next.x, next.y })) continue;
        visited.insert({ next.x, next.y });

        for (pair<int, int> direction : directions) {
            int newX = direction.first + next.x;
            int newY = direction.second + next.y;
            int newDist = next.dist + abs(toC[newX] - toC[next.x]) + abs(toR[newY] - toR[next.y]);
            bfs.push(node(newX, newY, newDist));
        }
    }
}