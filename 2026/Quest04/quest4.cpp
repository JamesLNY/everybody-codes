#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Participant {
	int parts;
	int time;

	bool operator < (const Participant& other) const {
		if (parts != other.parts) {
			return parts < other.parts;
		}
		return time > other.time;
	}
};

static void part1() {
	ifstream input("input4A.txt");
	string line;
	unordered_map<int, int> m;
	while (getline(input, line)) {
		replace(line.begin(), line.end(), '=', ' ');
		stringstream ss(line);
		string temp;
		int id, quest, part, time;
		ss >> temp >> id;
		ss >> temp >> quest;
		ss >> temp >> part;
		ss >> temp >> time;
		m.try_emplace(id, 0);
		m[id] += time;
	}
	vector<int> times;
	for (const auto& [id, time] : m) {
		times.push_back(time);
	}
	sort(times.begin(), times.end());
	int total = 0;
	for (int i = 0; i < times.size(); i++) {
		total += times[i] * (i + 1);
	}
	cout << total;
}

static void part2() {
	ifstream input("input4B.txt");
	string line;
	unordered_map<int, Participant> m;

	while (getline(input, line)) {
		replace(line.begin(), line.end(), '=', ' ');
		stringstream ss(line);
		string temp;
		int id, quest, part, time;
		ss >> temp >> id;
		ss >> temp >> quest;
		ss >> temp >> part;
		ss >> temp >> time;
		m.try_emplace(id);
		m[id].time += time;
		m[id].parts++;
	}

	vector<Participant> participants;
	for (const auto& [id, participant] : m) {
		participants.push_back(participant);
	}
	sort(participants.begin(), participants.end());
	reverse(participants.begin(), participants.end());
	int output = 0;
	for (int i = 0; i < participants.size(); i++) {
		output += participants[i].time * (i + 1);
	}
	cout << output;
}

static void part3() {
	struct Note {
		int id;
		int quest;
		int part;
		int time;

		bool operator < (const Note& other) {
			return tie(quest, part, id) < tie(other.quest, other.part, other.id);
		}
	};

	struct Participant {
		int id;
		int time;
		int points;
		int quest;
		int part;

		bool operator < (const Participant& other) {
			return time < other.time;
		}
	};

	ifstream input("input4C.txt");
	string line;
	vector<Note> notes;
	unordered_map<int, Participant> participants;
	while (getline(input, line)) {
		replace(line.begin(), line.end(), '=', ' ');
		string temp;
		Note note;
		stringstream ss(line);
		ss >> temp >> note.id;
		ss >> temp >> note.quest;
		ss >> temp >> note.part;
		ss >> temp >> note.time;
		notes.push_back(note);
		participants.try_emplace(note.id, Participant(note.id));
	}
	sort(notes.begin(), notes.end());
	for (int i = 0; i < notes.size(); i++) {
		Note n = notes[i];
		Participant& p = participants[n.id];
		p.time += n.time;
		p.quest = n.quest;
		p.part = n.part;

		if (i + 1 == notes.size() ||
			notes[i].quest != notes[i + 1].quest ||
			notes[i].part != notes[i + 1].part) {

			vector<Participant> ranking;
			for (const auto& [key, value] : participants) {
				ranking.push_back(value);
			}
			sort(ranking.begin(), ranking.end());

			int part = notes[i].part;
			int quest = notes[i].quest;

			int points = 50 * part;
			int numSame = 0;
			int prevTime = -1;
			for (Participant p : ranking) {
				if (p.part != part || p.quest != quest) continue;
				
				if (i > 0 && p.time == prevTime) {
					numSame++;
				}
				else {
					points -= numSame + 1;
					if (points < 0) break;
					numSame = 0;
				}

				participants[p.id].points += points + 1;
				prevTime = p.time;
			}
		}

		if (i + 1 < notes.size() &&
			notes[i].quest != notes[i + 1].quest) {

			for (auto& [key, value] : participants) {
				value.time = 0;
			}
		}
	}

	vector<int> ranking;
	for (const auto& [key, value] : participants) {
		ranking.push_back(value.points);
		if (value.points == 44) {
			cout << key << endl;;
		}
	}
	sort(ranking.begin(), ranking.end(), greater<int>());

	int output = 0;
	int numSame = 0;
	for (int i = 0; i < ranking.size(); i++) {
		output += (i + 1) * ranking[i];
		if (i > 0 && ranking[i] == ranking[i - 1]) {
			numSame++;
			output -= ranking[i] * numSame;
		}
		else {
			numSame = 0;
		}
	}
	cout << output;
}