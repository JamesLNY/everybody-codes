#include <iostream>
#include <fstream>
#include <string>
#include <numeric>

using namespace std;

static int calculatePotions(char c) {
    switch (c) {
    case 'B':
        return 1;
    case 'C':
        return 3;
    case 'D':
        return 5;
    }
    return 0;
}

static void part1() {
    ifstream input("input1A.txt");
    string creatures;
    int output = 0;
    if (input.is_open()) {
        input >> creatures;
    }
    input.close();
    for (char c : creatures) output += calculatePotions(c);
    cout << output;
}

static void part2() {
    ifstream input("input1B.txt");
    string creatures;
    int output = 0;
    if (input.is_open()) {
        input >> creatures;
    }
    input.close();
    for (int i = 0; i < creatures.length(); i += 2) {
        int creature1 = calculatePotions(creatures[i]);
        int creature2 = calculatePotions(creatures[i + 1]);
        if (creatures[i] != 'x' && creatures[i + 1] != 'x') output += 2;
        output += creature1 + creature2;
    }
    cout << output;
}

static void part3() {
    ifstream input("input1C.txt");
    string creatures;
    int output = 0;
    if (input.is_open()) {
        input >> creatures;
    }
    input.close();
    for (char c : creatures) output += calculatePotions(c);
    for (int i = 0; i < creatures.length(); i += 3) {
        string group = creatures.substr(i, 3);
        int numCreatures = 3 - count(group.begin(), group.end(), 'x');
        output += numCreatures * (numCreatures - 1);
    }
    cout << output;
}