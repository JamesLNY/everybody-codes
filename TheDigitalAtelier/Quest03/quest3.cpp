#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

static void parseInput(int &h, int &w, vector<int> &vo, vector<int> &ho, string filename) {
	ifstream input(filename);

	string temp;
	if (input.is_open()) {
		temp = string(istreambuf_iterator<char>(input), istreambuf_iterator<char>());
		replace(temp.begin(), temp.end(), '=', ' ');
		stringstream ss(temp);

		ss >> temp >> w;
		ss >> temp >> h;

		ss >> temp >> temp;
		for (char c : temp) {
			ho.push_back(c - '0');
		}

		ss >> temp >> temp;
		for (char c : temp) {
			vo.push_back(c - '0');
		}
	}
}

static void part1() {
	int w, h;
	vector<int> ho, vo;
	parseInput(h, w, vo, ho, "input3A.txt");

	int count = 0;
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			// Top bar
			if (x % 2 != ho[y % ho.size()]) continue;
			// Bottom bar
			if (x % 2 != ho[(y + 1) % ho.size()]) continue;
			// Left bar
			if (y % 2 != vo[x % vo.size()]) continue;
			// RIght bar
			if (y % 2 != vo[(x + 1) % vo.size()]) continue;

			count++;
		}
	}

	cout << count;
}

static void part2() {
	int w, h;
	vector<int> ho, vo;
	parseInput(h, w, vo, ho, "input3B.txt");

	// 0 : No Color, -1 & 1 : Colors
	vector<vector<int>> colors(h, vector<int>(w, 0));
	int color = 1;

	unordered_map<int, int> count;
	count[-1] = 0;
	count[1] = 0;

	for (int yy = 0; yy < h; yy++) {

		if (yy > 0) color = colors[yy - 1][0];

		for (int xx = 0; xx < w; xx++) {

			if (colors[yy][xx]) {
				color = colors[yy][xx];
				continue;
			}

			queue<pair<int, int>> toVisit;
			toVisit.push({ xx, yy });
			color *= -1; // Flip color

			while (!toVisit.empty()) {

				int x = toVisit.front().first;
				int y = toVisit.front().second;
				toVisit.pop();

				if (x < 0 || x >= w || y < 0 || y >= h) continue;

				if (colors[y][x]) continue;
				colors[y][x] = color;

				bool isolated = true;
				// Top bar
				if (x % 2 != ho[y % ho.size()]) {
					toVisit.push({ x, y - 1 });
					isolated = false;
				}
				// Bottom bar
				if (x % 2 != ho[(y + 1) % ho.size()]) {
					toVisit.push({ x, y + 1 });
					isolated = false;
				}
				// Left bar
				if (y % 2 != vo[x % vo.size()]) {
					toVisit.push({ x - 1, y });
					isolated = false;
				}
				// Right bar
				if (y % 2 != vo[(x + 1) % vo.size()]) {
					toVisit.push({ x + 1, y });
					isolated = false;
				}

				if (isolated) {
					count[color]++;
				}
			}
		}
	}

	cout << max(count[-1], count[1]);
}

static pair<int, int> scan(vector<int> ho, vector<int> vo, int w, int h) {
	vector<vector<int>> colors(h, vector<int>(w, 0));
	int color = 1;

	unordered_map<int, int> count;
	count[-1] = 0;
	count[1] = 0;

	for (int yy = 0; yy < h; yy++) {

		if (yy > 0) color = colors[yy - 1][0];

		for (int xx = 0; xx < w; xx++) {

			if (colors[yy][xx]) {
				color = colors[yy][xx];
				continue;
			}

			queue<pair<int, int>> toVisit;
			toVisit.push({ xx, yy });
			color *= -1; // Flip color

			while (!toVisit.empty()) {

				int x = toVisit.front().first;
				int y = toVisit.front().second;
				toVisit.pop();

				if (x < 0 || x >= w || y < 0 || y >= h) continue;

				if (colors[y][x]) continue;
				colors[y][x] = color;

				bool isolated = true;
				// Top bar
				if (x % 2 != ho[y % ho.size()]) {
					toVisit.push({ x, y - 1 });
					isolated = false;
				}
				// Bottom bar
				if (x % 2 != ho[(y + 1) % ho.size()]) {
					toVisit.push({ x, y + 1 });
					isolated = false;
				}
				// Left bar
				if (y % 2 != vo[x % vo.size()]) {
					toVisit.push({ x - 1, y });
					isolated = false;
				}
				// Right bar
				if (y % 2 != vo[(x + 1) % vo.size()]) {
					toVisit.push({ x + 1, y });
					isolated = false;
				}

				if (isolated) {
					count[color]++;
				}
			}
		}
	}

	return { count[-1], count[1] };
}

static void part3() {
	int w, h;
	vector<int> ho, vo;
	parseInput(h, w, vo, ho, "input3C.txt");

	pair<long long, long long> base = scan(ho, vo, vo.size() * 2, ho.size() * 2);
	pair<int, int> rightEdge = scan(ho, vo, w % (vo.size() * 2), ho.size() * 2);
	pair<int, int> bottomEdge = scan(ho, vo, vo.size() * 2, h % (ho.size() * 2));
	pair<int, int> bottomRight = scan(ho, vo, w % (vo.size() * 2), h % (ho.size() * 2));

	int widthTiles = w / (vo.size() * 2);
	int heightTiles = h / (ho.size() * 2);

	long long color1 = base.first * widthTiles * heightTiles +
					   rightEdge.first * heightTiles +
				 	   bottomEdge.first * widthTiles +
					   bottomRight.first;
	long long color2 = base.second * widthTiles * heightTiles +
					   rightEdge.second * heightTiles +
			 		   bottomEdge.second * widthTiles +
			 		   bottomRight.second;

	cout << max(color1, color2);
}