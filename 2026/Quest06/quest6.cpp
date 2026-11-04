#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

static void part1() {
	fstream input("input6A.txt");
	string line;
	unordered_map<string, vector<string>> records;
	while (input >> line) {
		replace(line.begin(), line.end(), ',', ' ');
		replace(line.begin(), line.end(), ':', ' ');
		stringstream ss(line);
		string item, ingredient;
		ss >> item;
		records.try_emplace(item, vector<string>());
		while (ss >> ingredient) {
			records[item].push_back(ingredient);
		}
	}
	queue<string> toVisit;
	toVisit.push("NULL");
	unordered_set<string> visited;
	while (!toVisit.empty()) {
		string item = toVisit.front();
		toVisit.pop();

		if (visited.contains(item)) continue;
		visited.insert(item);

		for (string ingredient : records[item]) {
			toVisit.push(ingredient);
		}
	}
	cout << visited.size() - 1;
}

static void part2() {
	fstream input("input6B.txt");
	string line;
	unordered_map<string, vector<string>> records;
	while (input >> line) {
		replace(line.begin(), line.end(), ',', ' ');
		replace(line.begin(), line.end(), ':', ' ');
		stringstream ss(line);
		string item, ingredient;
		ss >> item;
		while (ss >> ingredient) {
			records.try_emplace(ingredient, vector<string>());
			records[ingredient].push_back(item);
		}
	}
	queue<string> toVisit;
	toVisit.push("NULL");
	unordered_set<string> visited;
	while (!toVisit.empty()) {
		string item = toVisit.front();
		toVisit.pop();

		if (visited.contains(item)) continue;
		visited.insert(item);

		for (string ingredient : records[item]) {
			toVisit.push(ingredient);
		}
	}
	cout << visited.size() - 1;
}

static void part3() {
	fstream input("input6C.txt");
	string line;
	unordered_map<string, vector<string>> records;
	while (input >> line) {
		replace(line.begin(), line.end(), ',', ' ');
		replace(line.begin(), line.end(), ':', ' ');
		stringstream ss(line);
		string item, ingredient;
		ss >> item;
		while (ss >> ingredient) {
			records.try_emplace(ingredient, vector<string>());
			records[ingredient].push_back(item);
		}
	}
	unordered_map<string, int> nullsUsed;

	int output = 0;
	queue<string> toVisit;
	for (int i = 1; i <= 3; i++) {
		toVisit.push("NULLv" + to_string(i));
		unordered_set<string> visited;
		while (!toVisit.empty()) {
			string item = toVisit.front();
			toVisit.pop();

			if (visited.contains(item)) continue;
			visited.insert(item);

			nullsUsed.try_emplace(item, 0);
			nullsUsed[item]++;
			if (nullsUsed[item] == 2) {
				output++;
			}

			for (string ingredient : records[item]) {
				toVisit.push(ingredient);
			}
		}
	}
	cout << output;
}