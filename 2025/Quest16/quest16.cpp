#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <numeric>
#include "bigint.h"

using namespace std;

static vector<int> instructions;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        input >> temp;
        stringstream ss(temp);
        while (getline(ss, temp, ',')) {
            instructions.push_back(stoi(temp));
        }
    }
    input.close();
}

static void part1() {
    parseInput("input16A.txt");
    int output = 0;
    for (int i : instructions) {
        output += 90 / i;
    }
    cout << output;
}

static void part2() {
    parseInput("input16B.txt");
    vector<int> nums;
    long long output = 0;
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i] > 0) {
            nums.push_back(i + 1);
            for (int n = i; n < instructions.size(); n += i + 1) {
                instructions[n]--;
            }
        }
    }
    cout << accumulate(nums.begin(), nums.end(), 1ll, multiplies<long long>());
}

static void part3() {
    parseInput("input16C.txt");
    vector<bigint> nums;
    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i] > 0) {
            nums.push_back(i + 1);
            for (int n = i; n < instructions.size(); n += i + 1) {
                instructions[n]--;
            }
        }
    }
    bigint len = 0, numBlocks = 202520252025000;
    bigint divisor = 1;
    for (bigint i : nums) {
        divisor *= i;
    }
    numBlocks *= divisor;
    bigint sum = 0;
    for (int i = 0; i < nums.size(); i++) {
        sum += divisor / nums[i];
    }
    len = numBlocks / sum;
    bigint expected = 0;
    for (int i = 0; i < nums.size(); i++) {
        expected += len / nums[i];
    }
    bigint difference = 202520252025000 - expected;
    while (difference > to_bigint(0)) {
        len++;
        int additional = 0;
        for (bigint i : nums) {
            if (len % i == to_bigint(0)) additional++;
        }
        difference -= additional;
    }
    len -= 1;
    cout << len;
}