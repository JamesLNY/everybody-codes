#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

const vector<pair<int, int>> DIRECTIONS = {
	{1, 0}, {1, 1}, {0, 1}, {-1, 1},
	{-1, 0}, {-1, -1}, {0, -1}, {1, -1}
};

static vector<string> parseInput(string filename) {
	ifstream input(filename);
	string line;
	vector<string> map;
	while (input >> line) {
		map.push_back(line);
	}
	return map;
}

static void convertLand(vector<string>& map) {
	vector<vector<int>> grid(map.size(), vector<int>(map[0].size(), 0));

	int cx = map[0].size() / 2;
	int cy = map.size() / 2;

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == '1') {
				for (auto [dx, dy] : DIRECTIONS) {
					int xp = x + dx;
					int yp = y + dy;
					if (yp < 0 || yp >= map.size() ||
						xp < 0 || xp >= map[yp].size()) continue;
					grid[yp][xp]++;
				}
			}
		}
	}

	queue<pair<int, int>> toVisit;
	toVisit.push({ cx, cy });

	while (!toVisit.empty()) {
		auto [x, y] = toVisit.front();
		toVisit.pop();

		if (map[y][x] == '#') continue;

		for (auto [dx, dy] : DIRECTIONS) {
			int xp = x + dx;
			int yp = y + dy;

			if (yp < 0 || yp >= map.size() ||
				xp < 0 || xp >= map[yp].size()) continue;

			if (map[y][x] != '1') {
				grid[yp][xp]++;
			}

			if (grid[yp][xp] >= 5) {
				toVisit.push({ xp, yp });
			}
		}

		map[y][x] = '#';
	}
}

static void part1() {
	vector<string> map = parseInput("input5A.txt");
	convertLand(map);

	int count = 0;
	for (string s : map) {
		for (char c : s) {
			if (c == '#') count++;
		}
	}
	cout << count;
}

static void convertSand(vector<string>& map) {
	vector<vector<int>> grid(map.size(), vector<int>(map[0].size(), 0));

	queue<pair<int, int>> toVisit;
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == '#') {
				for (auto [dx, dy] : DIRECTIONS) {
					int xp = x + dx;
					int yp = y + dy;
					if (yp < 0 || yp >= map.size() ||
						xp < 0 || xp >= map[yp].size() || map[yp][xp] != '#') {
						toVisit.push({ x, y });
						break;
					}
				}
			}
		}
	}

	while (!toVisit.empty()) {
		auto [x, y] = toVisit.front();
		toVisit.pop();

		if (map[y][x] == '=') continue;
		map[y][x] = '=';

		for (auto [dx, dy] : DIRECTIONS) {
			int xp = x + dx;
			int yp = y + dy;

			if (yp < 0 || yp >= map.size() ||
				xp < 0 || xp >= map[yp].size()) continue;

			if (map[yp][xp] == '#') {
				grid[yp][xp]++;
			}

			if (grid[yp][xp] >= 5) {
				toVisit.push({ xp, yp });
			}
		}
	}
}

static void part2() {
	vector<string> map = parseInput("input5B.txt");
	convertLand(map);
	convertSand(map);
	
	int count = 0;
	for (string s : map) {
		for (char c : s) {
			if (c == '=') count++;
		}
	}
	cout << count;
}

static void part3() {
	vector<string> map = parseInput("input5C.txt");
	convertLand(map);
	convertSand(map);

	vector<vector<int>> grid(map.size(), vector<int>(map[0].size(), 0));

	queue<pair<int, int>> toVisit;
	for (int y = 2; y < map.size() - 2; y++) {
		for (int x = 2; x < map[y].size() - 2; x++) {
			bool possible = true;
			for (int dy = -2; dy <= 2; dy++) {
				for (int dx = -2; dx <= 2; dx++) {
					if (abs(dx) == 2 && abs(dy) == 2) continue;
					if (map[y + dy][x + dx] != '#') {
						possible = false;
					}
				}
			}
			if (possible) toVisit.push({ x, y });
		}
	}

	int count = 0;
	int round = 0;
	while (round <= 2) {
		int size = toVisit.size();
		while (size--) {
			auto [x, y] = toVisit.front();
			toVisit.pop();

			if (map[y][x] != '#') continue;
			bool possible = true;
			for (auto [dx, dy] : DIRECTIONS) {
				int xp = x + dx;
				int yp = y + dy;
				if (map[yp][xp] == '=') {
					possible = false;
					break;
				}
			}
			if (!possible) continue;

			map[y][x] = '@';
			count++;

			for (auto [dx, dy] : DIRECTIONS) {
				int xp = x + dx;
				int yp = y + dy;

				if (map[yp][xp] == '#') {
					grid[yp][xp]++;
				}

				if (grid[yp][xp] >= 4) {
					toVisit.push({ xp, yp });
				}
			}
		}
		round++;
	}

	cout << count;
}