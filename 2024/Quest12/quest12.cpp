// dh = final pos - initial pos
// dx = finalx - initial pos
// Possible --> (dx + dh) % 3 == 0

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

static struct target {
	int x, y;
	char type;
};

static void parseInput(string filename, int& height,
					   unordered_set<int>& catapults,
					   vector<target>& targets) {
	fstream input(filename);
	string temp;
	height = 0;
	while (input >> temp) {
		for (int x = 0; x < temp.size(); x++) {
			if (temp[x] == 'T' || temp[x] == 'H') {
				targets.push_back({ x, height, temp[x] });
			}
			else if (isupper(temp[x])) {
				catapults.insert(x);
			}
		}
		height++;
	}
	for (auto& [targetX, targetY, type] : targets) {
		// Subtract 1 for the ground
		targetY = height - targetY - 1;
	}
}

static void part1() {
	int height;
	unordered_set<int> catapults;
	vector<target> targets;

	parseInput("input12A.txt", height, catapults, targets);

	int total = 0;
	int catapultX = *catapults.begin();
	for (const auto& [targetX, targetY, type] : targets) {
		int dx = targetX - catapultX + targetY;
		int shootingPower = (dx - 1)/ 3;
		int segmentNumber = dx - shootingPower * 3;
		
		total += segmentNumber * shootingPower;
	}

	cout << total;
}

static void part2() {
	int height;
	unordered_set<int> catapults;
	vector<target> targets;

	parseInput("input12B.txt", height, catapults, targets);

	int total = 0;
	int catapultX = *catapults.begin();
	for (const auto& [targetX, targetY, type] : targets) {
		int dx = targetX - catapultX + targetY;
		int shootingPower = (dx - 1) / 3;
		int segmentNumber = dx - shootingPower * 3;

		int ranking = segmentNumber * shootingPower;
		if (type == 'H') ranking *= 2;

		total += ranking;
	}

	cout << total;
}

static void part3() {
	int height;
	unordered_set<int> catapults;
	vector<target> targets;

	parseInput("input12B.txt", height, catapults, targets);

	int total = 0;
	int catapultX = *catapults.begin();
	for (const auto& [targetX, targetY, type] : targets) {
		int dx = targetX - catapultX + targetY;
		int shootingPower = (dx - 1) / 3;
		int segmentNumber = dx - shootingPower * 3;

		int ranking = segmentNumber * shootingPower;
		if (type == 'H') ranking *= 2;

		total += ranking;
	}

	cout << total;
}

int main() {
	part2();
}