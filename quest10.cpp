#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

static void part1() {
	ifstream input("input10A.txt");
	vector<string> grid{
		istream_iterator<string>(input),
		istream_iterator<string>()
	};

	vector<unordered_set<char>> columns(8), rows(8);

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (grid[y][x] == '.') continue;
			columns[x].insert(grid[y][x]);
			rows[y].insert(grid[y][x]);
		}
	}

	for (int y = 2; y < 6; y++) {
		for (int x = 2; x < 6; x++) {
			for (char c : columns[x]) {
				if (rows[y].contains(c)) {
					cout << c;
					break;
				}
			}
		}
	}
}

static void part2() {
	ifstream input("input10B.txt");
	vector<string> grid;

	string temp;
	while (getline(input, temp)) {
		grid.push_back(temp);
	}

	long long total = 0;

	for (int Y = 0; Y < grid.size(); Y += 9) {
		for (int X = 0; X < grid[0].size(); X += 9) {
			vector<unordered_set<char>> columns(8), rows(8);

			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x++) {
					if (grid[Y + y][X + x] == '.') continue;
					columns[x].insert(grid[Y + y][X + x]);
					rows[y].insert(grid[Y + y][X + x]);
				}
			}

			int power = 0, pos = 1;

			for (int y = 2; y < 6; y++) {
				for (int x = 2; x < 6; x++) {
					for (char c : columns[x]) {
						if (rows[y].contains(c)) {
							power += (c - 'A' + 1) * pos;
							pos++;
							break;
						}
					}
				}
			}

			total += power;
		}
	}

	cout << total;
}

int main() {
	part2();
}