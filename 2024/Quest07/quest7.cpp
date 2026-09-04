#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

static unordered_map<string, vector<char>> parseInput(string filename) {
	ifstream input(filename);
	string temp;
	unordered_map<string, vector<char>> m;
	if (input.is_open()) {
		while (input >> temp) {
			temp = regex_replace(temp, regex(":|,"), " ");
			stringstream ss(temp);
			string segment;
			ss >> segment;
			m[segment] = {};
			while (ss >> temp) {
				m[segment].push_back(temp[0]);
			}
		}
	}
	return m;
}

static void part1() {
	unordered_map<string, vector<char>> tracks = parseInput("input7A.txt");
	vector<pair<string, int>> results;
	for (auto const& [track, plan] : tracks) {
		int curr = 10, sum = 0;
		for (int i = 0; i < 10; i++) {
			switch (plan[i % plan.size()]) {
			case '-':
				if (curr > 0) curr--;
				break;
			case '+':
				curr++;
				break;
			case '=':
				break;
			}
			sum += curr;
		}
		results.push_back({ track, sum });
	}
	sort(results.begin(), results.end(), 
		[](pair<string, int> a, pair<string, int> b) { return a.second > b.second; });
	for (pair<string, int> track : results) {
		cout << track.first;
	}
}

static string parseRacetrackB() {
	ifstream input("racetrackB.txt");
	vector<string> raw;
	string temp;
	if (input.is_open()) {
		while (getline(input, temp)) {
			raw.push_back(temp);
		}
	}
	string output = raw[0].substr(1);
	for (int i = 1; i < raw.size() - 1; i++) {
		output += raw[i].back();
	}
	reverse(raw.back().begin(), raw.back().end());
	output += raw.back();
	for (int i = raw.size() - 2; i > 0; i--) {
		output += raw[i][0];
	}
	return output + 'S';
}

static void part2() {
	string racetrack = parseRacetrackB();
	unordered_map<string, vector<char>> segments = parseInput("input7B.txt");
	vector<pair<string, int>> results;
	for (auto const& [segment, plan] : segments) {
		int curr = 10, sum = 0;
		for (int i = 0; i < 10; i++) { // loops
			for (int j = 0; j < racetrack.size(); j++) {
				if (racetrack[j] == '+') {
					curr++;
				}
				else if (racetrack[j] == '-') {
					if (curr > 0) curr--;
				}
				else {
					switch (plan[(i * racetrack.size() + j) % plan.size()]) {
					case '-':
						if (curr > 0) curr--;
						break;
					case '+':
						curr++;
						break;
					case '=':
						break;
					}
				}
				sum += curr;
			}
		}
		results.push_back({ segment, sum });
	}
	sort(results.begin(), results.end(),
		[](pair<string, int> a, pair<string, int> b) { return a.second > b.second; });
	for (pair<string, int> track : results) {
		cout << track.first << " " << track.second << endl;
	}
}

static unordered_set<string> permutateActionPlan() {
	const int NUM_PLUSES = 5;
	const int NUM_MINUSES = 3;
	const int NUM_EQUALS = 3;

	unordered_set<string> solutions;
	unordered_set<string> visited;
	queue<string> actionPlans;
	actionPlans.push(string(11, '+'));

	for (int i = 0; i < 6; i++) {
		int count = actionPlans.size();
		for (int j = 0; j < count; j++) {
			string plan = actionPlans.front();
			actionPlans.pop();
			if (visited.count(plan)) continue;
			visited.insert(plan);

			for (int pos = 0; pos < 11; pos++) {
				if (plan[pos] == '+') {
					string newPlan = plan;
					if (i < 3) {
						newPlan[pos] = '-';
					}
					else {
						newPlan[pos] = '=';
					}
					if (i == 5) {
						solutions.insert(newPlan);
					}
					else {
						actionPlans.push(newPlan);
					}
				}
			}
		}
	}

	return solutions;
}

static string parseRacetrackC() {
	ifstream input("racetrackC.txt");
	vector<string> raw;
	string temp;
	if (input.is_open()) {
		while (getline(input, temp)) {
			raw.push_back(temp);
		}
	}
	
	vector<vector<bool>> visited(raw.size(), vector<bool>(raw[0].size(), false));
	visited[0][0] = true;
	// x, y
	queue<pair<int, int>> toVisit;
	toVisit.push({ 1, 0 });

	const vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	string output = "";
	
	while (!toVisit.empty()) {
		auto [x, y] = toVisit.front();
		toVisit.pop();

		if (y < 0 || y >= raw.size() || x < 0 || x >= raw[y].size()) continue;
		if (raw[y][x] == ' ') continue;
		if (visited[y][x]) continue;
		visited[y][x] = true;
		output += raw[y][x];
		
		for (auto [dx, dy] : directions) {
			toVisit.push({ x + dx, y + dy });
		}
	}

	return output + 'S';
}

static long long travel(string racetrack, string plan) {
	long long curr = 10, sum = 0;
	for (int i = 0; i < 2024; i++) { // loops
		for (int j = 0; j < racetrack.size(); j++) {
			if (racetrack[j] == '+') {
				curr++;
			}
			else if (racetrack[j] == '-') {
				if (curr > 0) curr--;
			}
			else {
				switch (plan[(i * racetrack.size() + j) % plan.size()]) {
				case '-':
					if (curr > 0) curr--;
					break;
				case '+':
					curr++;
					break;
				case '=':
					break;
				}
			}
			sum += curr;
		}
	}
	return sum;
}

static void part3() {
	vector<char> input = parseInput("input7C.txt")["A"];
	string opponentPath(input.begin(), input.end());
	unordered_set<string> permutations = permutateActionPlan();
	string racetrack = parseRacetrackC();

	long long numToBeat = travel(racetrack, opponentPath);
	int count = 0;

	for (string s : permutations) {
		if (travel(racetrack, s) > numToBeat) {
			count++;
		}
	}

	cout << count;
}