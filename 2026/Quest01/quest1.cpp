#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

vector<int> parseInput(string filename) {
	ifstream input(filename);
	string line, temp;
	input >> line;
	stringstream ss(line);
	vector<int> output;
	while (getline(ss, temp, ',')) {
		output.push_back(stoi(temp));
	}
	return output;
}

static void part1() {
	vector<int> nums = parseInput("input1A.txt");

	int sum = 0;
	for (int num : nums) {
		int root = ceil(sqrt(num));
		sum += pow(root, 2) - num;
	}
	cout << sum;
}

static void part2() {
	vector<int> nums = parseInput("input1B.txt");

	int sum = 0;
	for (int num : nums) {
		if (num <= 4) {
			sum += 8 - num;
		}
		else {
			int remainder = num % 4;
			if (remainder > 0) {
				sum += 4 - remainder;
			}
		}
	}
	cout << sum;
}

static void part3() {
	vector<int> nums = parseInput("input1C.txt");

	int sum = 0;
	for (int num : nums) {
		if (num < 8) {
			sum += 8 - num;
		}
		else {
			int root = ceil(sqrt(num + 1));
			if (root % 2 == 0) root++;
			sum += pow(root, 2) - 1 - num;
		}
	}
	cout << sum;
}