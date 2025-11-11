#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

using namespace std;

static void part1() {
    ifstream input("input6A.txt");
    string notes;
    int fighters = 0, output = 0;
    if (input.is_open()) {
        input >> notes;
    }
    input.close();
    for (char c : notes) {
        if (c == 'A') {
            fighters++;
        }
        else if (c == 'a') {
            output += fighters;
        }
    }
    cout << output;
}

static void part2() {
    map<char, int> trainers;
    trainers['A'] = 0;
    trainers['B'] = 0;
    trainers['C'] = 0;
    ifstream input("input6B.txt");
    string notes;
    int output = 0;
    if (input.is_open()) {
        input >> notes;
    }
    input.close();
    for (char c : notes) {
        if (c <= 'Z') {
            trainers[c]++;
        }
        else {
            output += trainers['A' + c - 'a'];
        }
    }
    cout << output;
}

static void part3() {
    map<char, queue<int>> people;
    for (char type : {'A', 'B', 'C', 'a', 'b', 'c'}) {
        people[type] = {};
    }
    ifstream input("input6C.txt");
    string notes;
    int output = 0;
    if (input.is_open()) {
        input >> notes;
    }
    input.close();
    for (int n = 0; n < 1000; n++) {
        for (int i = 0; i < notes.size(); i++) {
            char c = notes[i];
            int index = n * notes.size() + i;
            for (char type : {'A', 'B', 'C', 'a', 'b', 'c'}) {
                if (people[type].size() == 0) continue;
                if (people[type].front() < index - 1000) people[type].pop();
            }
            people[c].push(index);
            if (c <= 'Z') {
                output += people['a' + c - 'A'].size();
            }
            else {
                output += people['A' + c - 'a'].size();
            }
        }
    }
    cout << output;
}