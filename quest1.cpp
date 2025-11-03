#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void part1() {
    ifstream input("input1A.txt");
    string temp = "";
    vector<string> names;
    int index = 0;
    if (input.is_open()) {
        input >> temp;
        stringstream ss(temp);
        while (getline(ss, temp, ',')) {
            names.push_back(temp);
        }
        input >> temp;
        ss.str(temp);
        ss.clear();
        while (getline(ss, temp, ',')) {
            int amount = temp[1] - '0';
            if (temp[0] == 'L') {
                index -= amount;
            }
            else {
                index += amount;
            }
            index = max(0, index);
            index = min((int) names.size() - 1, index);
        }
    }
    cout << names[index];
}

void part2() {
    ifstream input("input1B.txt");
    string temp = "";
    vector<string> names;
    int index = 0;
    if (input.is_open()) {
        input >> temp;
        stringstream ss(temp);
        while (getline(ss, temp, ',')) {
            names.push_back(temp);
        }
        input >> temp;
        ss.str(temp);
        ss.clear();
        while (getline(ss, temp, ',')) {
            int amount = stoi(temp.substr(1));
            if (temp[0] == 'L') {
                index -= amount;
            }
            else {
                index += amount;
            }
            index %= names.size();
        }
    }
    cout << names[index];
}

void part3() {
    ifstream input("input1C.txt");
    string temp = "";
    vector<string> names;
    if (input.is_open()) {
        input >> temp;
        stringstream ss(temp);
        while (getline(ss, temp, ',')) {
            names.push_back(temp);
        }
        input >> temp;
        ss.str(temp);
        ss.clear();
        while (getline(ss, temp, ',')) {
            int amount = stoi(temp.substr(1));
            if (temp[0] == 'L') amount *= -1;
            amount %= (int) names.size();
            if (amount < 0) amount += names.size();
            swap(names[0], names[amount]);
        }
    }
    cout << names[0];
}