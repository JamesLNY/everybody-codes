#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

vector<int> strings;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        input >> temp;
        stringstream parsedNotes;
        parsedNotes.str(temp);
        while (getline(parsedNotes, temp, ',')) strings.push_back(stoi(temp));
    }
    input.close();
}

static void part1() {
    parseInput("input8A.txt");
    int numNails = 32, output = 0;
    for (int i = 0; i < strings.size() - 1; i++) {
        if (abs(strings[i + 1] - strings[i]) == numNails / 2) output++;
    }
    cout << output;
}

static void part2() {
    parseInput("input8B.txt");
    map<int, vector<int>> m;
    int numNails = 256;
    int output = 0;
    for (int i = 1; i < numNails; i++) m[i] = {};
    for (int i = 0; i < strings.size() - 1; i++) {
        int a = strings[i];
        int b = strings[i + 1];
        int distLeft = min(a, b) - 1 + numNails - max(a, b);
        int distRight = max(a, b) - min(a, b) - 1;
        if (distLeft > distRight) {
            for (int n = 0; n < distLeft; n++) {
                int parsed = max(a, b) + 1 + n;
                if (parsed > numNails) parsed -= numNails;
                for (int s : m[parsed]) {
                    if (s > min(a, b) && s < max(a, b)) output++;
                }
            }
        }
        else {
            for (int n = 0; n < distRight; n++) {
                int parsed = min(a, b) + 1 + n;
                for (int s : m[parsed]) {
                    if (s < min(a, b) || s > max(a, b)) output++;
                }
            }
        }
        m[a].push_back(b);
        m[b].push_back(a);
    }
    cout << output;
}

static void part3() {
    parseInput("input8C.txt");
    map<int, vector<int>> m;
    int numNails = 256;
    int output = 0;
    for (int i = 1; i < numNails; i++) m[i] = {};
    for (int i = 0; i < strings.size() - 1; i++) {
        int a = strings[i];
        int b = strings[i + 1];
        m[a].push_back(b);
        m[b].push_back(a);
    }
    for (int i = 1; i <= numNails; i++) {
        for (int n = 1; n <= numNails; n++) {
            if (i == n) continue;
            int distLeft = min(i, n) - 1 + numNails - max(i, n);
            int distRight = max(i, n) - min(i, n) - 1;
            int numCrossed = 0;
            if (distLeft > distRight) {
                for (int k = 0; k < distLeft; k++) {
                    int parsed = max(i, n) + 1 + k;
                    if (parsed > numNails) parsed -= numNails;
                    for (int s : m[parsed]) {
                        if (s > min(i, n) && s < max(i, n)) numCrossed++;
                    }
                }
            }
            else {
                for (int k = 0; k < distRight; k++) {
                    int parsed = min(i, n) + 1 + k;
                    for (int s : m[parsed]) {
                        if (s < min(i, n) || s > max(i, n)) numCrossed++;
                    }
                }
            }
            if (count(m[i].begin(), m[i].end(), n)) numCrossed++;
            output = max(output, numCrossed);
        }
    }
    cout << output;
}