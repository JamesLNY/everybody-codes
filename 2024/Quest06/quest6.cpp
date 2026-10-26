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

static unordered_map<string, vector<string>> parseInput(string filename) {
	ifstream input(filename);
	string temp;
	unordered_map<string, vector<string>> m;
	if (input.is_open()) {
		while (input >> temp) {
			temp = regex_replace(temp, regex(":|,"), " ");
			stringstream ss(temp);
			string origin;
			ss >> origin;
			m[origin] = {};
			while (ss >> temp) {
				m[origin].push_back(temp);
			}
		}
	}
	return m;
}

static void part1() {
	unordered_map<string, vector<string>> m = parseInput("input6A.txt");
	// current node, path
	queue<pair<string, vector<string>>> q;
	q.push({ "RR", {} });
	// length, paths
	unordered_map<int, vector<string>> paths;

	while (!q.empty()) {
		pair<string, vector<string>> curr = q.front();
		q.pop();

		curr.second.push_back(curr.first);
		if (curr.first == "@") {
			string temp;
			for (string s : curr.second) {
				temp += s;
			}
			paths.try_emplace(curr.second.size(), vector<string>());
			paths[curr.second.size()].push_back(temp);
		}
		else {
			for (string s : m[curr.first]) {
				q.push({ s, curr.second });
			}
		}
	}
	int minP = numeric_limits<int>::max(), minL;
	for (auto const& [l, p] : paths) {
		if (p.size() < minP) {
			minP = p.size();
			minL = l;
		}
	}
	cout << paths[minL].front();
}

static void part2() {
	unordered_map<string, vector<string>> m = parseInput("input6B.txt");
	// current node, path
	queue<pair<string, vector<string>>> q;
	q.push({ "RR", {} });
	// length, paths
	unordered_map<int, vector<string>> paths;

	while (!q.empty()) {
		pair<string, vector<string>> curr = q.front();
		q.pop();

		curr.second.push_back(curr.first);
		if (curr.first == "@") {
			string temp;
			for (string s : curr.second) {
				temp += s[0];
			}
			paths.try_emplace(curr.second.size(), vector<string>());
			paths[curr.second.size()].push_back(temp);
		}
		else {
			for (string s : m[curr.first]) {
				q.push({ s, curr.second });
			}
		}
	}
	int minP = numeric_limits<int>::max(), minL;
	for (auto const& [l, p] : paths) {
		if (p.size() < minP) {
			minP = p.size();
			minL = l;
		}
	}
	cout << paths[minL].front();
}

static void part3() {
	unordered_map<string, vector<string>> m = parseInput("input6C.txt");
	// current node, path
	queue<pair<string, vector<string>>> q;
	q.push({ "RR", {} });
	// length, paths
	unordered_map<int, vector<string>> paths;

	while (!q.empty()) {
		pair<string, vector<string>> curr = q.front();
		q.pop();

		curr.second.push_back(curr.first);
		if (curr.first == "@") {
			string temp;
			for (string s : curr.second) {
				temp += s[0];
			}
			paths.try_emplace(curr.second.size(), vector<string>());
			paths[curr.second.size()].push_back(temp);
		}
		else {
			for (string s : m[curr.first]) {
				if (s != "BUG" && s != "ANT") {
					q.push({ s, curr.second });
				}
			}
		}
	}
	int minP = numeric_limits<int>::max(), minL;
	for (auto const& [l, p] : paths) {
		if (p.size() < minP) {
			minP = p.size();
			minL = l;
		}
	}
	cout << paths[minL].front();
}