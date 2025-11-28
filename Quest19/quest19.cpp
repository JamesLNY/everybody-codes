#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <queue>

using namespace std;

static map<int, vector<pair<int, int>>> m;
static int maxHeight = 0;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (input >> temp) {
            int key;
            pair<int, int> val;
            stringstream ss(temp);
            getline(ss, temp, ',');
            key = stoi(temp);
            getline(ss, temp, ',');
            val.first = stoi(temp);
            getline(ss, temp, ',');
            val.second = val.first + stoi(temp) - 1;
            if (m.count(key)) {
                m[key].push_back(val);
            }
            else {
                m[key] = { val };
            }
            maxHeight = max(maxHeight, val.second);
        }
    }
    input.close();
}

struct bird {
    int y, x, numFlaps;
    bird(int xi, int yi, int numFlapsi) {
        y = yi;
        x = xi;
        numFlaps = numFlapsi;
    }
};

static void part1() {
    parseInput("input19A.txt");
    queue<bird> bfs;
    bfs.push(bird(0, 0, 0));
    int maxWidth = m.rbegin()->first;
    int output = numeric_limits<int>::max();
    map<pair<int, int>, int> cache;
    while (!bfs.empty()) {
        bird b = bfs.front();
        bfs.pop();
        if (b.y > maxHeight + 2 || b.y < 0) continue;
        if (cache.count({ b.x, b.y }) && cache[{b.x, b.y}] <= b.numFlaps) continue;
        cache[{b.x, b.y}] = b.numFlaps;
        if (m.count(b.x)) {
            bool collide = true;
            for (pair<int, int> wall : m[b.x]) {
                if (b.y >= wall.first && b.y <= wall.second) collide = false;
            }
            if (collide) continue;
        }
        if (b.x == maxWidth) {
            output = min(output, b.numFlaps);
            continue;
        }
        bfs.push(bird(b.x + 1, b.y + 1, b.numFlaps + 1));
        bfs.push(bird(b.x + 1, b.y - 1, b.numFlaps));
    }
    cout << output;
}

static void part2() {
    parseInput("input19B.txt");
    queue<bird> bfs;
    bfs.push(bird(0, 0, 0));
    int maxWidth = m.rbegin()->first;
    int output = numeric_limits<int>::max();
    map<pair<int, int>, int> cache;
    while (!bfs.empty()) {
        bird b = bfs.front();
        bfs.pop();
        if (b.y > maxHeight + 2 || b.y < 0) continue;
        if (cache.count({ b.x, b.y }) && cache[{b.x, b.y}] <= b.numFlaps) continue;
        cache[{b.x, b.y}] = b.numFlaps;
        if (m.count(b.x)) {
            bool collide = true;
            for (pair<int, int> opening : m[b.x]) {
                if (b.y >= opening.first && b.y <= opening.second) collide = false;
            }
            if (collide) continue;
        }
        if (b.x == maxWidth) {
            output = min(output, b.numFlaps);
            continue;
        }
        bfs.push(bird(b.x + 1, b.y + 1, b.numFlaps + 1));
        bfs.push(bird(b.x + 1, b.y - 1, b.numFlaps));
    }
    cout << output;
}

static void part3() {
    parseInput("input19C.txt");
    queue<bird> bfs;
    bfs.push(bird(0, 0, 0));
    int maxWidth = m.rbegin()->first;
    vector<pair<int, long long>> prevCol = { { 0, 0 } };
    int prevk = 0;
    for (auto it = m.begin(); it != m.end(); it++) {
        int k = it->first;
        vector<pair<int, long long>> newCol;
        for (pair<int, int> opening : m[k]) {
            for (int y = opening.first; y <= opening.second; y++) {
                long long minCost = numeric_limits<long long>::max();
                for (pair<int, int> coord : prevCol) {
                    int dist = k - prevk;
                    long long cost = coord.second;
                    if (y > coord.first) cost += y - coord.first;
                    dist -= abs(y - coord.first);
                    if (dist < 0) continue;
                    if (dist % 2 == 1) continue;
                    cost += dist / 2;
                    minCost = min(minCost, cost);
                }
                if (minCost == numeric_limits<long long>::max()) continue;
                newCol.push_back({ y, minCost });
            }
        }
        prevk = k;
        prevCol = newCol;
    }
    long long output = numeric_limits<long long>::max();
    for (pair<int, long long> p : prevCol) {
        output = min(output, p.second);
    }
    cout << output;
}