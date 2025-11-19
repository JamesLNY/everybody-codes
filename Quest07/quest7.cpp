#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

namespace quest7 {
    map<char, vector<char>> possibilities;
    vector<string> names;

    static void parseInput(string fileName) {
        ifstream input(fileName);
        string temp;
        stringstream notes;
        if (input.is_open()) {
            getline(input, temp);
            notes.str(temp);
            while (getline(notes, temp, ',')) {
                names.push_back(temp);
            }
            getline(input, temp);
            while (getline(input, temp)) {
                vector<char> values;
                int index = find(temp.begin(), temp.end(), '>') - temp.begin();
                char key = temp[0];
                notes.clear();
                notes.str(temp.substr(index + 2));
                while (getline(notes, temp, ',')) {
                    values.push_back(temp[0]);
                }
                possibilities[key] = values;
            }
        }
        input.close();
    }

    static void part1() {
        parseInput("input7A.txt");
        for (string s : names) {
            for (int i = 0; i < s.size() - 1; i++) {
                if (count(possibilities[s[i]].begin(), possibilities[s[i]].end(), s[i + 1]) == 0) {
                    break;
                }
                if (i == s.size() - 2) cout << s;
            }
        }
    }

    static void part2() {
        parseInput("input7B.txt");
        int output = 0;
        for (int n = 0; n < names.size(); n++) {
            string s = names[n];
            for (int i = 0; i < s.size() - 1; i++) {
                if (count(possibilities[s[i]].begin(), possibilities[s[i]].end(), s[i + 1]) == 0) {
                    break;
                }
                if (i == s.size() - 2) output += n + 1;
            }
        }
        cout << output;
    }

    static bool checkPrefix(string s, map<char, vector<char>> possibilities) {
        for (int i = 0; i < s.size() - 1; i++) {
            if (count(possibilities[s[i]].begin(), possibilities[s[i]].end(), s[i + 1]) == 0) {
                return false;
            }
        }
        return true;
    }

    map<char, map<int, int>> memoization;

    static int possibleCharacters(map<char, vector<char>> possibilities, string s, int length) {
        char c = s[s.size() - 1];
        if (memoization[c].count(length)) return memoization[c][length];
        int output = 0;
        if (length >= 7) output++;
        if (length == 11) return output;
        for (char n : possibilities[c]) {
            output += possibleCharacters(possibilities, s + n, length + 1);
        }
        memoization[c][length] = output;
        return output;
    }

    static void part3() {
        parseInput("input7C.txt");
        int output = 0;
        for (int n = 0; n < names.size(); n++) {
            string s = names[n];
            bool exit = false;
            for (int i = 0; i < n; i++) {
                if (s.find(names[i]) != string::npos) exit = true;
            }
            if (!checkPrefix(s, possibilities) || exit) continue;
            output += possibleCharacters(possibilities, s, s.size());
        }
        cout << output;
    }
}