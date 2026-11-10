#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <regex>
#include <queue>
#include <unordered_set>

using namespace std;

struct Cloud {
	int energy;
	vector<int> connections = {};
	vector<int> impulses = vector<int>(11);
};

static void part1() {
	fstream input("input7A.txt");
	string line;

	unordered_map<int, Cloud> clouds;

	int start;

	int maxConnections = 0;
	while (getline(input, line)) {
		line = regex_replace(line, regex("([a-z]+=)|,"), " ");
		stringstream ss(line);
		int id, energy, connection;
		ss >> id >> energy;
		clouds[id] = Cloud{ .energy = energy };
		while (ss >> connection) {
			clouds[id].connections.push_back(connection);
		}
		if (clouds[id].connections.size() > maxConnections) {
			maxConnections = clouds[id].connections.size();
			start = id;
		}
	}

	// id, energy
	queue<pair<int, int>> toVisit;
	toVisit.push({ start, 5 });

	while (!toVisit.empty()) {
		auto [id, energy] = toVisit.front();
		toVisit.pop();

		if (energy == 0) continue;

		clouds[id].energy += energy;

		for (int connection : clouds[id].connections) {
			toVisit.push({ connection, energy - 1 });
		}
	}

	int total = 0;
	for (auto [key, val] : clouds) {
		total += val.energy;
	}
	cout << total;
}

static unordered_map<int, unordered_map<int, int>> cache;

static int propagate(int id, int energy, unordered_map<int, Cloud>& clouds) {
	if (cache.contains(id) && cache[id].contains(energy)) {
		return cache[id][energy];
	}

	if (energy == 1) {
		return 1;
	}

	int output = energy;
	for (int connection : clouds[id].connections) {
		output += propagate(connection, energy - 1, clouds);
	}

	cache.try_emplace(id, unordered_map<int, int>());
	cache[id][energy] = output;
	return output;
}

static void part2() {
	fstream input("input7B.txt");
	string line;

	unordered_map<int, Cloud> clouds;

	int start;
	int total = 0;

	int maxConnections = 0;
	while (getline(input, line)) {
		line = regex_replace(line, regex("([a-z]+=)|,"), " ");
		stringstream ss(line);
		int id, energy, connection;
		ss >> id >> energy;
		clouds[id] = Cloud{ .energy = energy };
		total += energy;
		while (ss >> connection) {
			clouds[id].connections.push_back(connection);
		}
		if (clouds[id].connections.size() > maxConnections) {
			maxConnections = clouds[id].connections.size();
			start = id;
		}
	}

	total += propagate(start, 10, clouds);
	cout << total;
}

static void part3() {
	fstream input("input7C.txt");
	string line;

	vector<Cloud> clouds = vector<Cloud>();

	int base = 0;
	int maxConnections = 0;
	while (getline(input, line)) {
		line = regex_replace(line, regex("([a-z]+=)|,"), " ");
		stringstream ss(line);
		int id, energy, connection;
		ss >> id >> energy;
		base += energy;
		clouds.push_back(Cloud{ .energy = energy });
		while (ss >> connection) {
			clouds.back().connections.push_back(connection - 1);
		}
	}

	int numClouds = clouds.size();
	
	queue<int> toVisit;
	unordered_set<int> visited;
	unordered_set<int> exploded;

	vector<Cloud>* oldClouds = new vector<Cloud>(clouds);
	vector<Cloud>* newClouds = new vector<Cloud>(clouds);

	int best = 0;

	for (int start = 0; start < numClouds; start++) {
		toVisit.push(start);
		(*newClouds)[start].impulses[10] = 1;
		exploded.clear();

		for (int i = 0; i < numClouds; i++) {
			(*oldClouds)[i].energy = clouds[i].energy;
			(*newClouds)[i].energy = clouds[i].energy;
		}

		while (!toVisit.empty()) {
			swap(oldClouds, newClouds);
			for (int i = 0; i < numClouds; i++) {
				Cloud& cloud = (*newClouds)[i];
				fill(cloud.impulses.begin(), cloud.impulses.end(), 0);
			}
			visited.clear();

			int count = toVisit.size();
			while (count--) {
				int curr = toVisit.front();
				toVisit.pop();
				if (visited.contains(curr)) continue;
				visited.insert(curr);

				if (exploded.contains(curr)) continue;

				Cloud& cloud = (*oldClouds)[curr];

				for (int i = 1; i <= 10; i++) {
					int impulse = i * cloud.impulses[i];

					cloud.energy += impulse;
					(*newClouds)[curr].energy += impulse;

					if (i > 1 && impulse > 0) {
						for (int connection : cloud.connections) {
							(*newClouds)[connection].impulses[i - 1] += cloud.impulses[i];
							toVisit.push(connection);
						}
					}
				}

				if (cloud.energy >= 1000000) {
					exploded.insert(curr);
					for (int connection : cloud.connections) {
						(*newClouds)[connection].impulses[10]++;
						toVisit.push(connection);
					}
				}
			}
		}

		int total = 0;
		for (Cloud& cloud : *newClouds) {
			if (cloud.energy < 1000000) {
				total += cloud.energy;
			}
		}
		best = max(best, total);
	}

	cout << best;

	delete oldClouds;
	delete newClouds;
}