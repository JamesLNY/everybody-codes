#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

static vector<long long> ducks;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (input >> temp) {
            ducks.push_back(stoll(temp));
        }
    }
    input.close();
}

static void part1() {
    parseInput("input11A.txt");
    int output = 0, rounds = -1;
    bool moved = true;
    while (moved) {
        moved = false;
        for (int n = 0; n < ducks.size() - 1; n++) {
            if (ducks[n + 1] < ducks[n]) {
                ducks[n + 1]++;
                ducks[n]--;
                moved = true;
            }
        }
        rounds++;
        for (int i : ducks) cout << i << " ";
        cout << endl;
        if (rounds == 10) {
            break;
        }
    }
    if (rounds < 10) {
        moved = true;
        while (moved) {
            moved = false;
            for (int n = 0; n < ducks.size() - 1; n++) {
                if (ducks[n + 1] > ducks[n]) {
                    ducks[n + 1]--;
                    ducks[n]++;
                    moved = true;
                }
            }
            rounds++;
            for (int i : ducks) cout << i << " ";
            cout << endl;
            if (rounds == 10) {
                break;
            }
        }
    }
    for (int i = 0; i < ducks.size(); i++) {
        output += (i + 1) * ducks[i];
    }
    cout << output;
}

static void part2() {
    parseInput("input11B.txt");
    int rounds = -1;
    bool moved = true;
    while (moved) {
        moved = false;
        for (int n = 0; n < ducks.size() - 1; n++) {
            if (ducks[n + 1] < ducks[n]) {
                ducks[n + 1]++;
                ducks[n]--;
                moved = true;
            }
        }
        rounds++;
    }
    moved = true;
    while (moved) {
        moved = false;
        for (int n = 0; n < ducks.size() - 1; n++) {
            if (ducks[n + 1] > ducks[n]) {
                ducks[n + 1]--;
                ducks[n]++;
                moved = true;
            }
        }
        rounds++;
    }
    cout << rounds - 1;
}

static void part3() {
    parseInput("input11C.txt");
    long long sum = 0, rounds = 0;
    sum = accumulate(ducks.begin(), ducks.end(), 0ll);
    long long average = sum / ducks.size();
    for (int i = 0; i < ducks.size(); i++) {
        if (ducks[i] < average) {
            rounds += average - ducks[i];
        }
    }
    cout << rounds;
}