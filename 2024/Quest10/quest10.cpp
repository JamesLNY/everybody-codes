#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

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

static void phase1(vector<string> &grid, int startX, int startY) {
	vector<unordered_set<char>> columns(8), rows(8);
	
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (grid[startY + y][startX + x] == '.' ||
				grid[startY + y][startX + x] == '?') continue;
			columns[x].insert(grid[startY + y][startX + x]);
			rows[y].insert(grid[startY + y][startX + x]);
		}
	}

	for (int y = 2; y < 6; y++) {
		for (int x = 2; x < 6; x++) {
			for (char c : columns[x]) {
				if (rows[y].contains(c)) {
					grid[startY + y][startX + x] = c;
					break;
				}
			}
		}
	}
}

static void phase2(vector<string> &grid, int startX, int startY) {
	// Go through cols
	for (int iter = 0; iter < 2; iter++) {
		for (int isRow = 0; isRow < 2; isRow++) {
			for (int x = 2; x < 6; x++) {
				int missing = -1;
				bool possible = true;
				unordered_set<char> found;
				for (int y = 0; y < 8; y++) {
					if (isRow) swap(x, y); // P1

					char c = grid[startY + y][startX + x];

					if (c == '.' || c == '?') {
						if (isRow) swap(x, y);
						if (missing != -1) {
							possible = false;
							break;
						}
						missing = y;
						continue;
					}

					if (found.contains(c)) {
						found.erase(c);
					}
					else {
						found.insert(c);
					}

					if (isRow) swap(x, y); // P1
				}

				if (isRow) swap(missing, x); // P2

				if (found.size() == 1 && possible) {
					grid[startY + missing][startX + x] = *found.begin();
				}

				if (isRow) swap(missing, x); // P2
			}
		}
	}
}

static bool isComplete(vector<string> &grid, int startX, int startY) {
	for (int x = 2; x < 6; x++) {
		for (int y = 2; y < 6; y++) {
			if (grid[startY + y][startX + x] == '.') {
				return false;
			}
		}
	}
	return true;
}

static int evaluatePower(vector<string>& grid, int startX, int startY) {
	int power = 0, pos = 1;
	for (int y = 2; y < 6; y++) {
		for (int x = 2; x < 6; x++) {
			power += (grid[startY + y][startX + x] - 'A' + 1) * pos;
			pos++;
		}
	}
	return power;
}

static void part3() {
	ifstream input("input10C.txt");
	vector<string> grid;

	string temp;
	while (getline(input, temp)) {
		grid.push_back(temp);
	}

	vector<pair<int, int>> directions = { {6, 0}, {-6, 0}, {0, 6}, {0, -6} };

	// X, Y
	vector<vector<bool>> completed(grid[0].size() / 6, vector<bool>(grid.size() / 6, false));
	queue<pair<int, int>> toComplete;

	for (int Y = 0; Y < grid.size() - 2; Y += 6) {
		for (int X = 0; X < grid[0].size() - 2; X += 6) {
			phase1(grid, X, Y);
			phase2(grid, X, Y);
			if (isComplete(grid, X, Y)) {
				completed[X / 6][Y / 6] = true;
				for (auto& [dx, dy] : directions) {
					toComplete.push({ X + dx, Y + dy });
				}
			}
		}
	}

	while (!toComplete.empty()) {
		auto& [X, Y] = toComplete.front();
		toComplete.pop();

		if (X < 0 || X >= grid[0].size() - 2 ||
			Y < 0 || Y >= grid.size() - 2) continue;
		if (completed[X / 6][Y / 6]) continue;

		phase1(grid, X, Y);
		phase2(grid, X, Y);
		if (isComplete(grid, X, Y)) {
			completed[X / 6][Y / 6] = true;
			for (auto& [dx, dy] : directions) {
				toComplete.push({ X + dx, Y + dy });
			}
		}
	}

	long output = 0;
	for (int Y = 0; Y < grid.size() - 2; Y += 6) {
		for (int X = 0; X < grid[0].size() - 2; X += 6) {
			//printProcess(grid, X, Y);
			if (completed[X / 6][Y / 6]) {
				int power = evaluatePower(grid, X, Y);
				output += power;
			}
		}
	}

	cout << output;
}