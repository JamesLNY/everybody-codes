#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// key greater than all values
using AdjacencyMap = unordered_map<int, unordered_set<int>>;

static vector<AdjacencyMap> parseInput(string filename) {
	fstream input(filename);
	string line;
	vector<AdjacencyMap> output;
	while (getline(input, line)) {
		stringstream ss(line);
		AdjacencyMap m;
		string comparison;
		while (ss >> comparison) {
			int idx = comparison.find_first_of("<>");
			char op = comparison[idx];
			int a = stoi(comparison.substr(0, idx));
			int b = stoi(comparison.substr(idx + 1));
			if (op == '<') {
				swap(a, b);
			}
			m.try_emplace(a, unordered_set<int>());
			m[a].insert(b);
		}
		output.push_back(m);
	}
	return output;
}

static void part1() {
	vector<AdjacencyMap> input = parseInput("input2A.txt");
	int total = 0;
	for (AdjacencyMap m : input) {
		int numBlades = m.size() + 1;

		vector<int> order(numBlades);
		unordered_set<int> visited;

		for (const auto& [key, val] : m) {
			order[val.size()] = key;
			visited.insert(key);
		}

		for (int i = 1; i <= numBlades; i++) {
			if (!visited.contains(i)) {
				order[0] = i;
				break;
			}
		}

		for (int i = 0; i < numBlades; i++) {
			total += order[i] * pow(10, i);
		}
	}
	cout << total;
}

static void part2() {
	vector<AdjacencyMap> input = parseInput("input2B.txt");
	long long total = 0;
	for (AdjacencyMap m : input) {
		int numBlades = m.size() + 1;
		vector<int> order(numBlades);

		for (int i = 1; i <= numBlades; i++) {
			if (!m.contains(i)) {
				order[0] = i;
			}
			else {
				queue<int> toVisit;
				toVisit.push(i);
				unordered_set<int> visited;
				while (!toVisit.empty()) {
					int next = toVisit.front();
					toVisit.pop();
					if (visited.contains(next)) continue;
					visited.insert(next);
					for (int i : m[next]) {
						toVisit.push(i);
					}
				}
				visited.erase(i);
				order[visited.size()] = i;
			}
		}

		for (int i = 0; i < numBlades; i++) {
			total += order[i] * pow(10, i);
		}
	}
	cout << total;
}

static void part3() {
	vector<AdjacencyMap> input = parseInput("input2C.txt");
	long long total = 0;
	for (AdjacencyMap m : input) {
		int numBlades = m.size() + 1;
		vector<int> order(numBlades);

		for (int i = 1; i <= numBlades; i++) {
			if (!m.contains(i)) {
				order[0] = i;
			}
			else {
				queue<int> toVisit;
				toVisit.push(i);
				unordered_set<int> visited;
				while (!toVisit.empty()) {
					int next = toVisit.front();
					toVisit.pop();
					if (visited.contains(next)) continue;
					visited.insert(next);
					for (int i : m[next]) {
						toVisit.push(i);
					}
				}
				visited.erase(i);
				order[visited.size()] = i;
			}
		}

		for (int i = 0; i < numBlades; i++) {
			total += order[i] * pow(10, i);
		}
	}
	cout << total;
}