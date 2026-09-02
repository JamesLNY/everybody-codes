#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

static void part1() {
	ifstream input("input5A.txt");
	vector<list<int>> lines(4);

	int temp, index = 0;
	if (input.is_open()) {
		while (input >> temp) {
			lines[index].push_back(temp - 1);
			index = (index + 1) % 4;
		}
		for (int round = 0; round < 10; round++) {
			int clapper = lines[round % 4].front();
			lines[round % 4].pop_front();
			
			int newLine = (round + 1) % 4;
			
			list<int>::iterator it;
			if (clapper > lines[newLine].size()) {
				it = lines[newLine].end();
				it = prev(it, clapper - lines[newLine].size());
			}
			else {
				it = lines[newLine].begin();
				advance(it, clapper);
			}
			lines[newLine].insert(it, clapper);
		}
		for (int i = 0; i < 4; i++) {
			cout << lines[i].front() + 1;
		}
	}
}

static void part2() {
	ifstream input("input5B.txt");
	vector<list<int>> lines(4);
	unordered_map<string, int> shouts;

	int temp, index = 0;
	if (input.is_open()) {
		while (input >> temp) {
			lines[index].push_back(temp);
			index = (index + 1) % 4;
		}
		for (int round = 0; round < numeric_limits<int>::max(); round++) {
			int clapper = lines[round % 4].front();
			lines[round % 4].pop_front();

			int newLine = (round + 1) % 4;
			int movement = (clapper - 1) % (lines[newLine].size() * 2);

			list<int>::iterator it;
			if (movement > lines[newLine].size()) {
				it = lines[newLine].end();
				it = prev(it, movement - lines[newLine].size());
			}
			else {
				it = lines[newLine].begin();
				advance(it, movement);
			}
			lines[newLine].insert(it, clapper);

			string num = "";
			for (int i = 0; i < 4; i++) {
				num += to_string(lines[i].front());
			}
			
			shouts.try_emplace(num, 0);
			shouts[num]++;

			if (shouts[num] == 2024) {
				cout << (round + 1) * stoll(num);
				break;
			}
		}
		
	}
}

static void part3() {
	ifstream input("input5C.txt");
	vector<list<int>> lines(4);
	unordered_set<string> cache;
	long long big = 0;

	int temp, index = 0;
	if (input.is_open()) {
		while (input >> temp) {
			lines[index].push_back(temp);
			index = (index + 1) % 4;
		}
		for (int round = 0; round < numeric_limits<int>::max(); round++) {
			int clapper = lines[round % 4].front();
			lines[round % 4].pop_front();

			int newLine = (round + 1) % 4;
			int movement = (clapper - 1) % (lines[newLine].size() * 2);

			list<int>::iterator it;
			if (movement > lines[newLine].size()) {
				it = lines[newLine].end();
				it = prev(it, movement - lines[newLine].size());
			}
			else {
				it = lines[newLine].begin();
				advance(it, movement);
			}
			lines[newLine].insert(it, clapper);

			string num = "";
			for (int i = 0; i < 4; i++) {
				num += to_string(lines[i].front());
			}
			big = max(big, stoll(num));

			string state = "";
			for (list<int> line : lines) {
				for (int participant : line) {
					state += to_string(participant) + " ";
				}
				state += '\n';
			}
			if (cache.contains(state)) {
				cout << big;
				break;
			}
			cache.insert(state);
		}
	}
}