#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <set>
#include <queue>

using namespace std;

static vector<string> people;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (input >> temp) {
            stringstream ss;
            ss.str(temp);
            getline(ss, temp, ':');
            getline(ss, temp, ':');
            people.push_back(temp);
        }
    }
    input.close();
}

static void part1() {
    parseInput("input9A.txt");
    vector<bool> A(people[0].size());
    vector<bool> B(people[1].size());
    vector<bool> C(people[2].size());
    for (int i = 0; i < people[0].size(); i++) {
        if (people[0][i] == people[1][i]) {
            A[i] = true;
            B[i] = true;
        }
        if (people[1][i] == people[2][i]) {
            B[i] = true;
            C[i] = true;
        }
        if (people[0][i] == people[2][i]) {
            A[i] = true;
            C[i] = true;
        }
    }
    int output = 0;
    if (count(A.begin(), A.end(), false) == 0) {
        output += accumulate(B.begin(), B.end(), 0);
        output *= accumulate(C.begin(), C.end(), 0);
    }
    if (count(B.begin(), B.end(), false) == 0) {
        output += accumulate(A.begin(), A.end(), 0);
        output *= accumulate(C.begin(), C.end(), 0);
    }
    if (count(C.begin(), C.end(), false) == 0) {
        output += accumulate(B.begin(), B.end(), 0);
        output *= accumulate(A.begin(), A.end(), 0);
    }
    cout << output;
}

static long long similarity(string a, string b) {
    long long output = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) output++;
    }
    return output;
}

static void part2() {
    parseInput("input9B.txt");
    // child, others, key
    vector<vector<vector<unsigned int>>> bitmap;
    for (string person : people) {
        vector<vector<unsigned int>> connection;
        for (string otherPerson : people) {
            vector<unsigned int> key;
            if (otherPerson == person) {
                connection.push_back({ 0, 0, 0, 0 });
                continue;
            }
            for (int n = 0; n < 4; n++) {
                unsigned int temp = 0;
                for (int i = 0; i < 32; i++) {
                    temp = temp << 1;
                    if (person[n * 32 + i] == otherPerson[n * 32 + i]) {
                        temp += 1;
                    }
                }
                key.push_back(temp);
            }
            connection.push_back(key);
        }
        bitmap.push_back(connection);
    }
    map<string, pair<string, string>> parents;
    for (int i = 0; i < bitmap.size(); i++) {
        for (int n = 0; n < bitmap[i].size(); n++) {
            if (n == i) continue;
            for (int j = n + 1; j < bitmap[i].size(); j++) {
                if (j == i) continue;
                for (int k = 0; k < 4; k++) {
                    if ((bitmap[i][j][k] | bitmap[i][n][k]) != 4294967295) {
                        break;
                    }
                    if (k == 3) {
                        parents[people[i]] = { people[j], people[n] };
                    }
                }
            }
        }
    }
    long long output = 0;
    for (const auto& pair : parents) {
        output += similarity(pair.first, pair.second.first) * similarity(pair.first, pair.second.second);
    }
    cout << output;
}

static void part3() {
    parseInput("input9C.txt");
    // child, others, key
    vector<vector<vector<unsigned int>>> bitmap;
    for (string person : people) {
        vector<vector<unsigned int>> connection;
        for (string otherPerson : people) {
            vector<unsigned int> key;
            if (otherPerson == person) {
                connection.push_back({ 0, 0, 0, 0 });
                continue;
            }
            for (int n = 0; n < 4; n++) {
                unsigned int temp = 0;
                for (int i = 0; i < 32; i++) {
                    temp = temp << 1;
                    if (person[n * 32 + i] == otherPerson[n * 32 + i]) {
                        temp += 1;
                    }
                }
                key.push_back(temp);
            }
            connection.push_back(key);
        }
        bitmap.push_back(connection);
    }
    map<int, pair<int, int>> parents;
    for (int i = 0; i < bitmap.size(); i++) {
        for (int n = 0; n < bitmap[i].size(); n++) {
            if (n == i) continue;
            for (int j = n + 1; j < bitmap[i].size(); j++) {
                if (j == i) continue;
                for (int k = 0; k < 4; k++) {
                    if ((bitmap[i][j][k] | bitmap[i][n][k]) != 4294967295) {
                        break;
                    }
                    if (k == 3) {
                        parents[i] = { j, n };
                    }
                }
            }
        }
    }
    long long output = 0;
    vector<int> biggestFamily = {};
    vector<bool> visited(people.size());
    vector<set<int>> m(people.size(), set<int>());
    for (pair<int, pair<int, int>> couple : parents) {
        m[couple.first].insert(couple.second.first);
        m[couple.first].insert(couple.second.second);
        m[couple.second.first].insert(couple.first);
        m[couple.second.second].insert(couple.first);
    }
    for (int i = 0; i < people.size(); i++) {
        if (visited[i]) continue;
        queue<int> bfs;
        vector<int> family;
        bfs.push(i);
        while (!bfs.empty()) {
            int next = bfs.front();
            bfs.pop();
            if (visited[next]) continue;
            family.push_back(next);
            visited[next] = true;
            for (int j : m[next]) {
                bfs.push(j);
            }
        }
        if (family.size() > biggestFamily.size()) {
            biggestFamily = family;
        }
    }
    cout << accumulate(biggestFamily.begin(), biggestFamily.end(), 0) + biggestFamily.size();
}