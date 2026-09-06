#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

static void part1() {
	ifstream input("input9A.txt");
	vector<int> balls{
		istream_iterator<int>(input),
		istream_iterator<int>()
	};
	
	array stamps = { 1, 3, 5, 10 };
	sort(stamps.begin(), stamps.end(), greater<int>());

	int sum = 0;
	for (int ball : balls) {
		for (int stamp : stamps) {
			sum += ball / stamp;
			ball %= stamp;
		}
	}

	cout << sum;
}

static void part2() {
	ifstream input("input9B.txt");
	vector<int> balls;

	int maxBrightness = 0, temp;
	while (input >> temp) {
		balls.push_back(temp);
		maxBrightness = max(maxBrightness, temp);
	}

	array stamps = { 1, 3, 5, 10, 15, 16, 20, 24, 25, 30 };

	vector<int> distances(maxBrightness + 1, 0);
	for (int i = 1; i <= maxBrightness; i++) {
		int minBeetles = numeric_limits<int>::max();
		for (int s : stamps) {
			if (s <= i) {
				minBeetles = min(minBeetles, distances[i - s]);
			}
		}
		distances[i] = minBeetles + 1;
	}

	int sum = 0;
	for (int b : balls) {
		sum += distances[b];
	}
	cout << sum;
}

static void part3() {
	ifstream input("input9C.txt");
	vector<int> balls;
	array stamps = { 1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101 };

	int maxBrightness = 0, temp;
	while (input >> temp) {
		balls.push_back(temp);
		maxBrightness = max(maxBrightness, temp);
	}
	maxBrightness = maxBrightness / 2 + 50;

	vector<int> distances(maxBrightness + 1, 0);

	for (int i = 1; i <= maxBrightness; i++) {
		int minBeetles = numeric_limits<int>::max();
		for (int s : stamps) {
			if (s <= i) {
				minBeetles = min(minBeetles, distances[i - s]);
			}
		}
		distances[i] = minBeetles + 1;
	}

	int sum = 0;
	for (int b : balls) {
		int minBeetles = numeric_limits<int>::max();
		for (int i = b / 2 - 49; i <= b / 2; i++) {
			minBeetles = min(minBeetles, distances[i] + distances[b - i]);
		}
		sum += minBeetles;
	}
	cout << sum;
}