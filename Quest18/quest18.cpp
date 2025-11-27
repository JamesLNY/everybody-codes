#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct branch {
    int from;
    int thickness;
    branch(int fromi, int thicknessi) {
        from = fromi;
        thickness = thicknessi;
    }
};

struct plant {
    int thickness;
    int incomingEnergy;
    vector<branch> incomingPlants;
    plant(int thicknessi) {
        thickness = thicknessi;
        incomingEnergy = 0;
    }
};

vector<plant> plants;
vector<vector<int>> schemas;

static void part1() {
    ifstream input("input18A");
    if (input.is_open()) {
        string temp;
        while (!input.eof()) {
            input >> temp;
            if (temp == "Plant") {
                input >> temp >> temp >> temp >> temp;
                int thickness = stoi(temp.substr(0, temp.size() - 1));
                plant newPlant(thickness);
                plants.push_back(newPlant);
            }
            else if (temp == "-") {
                plant& newPlant = plants.back();
                int thickness;
                input >> temp;
                if (temp == "free") {
                    input >> temp >> temp >> temp >> thickness;
                    newPlant.incomingEnergy += thickness;
                }
                else {
                    int connectedPlant;
                    input >> temp >> temp >> connectedPlant;
                    input >> temp >> temp >> thickness;
                    connectedPlant--;
                    if (plants[connectedPlant].incomingEnergy >= plants[connectedPlant].thickness) {
                        newPlant.incomingEnergy += plants[connectedPlant].incomingEnergy * thickness;
                    }
                }
            }
        }
    }
    input.close();
    cout << plants.back().incomingEnergy;
}

static int numFree = 0;

static void parseInput(string fileName) {
    ifstream input(fileName);
    if (input.is_open()) {
        string temp;
        while (!input.eof()) {
            input >> temp;
            if (temp == "Plant") {
                input >> temp >> temp >> temp >> temp;
                int thickness = stoi(temp.substr(0, temp.size() - 1));
                plant newPlant(thickness);
                plants.push_back(newPlant);
            }
            else if (temp == "-") {
                plant& newPlant = plants.back();
                int thickness;
                input >> temp;
                if (temp == "free") {
                    numFree++;
                    input >> temp >> temp >> temp >> temp;
                    newPlant.incomingEnergy = 1;
                }
                else {
                    int connectedPlant;
                    input >> temp >> temp >> connectedPlant;
                    input >> temp >> temp >> thickness;
                    connectedPlant--;
                    newPlant.incomingPlants.push_back(branch(connectedPlant, thickness));
                }
            }
            else if (temp == "1" || temp == "0") {
                vector<int> schema = { stoi(temp) };
                for (int i = 1; i < numFree; i++) {
                    input >> temp;
                    schema.push_back(stoi(temp));
                }
                schemas.push_back(schema);
            }
        }
    }
    input.close();
}

static int useSchema(vector<int> schema) {
    vector<plant> newPlants = plants;
    for (int i = 0; i < numFree; i++) {
        newPlants[i].incomingEnergy = schema[i];
    }
    for (int i = numFree; i < newPlants.size(); i++) {
        plant& newPlant = newPlants[i];
        for (branch b : newPlant.incomingPlants) {
            if (newPlants[b.from].incomingEnergy >= newPlants[b.from].thickness) {
                newPlant.incomingEnergy += newPlants[b.from].incomingEnergy * b.thickness;
            }
        }
    }
    if (newPlants[newPlants.size() - 1].incomingEnergy < newPlants[newPlants.size() - 1].thickness) return 0;
    return newPlants[newPlants.size() - 1].incomingEnergy;
}

static void part2() {
    parseInput("input18B.txt");
    long long output = 0;
    for (vector<int> schema : schemas) {
        output += useSchema(schema);
    }
    cout << output;
}

static void part3() {
    // Solved using assumptions made by looking at the input
    parseInput("input18C.txt");
    long long output = 0;
    vector<long long> outputs;
    vector<int> possible;
    vector<int> optimalSchema(numFree, 1);
    for (int i = 82; i < 91; i++) {
        for (branch b : plants[i - 1].incomingPlants) {
            if (b.thickness < 0) {
                optimalSchema[b.from] = 0;
            }
        }
    }
    long long maxEnergy = useSchema(optimalSchema);
    for (vector<int> schema : schemas) {
        int temp = useSchema(schema);
        if (temp == 0) continue;
        output += maxEnergy - temp;
    }
    cout << output;
}