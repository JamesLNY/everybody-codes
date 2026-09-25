#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <ranges>

using namespace std;
using ll = long long;

static unordered_map<string, vector<string>> parseInput(string filename) {
	fstream input(filename);
	string temp;
	unordered_map<string, vector<string>> m;
	string node, neighbor;
	while (input >> temp) {
		replace(temp.begin(), temp.end(), ':', ' ');
		replace(temp.begin(), temp.end(), ',', ' ');
		stringstream ss(temp);
		ss >> node;
		m[node] = {};
		while (ss >> neighbor) {
			m[node].push_back(neighbor);
		}
	}
	return m;
}

static void part1() {
	unordered_map<string, vector<string>> m = parseInput("input11A.txt");
	unordered_map<string, int> counts = { { "A", 1 } };

	for (int round = 0; round < 4; round++) {
		unordered_map<string, int> next;
		for (const auto& [key, val] : counts) {
			for (string c : m[key]) {
				next.try_emplace(c, 0);
				next[c] += val;
			}
		}
		counts = next;
	}

	int total = 0;
	for (const auto& [key, val] : counts) {
		total += val;
	}
	cout << total;
}

static void part2() {
	unordered_map<string, vector<string>> m = parseInput("input11B.txt");
	unordered_map<string, int> counts = { { "Z", 1}};

	for (int round = 0; round < 10; round++) {
		unordered_map<string, int> next;
		for (const auto& [key, val] : counts) {
			for (string c : m[key]) {
				next.try_emplace(c, 0);
				next[c] += val;
			}
		}
		counts = next;
	}

	int total = 0;
	for (const auto& [key, val] : counts) {
		total += val;
	}
	cout << total;
}

static void part3() {
	unordered_map<string, vector<string>> m = parseInput("input11C.txt");

	auto temp = views::keys(m);
	vector<string> keys{ temp.begin(), temp.end() };

	ll big = 0, small = numeric_limits<ll>::max();

	for (string s : keys) {
		unordered_map<string, ll> counts = { { s, 1 } };

		for (int round = 0; round < 20; round++) {
			unordered_map<string, ll> next;
			for (const auto& [key, val] : counts) {
				for (string c : m[key]) {
					next.try_emplace(c, 0);
					next[c] += val;
				}
			}
			counts = next;
		}

		ll total = 0;
		for (const auto& [key, val] : counts) {
			total += val;
		}

		big = max(big, total);
		small = min(small, total);
	}
	
	cout << big - small;
}