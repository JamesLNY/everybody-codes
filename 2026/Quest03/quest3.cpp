#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

static int convertBase(string standard, string vote) {
	int output = 0;
	for (int i = 0; i < vote.size(); i++) {
		output += (vote[i] - '0') * pow(standard[i % standard.size()] - '0', i);
	}
	return output;
}

static void part1() {
	ifstream input("input3A.txt");
	int output = 0;
	while (input.good()) {
		string standard, vote;
		input >> standard;
		standard = standard.substr(4);
		input >> vote;
		reverse(standard.begin(), standard.end());
		reverse(vote.begin(), vote.end());
		output += convertBase(standard, vote);
	}
	cout << output;
}

static void part2() {
	ifstream input("input3B.txt");
	long long output = 0;
	while (input.good()) {
		string standard, vote;
		input >> standard;
		standard = standard.substr(4);
		input >> vote;
		reverse(standard.begin(), standard.end());
		reverse(vote.begin(), vote.end());
		output += convertBase(standard, vote);
	}
	cout << output;
}

static void part3() {
	ifstream input("input3C.txt");
	long long output = 0;
	while (input.good()) {
		string standard, vote;
		input >> standard;
		standard = standard.substr(5);
		input >> vote;
		int raw = stoi(vote);
		reverse(standard.begin(), standard.end());
		reverse(vote.begin(), vote.end());

		int parsed = convertBase(standard, vote);

		bool viable = true;
		for (int j = 0; j < raw; j++) {
			string vote = to_string(j);
			reverse(vote.begin(), vote.end());
			int result = convertBase(standard, vote);
			if (result == parsed) {
				viable = false;
				break;
			}
		}

		if (viable) output += parsed;
	}
	cout << output;
}