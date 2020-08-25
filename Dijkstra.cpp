#include <iostream>
#include <vector>
#include <algorithm>
#include "Position.h"

int main() {
    vector<Pos> fathers;
    Pos AA(1, 1), BB(2, 2), CC(3, 3);
    fathers.push_back(AA);
    fathers.push_back(BB);
    fathers.push_back(CC);
    vector<int>::iterator it;
    it = find(fathers.begin(), fathers.end(), BB);
    if(it == fathers.end()) {
        cout << "did not find" << endl;
    } else {
        cout << "find!" << endl;
    }
}
