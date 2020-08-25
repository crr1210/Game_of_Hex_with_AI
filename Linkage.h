#ifndef LINKAGE_H
#define LINKAGE_H

#include <vector>
#include <iostream>
#include "Position.h"
using namespace std;

class Linkage { //represents one player's linking status on board
public:
    Linkage() {};// player should only be 1 or 2
    Linkage& operator=(const Linkage& other);
    void initialize(int size, int player);
    Pos& findRoot(Pos &a) const;
    bool win(int player);
    void unite(Pos &posA, Pos &posB);
    void addMove(Pos move);
    void print (int num) const;
    int longestPath(int curPlayer) const;
    int searchVector(vector<Pos> fathers, Pos pos) const;
    void setUnionBoard();

private:
    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 1}, {-1, 0}, {0, -1}, {1, -1}};  // six directions you should check
    vector<vector<int>> unionBoard; // represent the union of pieces: 1-->1st group, 2-->2nd group, ... others are all 0
    vector<Pos> fathers;
    vector<vector<Pos>> root; //represents the root of a point
    int groupNum = 0;
    int player = 0; // Black = 1 or White = 2
    int size; // size of the board
};

#endif