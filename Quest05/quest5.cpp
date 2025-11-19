#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace quest5 {
    struct row {
        int low = 0;
        int mid = 0;
        int high = 0;
    };

    static long long calculateFishbone(vector<int> v) {
        row newRow;
        newRow.mid = v[0];
        vector<row> fishbone;
        v.erase(v.begin());
        fishbone.push_back(newRow);
        for (int i : v) {
            for (int n = 0; n < fishbone.size(); n++) {
                row& r = fishbone[n];
                if (i < r.mid && r.low == 0) {
                    r.low = i;
                    break;
                }
                else if (i > r.mid && r.high == 0) {
                    r.high = i;
                    break;
                }
                if (n == fishbone.size() - 1) {
                    newRow = row();
                    newRow.mid = i;
                    fishbone.push_back(newRow);
                    break;
                }
            }
        }
        string output = "";
        for (row r : fishbone) {
            output += to_string(r.mid);
        }
        return stoll(output);
    }

    static void part1() {
        ifstream input("input5A.txt");
        vector<int> v;
        int indentifier;
        string temp;
        stringstream ss;
        if (input.is_open()) {
            input >> temp;
            int index = temp.find(':');
            indentifier = stoi(temp.substr(0, index));
            ss.str(temp.substr(index + 1));
        }
        input.close();
        while (getline(ss, temp, ',')) {
            v.push_back(stoi(temp));
        }
        cout << calculateFishbone(v);
    }

    static void part2() {
        ifstream input("input5B.txt");
        vector<int> v;
        string temp;
        long long lower = -1, upper = -1;
        stringstream ss;
        if (input.is_open()) {
            while (input >> temp) {
                int index = temp.find(':');
                ss.clear();
                ss.str(temp.substr(index + 1));
                v = {};
                while (getline(ss, temp, ',')) {
                    v.push_back(stoi(temp));
                }
                long long quality = calculateFishbone(v);
                if (lower == -1) {
                    lower = quality;
                    upper = quality;
                }
                else {
                    lower = min(lower, quality);
                    upper = max(upper, quality);
                }
            }
        }
        input.close();
        cout << upper - lower;
    }

    static pair<long long, vector<long long>> generateFishbone(vector<int> v) {
        row newRow;
        newRow.mid = v[0];
        vector<row> fishbone;
        v.erase(v.begin());
        fishbone.push_back(newRow);
        for (int i : v) {
            for (int n = 0; n < fishbone.size(); n++) {
                row& r = fishbone[n];
                if (i < r.mid && r.low == 0) {
                    r.low = i;
                    break;
                }
                else if (i > r.mid && r.high == 0) {
                    r.high = i;
                    break;
                }
                if (n == fishbone.size() - 1) {
                    newRow = row();
                    newRow.mid = i;
                    fishbone.push_back(newRow);
                    break;
                }
            }
        }
        vector<long long> convertedFishbone;
        string quality = "";
        for (row r : fishbone) {
            quality += to_string(r.mid);
            convertedFishbone.push_back(stoll(to_string(r.low) + to_string(r.mid) + (to_string(r.high) == "0" ? "" : to_string(r.high))));
        }
        return { stoll(quality), convertedFishbone };
    }

    struct sword {
        int identifier;
        long long quality;
        vector<long long> levels;
        sword(int identifier, long long quality, vector<long long> levels) {
            this->identifier = identifier;
            this->quality = quality;
            this->levels = levels;
        }
    };

    static void part3() {
        ifstream input("input5C.txt");
        vector<int> v;
        string temp;
        stringstream ss;
        vector<sword> swords;
        if (input.is_open()) {
            while (input >> temp) {
                int index = temp.find(':');
                int identifier = stoi(temp.substr(0, index));
                ss.clear();
                ss.str(temp.substr(index + 1));
                v = {};
                while (getline(ss, temp, ',')) {
                    v.push_back(stoi(temp));
                }
                pair<long long, vector<long long>> fishbone = generateFishbone(v);
                swords.push_back(sword(identifier, fishbone.first, fishbone.second));
            }
        }
        input.close();
        sort(swords.begin(), swords.end(), [](const sword& a, const sword& b) {
            if (a.quality != b.quality) {
                return a.quality > b.quality;
            }
            else {
                for (int i = 0; i < a.levels.size(); i++) {
                    if (a.levels[i] != b.levels[i]) {
                        return a.levels[i] > b.levels[i];
                    }
                }
                return a.identifier > b.identifier;
            }
            });
        long long output = 0;
        for (int i = 1; i <= swords.size(); i++) {
            output += swords[i - 1].identifier * i;
        }
        cout << output;
    }
}