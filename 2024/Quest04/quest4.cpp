#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static void part1() {
	ifstream input("input4A.txt");
	vector<int> lengths;
	int temp;
	if (input.is_open()) {
		while (input >> temp) {
			lengths.push_back(temp);
		}
		int minLength = *min_element(lengths.begin(), lengths.end());
		int output = 0;
		for (int l : lengths) {
			output += l - minLength;
		}
		cout << output;
	}
}

// Same as part1
static void part2() {
	ifstream input("input4B.txt");
	vector<int> lengths;
	int temp;
	if (input.is_open()) {
		while (input >> temp) {
			lengths.push_back(temp);
		}
		int minLength = *min_element(lengths.begin(), lengths.end());
		int output = 0;
		for (int l : lengths) {
			output += l - minLength;
		}
		cout << output;
	}
}

static void part3() {
	ifstream input("input4C.txt");
	vector<int> lengths;
	int temp;
	if (input.is_open()) {
		long long sum = 0;
		while (input >> temp) {
			lengths.push_back(temp);
			sum += temp;
		}
		int average = lround((double)sum / lengths.size());
		int output = 0;
		for (int l : lengths) {
			output += abs(l - average);
		}
		cout << output;
	}
}