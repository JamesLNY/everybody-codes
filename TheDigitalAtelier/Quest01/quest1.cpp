#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <limits>

using namespace std;

static void part1() {
    ifstream input("input1A.txt");
    string temp = "";
    int sum = 0;
    if (input.is_open()) {
        while (input >> temp) {
            int index = 0;
            unordered_set<int> visited = { 0 };
            stringstream ss(temp);
            while (getline(ss, temp, ',')) {
                int length = stoi(temp);
                if (length < index && !visited.count(index - length)) {
                    index -= length;
                    visited.insert(index);
                }
                else {
                    index += length;
                    visited.insert(index);
                }
            }
            sum += index;
        }
    }
    input.close();
    cout << sum;
}

class DisjointSetUnion {
public:
    unordered_map<int, int> parent;
    unordered_map<int, int> size;
    // maximum index in a set (stored with the representative)
    unordered_map<int, int> maxIndex;

    void make_set(int v) {
        parent[v] = v;
        maxIndex[v] = v;
        size[v] = 1;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    int max_set(int v) {
        int representative = find_set(v);
        return maxIndex[representative];
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a; // a becomes the representative
            size[a] += size[b];
            maxIndex[a] = max(maxIndex[a], maxIndex[b]);
        }
    }
};

static void part2() {
    ifstream input("input1B.txt");
    string temp = "";
    int sum = 0;
    if (input.is_open()) {
        while (input >> temp) {
            int index = 0;
            DisjointSetUnion dsu;
            
            unordered_set<int> visited = { 0 };
            unordered_set<int> jumped_over = { 0 };

            stringstream ss(temp);
            while (getline(ss, temp, ',')) {
                int length = stoi(temp);
                int prev = index;
                if (length < index 
                    && !visited.count(index - length)
                    && !jumped_over.count(index - length)) { // backwards jump
                    index -= length;
                }
                else { // forward jump
                    index += length;
                }

                // collision
                if (visited.count(index)) {
                    index = dsu.max_set(index) + 1;
                }

                // update dsu
                dsu.make_set(index);
                if (visited.count(index + 1)) {
                    dsu.union_sets(index, index + 1);
                }
                if (visited.count(index - 1)) {
                    dsu.union_sets(index, index - 1);
                }

                // update visited
                visited.insert(index);
            }
            sum += index;
        }
    }
    input.close();
    cout << sum;

}

static void part3() {
    ifstream input("input1C.txt");
    string temp = "";
    int sum = 0;
    if (input.is_open()) {
        while (input >> temp) {
            int index = 0;
            bool step = false;
            vector<map<int, int>> jumps(2);
            vector<unordered_set<int>> visited(2);

            stringstream ss(temp);
            while (getline(ss, temp, ',')) {

                if (visited[step].count(index)) continue;

                int length = stoi(temp);

                bool canJumpBack = true;
                int jumpMax = numeric_limits<int>::max(); // further than furthest visited node
                int jumpMin = 0;
                int forwardJump = index + length;

                for (const auto& [start, end] : jumps[step]) {
                    // phase 1 - check for backwards jump
                    if (start <= index - length && end >= index - length && end < index) { // BUG --> END MUST BE LESS THAN INDEX
                        canJumpBack = false;
                    }
                    // phase 2 - check for enclosing arcs
                    if (start < index && end > index) {
                        jumpMax = min(jumpMax, end);
                        jumpMin = max(jumpMin, start);
                    }
                    // phase 3 - check for forwards jump
                    if (start > index && start <= forwardJump && end >= forwardJump) {
                        forwardJump = end + 1;
                    }
                }

                // determine jump
                int prev = index;
                if (canJumpBack && index - length > jumpMin) { // backward jump
                    index -= length;
                    jumps[step][index] = prev;
                    visited[step].insert(index);
                    step = !step;
                }
                else if (forwardJump < jumpMax) { // forward jump
                    index = forwardJump;
                    jumps[step][prev] = index;
                    visited[step].insert(index);
                    step = !step;
                }
            }
            sum += index;
        }
    }
    input.close();
    cout << sum;
}

int main() {
    part3();
}