#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

static pair<long long, long long> multiply(pair<long long, long long> A, pair<long long, long long> B) {
    return { A.first * B.first - A.second * B.second, A.first * B.second + B.first * A.second };
}

static pair<long long, long long> add(pair<long long, long long> A, pair<long long, long long> B) {
    return { A.first + B.first, A.second + B.second };
}

static pair<long long, long long> divide(pair<long long, long long> A, pair<long long, long long> B) {
    return { A.first / B.first, A.second / B.second };
}

static pair<long long, long long> getA(string fileName) {
    ifstream input(fileName);
    string inputLine = "";
    if (input.is_open()) {
        input >> inputLine;
    }
    input.close();
    inputLine = inputLine.substr(3, inputLine.size() - 4);
    int delim = inputLine.find(',');
    return { stoi(inputLine.substr(0, delim)), stoi(inputLine.substr(delim + 1)) };
}

static void part1() {
    pair<long long, long long> A = getA("input2A.txt"), output = { 0, 0 };
    for (int i = 0; i < 3; i++) {
        output = multiply(output, output);
        output = divide(output, { 10, 10 });
        output = add(output, A);
    }
    cout << "[" << output.first << ',' << output.second << ']';
}

static bool test(pair<long long, long long> A) {
    pair<long long, long long> output = { 0, 0 };
    for (int i = 0; i < 100; i++) {
        output = multiply(output, output);
        output = divide(output, { 100000, 100000 });
        output = add(output, A);
        if (abs(output.first) > 1000000 || abs(output.second) > 1000000) return false;
    }
    return true;
}

static void part2() {
    pair<long long, long long> A = getA("input2B.txt");
    int output = 0;
    for (int dx = 0; dx < 101; dx++) {
        for (int dy = 0; dy < 101; dy++) {
            output += test({ A.first + dx * 10, A.second + dy * 10 });
        }
    }
    cout << output;
}

static void part3() {
    pair<long long, long long> A = getA("input2C.txt");
    int output = 0;
    for (int dx = 0; dx < 1001; dx++) {
        for (int dy = 0; dy < 1001; dy++) {
            output += test({ A.first + dx, A.second + dy });
        }
    }
    cout << output;
}