#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <array>

using namespace std;

static vector<vector<char>> triangles;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (input >> temp) {
            triangles.push_back(vector<char>(temp.begin(), temp.end()));
        }
    }
    input.close();
}

static void part1() {
    int output = 0;
    parseInput("input20A.txt");
    for (int i = 0; i < triangles.size(); i++) {
        for (int j = 0; j < triangles[0].size(); j++) {
            if (triangles[i][j] == '.' || triangles[i][j] == '#') continue;
            if (j < triangles[0].size() - 1 && triangles[i][j + 1] == 'T') output++;
            if (i < triangles.size() - 1 && (j - i) % 2 == 1 && triangles[i + 1][j] == 'T') output++;
        }
    }
    cout << output;
}

struct node {
    int x;
    int y;
    int dist;
    int rotation;
    node(int xi, int yi, int disti) {
        x = xi;
        y = yi;
        dist = disti;
        rotation = 0;
    }
    node(int xi, int yi, int disti, int rotationi) {
        node(xi, yi, disti);
        rotation = rotationi;
    }
};

static void part2() {
    parseInput("input20B.txt");
    queue<node> bfs;
    bfs.push(node(triangles[0].size() / 2, triangles.size() - 1, 0));
    vector<vector<bool>> visited(triangles.size(), vector<bool>(triangles[0].size(), false));
    while (!bfs.empty()) {
        node curr = bfs.front();
        bfs.pop();
        if (curr.x < 0 || curr.x >= triangles[0].size() || curr.y < 0 || curr.y >= triangles.size()) continue;
        if (triangles[curr.y][curr.x] == '.' || triangles[curr.y][curr.x] == '#') continue;
        if (visited[curr.y][curr.x]) continue;
        visited[curr.y][curr.x] = true;
        if (triangles[curr.y][curr.x] == 'E') {
            cout << curr.dist;
            break;
        }
        if ((curr.x - curr.y) % 2 == 0) {
            bfs.push(node(curr.x, curr.y - 1, curr.dist + 1));
        }
        if ((curr.x - curr.y) % 2 == 1) {
            bfs.push(node(curr.x, curr.y + 1, curr.dist + 1));
        }
        bfs.push(node(curr.x - 1, curr.y, curr.dist + 1));
        bfs.push(node(curr.x + 1, curr.y, curr.dist + 1));
    }
}

static void rotateEdge(vector<vector<char>>& map, pair<int, int> start) {
    // start: x, y
    int dist = map[0].size() - start.first * 2 - 1;
    queue<char> order;
    for (int d = 0; d < dist; d++) {
        order.push(map[start.second][start.first]);
        start.first++;
    }
    pair<int, int> newStart = start;
    for (int d = 0; d < dist; d++) {
        order.push(map[start.second][start.first]);
        d % 2 == 0 ? start.first-- : start.second++;
    }
    for (int d = 0; d < dist; d++) {
        order.push(map[start.second][start.first]);
        d % 2 == 0 ? start.second-- : start.first--;
    }
    order.push(map[start.second][start.first]);
    start = newStart;
    for (int d = 0; d < dist; d++) {
        map[start.second][start.first] = order.front();
        order.pop();
        d % 2 == 0 ? start.first-- : start.second++;
    }
    for (int d = 0; d < dist; d++) {
        map[start.second][start.first] = order.front();
        order.pop();
        d % 2 == 0 ? start.second-- : start.first--;
    }
    for (int d = 0; d < dist; d++) {
        map[start.second][start.first] = order.front();
        order.pop();
        start.first++;
    }
    map[start.second][start.first] = order.front();
}

static void rotateTriangle(vector<vector<char>>& triangle) {
    pair<int, int> coord = { 0, 0 };
    while (coord.first < triangles[0].size() / 2) {
        rotateEdge(triangles, coord);
        coord.first += 3;
        coord.second += 1;
    }
}

static void part3() {
    parseInput("input20C.txt");

    queue<node> bfs;
    bfs.push(node(triangles[0].size() / 2, triangles.size() - 1, 0));

    map<array<int, 3>, bool> visited;

    int currIter = 0;
    while (!bfs.empty()) {
        node curr = bfs.front();
        bfs.pop();
        if (curr.dist > currIter) {
            currIter++;
            rotateTriangle(triangles);
        }
        if (curr.x < 0 || curr.x >= triangles[0].size() || curr.y < 0 || curr.y >= triangles.size()) continue;
        if (triangles[curr.y][curr.x] == '.' || triangles[curr.y][curr.x] == '#') continue;

        if (visited.count({ curr.dist % 3, curr.y, curr.x })) continue;
        visited[{curr.dist % 3, curr.y, curr.x }] = true;

        if (triangles[curr.y][curr.x] == 'E') {
            cout << curr.dist;
            break;
        }

        if ((curr.x - curr.y) % 2 == 0) {
            bfs.push(node(curr.x, curr.y - 1, curr.dist + 1));
        }
        if ((curr.x - curr.y) % 2 == 1) {
            bfs.push(node(curr.x, curr.y + 1, curr.dist + 1));
        }

        bfs.push(node(curr.x - 1, curr.y, curr.dist + 1));
        bfs.push(node(curr.x + 1, curr.y, curr.dist + 1));
        bfs.push(node(curr.x, curr.y, curr.dist + 1));
    }
}