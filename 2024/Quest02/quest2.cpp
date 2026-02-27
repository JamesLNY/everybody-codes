#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

static void part1() {
    ifstream input("input2A.txt");
    string inputline, temp, inscription;
    stringstream inputlinestream;
    vector<string> runicWords;
    int output = 0;
    if (input.is_open()) {
        getline(input, inputline);
        inputlinestream.str(inputline.substr(6));
        while (getline(inputlinestream, temp, ',')) runicWords.push_back(temp);
        for (int i = 0; i < 2; i++) getline(input, inputline);
        inscription = inputline;
    }
    input.close();
    for (int i = 0; i < inscription.size(); i++) {
        for (string s : runicWords) {
            if (inscription.substr(i, s.length()) == s) output++;
        }
    }
    cout << output;
}

static void part2() {
    ifstream input("input2B.txt");
    string inputline, temp;
    stringstream inputlinestream;
    vector<string> runicWords;
    vector<string> inscriptions;
    int output = 0;
    if (input.is_open()) {
        getline(input, inputline);
        inputlinestream.str(inputline.substr(6));
        while (getline(inputlinestream, temp, ',')) runicWords.push_back(temp);
        getline(input, temp);
        while (getline(input, temp)) inscriptions.push_back(temp);
    }
    input.close();
    map<char, vector<string>> m;
    for (string s : runicWords) {
        for (int i = 0; i < 2; i++) {
            if (m.count(s[0])) {
                m[s[0]].push_back(s);
            }
            else {
                m[s[0]] = { s };
            }
            reverse(s.begin(), s.end());
        }
    }
    for (string s : inscriptions) {
        vector<int> count(s.length());
        list<pair<string, int>> possibilities;
        for (int n = 0; n < s.length(); n++) {
            char c = s[n];
            auto it = possibilities.begin();
            while (it != possibilities.end()) {
                pair<string, int>& p = *it;
                if (p.first[p.second] != c) {
                    while (p.second > 0) {
                        count[n - p.second]--;
                        p.second--;
                    }
                    it = possibilities.erase(it);
                }
                else {
                    count[n]++;
                    if (p.second == p.first.length() - 1) {
                        it = possibilities.erase(it);
                    }
                    else {
                        p.second++;
                        it++;
                    }
                }
            }
            for (string s : m[c]) {
                count[n]++;
                if (s.length() > 1) possibilities.push_back({ s, 1 });
            }
        }
        while (possibilities.size() != 0) {
            pair<string, int> p = possibilities.back();
            possibilities.pop_back();
            while (p.second > 0) {
                count[count.size() - p.second]--;
                p.second--;
            }
        }
        for (int i : count) {
            if (i > 0) output++;
        }
    }
    cout << output;
}

static vector<int> checkLine(string s, map<char, vector<string>> m, bool loop) {
    vector<int> count(s.length());
    list<pair<string, int>> possibilities;
    for (int n = 0; n < s.length(); n++) {
        char c = s[n];
        auto it = possibilities.begin();
        while (it != possibilities.end()) {
            pair<string, int>& p = *it;
            if (p.first[p.second] != c) {
                while (p.second > 0) {
                    count[n - p.second]--;
                    p.second--;
                }
                it = possibilities.erase(it);
            }
            else {
                count[n]++;
                if (p.second == p.first.length() - 1) {
                    it = possibilities.erase(it);
                }
                else {
                    p.second++;
                    it++;
                }
            }
        }
        for (string s : m[c]) {
            count[n]++;
            if (s.length() > 1) possibilities.push_back({ s, 1 });
        }
    }
    while (possibilities.size() != 0) {
        pair<string, int> p = possibilities.back();
        possibilities.pop_back();
        if (loop) {
            int i = p.second;
            while (p.second < p.first.length()) {
                if (s[p.second - i] != p.first[p.second]) break;
                p.second++;
            }
            if (p.second == p.first.length()) {
                for (int j = 0; j < p.second - i; j++) count[j]++;
            }
            else {
                while (i > 0) {
                    count[count.size() - i]--;
                    i--;
                }
            }
        }
        else {
            while (p.second > 0) {
                count[count.size() - p.second]--;
                p.second--;
            }
        }
    }
    return count;
}

static void part3() {
    ifstream input("input2C.txt");
    string inputline, temp;
    stringstream inputlinestream;
    vector<string> runicWords;
    vector<string> rows, cols;
    int output = 0;
    if (input.is_open()) {
        getline(input, inputline);
        inputlinestream.str(inputline.substr(6));
        while (getline(inputlinestream, temp, ',')) runicWords.push_back(temp);
        getline(input, temp);
        while (getline(input, temp)) rows.push_back(temp);
    }
    for (int i = 0; i < rows[0].length(); i++) {
        string temp = "";
        for (int j = 0; j < rows.size(); j++) {
            temp += rows[j][i];
        }
        cols.push_back(temp);
    }
    input.close();
    vector<vector<bool>> hasScale(rows.size(), vector<bool>(rows[0].size()));
    map<char, vector<string>> m;
    for (string s : runicWords) {
        for (int i = 0; i < 2; i++) {
            if (m.count(s[0])) {
                m[s[0]].push_back(s);
            }
            else {
                m[s[0]] = { s };
            }
            reverse(s.begin(), s.end());
        }
    }
    for (int i = 0; i < rows.size(); i++) {
        vector<int> output = checkLine(rows[i], m, true);
        for (int j = 0; j < output.size(); j++) {
            if (output[j] > 0) {
                hasScale[i][j] = true;
            }
        }
    }
    for (int i = 0; i < cols.size(); i++) {
        vector<int> output = checkLine(cols[i], m, false);
        for (int j = 0; j < output.size(); j++) {
            if (output[j] > 0) {
                hasScale[j][i] = true;
            }
        }
    }
    for (vector<bool> v : hasScale) {
        for (bool b : v) {
            if (b) output++;
        }
    }
    cout << output;
}