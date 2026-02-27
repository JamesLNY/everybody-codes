#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

static vector<vector<char>> chessboard;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (input >> temp) {
            chessboard.push_back(vector<char>(temp.begin(), temp.end()));
        }
    }
    input.close();
}

static void part1() {
    parseInput("input10A.txt");
    // row, col, numMoves;
    queue<pair<pair<int, int>, int>> bfs;
    for (int row = 0; row < chessboard.size(); row++) {
        for (int col = 0; col < chessboard[0].size(); col++) {
            if (chessboard[row][col] == 'D') {
                chessboard[row][col] = '.';
                bfs.push({ { row, col }, 0 });
            }
        }
    }
    vector<vector<bool>> visited(chessboard.size(), vector<bool>(chessboard[0].size(), false));
    vector<pair<int, int>> directions = { {1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };
    int output = 0;
    while (!bfs.empty()) {
        pair<pair<int, int>, int> next = bfs.front();
        bfs.pop();
        if (next.first.first < 0 || next.first.first >= chessboard.size() ||
            next.first.second < 0 || next.first.second >= chessboard[0].size()) continue;
        if (visited[next.first.first][next.first.second]) continue;
        if (next.second > 4) continue;
        visited[next.first.first][next.first.second] = true;
        if (chessboard[next.first.first][next.first.second] == 'S') {
            output++;
        }

        for (pair<int, int> direction : directions) {
            bfs.push({ {next.first.first + direction.first, next.first.second + direction.second}, next.second + 1 });
        }
    }
    cout << output;
}

// P = Safe Sheep

static set<pair<int, int>> sheep;

static void passRound() {
    set<pair<int, int>> newSheep;
    for (pair<int, int> p : sheep) {
        if (p.first + 1 < chessboard.size()) newSheep.insert({ p.first + 1, p.second });
    }
    sheep = newSheep;
}

static void part2() {
    parseInput("input10B.txt");
    // row, col;
    pair<int, int> dragonStart;
    for (int row = 0; row < chessboard.size(); row++) {
        for (int col = 0; col < chessboard[0].size(); col++) {
            if (chessboard[row][col] == 'D') {
                dragonStart = { row, col };
                chessboard[row][col] = '.';
            }
            else if (chessboard[row][col] == 'S') {
                sheep.insert({ row, col });
            }
        }
    }
    queue<pair<int, int>> bfs;
    bfs.push(dragonStart);
    vector<pair<int, int>> directions = { {1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };
    int output = 0;
    for (int i = 0; i < 21; i++) {
        int numPossible = bfs.size();
        vector<vector<bool>> visited(chessboard.size(), vector<bool>(chessboard[0].size(), false));
        while (numPossible--) {
            pair<int, int> next = bfs.front();
            bfs.pop();
            if (visited[next.first][next.second]) continue;
            visited[next.first][next.second] = true;
            if (chessboard[next.first][next.second] != '#') {
                if (sheep.count({ next.first, next.second })) {
                    sheep.erase({ next.first, next.second });
                    output++;
                }
            }
            if (i == 20) continue;
            for (pair<int, int> direction : directions) {
                if (next.first + direction.first < 0 || next.first + direction.first >= chessboard.size() ||
                    next.second + direction.second < 0 || next.second + direction.second >= chessboard[0].size()) continue;
                if (chessboard[next.first + direction.first][next.second + direction.second] != '#') {
                    if (sheep.count({ next.first + direction.first, next.second + direction.second })) {
                        sheep.erase({ next.first + direction.first, next.second + direction.second });
                        output++;
                    }
                }
                bfs.push({ next.first + direction.first, next.second + direction.second });
            }
        }
        passRound();
    }
    cout << output;
}

struct board {
    set<pair<int, int>> sheep;
    pair<int, int> dragon;
    board(set<pair<int, int>> newSheep, pair<int, int> newDragon) {
        sheep = newSheep;
        dragon = newDragon;
    }
};

static vector<pair<int, int>> directions = { {1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1} };

static map<pair<set<pair<int, int>>, pair<int, int>>, long long> checked;

static long long bfs(board next) {
    pair<set<pair<int, int>>, pair<int, int>> hash = { next.sheep, next.dragon };
    if (checked.count(hash)) return checked[hash];

    if (next.sheep.size() == 0) {
        checked[hash] = 1;
        return 1;
    }

    vector<board> sheepMoves;
    bool escaped = false;

    for (pair<int, int> deltaSheep : next.sheep) {
        pair<int, int> newSheep = { deltaSheep.first + 1, deltaSheep.second };
        if (newSheep.first == next.dragon.first && newSheep.second == next.dragon.second
            && chessboard[newSheep.first][newSheep.second] != '#') continue;
        board newBoard(next.sheep, next.dragon);
        newBoard.sheep.erase(deltaSheep);
        if (newSheep.first < chessboard.size()) {
            newBoard.sheep.insert(newSheep);
            sheepMoves.push_back(newBoard);
        }
        else {
            escaped = true;
        }
    }

    if (sheepMoves.size() == 0 && escaped) {
        checked[hash] = 0;
        return 0;
    }

    if (sheepMoves.size() == 0) sheepMoves.push_back(next);

    long long output = 0;
    for (board b : sheepMoves) {
        for (pair<int, int> direction : directions) {
            if (b.dragon.first + direction.first < 0 || b.dragon.first + direction.first >= chessboard.size() ||
                b.dragon.second + direction.second < 0 || b.dragon.second + direction.second >= chessboard[0].size()) continue;
            board newBoard(b.sheep, { b.dragon.first + direction.first, b.dragon.second + direction.second });
            if (chessboard[b.dragon.first + direction.first][b.dragon.second + direction.second] != '#') {
                newBoard.sheep.erase({ b.dragon.first + direction.first, b.dragon.second + direction.second });
            }
            output += bfs(newBoard);
        }
    }

    checked[hash] = output;
    return output;
}

static void part3() {
    parseInput("input10C.txt");
    pair<int, int> dragonStart;
    for (int row = 0; row < chessboard.size(); row++) {
        for (int col = 0; col < chessboard[0].size(); col++) {
            if (chessboard[row][col] == 'D') {
                dragonStart = { row, col };
                chessboard[row][col] = '.';
            }
            else if (chessboard[row][col] == 'S') {
                sheep.insert({ row, col });
            }
        }
    }
    long long output = bfs(board(sheep, dragonStart));
    cout << output;
}