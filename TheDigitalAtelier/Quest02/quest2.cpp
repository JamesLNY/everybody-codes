#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

static vector<string> parseInput(string filename) {
	ifstream input(filename);
	string temp;
	vector<string> lines;
	if (input.is_open()) {
		while (input >> temp) {
			temp = regex_replace(temp, regex("=|,"), " ");
			temp = regex_replace(temp, regex("\\[|\\]"), "");
			lines.push_back(temp);
		}
	}
	return lines;
}

static void part1() {
	vector<string> input = parseInput("input2A.txt");
	string temp;
	unordered_map<string, pair<int, int>> points;
	unordered_map<int, unordered_set<int>> visited;

	double x, y;
	for (int i = 0; i < input.size() - 1; i++) {
		stringstream ss(input[i]);
		ss >> temp >> x >> y;
		points[temp] = { x, y };
	}
	string instructions;
	stringstream ss(input.back());
	ss >> temp >> instructions;

	x = points["START"].first;
	y = points["START"].second;
	visited[x].insert(y);
	for (char c : instructions) {
		pair<int, int> flag = points[string(1, c)];
		x = (x + flag.first) / 2;
		y = (y + flag.second) / 2;
		visited[x].insert(y);
	}
	int output = 0;
	for (const auto& [key, val] : visited) {
		output += val.size();
	}
	cout << output;
}

static void part2() {
	vector<string> input = parseInput("input2B.txt");
	string temp;
	unordered_map<string, pair<int, int>> points;
	unordered_map<int, unordered_set<int>> visited, fireflies;

	double x, y;
	for (int i = 0; i < input.size() - 1; i++) {
		stringstream ss(input[i]);
		ss >> temp >> x >> y;
		points[temp] = { x, y };
	}
	string instructions;
	stringstream ss(input.back());
	ss >> temp >> instructions;

	const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	x = points["START"].first;
	y = points["START"].second;

	for (pair<int, int> dir : directions) {
		if (!visited[x + dir.first].count(y + dir.second)) {
			fireflies[x + dir.first].insert(y + dir.second);
		}
	}

	visited[x].insert(y);
	for (char c : instructions) {
		pair<int, int> flag = points[string(1, c)];
		x = (x + flag.first) / 2;
		y = (y + flag.second) / 2;
		visited[x].insert(y);
		fireflies[x].erase(y);

		for (pair<int, int> dir : directions) {
			if (!visited[(int) x + dir.first].count((int) y + dir.second)) {
				fireflies[(int) x + dir.first].insert((int) y + dir.second);
			}
		}
	}
	int output = 0;
	for (const auto& [key, val] : fireflies) {
		output += val.size();
	}

	cout << output;
}

static void part3() {
	vector<string> input = parseInput("input2C.txt");
	string temp;

	vector<string> flags;
	unordered_map<string, pair<int, int>> points;
	unordered_map<int, unordered_set<int>> visited, fireflies;

	double x, y;
	for (int i = 0; i < input.size(); i++) {
		stringstream ss(input[i]);
		ss >> temp >> x >> y;
		if (temp != "START") {
			flags.push_back(temp);
		}
		points[temp] = { x, y };
	}

	const vector<pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

	queue<pair<int, int>> toVisit;
	toVisit.push({ points["START"].first, points["START"].second });

	while (!toVisit.empty()) {
		x = toVisit.front().first;
		y = toVisit.front().second;
		toVisit.pop();

		if (visited[x].count(y)) continue;

		visited[x].insert(y);
		fireflies[x].erase(y);

		for (pair<int, int> dir : directions) {
			if (!visited[(int)x + dir.first].count((int)y + dir.second)) {
				fireflies[(int)x + dir.first].insert((int)y + dir.second);
			}
		}

		for (string s : flags) {
			pair<int, int> flag = points[s];
			toVisit.push({ (x + flag.first) / 2,
						   (y + flag.second) / 2 });
		}
	}

	//for (int i = -1; i < 10; i++) {
	//	for (int j = -1; j < 10; j++) {
	//		if (visited[i].count(j)) {
	//			cout << "X";
	//		}
	//		else if (fireflies[i].count(j)) {
	//			cout << "F";
	//		}
	//		else {
	//			cout << ".";
	//		}
	//	}
	//	cout << endl;
	//}

	int output = 0;
	for (const auto& [key, val] : fireflies) {
		output += val.size();
	}

	cout << output;
}

int main() {
	part3();
}