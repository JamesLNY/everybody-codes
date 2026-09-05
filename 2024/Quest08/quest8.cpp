#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

static void part1() {
	ifstream input("input8A.txt");
	int blocks;
	input >> blocks;

	int height = ceil(sqrt(blocks));
	int width = height * 2 - 1;
	int remainder = pow(height, 2) - blocks;

	cout << width * remainder;
}

static void part2() {
	const int numAcolytes = 1111;
	int numBlocks = 20240000;

	ifstream input("input8B.txt");
	int numPriests;
	input >> numPriests;

	int width = -1;
	int thickness = 1;
	while (numBlocks > 0) {
		width += 2;
		numBlocks -= width * thickness;
		thickness = (thickness * numPriests) % numAcolytes;
	}

	cout << abs(numBlocks) * width;
}

static void part3() {
	const int numAcolytes = 10;
	int numBlocks = 202400000;

	vector<int> prefixSum;

	ifstream input("input8C.txt");
	long long numPriests;
	input >> numPriests;

	int thickness = 1;
	int width = -1;

	while (numBlocks > 0) {
		width += 2;
		numBlocks -= width * thickness;
		thickness = (thickness * numPriests) % numAcolytes + numAcolytes;
		prefixSum.push_back(thickness);
	}
	
	prefixSum.pop_back();
	reverse(prefixSum.begin(), prefixSum.end());
	partial_sum(prefixSum.begin(), prefixSum.end(), prefixSum.begin());
	prefixSum[0] = 0;

	for (int height : prefixSum) {
		numBlocks += (numPriests * width * height) % numAcolytes * 2;
	}
	numBlocks += (numPriests * width * (prefixSum.back() + 1)) % numAcolytes;

	cout << abs(numBlocks);
}